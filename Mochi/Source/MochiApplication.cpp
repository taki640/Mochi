#include "MochiApplication.hpp"

#include "ModernTheme.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <stb/stb_image.h>

#include "../../ThirdParty/glfw/glfw/include/GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "../../ThirdParty/glfw/glfw/include/GLFW/glfw3native.h"

namespace Mochi
{
	bool MochiApplication::Init(const MochiApplicationInitInfo& initInfo)
	{
		OnBeforeApplicationInit();

		m_Running = true;
		if (!InitGlfw(initInfo))
			return false;
		InitDearImGui(initInfo);

		OnApplicationInit();
		return true;
	}

	void MochiApplication::Run()
	{
		while (m_Running)
		{
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT);

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			OnApplicationRender();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backupContext = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backupContext);
			}

			glfwSwapBuffers(m_Window);
		}
	}

	void MochiApplication::Shutdown()
	{
		OnApplicationShutdown();
		ShutdownDearImGui();
		ShutdownGlfw();
	}

	void MochiApplication::Close()
	{
		if (CanCloseNow())
			m_Running = false;
	}

	bool MochiApplication::CanCloseNow()
	{
		return true;
	}

	bool MochiApplication::InitGlfw(const MochiApplicationInitInfo& initInfo)
	{
		if (!glfwInit())
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		if (initInfo.Maximized)
			glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

		Vector2<int> initialPosition = initInfo.WindowPosition;
		if (initInfo.WindowPositionCenter)
		{
			Vector2<int> screenSize;
			glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), nullptr, nullptr, &screenSize.X, &screenSize.Y);
			for (int i = 0; i < 2; i++)
				initialPosition[i] = (int)((screenSize[i] - initInfo.WindowSize[i]) * 0.5f);
		}

		if (initialPosition.X > -1 && initialPosition.Y > -1)
		{
			glfwWindowHint(GLFW_POSITION_X, initialPosition.X);
			glfwWindowHint(GLFW_POSITION_Y, initialPosition.Y);
		}

		m_Window = glfwCreateWindow(initInfo.WindowSize.X, initInfo.WindowSize.Y, initInfo.ApplicationName, nullptr, nullptr);
		if (m_Window == nullptr)
			return false;

		int width;
		int height;
		uint8_t* iconData = nullptr;
		if (initInfo.Icon.Data != nullptr)
		{
			int channels;
			iconData = stbi_load_from_memory(initInfo.Icon.Data, initInfo.Icon.DataBufferSize, &width, &height, &channels, 0);
		}
		else if (initInfo.Icon.Path.data() != nullptr)
		{
			int channels;
			iconData = stbi_load(initInfo.Icon.Path.data(), &width, &height, &channels, 0);
		}

		if (iconData != nullptr)
		{
			GLFWimage image{ width, height, iconData };
			glfwSetWindowIcon(m_Window, 1, &image);	// copies the data pointer
			stbi_image_free(iconData);
		}

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);

		glViewport(0, 0, initInfo.WindowSize.X, initInfo.WindowSize.Y);
		m_WindowSize = initInfo.WindowSize;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glfwSetWindowUserPointer(m_Window, this);

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
			MochiApplication* app = (MochiApplication*)glfwGetWindowUserPointer(window);
			app->m_WindowSize.X = width;
			app->m_WindowSize.Y = height;
		});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int x, int y)
		{
			MochiApplication* app = (MochiApplication*)glfwGetWindowUserPointer(window);
			app->m_WindowPosition.X = x;
			app->m_WindowPosition.Y = y;
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			MochiApplication* app = (MochiApplication*)glfwGetWindowUserPointer(window);
			app->Close();
		});

		glfwGetWindowPos(m_Window, &m_WindowPosition.X, &m_WindowPosition.Y);
		return true;
	}

	void MochiApplication::ShutdownGlfw()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void MochiApplication::InitDearImGui(const MochiApplicationInitInfo& initInfo)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= initInfo.EnableDocking   ? ImGuiConfigFlags_DockingEnable   : ImGuiConfigFlags_None;
		io.ConfigFlags |= initInfo.EnableViewports ? ImGuiConfigFlags_ViewportsEnable : ImGuiConfigFlags_None;

		if (!initInfo.ImGuiConfigurationFilename.empty())
		{
			// ImGui does not copy the filename so we need to copy and maintain the buffer ourselves.
			const size_t bufferSize = initInfo.ImGuiConfigurationFilename.size() + 1;
			m_ImGuiConfigurationFile = new char[bufferSize];
			strcpy_s(m_ImGuiConfigurationFile, bufferSize, initInfo.ImGuiConfigurationFilename.c_str());
		}

		// We set also want to set to nullptr to not save the file
		io.IniFilename = m_ImGuiConfigurationFile;

		if (initInfo.Font != nullptr)
			initInfo.Font->Load();

		ImGui::StyleColorsDark();
		Internal::SetModernColors();

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 460 core");
	}

	void MochiApplication::ShutdownDearImGui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		delete[] m_ImGuiConfigurationFile;
		m_ImGuiConfigurationFile = nullptr;
	}

	void* MochiApplication::GetNativeWindow() const
	{
		return glfwGetWin32Window(m_Window);
	}
}

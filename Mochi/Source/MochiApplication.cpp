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
#ifdef MOCHI_WINDOWS
	extern void RegisterDialogsHWND(HWND hwnd);
#endif

	int MochiApplication::Run(const MochiApplicationInitInfo& initInfo)
	{
		m_Running = true;

		if (!OnBeforeApplicationInit())
			return 1;
		if (!InitGlfw(initInfo))
			return 1;
		InitDearImGui(initInfo);
		if (!OnApplicationInit())
			return 1;

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

		// If we're not exiting with a success error code, assume the client application doesn't want to properly shutdown.
		// Imagine the situation: An application always saves a configuration file on shutdown, the loading of this same file
		// causes an error and the application wants to exit. If shutdown is called and the file was half-loaded it will completely
		// overwrite the broken file with a different broken file. Now the programmer and maybe the user have no idea of what's
		// happening.
		// But still, I not a huge fan of this. Maybe, it could be nice to have a force shutdown callback option?
		if (m_ExitCode == 0)
			OnApplicationShutdown();

		ShutdownDearImGui();
		ShutdownGlfw();
		return m_ExitCode;
	}

	void MochiApplication::Close(int exitCode)
	{
		if (exitCode == 0)
		{
			if (CanCloseNow())
			{
				m_Running = false;
				m_ExitCode = 0;
			}
		}
		else
		{
			m_Running = false;
			m_ExitCode = exitCode;
		}
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

	#ifdef MOCHI_WINDOWS
		RegisterDialogsHWND(glfwGetWin32Window(m_Window));
	#endif
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
		io.ConfigFlags |= initInfo.EnableKeyboardNavigation ? ImGuiConfigFlags_NavEnableKeyboard : ImGuiConfigFlags_None;
		io.ConfigFlags |= initInfo.EnableGamepadNavigation  ? ImGuiConfigFlags_NavEnableGamepad  : ImGuiConfigFlags_None;
		io.ConfigFlags |= initInfo.EnableDocking            ? ImGuiConfigFlags_DockingEnable     : ImGuiConfigFlags_None;
		io.ConfigFlags |= initInfo.EnableViewports          ? ImGuiConfigFlags_ViewportsEnable   : ImGuiConfigFlags_None;

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
		else
			io.Fonts->AddFontDefaultVector();

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

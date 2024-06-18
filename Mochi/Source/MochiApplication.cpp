#include "MochiApplication.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Mochi
{
	bool MochiApplication::Init(const MochiApplicationInfo& info)
	{
		m_ApplicationInfo = info;
		m_Running = true;
		if (!InitGlfw())
			return false;
		InitDearImGui();
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

			OnImGuiRender();

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

	bool MochiApplication::InitGlfw()
	{
		if (!glfwInit())
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(m_ApplicationInfo.WindowSize.X, m_ApplicationInfo.WindowSize.Y, m_ApplicationInfo.ApplicationName, nullptr, nullptr);
		if (m_Window == nullptr)
			return false;

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);

		glViewport(0, 0, m_ApplicationInfo.WindowSize.X, m_ApplicationInfo.WindowSize.Y);
		m_WindowSize = m_ApplicationInfo.WindowSize;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glfwSetWindowUserPointer(m_Window, this);

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
			MochiApplication* app = (MochiApplication*)glfwGetWindowUserPointer(window);
			app->m_WindowSize.X = width;
			app->m_WindowSize.Y = height;
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			MochiApplication* app = (MochiApplication*)glfwGetWindowUserPointer(window);
			app->Close();
		});

		return true;
	}

	void MochiApplication::ShutdownGlfw()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void MochiApplication::InitDearImGui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= m_ApplicationInfo.EnableDocking   ? ImGuiConfigFlags_DockingEnable   : ImGuiConfigFlags_None;
		io.ConfigFlags |= m_ApplicationInfo.EnableViewports ? ImGuiConfigFlags_ViewportsEnable : ImGuiConfigFlags_None;

		if (m_ApplicationInfo.FontFilename != nullptr)
			io.Fonts->AddFontFromFileTTF(m_ApplicationInfo.FontFilename, m_ApplicationInfo.FontSize);

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 460 core");
	}

	void MochiApplication::ShutdownDearImGui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}

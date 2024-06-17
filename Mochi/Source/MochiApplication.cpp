#include "MochiApplication.hpp"

namespace Mochi
{
	bool MochiApplication::Init(const MochiApplicationInfo& info)
	{
		m_ApplicationInfo = info;
		if (!InitGlfw())
			return false;
		return true;
	}

	void MochiApplication::Run()
	{
		while (!glfwWindowShouldClose(m_Window))
		{
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT);
			OnImGuiRender();
			glfwSwapBuffers(m_Window);
		}
	}

	void MochiApplication::Shutdown()
	{
		ShutdownGlfw();
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
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow*, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

		return true;
	}

	void MochiApplication::ShutdownGlfw()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
}

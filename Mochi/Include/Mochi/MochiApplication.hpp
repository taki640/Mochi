#pragma once

#include "Utils.hpp"
#include "../../ThirdParty/glfw/include/GLFW/glfw3.h"

namespace Mochi
{
	struct MochiApplicationInfo
	{
		const char* ApplicationName = "Mochi Application";
		Vector2<int> WindowSize = { 1280, 720 };
	};

	class MochiApplication
	{
	public:
		bool Init(const MochiApplicationInfo& info);
		void Run();
		void Shutdown();

		void Close();

		const MochiApplicationInfo& GetApplicationInfo() const { return m_ApplicationInfo; }
		GLFWwindow* GetWindow() { return m_Window; }
		const GLFWwindow* GetWindow() const { return m_Window; }
	protected:
		virtual void OnImGuiRender() = 0;

		// Override this function to prevent the application from closing.
		// This would be better to be an event, but we don't have an event system yet :P
		virtual bool CanCloseNow();
	private:
		MochiApplicationInfo m_ApplicationInfo;
		GLFWwindow* m_Window;
		bool m_Running = false;

		bool InitGlfw();
		void ShutdownGlfw();
	};
}

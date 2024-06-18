#pragma once

#include "Utils.hpp"
#include "../../ThirdParty/glfw/include/GLFW/glfw3.h"

namespace Mochi
{
	struct MochiApplicationInfo
	{
		const char* ApplicationName = "Mochi Application";
		Vector2<int> WindowSize = { 1280, 720 };
		bool EnableDocking = true;
		bool EnableViewports = true;
		const char* ImGuiConfigurationFilename = "imgui.ini";
		const char* FontFilename = nullptr;
		float FontSize = 12.0f;
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
		const Vector2<int>& GetWindowSize() const { return m_WindowSize; }
	protected:
		virtual void OnBeforeApplicationInit() {}
		virtual void OnApplicationInit() {}
		virtual void OnApplicationRender() {}
		virtual void OnApplicationShutdown() {}

		// Override this function to prevent the application from closing.
		// This would be better to be an event, but we don't have an event system yet :P
		virtual bool CanCloseNow();
	private:
		MochiApplicationInfo m_ApplicationInfo;
		GLFWwindow* m_Window = nullptr;
		Vector2<int> m_WindowSize;
		bool m_Running = false;

		bool InitGlfw();
		void ShutdownGlfw();

		void InitDearImGui();
		void ShutdownDearImGui();
	};
}

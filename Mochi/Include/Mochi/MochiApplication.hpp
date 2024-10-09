#pragma once

#include "ApplicationIcon.hpp"
#include "Font.hpp"
#include "Utils.hpp"

struct GLFWwindow;

namespace Mochi
{
	struct MochiApplicationInfo
	{
		const char* ApplicationName = "Mochi Application";		// The name of the application that appears on the window and taskbar.
		Vector2<int> WindowSize = { 1280, 720 };				// The initial size of the window. If Maximized is set to true, it's the size of the window in normal state.
		bool Maximized = false;									// Initialize the window in the maximized state.
		ApplicationIcon Icon;									// The icon that appears on the window and taskbar.
		bool EnableDocking = true;								// Enable ImGui docking feature.
		bool EnableViewports = true;							// Enable ImGui viewports feature.
		std::string ImGuiConfigurationFilename = "imgui.ini";	// Set to empty to not save a imgui configuration file.
		BaseFont* Font = nullptr;								// A MemoryFont or FileFont (see Font.hpp), if nullptr the default imgui font is loaded
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
		void* GetNativeWindow() const;
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
		char* m_ImGuiConfigurationFile = nullptr;

		bool InitGlfw();
		void ShutdownGlfw();

		void InitDearImGui();
		void ShutdownDearImGui();
	};
}

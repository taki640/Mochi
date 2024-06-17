#pragma once

#include <string>

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
	protected:
		virtual void OnImGuiRender() = 0;
	private:
		MochiApplicationInfo m_ApplicationInfo;
		GLFWwindow* m_Window;

		bool InitGlfw();
		void ShutdownGlfw();
	};
}

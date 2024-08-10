#include "Mochi/MochiApplication.hpp"

#include <imgui.h>

class Application : public Mochi::MochiApplication
{
protected:
	virtual void OnApplicationRender() override
	{
		ImGui::ShowDemoWindow();
	}
};

#ifndef MOCHI_FINAL
int main()
#else
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
#endif
{
	Mochi::MochiApplicationInfo info;
	info.FontFilename = "..\\ThirdParty\\imgui\\misc\\fonts\\Roboto-Medium.ttf";
	info.FontSize = 14.0f;
	Application app;
	app.Init(info);
	app.Run();
	app.Shutdown();

	return 0;
}

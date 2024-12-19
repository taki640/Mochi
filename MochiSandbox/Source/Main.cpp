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
	Mochi::FileFont font("..\\ThirdParty\\imgui\\misc\\fonts\\Roboto-Medium.ttf", 14.0f);
	Mochi::MochiApplicationInfo info;
	info.Font = &font;

	Application app;
	app.Init(info);
	app.Run();
	app.Shutdown();

	return 0;
}

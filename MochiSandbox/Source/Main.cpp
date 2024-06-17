#include "Mochi/MochiApplication.hpp"

#include <imgui.h>

class Application : public Mochi::MochiApplication
{
protected:
	virtual void OnImGuiRender() override
	{
		ImGui::ShowDemoWindow();
	}
};

int main()
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

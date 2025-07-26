#include "Mochi/MochiApplication.hpp"

#define MOCHI_EMBED_ROBOTO_MEDIUM
#include "Mochi/Fonts/Roboto.hpp"

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
	Mochi::MemoryFont font(Mochi::Embed::FONT_ROBOTO_MEDIUM, Mochi::Embed::FONT_ROBOTO_MEDIUM_SIZE, 14.0f, true, false);
	Mochi::MochiApplicationInitInfo info;
	info.Font = &font;
	info.WindowPositionCenter = true;

	Application app;
	return app.Run(info);
}

#include "Mochi/MochiApplication.hpp"

class Application : public Mochi::MochiApplication
{
protected:
	virtual void OnImGuiRender() override
	{

	}
};

int main()
{
	Mochi::MochiApplicationInfo info;
	Application app;
	app.Init(info);
	app.Run();
	app.Shutdown();

	return 0;
}

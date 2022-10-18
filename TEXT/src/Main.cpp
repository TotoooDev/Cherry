#include <App.h>

int main(int argc, char* argv[])
{
	WindowSpecification spec;
	spec.Width = 800;
	spec.Height = 600;
	spec.Title = "TEXT Editor";
	spec.VSync = true;

	App app(spec);
	app.Run();

	return 0;
}
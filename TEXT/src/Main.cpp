#include <App.h>

int main(int argc, char* argv[])
{
	WindowSpecification spec;
	spec.Width = 1024;
	spec.Height = 768;
	spec.Title = "Cherry Editor";
	spec.VSync = true;

	App app(spec);
	app.Run();

	return 0;
}
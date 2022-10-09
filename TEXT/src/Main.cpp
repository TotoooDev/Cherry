#include <App.h>

int main(int argc, char* argv[])
{
	WindowSpecification spec;
	spec.Width = 1280;
	spec.Height = 720;
	spec.Title = "TEXT Editor";

	App app(spec);
	app.Run();

	return 0;
}
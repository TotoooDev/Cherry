#include <App.h>
#include <ImGui/imgui.h>
#include <vector>

App::App(const WindowSpecification& spec)
	: m_Window(spec)
{

}

void App::Run()
{
	while (!m_Window.ShouldClose())
	{
		m_Window.PollEvents();

		m_Window.BeginImGui();

		// Epic ImGui stuff here
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::BeginMainMenuBar();
		ImGui::EndMainMenuBar();

		m_Editor.Draw(&m_ShowEditor);

		m_Window.EndImGui();

		m_Window.Swap();
	}
}
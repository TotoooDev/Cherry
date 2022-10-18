#include <App.h>
#include <Utils.h>
#include <Keycode.h>
#include <ImGui/imgui.h>
#include <vector>
#include <fstream>
#include <iostream>

App::App(const WindowSpecification& spec)
	: m_Window(spec), m_BrowserPanel(&m_Editors)
{
	
}

void App::Run()
{
	while (m_IsRunning)
	{
		m_IsRunning = !m_Window.ShouldClose();

		m_Window.PollEvents();
		HandleInputs();

		m_Window.BeginImGui();

		CreateDockspace();

		DrawMenuBar();

		for (auto&& [editor, isOpen] : m_Editors)
		{
			if (isOpen)
				editor.Draw(&isOpen);
			if (editor.IsFocused())
				m_FocusedEditor = &editor;
		}

		if (m_ShowBrowserPanel)
			m_BrowserPanel.Draw(&m_ShowBrowserPanel);

		if (m_ShowStartPanel)
		{
			m_StartPanel.Draw(&m_ShowStartPanel);
			if (m_StartPanel.New())
				New();
			if (m_StartPanel.Open())
				Open();
			if (m_StartPanel.OpenFolder())
				OpenFolder();
		}

		m_Window.EndImGui();

		m_Window.Swap();
	}
}

void App::CreateDockspace()
{
	// Create the dockspace
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
	// and handle the pass-thru hole, so we ask Begin() to not render a background.
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
	// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
	// all active windows docked into it will lose their parent and become undocked.
	// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
	// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", &m_IsRunning, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
}

void App::DrawMenuBar()
{
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("New", "Ctrl+N"))
			New();

		ImGui::Separator();

		if (ImGui::MenuItem("Open...", "Ctrl+O"))
			Open();
		if (ImGui::MenuItem("Open folder...", "Ctrl+Shift+O"))
			OpenFolder();

		ImGui::Separator();

		if (ImGui::MenuItem("Save", "Ctrl+S"))
			Save();
		if (ImGui::MenuItem("Save as...", "Ctrl+Shift+S"))
			SaveAs();
		if (ImGui::MenuItem("Save all..."))
			SaveAll();

		ImGui::Separator();

		if (ImGui::MenuItem("Quit", "Alt+F4"))
			m_Window.Close();

		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem("Undo", "Ctrl+Z", nullptr, m_FocusedEditor != nullptr))
			m_FocusedEditor->GetEditor().Undo();
		if (ImGui::MenuItem("Redo", "Ctrl+Y", nullptr, m_FocusedEditor != nullptr))
			m_FocusedEditor->GetEditor().Redo();

		ImGui::Separator();

		if (ImGui::MenuItem("Cut", "Ctrl+X", nullptr, m_FocusedEditor != nullptr))
			m_FocusedEditor->GetEditor().Cut();
		if (ImGui::MenuItem("Copy", "Ctrl+C", nullptr, m_FocusedEditor != nullptr))
			m_FocusedEditor->GetEditor().Copy();
		if (ImGui::MenuItem("Paste", "Ctrl+V", nullptr, m_FocusedEditor != nullptr))
			m_FocusedEditor->GetEditor().Paste();

		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("View"))
	{
		ImGui::MenuItem("File browser", "", &m_ShowBrowserPanel);
		ImGui::MenuItem("Get started", "", &m_ShowStartPanel);

		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}

void App::HandleInputs()
{
	if (m_Window.Key(TOE_KEY_LEFT_CONTROL) || m_Window.Key(TOE_KEY_RIGHT_CONTROL))
	{
		if (m_Window.Key(TOE_KEY_LEFT_SHIFT) || m_Window.Key(TOE_KEY_RIGHT_SHIFT))
		{
			if (m_Window.Key(TOE_KEY_O))
				OpenFolder();
			if (m_Window.Key(TOE_KEY_S))
				SaveAs();
		}
		if (m_Window.Key(TOE_KEY_N))
			New();
		if (m_Window.Key(TOE_KEY_O))
			Open();
		if (m_Window.Key(TOE_KEY_S))
			Save();

		if (m_Window.Key(TOE_KEY_Z))
			m_FocusedEditor->GetEditor().Undo();
		if (m_Window.Key(TOE_KEY_Y))
			m_FocusedEditor->GetEditor().Redo();

		if (m_Window.Key(TOE_KEY_X))
			m_FocusedEditor->GetEditor().Cut();
		if (m_Window.Key(TOE_KEY_C))
			m_FocusedEditor->GetEditor().Copy();
		if (m_Window.Key(TOE_KEY_P))
			m_FocusedEditor->GetEditor().Paste();
	}
}

void App::New()
{
	EditorPanel editor;
	editor.GetEditor().SetShowWhitespaces(false);
	m_Editors.push_back({ editor, true });
}

void App::Open()
{
	std::string path = Utils::OpenFileDialog("All files\0*.*\0", m_Window.GetNativeWindow());
	if (!path.empty())
	{
		// Check is the editor already exists
		bool exists = false;
		for (auto&& [editor, isOpen] : m_Editors)
		{
			if (path == editor.GetPath())
			{
				if (!isOpen)
					isOpen = true;
				exists = true;
				break;
			}
		}
		if (exists)
			return;

		EditorPanel editor(path, Utils::FileName(path));
		std::ifstream t(path);
		if (t.good())
		{
			std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
			editor.GetEditor().SetText(str);
			editor.GetEditor().SetShowWhitespaces(false);
			// editor.GetEditor().SetTextChanged(false);
			m_Editors.push_back({ editor, true });
		}
	}
}

void App::OpenFolder()
{
	std::string path = Utils::OpenFolderDialog();
	m_BrowserPanel.SetCurrentPath(path);
}

void App::Save()
{
	if (!m_FocusedEditor)
		return;
	if (m_FocusedEditor->GetPath().empty())
	{
		SaveAs();
		return;
	}
	std::ofstream file(m_FocusedEditor->GetPath());
	file << m_FocusedEditor->GetEditor().GetText();
	m_FocusedEditor->SetEdited(false);
}

void App::SaveAs()
{
	std::string path = Utils::SaveFileDialog("All files\0*.*\0", m_Window.GetNativeWindow());
	if (!path.empty())
	{
		m_FocusedEditor->SetPath(path);
		m_FocusedEditor->SetName(Utils::FileName(path));
		std::ofstream file(path);
		file << m_FocusedEditor->GetEditor().GetText();
		m_FocusedEditor->SetEdited(false);
	}
}

void App::SaveAll()
{
	for (auto&& [editor, isOpen] : m_Editors)
	{
		m_FocusedEditor = &editor;
		Save();
	}
}
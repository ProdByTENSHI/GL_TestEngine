#include "DebugUI.h"

#include <string>
#include <iostream>

#include "time/Time.h"

namespace engine {
	DebugUI::DebugUI(Window& window) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
		ImGui_ImplOpenGL3_Init();

		m_showWireframe = new bool;
		*m_showWireframe = false;
	}

	DebugUI::~DebugUI() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

	}

	void DebugUI::render() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Debug Graph");

		ImGui::Text("FPS: %i", (int)std::round(Time::getFPS()));
		ImGui::Text("Time in Seconds: % f", Time::getTime());
		ImGui::Text("Delta Time: %f", Time::getDeltaTime());
		ImGui::Checkbox("Show Wireframe", m_showWireframe);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
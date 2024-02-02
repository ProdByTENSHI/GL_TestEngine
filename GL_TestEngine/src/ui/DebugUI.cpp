#include "DebugUI.h"

#include <string>
#include <iostream>

#include "model/Model.h"
#include "ecs/ECS.h"
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

		m_ambientColorR = new float;
		m_ambientColorG = new float;
		m_ambientColorB = new float;
		m_ambientIntensity = new float;

		*m_ambientColorR = 1.0f;
		*m_ambientColorG = 1.0f;
		*m_ambientColorB = 1.0f;
		*m_ambientIntensity = 0.25f;

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

		ImGui::Text("FPS: %f", Time::getFPS());
		ImGui::Text("Time in Seconds: % f", Time::getTime());
		ImGui::Text("Delta Time: %f", Time::getDeltaTime());
		ImGui::Text("Entities in Scene: %i", EntityManager::getInstance()->getEntityCount());
		ImGui::Text("Total Triangles in Scene: %i", Model::triangleCount);
		ImGui::Checkbox("Show Wireframe", m_showWireframe);

		ImGui::SliderFloat("Ambient R: ", m_ambientColorR, 0.0f, 1.0f);
		ImGui::SliderFloat("Ambient G: ", m_ambientColorG, 0.0f, 1.0f);
		ImGui::SliderFloat("Ambient B: ", m_ambientColorB, 0.0f, 1.0f);
		ImGui::SliderFloat("Ambient Intensity: ", m_ambientIntensity, 0.0f, 5.0f);

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
#pragma once

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "core/Window.h"

namespace engine {
	class DebugUI {
	public:
		DebugUI(Window& window);
		~DebugUI();

		void render();

		inline bool shouldShowWireFrame() { return *m_showWireframe; }

		// Light Stuff
		float* m_ambientColorR = nullptr;
		float* m_ambientColorG = nullptr;
		float* m_ambientColorB = nullptr;
		float* m_ambientIntensity = nullptr;

	private:
		// Model Stuff
		bool* m_showWireframe = nullptr;
	};
}
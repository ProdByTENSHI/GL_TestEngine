#pragma once

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "core/ScriptLifeTime.h"
#include "core/Window.h"

namespace engine {
	class DebugUI : public ScriptLifeTime {
	public:
		DebugUI(Window& window);
		~DebugUI();

		void onRender();

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
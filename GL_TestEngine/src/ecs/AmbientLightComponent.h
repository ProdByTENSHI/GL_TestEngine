#include "BaseComponent.h"
#include "RenderComponent.h"
#include "renderer/Shader.h"

namespace engine {
	class AmbientLightComponent : public BaseComponent, public RenderComponent {
	public:
		AmbientLightComponent(float r, float g, float b, float a, float intensity, Shader& shader) {
			setValues(r, g, b, a, intensity);

			m_shader = &shader;
		}

		void setValues(float r, float g, float b, float a, float intensity) {
			m_r = r;
			m_b = b;
			m_g = g;
			m_a = a;
			m_intensity = intensity;
		}

		void render() override {
			m_shader->setUniform4f("u_AmbientColor", m_r, m_g, m_b, m_a);
			m_shader->setUniform1f("u_AmbientIntensity", m_intensity);
		}

		inline const unsigned int getType() override { return m_type; }
		inline const std::string& getName() override { return m_name; }
		inline const bool isComponentUnique() override { return m_isUnique; }

	protected:
		unsigned int m_type = ComponentType::RenderType | ComponentType::LightType | ComponentType::AmbientLightType;

		const std::string m_name = "Ambient Light Component";
		const bool m_isUnique = false;

	private:
		Shader* m_shader = nullptr;

		float m_r = 0.0f;
		float m_g = 0.0f;
		float m_b = 0.0f;
		float m_a = 1.0f;
		float m_intensity = 1.0f;
	};
}
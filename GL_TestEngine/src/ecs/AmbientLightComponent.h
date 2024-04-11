#include "BaseComponent.h"
#include "RenderComponent.h"
#include "renderer/Shader.h"

namespace engine {
	class AmbientLightComponent : public BaseComponent, public RenderComponent {
	public:
		AmbientLightComponent(const glm::vec3& color, float intensity) {
			setValues(color, intensity);
		}

		void setValues(const glm::vec3& color, float intensity) {
			m_color = color;
			m_intensity = intensity;
		}

		void render(Shader& shader) override { }

		void setShaderUniforms(Shader& shader) override {
			shader.setUniform3f("u_AmbientColor", m_color);
			shader.setUniform1f("u_AmbientIntensity", m_intensity);
		}

		inline const unsigned int getType() override { return m_type; }
		inline const std::string& getName() override { return m_name; }
		inline const bool isComponentUnique() override { return m_isUnique; }

	protected:
		unsigned int m_type = ComponentType::RenderType | ComponentType::LightType | ComponentType::AmbientLightType;

		const std::string m_name = "Ambient Light Component";
		const bool m_isUnique = false;

	private:
		glm::vec3 m_color = glm::vec3(0);
		float m_intensity = 1.0f;
	};
}
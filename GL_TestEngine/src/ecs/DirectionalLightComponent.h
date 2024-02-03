#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "renderer/Shader.h"

namespace engine {
	class DirectionalLightComponent : public BaseComponent, public RenderComponent {
	public:
		DirectionalLightComponent(float r, float g, float b, float intensity, const TransformComponent& transform) {
			setValues(r, g, b, intensity);

			m_transform = const_cast<TransformComponent*>(&transform);
		}

		void setValues(float r, float g, float b, float intensity) {
			m_color.x = r;
			m_color.y = g;
			m_color.z = b;

			m_intensity = intensity;
		}

		void render(Shader& shader) override { }

		void setShaderUniforms(Shader& shader) override {
			shader.setUniform3f("u_LightPosition", m_transform->getPosition());
			shader.setUniform3f("u_LightColor", m_color);
			shader.setUniform1f("u_LightIntensity", m_intensity);
		}

		inline const unsigned int getType() override { return m_type; }
		inline const std::string& getName() override { return m_name; }
		inline const bool isComponentUnique() override { return m_isUnique; }

	protected:
		unsigned int m_type = ComponentType::RenderType | ComponentType::LightType | ComponentType::DirectionalLightType;

		const std::string m_name = "Directional Light Component";
		const bool m_isUnique = false;

	private:
		TransformComponent* m_transform = nullptr;

		glm::vec3 m_color = glm::vec3(0);

		float m_intensity = 1.0f;
	};
}
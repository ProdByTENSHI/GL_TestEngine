#include "BaseComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "renderer/Shader.h"

namespace engine {
	class DirectionalLightComponent : public BaseComponent, public RenderComponent {
	public:
		DirectionalLightComponent(float r, float g, float b, float intensity, const TransformComponent& transform, Shader& shader) {
			setValues(r, g, b, intensity);

			m_transform = const_cast<TransformComponent*>(&transform);
			m_shader = &shader;
		}

		void setValues(float r, float g, float b, float intensity) {
			m_r = r;
			m_b = b;
			m_g = g;
			m_intensity = intensity;
		}

		// TODO: Fix Frag Shader. Something is fucked
		void render() override {
			m_shader->setUniform3f("u_LightColor", m_r, m_g, m_b);
			m_shader->setUniform1f("u_LightIntensity", m_intensity);
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
		Shader* m_shader = nullptr;

		float m_r = 0.0f;
		float m_g = 0.0f;
		float m_b = 0.0f;
		float m_intensity = 1.0f;
	};
}
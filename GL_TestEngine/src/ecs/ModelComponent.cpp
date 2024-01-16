#include "ModelComponent.h"

namespace engine {
	void ModelComponent::render() {
		m_model->render(*m_shader);
	}
}
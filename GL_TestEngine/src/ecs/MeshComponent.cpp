#include "MeshComponent.h"

namespace engine {
	void MeshComponent::render() {
		m_mesh->render(*m_shader);
	}
}
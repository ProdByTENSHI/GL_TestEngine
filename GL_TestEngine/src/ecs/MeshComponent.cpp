#include "MeshComponent.h"

namespace ecs {
	void MeshComponent::render() {
		m_mesh->render(*m_shader);
	}
}
#include "MeshComponent.h"

namespace ecs {
	void MeshComponent::render(glm::vec3 position, const char* positionUniform) {
		m_shader->bind();
		m_mesh->getVao().bind();

		m_shader->setUniform3f(positionUniform, position.x, position.y, position.z);

		glDrawElements(GL_TRIANGLES, m_mesh->getIndices().size(), GL_UNSIGNED_INT, nullptr);

		m_mesh->getVao().unbind();
		m_shader->unbind();
	}
}
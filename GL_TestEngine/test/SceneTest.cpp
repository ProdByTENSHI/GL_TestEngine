#include "core/Application.h"
#include "ui/DebugUI.h"
#include "camera/Camera.h"
#include "ecs/ECS.h"
#include "ecs/Components.h"

using namespace engine;

int main(int argc, char* argv[]) {
	Application* app = new Application("GL Test Engine", 1280, 720);

	Camera* camera = new Camera(60.0f, 0.01f, 100.0f, glm::vec3(0.0f, 0.0f, -1.0f), app->getWindow().getWidth(), app->getWindow().getHeight(), app->getShader());
	app->addToCallStack(camera);

	DebugUI* ui = new DebugUI(app->getWindow());
	app->addToCallStack(ui);

	Entity* ambientLight = &EntityManager::getInstance()->createEmptyEntity();
	EntityManager::getInstance()->addComponent(ambientLight->getId(), new TransformComponent(glm::vec3(0), glm::vec3(0), glm::vec3(0)));
	EntityManager::getInstance()->addComponent(ambientLight->getId(), new AmbientLightComponent(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f));

	Entity* entity = &EntityManager::getInstance()->createEmptyEntity();  
	TransformComponent* transform = (TransformComponent*)EntityManager::getInstance()->addComponent(entity->getId(), new TransformComponent(glm::vec3(0), glm::vec3(0), glm::vec3(0)));
	EntityManager::getInstance()->addComponent(entity->getId(), new ModelComponent("res/models/box-large.obj", *transform));

	//camera->HandleInput(*app->getWindow().getWindow(), 20.0f);
	app->update();

	delete app;
	
	return 0;
}
#include <ctime>
#include <iostream>

using namespace std;

#include <Core/Engine.h>

#include <Laboratoare/LabList.h>

int main(int argc, char **argv)
{
	srand((unsigned int)time(NULL));

	WindowProperties wp;
	wp.resolution = glm::ivec2(1280, 720);

	WindowObject* window = Engine::Init(wp);

	World *world = new Tema1();
	world->Init();
	world->Run();

	Engine::Exit();

	return 0;
}
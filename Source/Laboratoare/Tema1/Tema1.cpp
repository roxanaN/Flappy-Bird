#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

Tema1::Tema1() {}

Tema1::~Tema1() {}

void Tema1::Init() {
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(true);
	frameDim = resolution.y;

	glm::vec3 corner = glm::vec3(0, 0, 0);
	glm::vec3 green = glm::vec3(0.5, 1, 0.5);
	glm::vec3 orange = glm::vec3(1, 0.5, 0);
	glm::vec3 darkOrange = glm::vec3(1, 0.3, 0);
	glm::vec3 bronze = glm::vec3(0.55, 0.47, 0.14);
	glm::vec3 black = glm::vec3(0, 0, 0);

	gameOver = false;
	start = false;
	pipeLength = 100;
	pipeWidth = 700;

	distance = 400;
	tunel = 250;
	angle = 0;
	jump = 100;
	score = 0;

	B = 5;
	N = 4;
	gravity = 0;
	speed = 4;
	rot = 0;

	// wing, body, eye, head, beak
	std::vector<float> xb = { 380, 400, 440, 435, 445 };
	for (int i = 0; i < B; ++i) {
		xBird.push_back(xb[i]);
	}

	std::vector<float> dimb = { 25, 25, 5, 15, 15 };
	for (int i = 0; i < B; ++i) {
		dimBird.push_back(dimb[i]);
	}

	std::vector<float> yb = { 410, 400, 405, 400, 390 };
	for (int i = 0; i < B; ++i) {
		yBird.push_back(yb[i]); 
	}

	birdBeak = xBird[B - 1];

	X = resolution.x + 100;
	for (int i = 0; i < N; ++i) {
		translatePipe.push_back(X);
		xPipe.push_back(X);
		X += distance;

		count.push_back(false);
	}

	std::vector<float> yp = { 300, 350, 150, 280 };
	for (int i = 0; i < N; ++i) {
		yDown.push_back(yp[i] - resolution.y);
		chooseY.push_back(yp[i] - resolution.y);
	}

	Mesh* pipe = Object2D::CreateRectangle("rectangle", corner, pipeLength, pipeWidth, green, true);
	Mesh* wing = Object2D::CreateTriangle("wing", corner, dimBird[0], darkOrange, true);
	Mesh* body = Object2D::CreateCircle("body", corner, dimBird[1], 360, orange, true);
	Mesh* eye = Object2D::CreateCircle("eye", corner, dimBird[2], 360, black, true);
	Mesh* head = Object2D::CreateCircle("head", corner, dimBird[3], 360, orange, true);
	Mesh* beak = Object2D::CreateTriangle("beak", corner, dimBird[4], bronze, true);

	bird.push_back("wing");
	bird.push_back("body");
	bird.push_back("eye");
	bird.push_back("head");
	bird.push_back("beak");

	AddMeshToList(pipe);
	AddMeshToList(wing);
	AddMeshToList(body);
	AddMeshToList(eye);
	AddMeshToList(head);
	AddMeshToList(beak);
}

void Tema1::FrameStart() {
	glClearColor(0.5, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) {
	// Bird Problem
	for (int i = 0; i < B; ++i) {
		yBird[i] -= gravity;

		if (yBird[i] < 0 || yBird[i] > frameDim) {
			GameOver();
		}

		modelMatrix = glm::mat3(1);
		if(!i) {
			modelMatrix *= Transform2D::Rotate(rot);
		}
		(i < 2) ? modelMatrix *= Transform2D::Translate(xBird[i], yBird[i])
			    : modelMatrix *= Transform2D::Translate(xBird[i], yBird[i] + angle);
		RenderMesh2D(meshes[bird[i]], shaders["VertexColor"], modelMatrix);
	}

	// Game over
	if (!gameOver) {
		for (int i = 0; i < N; ++i) {
			float yUp = yDown[i] + tunel + pipeWidth;
			float yBeak = yBird[B - 1];
			if (((birdBeak >= xPipe[i] && birdBeak <= xPipe[i] + pipeLength)
				&& (yDown[i] + pipeWidth >= yBeak || yUp <= yBeak))) {
				GameOver();
			}
		}
	}

	// Pipes Problem
	for (int i = 0; i < N; ++i) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(xPipe[i], yDown[i]);
		RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

		float yUp = yDown[i] + tunel + pipeWidth;
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(xPipe[i], yUp);
		RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

		if (xBird[1] > xPipe[i] + pipeLength && !count[i] && !gameOver) {
			++score;
			count[i] = true;

			printf("Score : %d\n", score);
		}

		if (speed) {
			xPipe[i] -= speed;
			if (xPipe[i] < - pipeLength) {
				translatePipe[i] = translatePipe[0];
				xPipe[i] = translatePipe[0] + pipeLength;

				int idx = rand() % N;
				yDown[i] = chooseY[idx];

				count[i] = false;
			}
		}
	}
}

void Tema1::FrameEnd() {}

void Tema1::OnInputUpdate(float deltaTime, int mods) {}

void Tema1::OnKeyPress(int key, int mods) {
	if (key == GLFW_KEY_SPACE) {
		if (!gameOver) {
			gravity = 4;
		}

		for (int i = 0; i < B; ++i) {
			yBird[i] += jump;
		}

		if (!gameOver) {
			(!start) ? angle += 20 : angle += 40;
			rot += 2;
		}
	}
}

void Tema1::OnKeyRelease(int key, int mods) {
	if (key == GLFW_KEY_SPACE) {
		if (!gameOver) {
			(!start) ? angle -= 20 : angle -= 40;
			rot -= 2;
		}

		if (!start) {
			for (int i = 2; i < B; ++i) {
				yBird[i] -= 20;
			}

			start = true;
		}
	}
}

void Tema1::GameOver() {
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int k = 0; k < B; ++k) {
		(k < B - 1) ? ((!k) ? yBird[k] = 60 : yBird[k] = 50) : yBird[k] = 40;
		angle = -20;
		modelMatrix = glm::mat3(1);
		(k < 2) ? modelMatrix *= Transform2D::Translate(xBird[k], yBird[k])
			: modelMatrix *= Transform2D::Translate(xBird[k], yBird[k] + angle);
		RenderMesh2D(meshes[bird[k]], shaders["VertexColor"], modelMatrix);
	}

	gravity = 0;
	jump = 0;
	speed = 0;

	printf(" ------------------------------------------------------------------------ \n");
	printf("|    *****      *     *       * ******       ****  *       ****** ****    |\n");
	printf("|   *          * *    * *   * * *           *    *  *     * *     *   *   |\n");
	printf("|   *  ****   *   *   *  * *  * *****       *    *   *   *  ****  ****    |\n");
	printf("|   *  *  *  *******  *   *   * *           *    *    * *   *     * *     |\n");
	printf("|    *****  *       * *       * ******       ****      *    ***** *   *   |\n");
	printf(" ------------------------------------------------------------------------- \n");
	printf("\nFinal Score : %d\n", score);
	gameOver = true;
}

#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void GameOver();

	protected:
		glm::mat3 modelMatrix;
		float X, pipeLength, pipeWidth;
		float frameDim;
		float gravity;
		int N;
		int B;
		float distance;
		float tunel;
		float angle;
		float jump;
		float birdBeak;
		float speed;
		float rot;
		int score;
		bool gameOver;
		bool start;

		std::vector<float> translatePipe, xPipe;
		std::vector<float> yDown, chooseY;
		std::vector<float> xBird, dimBird, yBird;
		std::vector<std::string> bird;
		std::vector<bool> count;
};

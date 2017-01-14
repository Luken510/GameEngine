#pragma once
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"
#include <glm/glm.hpp>
#include "drawframeworks.h"

using namespace SetUp;
using namespace DrawFrame;

namespace Game
{
	class GameScene : public Scene
	{
	private:
		int m_iWidth, m_iHeight;

		//Robot Robot
		//Room room
		//Room room2
		//Desk?
		//Table?s
		//Teapot?

		DrawFrameWork DrawClass;


		glm::mat4 model; // for mvp

		void setMatrices(Camera::QuatCamera &camera); // set the matricies for the camera

		bool m_Toggle;

	public:
		GameScene(); // Constructor

		void setLightParams(Camera::QuatCamera &camera); //Setup the lighting

		void initScene(Camera::QuatCamera &camera); //Initialise the scene

		void update(float t); //Update the scene

		void render(Camera::QuatCamera &camera);	//Render the scene

		void resize(Camera::QuatCamera &camera, int, int); //Resize


	};
}


























#endif // GAMESCENE_H

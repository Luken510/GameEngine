#pragma once
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"

#include "gl_core_4_3.hpp"
#include <GLFW/glfw3.h>
#include "glutils.h"
#include "scene.h"
#include "glslprogram.h"
#include <glm/glm.hpp>
#include "drawframeworks.h"

using namespace Camera;

namespace GameScene
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

	//	DrawFrame::DrawFrameWork DrawFrameTest;

		glm::mat4 model; // for mvp

		void setMatrices(QuatCamera & camera); // set the matricies for the camera

		void compileAndLinkShader(); //Compile and link the shader

		bool m_Toggle;

	public:
		GameScene(); // Constructor

		void setLightParams(QuatCamera & camera); //Setup the lighting

		void initScene(QuatCamera & camera); //Initialise the scene

		void update(float t); //Update the scene

		void render(QuatCamera & camera);	//Render the scene

		void resize(QuatCamera & camera, int, int); //Resize

		void toggleRs();

	};
}


























#endif // GAMESCENE_H

#pragma once
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "scene.h"

#include "robot.h"

#include "glslprogram.h"

#include "modelLoader.h"

using namespace egf;

namespace ecr
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

		GLSLProgram myGLSL_prog;

		Robot* theRobot;
		Model* theSpookyGuy;
		Model* theHouse;
		
		void compileAndLinkShader();

		glm::mat4 model; // for mvp

		void setMatrices(ecr::QuatCamera &camera); // set the matricies for the camera
		
		GLuint ShadingRobot, ShadingObject;

	public:
		GameScene(); // Constructor

		void setLightParams(ecr::QuatCamera &camera); //Setup the lighting

		void initScene(ecr::QuatCamera &camera); //Initialise the scene

		void update(float t); //Update the scene

		void render(ecr::QuatCamera &camera);	//Render the scene

		void resize(ecr::QuatCamera &camera, int, int); //Resize

		void animate(bool a, int x);


	};
}


























#endif // GAMESCENE_H

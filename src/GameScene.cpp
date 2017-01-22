
#include "GameScene.h"
#include "stdafx.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
using std::cerr;
using std::endl;

//#include "defines.h"

//using glm::vec3;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>


using namespace ecr;

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Default constructor
	/////////////////////////////////////////////////////////////////////////////////////////////
	GameScene::GameScene()
	{
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	//Initialise the scene
	/////////////////////////////////////////////////////////////////////////////////////////////
	void GameScene::initScene(ecr::QuatCamera &camera)
	{
		//|Compile and link the shader  

		compileAndLinkShader();

		gl::Enable(gl::DEPTH_TEST);

		//Set up the lighting
		setLightParams(camera);


		ShadingRobot = gl::GetSubroutineIndex(myGLSL_prog.getHandle(), gl::FRAGMENT_SHADER, "Robot");
		ShadingObject = gl::GetSubroutineIndex(myGLSL_prog.getHandle(), gl::FRAGMENT_SHADER, "Objects");

		theHouse = new Model("../assets/house/house.FBX");

		//Create the objects
		theSpookyGuy = new Model("../assets/nanosuit/nanosuit.obj");



		//Create the robot
		theRobot = new Robot;

	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	//Update 
	/////////////////////////////////////////////////////////////////////////////////////////////

	void GameScene::update(float t)
	{
		theRobot->Update(t);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Set up the lighting variables in the shader
	/////////////////////////////////////////////////////////////////////////////////////////////
	void GameScene::setLightParams(ecr::QuatCamera &camera)
	{
		vec3 WorldLightPos = vec3(10.0f, 10.0f, 10.0f);

		myGLSL_prog.setUniform("Ld", 0.9f, 0.5f, 0.3f); // diffuse light intentsity
		myGLSL_prog.setUniform("La", 0.2f, 0.2f, 0.2f); // ambient light intentsity
		myGLSL_prog.setUniform("n", 0.9f, 0.5f, 0.3f); // specular exponent
		myGLSL_prog.setUniform("Al", 0.0001f); // light attenuation		
		myGLSL_prog.setUniform("LightPosition", WorldLightPos);
		myGLSL_prog.setUniform(("CameraPos"), camera.position());

	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Render the scene
	/////////////////////////////////////////////////////////////////////////////////////////////
	void GameScene::render(ecr::QuatCamera &camera)
	{
		//OpenGL Clear ColourBits and Depth bits before rendering scene
	
		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

		myGLSL_prog.use();
		//Now set up the Robot
		gl::UniformSubroutinesuiv(gl::FRAGMENT_SHADER, 1, &ShadingRobot);
		model = mat4(1.0f);
		setMatrices(camera);
		myGLSL_prog.setUniform("Kd", 0.0f, 0.0f, 1.0f); // diffuse light
		myGLSL_prog.setUniform("Ka", 0.0f, 0.0f, 1.0f); // ambient light
		myGLSL_prog.setUniform("Ks", 0.0f, 0.0f, 1.0f); // specular light
		theRobot->Render();

		gl::UniformSubroutinesuiv(gl::FRAGMENT_SHADER, 1, &ShadingObject);
		// Draw the loaded model
		model = mat4(1.0f) * glm::translate(vec3(5.0f, -5.0f, 5.0f));
		setMatrices(camera);
		theSpookyGuy->Render(&myGLSL_prog);

		gl::UniformSubroutinesuiv(gl::FRAGMENT_SHADER, 1, &ShadingObject);
		// Draw the loaded model
		model = mat4(1.0f) * glm::translate(vec3(50.0f,-5.0f,50.0f)) * glm::scale (vec3(0.8f,0.8f,0.8f));
		setMatrices(camera);
		theHouse->Render(&myGLSL_prog);

		
		
	}


	/////////////////////////////////////////////////////////////////////////////////////////////
	//Send the MVP matrices to the GPU
	/////////////////////////////////////////////////////////////////////////////////////////////
	
	void GameScene::setMatrices(ecr::QuatCamera &camera)
	{
		mat4 mv = (camera.view()) * model;

	//Negate Translate for camera view
		mat4 mTempView = camera.view();
		mTempView[3][0] = 0.0f;
		mTempView[3][1] = 0.0f;
		mTempView[3][2] = 0.0f;
		mv = mTempView * model;

		mat3 mNormal = mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) );

		myGLSL_prog.setUniform("NormalMatrix", mNormal);
		myGLSL_prog.setUniform("M", model);
		myGLSL_prog.setUniform("V", camera.view());
		myGLSL_prog.setUniform("P", camera.projection());
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	// resize the viewport
	/////////////////////////////////////////////////////////////////////////////////////////////
	void GameScene::resize(ecr::QuatCamera &camera, int w, int h)
	{
		gl::Viewport(0, 0, w, h);
		m_iWidth = w;
		m_iHeight = h;
		camera.setAspectRatio((float)w / h);

	}

	void GameScene::compileAndLinkShader()
	{

		try {
			myGLSL_prog.compileShader("Shaders/diffuse.vert");
			myGLSL_prog.compileShader("Shaders/diffuse.frag");
			myGLSL_prog.link();
			myGLSL_prog.validate();
			myGLSL_prog.use();
		}
		catch (GLSLProgramException & e) {
			std::cerr << e.what() << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	void GameScene::animate(bool a, int x)
	{
		theRobot->Animated(a, x);
	}
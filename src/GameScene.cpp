
#include "GameScene.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
using std::cerr;
using std::endl;

//#include "defines.h"

//using glm::vec3;

using namespace DrawFrame;


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>


namespace GameScene
{
	/////////////////////////////////////////////////////////////////////////////////////////////
	// Default constructor
	/////////////////////////////////////////////////////////////////////////////////////////////
	GameScene::GameScene()
	{
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	//Initialise the scene
	/////////////////////////////////////////////////////////////////////////////////////////////
	void GameScene::initScene(QuatCamera & camera)
	{
		//|Compile and link the shader  
		DrawFrameWork::CompileAndLinkShader();

		DrawFrameWork::EnableDepth();

		//Set up the lighting
		DrawFrameWork::setLightParams(camera.position());


		//Create the plane to represent the ground
		//plane = new VBOPlane(100.0, 100.0, 100, 100);



	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	//Update not used at present
	/////////////////////////////////////////////////////////////////////////////////////////////
	void GameScene::update(float t)
	{

	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Set up the lighting variables in the shader
	/////////////////////////////////////////////////////////////////////////////////////////////
	void GameScene::setLightParams(QuatCamera & camera)
	{
		vec3 WorldLightPos = vec3(10.0f, 10.0f, 10.0f);
		DrawFrameWork::setLightParams(camera.position(), WorldLightPos);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Render the scene
	/////////////////////////////////////////////////////////////////////////////////////////////
	void GameScene::render(QuatCamera & camera)
	{
		//OpenGL Clear ColourBits and Depth bits before rendering scene
		DrawFrameWork::clearBits();


		//Now set up the teapot 
		model = mat4(1.0f);
		setMatrices(camera);
		//Set the Teapot material properties in the shader and render
		prog.setUniform("Kd", 0.9f, 0.5f, 0.3f); // diffuse light
		prog.setUniform("Ka", 0.2f, 0.2f, 0.2f); // ambient light
		prog.setUniform("Ks", 0.9f, 0.5f, 0.3f); // specular light

	}


	/////////////////////////////////////////////////////////////////////////////////////////////
	//Send the MVP matrices to the GPU
	/////////////////////////////////////////////////////////////////////////////////////////////
	void GameScene::setMatrices(QuatCamera & camera)
	{
		mat4 mv = camera.view() * model;

		//Negate translate of camera view for skybox
		mat4 TempView = camera.view();
		TempView[3][0] = 0.0f;
		TempView[3][1] = 0.0f;
		TempView[3][2] = 0.0f;
		mv = TempView * model;


		prog.setUniform("ModelViewMatrix", mv);
		prog.setUniform("NormalMatrix",
			mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
		prog.setUniform("MVP", camera.projection() * mv);
		// the correct matrix to transform the normal is the transpose of the inverse of the M matrix
		mat3 normMat = glm::transpose(glm::inverse(mat3(model)));
		prog.setUniform("M", model);
		//prog.setUniform("NormalMatrix", normMat);
		prog.setUniform("V", camera.view());
		prog.setUniform("P", camera.projection());
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	// resize the viewport
	/////////////////////////////////////////////////////////////////////////////////////////////
	void GameScene::resize(QuatCamera & camera, int w, int h)
	{
		gl::Viewport(0, 0, w, h);
		width = w;
		height = h;
		camera.setAspectRatio((float)w / h);

	}

	void GameScene::toggleRs()
	{
		m_Toggle = !m_Toggle;
	}
}
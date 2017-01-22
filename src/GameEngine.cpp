// GameEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "scene.h"
#include <string>
using namespace std;

#include "QuatCamera.h"
#include "timer.h"
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define MOVE_VELOCITY 0.01f
#define ROTATE_VELOCITY 0.001f
//prog.use()
//do the matrix then render
//use obj loader
//mat4 for moving robot, with cos things?
//The GLFW Window
GLFWwindow *window;

//The Scene
ecr::Scene *scene;

//The camera
ecr::QuatCamera camera1;
ecr::QuatCamera camera2;
ecr::QuatCamera *CameraController = &camera1;

//To keep track of cursor location
double lastCursorPositionX, lastCursorPositionY, cursorPositionX, cursorPositionY;

/////////////////////////////////////////////////////////////////////////////////////////////
//Callback function for keypress use to toggle animate (not used at the moment)
// and to check for R to reset camera
/////////////////////////////////////////////////////////////////////////////////////////////
static void key_callback(GLFWwindow* window, int key, int cancode, int action, int mods)
{

	if (key == 'R' && action == GLFW_RELEASE)
		CameraController->reset();
	if (key == GLFW_KEY_1 && action == GLFW_RELEASE)
		CameraController->toggleCamera(1);
	if (key == GLFW_KEY_2 && action == GLFW_RELEASE)
		CameraController->toggleCamera(2);
	/////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		scene->animate(TRUE, 0);
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		scene->animate(TRUE, 1);
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		scene->animate(TRUE, 2);
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		scene->animate(TRUE, 3);
	/////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////////

	if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
		scene->animate(FALSE, 4);
	if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
		scene->animate(FALSE, 4);
	if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
		scene->animate(FALSE, 4);
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
		scene->animate(FALSE, 4);
}


/////////////////////////////////////////////////////////////////////////////////////////////
//Callback function when mouse wheel is scrolled
/////////////////////////////////////////////////////////////////////////////////////////////
void scroll_callback(GLFWwindow *window, double x, double y)
{
	CameraController->zoom((float)y*0.5f);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Initialise 
/////////////////////////////////////////////////////////////////////////////////////////////
void initializeGL() {


	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	lastCursorPositionX = 0.0;
	lastCursorPositionY = 0.0;
	cursorPositionX = 0.0;
	cursorPositionY = 0.0;


	// Create the scene class and initialise it for the camera
	scene = new ecr::GameScene();

	if (CameraController->getCurrentCam() == 1)
	{
		CameraController = &camera1;
	}
	else if (CameraController->getCurrentCam() == 2)
	{
		CameraController = &camera2;
	}
	scene->initScene(*CameraController);
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Update
/////////////////////////////////////////////////////////////////////////////////////////////
void update(float t)
{

	//Get the current cursor position
	glfwGetCursorPos(window, &cursorPositionX, &cursorPositionY);

	//See how much the cursor has moved
	float deltaX = (float)(lastCursorPositionX - cursorPositionX);
	float deltaY = (float)(lastCursorPositionY - cursorPositionY);

	//Using a different way (i.e. instead of callback) to check for LEFT mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
	{
		
		//Rotate the camera. The 0.001f is a velocity mofifier to make the speed sensible

		CameraController->rotate(deltaX*ROTATE_VELOCITY, deltaY*ROTATE_VELOCITY);

	}

	//Using a different way (i.e. instead of callback) to check for RIGHT mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
	{
		
		//Rotate the camera. The 0.01f is a velocity mofifier to make the speed sensible
		CameraController->pan(deltaX*MOVE_VELOCITY, deltaY*MOVE_VELOCITY);

	}
	//To adjust Roll with MIDDLE mouse button
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE))
	{

		CameraController->roll(deltaX*ROTATE_VELOCITY);
	}

	scene->update(t);

	
	
	//Store the current cursor position
	lastCursorPositionX = cursorPositionX;
	lastCursorPositionY = cursorPositionY;

}


/////////////////////////////////////////////////////////////////////////////////////////////
// Main loop updates scene and renders until we quit
/////////////////////////////////////////////////////////////////////////////////////////////
void mainLoop() {
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		
		update((float)glfwGetTime());

		scene->render(*CameraController);

		//is running;
		//GUI->update
		//Render->draw



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
// resize
/////////////////////////////////////////////////////////////////////////////////////////////
void resizeGL(ecr::QuatCamera &camera, int w, int h) {
	scene->resize(camera, w, h);
}


/////////////////////////////////////////////////////////////////////////////////////////////
// main entry point
/////////////////////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{

	string name = "Prototype";

	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);

	// Select OpenGL 4.3 with a forward compatible core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);

	// Open the window
	string title = "Engine - " + name;
	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, title.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	//Key callback
	glfwSetKeyCallback(window, key_callback);

	//Mouse callback, not used at the moment
	//glfwSetMouseButtonCallback(window,mouse_callback);

	//Scroll callback
	glfwSetScrollCallback(window, scroll_callback);//Set callback

												   // Load the OpenGL functions.
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

	if (!didLoad) {

		glfwTerminate();
		exit(EXIT_FAILURE);
	}



	// Initialization
	initializeGL();

	resizeGL(*CameraController, WIN_WIDTH, WIN_HEIGHT);


	// Enter the main loop
	mainLoop();

	// Close window and terminate GLFW
	glfwTerminate();

	delete scene;

	// Exit program
	exit(EXIT_SUCCESS);
}





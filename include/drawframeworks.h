#pragma once
#ifndef DRAWFRAMEWORKS_H
#define DRAWFRAMEWORKS_H

#include "gl_core_4_3.hpp"
#include <GLFW/glfw3.h>
#include "glutils.h"
#include "scene.h"
#include "glslprogram.h"
#include <ostream>
#include <iostream>


//multiple versions of the same thing to take a certain type
namespace DrawFrame
{

class DrawFrameWork
{
private:

	static unsigned int vaoHandle;
	static GLSLProgram prog;

public:
	DrawFrameWork();

	~DrawFrameWork();

	static void setVBOs(float fvData[], float fnData[], float ftData[], // vertex, normals, and texture co-ords
		float size, unsigned int handle[], int indicies[], unsigned int IndiciesSize); // with indicies

	static void setVBOs(float fvData[], float fnData[], float ftData[],
		float size, unsigned int handle[]); // without indicies

	//Rendering function to render the used Current VBOs and VAOs
	static void render(unsigned int VAO, unsigned int DrawCount, bool indicies);

	//OpenGL functions to set and disable Depth
	static void EnableDepth();
	static void DisableDepth();

	//Compling the shader program
	static void CompileAndLinkShader();

	//Setting the Light Params for the Camera's position etc.
	static void setLightParams(glm::vec3 CamPos, glm::vec3 WorldLight,
		float AmbIntensity, float DiffIntensity, float SpecularIntensity); // setting the Light Values for the shader

	//Clear Buffer Bits, colour and depth
	static void clearBits();
















};


}
#endif
#pragma once
#ifndef DRAWFRAMEWORKS_H
#define DRAWFRAMEWORKS_H

#include "gl_core_4_3.hpp"
#include <GLFW/glfw3.h>
#include "glutils.h"
#include "glslprogram.h"
#include <ostream>
#include <iostream>

//multiple versions of the same thing to take a certain type
namespace DrawFrame
{

class DrawFrameWork
{
private:
	GLuint vaoHandle;
	GLSLProgram prog;


public:
	 
	
	DrawFrameWork();

	~DrawFrameWork(); //need to implement to clean up any VBOs and VAOs

	 void setVBOs(GLfloat fvData[], GLfloat fnData[], GLfloat ftData[], // vertex, normals, and texture co-ords
		 GLuint size, GLuint handle[], GLfloat indicies[], GLuint IndiciesSize); // with indicies

	 void setVBOs(GLfloat fvData[], GLfloat fnData[], GLfloat ftData[],
		 GLuint size, GLuint handle[]); // without indicies

	//Rendering function to render the used Current VBOs and VAOs
	 void render(GLuint VAO, GLuint DrawCount, bool indicies);

	//OpenGL functions to set and disable Depth
	 void EnableDepth();
	// void DisableDepth();

	//Compling the shader program
	 void CompileAndLinkShader();

	//Setting the Light Params for the Camera's position etc.
	 void setLightParams(vec3 CamPos, vec3 WorldLight,
		float AmbIntensity, float DiffIntensity, float SpecularIntensity); // setting the Light Values for the shader

	//Clear Buffer Bits, colour and depth
	 void clearBits();

	//Set the Reflectivity - used for objects rendering

	 void setReflectivity(vec3 ambientReflect, vec3 diffuseReflect, vec3 specularReflect);

	//Set the matricies for M V P
	 void setMatricies(mat3 NormalMatrix, mat4 model, mat4 view, mat4 proj);

	 void setViewPort(GLint x, GLint y, GLint width, GLint height);








};


}
#endif
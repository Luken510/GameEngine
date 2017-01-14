#pragma once
#ifndef  CUBE_H
#define CUBE_H

#include <glm\glm.hpp>
#include <GLFW\glfw3.h>


using namespace glm;

namespace Shape
{
	class  Cube
	{

	private:

		//vec3 m_vDimentions;
		GLfloat m_vPosition;
		GLfloat m_vTextureCoords;
		vec3 m_vOrigin;
		vec3 m_vOrientation;

	public:

		Cube(vec3 vPos, vec3 vOrigin, vec3 vOrient);
		~Cube();


		void draw();
		void render();
		void update();



	};


}


#endif // ! CUBE_H

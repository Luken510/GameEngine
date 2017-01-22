#pragma once
#ifndef  CUBE_H
#define CUBE_H
#include <glm\glm.hpp>

using namespace glm;

namespace ecr
{
	class  Cube
	{

	private:


		GLuint m_vaoHandle;
		GLuint m_vboHandle[3];

		GLuint m_vNumOfIndicies;

		//glm::vec3 m_vDimentions;
		
		GLfloat m_vTextureCoords; // texture co-ordinates 
		vec3 m_vOrigin; // center
		vec3 m_vOrientation; // rotation
		vec3 m_vSize;
		
		vec3 m_vVertexNormalTemp;
		GLfloat m_vVertexNormalTemp2[108];

	public: // appifanhy right now
		/*so the way it works is that oritation is just rotation, and diamentions is just scaling, so you only gotta translate rotate and scale the 24 points given from the original
		now to constantly update the position according to the overall robots positions at the moment, i can retain the last piece of information, or i can set up a controller like 
		thing to go through the code and refer back the position to me, so the update is constantly something + that different position. 
		now the indices can be used, just update all 8 points, and let the shader pick the ones it wants, you dont need to indivually find out which ones it is using, just calculate them all
		
		mesh program, miught have soemthing to do with glsl program for the shader, have a quick look, see if you can use your framework to coinside with the other open tutorials, instead of 
		ripping it completly out //// mesh will use glsl, maybe somehow intergrate it within the drawframework class?. GLGLGLLGLGLGLGLGLGLGLLGLGLGLLGLGLL
		
		drawing the room, use 3dsmax to show you can import things and shit, the lgihting use a direction light, or something with a spotlight, maybe try get the spotlight to follow the character
		HYPE 
		++++++++++++++++++++++*/

		Cube(vec3 vPos, vec3 vOrigin, float fOrient, vec3 vSize);
		~Cube();
		GLfloat m_vVertexNormal[108];
		GLfloat  m_vPosition[108]; // position

		void render();
		void update(vec3 vposition, float frotateangle, float fnewAngle, vec3 robotpos, bool rotating);
		glm::vec3  evaluateNormal(vec3 v0); // normalised before sent back


	};


}


#endif // ! CUBE_H

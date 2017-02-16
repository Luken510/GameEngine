#pragma once
#ifndef  FLOOR_H
#define FLOOR_H

#include "cube.h"

namespace ecr
{

	class Floor
	{
	private:

		ecr::Cube* theFloor;
		glm::vec3 m_Position;


	public:
		Floor();
		~Floor();

		void DrawFloor();
		void Render();
	};

}


#endif
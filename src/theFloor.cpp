#include "stdafx.h"
#include "theFloor.h"

using namespace ecr;

Floor::Floor()
{
	m_Position = glm::vec3(0, 0, 0);
	DrawFloor();
}


void Floor::DrawFloor()
{
	theFloor = new Cube(glm::vec3(m_Position.x, (m_Position.y - 8.0f), m_Position.z), m_Position, 0.0f, glm::vec3(200, 2, 200));
}

void Floor::Render()
{
	theFloor->render();
}

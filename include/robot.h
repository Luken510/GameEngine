#pragma once
#ifndef  ROBOT_H
#define ROBOT_H

#include "cube.h"


// constants for arm and leg movement states
const char BACKWARD_STATE = 0;
const char FORWARD_STATE = 1;

// index constants for accessing arm and leg array data
const char LEFT = 0;
const char RIGHT = 1;

// index for moving left right, forwards and backwards
const char MOVEFOWARD = 0;
const char MOVEBACKWARD = 1;
const char MOVELEFT = 2;
const char MOVERIGHT = 3;


class Robot
{
private:

	ecr::Cube* Head;
	ecr::Cube* torso;
	ecr::Cube* arm_left;
	ecr::Cube* arm_right;
	ecr::Cube* leg_left;
	ecr::Cube* leg_right;

	vec3 newPosition;
	vec3 oldposition;

	glm::vec3 m_Position;
	glm::vec3 m_Orientation; // where its been rotated
	
	char legStates[2];
	char armStates[2];
	float legAngles[2];
	float armAngles[2];
	int fDirection;
	float fRotationAngle;
	float animationspeed;
	bool bIsAnimated;
	bool bIsRotating;


public:
	Robot();
	~Robot();

	void DrawRobot();
	void Update(float dt);
	void Render();

	void Animated(bool a, int x);

};




#endif
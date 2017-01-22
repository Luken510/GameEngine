#include "stdafx.h"
#include "robot.h"
#include <math.h>
#define _USE_MATH_DEFINES

using namespace ecr;

Robot::Robot()

{
	m_Position = glm::vec3(0, 0, 0);
	m_Orientation = glm::vec3(0, 0, 0);
	vec3 newPosition;
	vec3 oldposition = m_Position;
	fRotationAngle = 180.0f;
	animationspeed = 0.2f;
	bIsAnimated = FALSE;
	bIsRotating = FALSE;
	DrawRobot();
}

Robot::~Robot()
{
	delete Head;
	delete torso;
	delete arm_left;
	delete arm_right;
	delete leg_left;
	delete leg_right;
}

void Robot::DrawRobot()
{
	

	Head = new Cube(glm::vec3(m_Position.x, (m_Position.y + 3.5f), m_Position.z), m_Position, fRotationAngle, glm::vec3(2, 2, 2));
							// position the head relative to the robot   // origin is the robots // orient to the robot // then scale to a certain shape e.g. sqaure
	torso = new Cube(glm::vec3(m_Position.x, m_Position.y, m_Position.z), m_Position, fRotationAngle, glm::vec3(3, 5, 2));
	arm_left = new Cube(glm::vec3((m_Position.x + 2.0f), (m_Position.y - 0.3f), (m_Position.z - 0.5f)), m_Position, fRotationAngle, glm::vec3(1, 4, 1));
	arm_right = new Cube(glm::vec3( (m_Position.x - 2.0f), (m_Position.y - 0.3f), (m_Position.z - 0.5f)), m_Position, fRotationAngle, glm::vec3(1, 4, 1));
	leg_left = new Cube(glm::vec3((m_Position.x - 1.0f), (m_Position.y - 5.3f), (m_Position.z - 0.5f)), m_Position, fRotationAngle, glm::vec3(1, 5, 1));
	leg_right = new Cube(glm::vec3((m_Position.x + 1.0f), (m_Position.y - 5.3f), (m_Position.z - 0.5f)), m_Position, fRotationAngle, glm::vec3(1, 5, 1));
	// TO DO :
	// FEET?

}

void Robot::Render()
{

	Head->render();
	torso->render();
	arm_left->render();
	arm_right->render();
	leg_left->render();
	leg_right->render();                                                  

}

void Robot::Update(float dt)
{
	if (bIsAnimated == TRUE)
	{
		float fOldRotating = fRotationAngle;

		if (dt > 0.1f)
			dt = 0.01f; // reset the timer

		if (fDirection == MOVELEFT)
		{
			bIsRotating = TRUE;
			if (fRotationAngle > (360))
			{
				fRotationAngle = (360);
			}
			fRotationAngle += 0.5f;
		
		}
		else if (fDirection == MOVERIGHT)
		{
			bIsRotating = TRUE;
			if (fRotationAngle < -(360))
			{
				fRotationAngle = -(360);
			}
			fRotationAngle -= 0.5f;
		}

		 oldposition = m_Position;

		switch (fDirection)
		{
		case MOVEFOWARD:
			bIsRotating = FALSE;
			m_Position.x -= sin(((M_PI / 180) * fRotationAngle));
			m_Position.z -= cos(((M_PI / 180) * fRotationAngle));
			 newPosition = m_Position - oldposition;
			break;
		case MOVEBACKWARD:
			bIsRotating = FALSE;
			m_Position.x += sin(((M_PI / 180) * fRotationAngle));
			m_Position.z += cos(((M_PI / 180) * fRotationAngle));
			newPosition = m_Position - oldposition;
			break;
		default:
			break;
		}

		
			// if leg is moving forward, increase angle, else decrease angle
			for (char side = 0; side < 2; side++)
			{
				// arms
				if (armStates[side] == FORWARD_STATE)
					armAngles[side] += animationspeed * 0.05f * dt;
				else
					armAngles[side] -= animationspeed * 0.05f * dt;

				// change state if exceeding angles
				if (armAngles[side] >= glm::radians(15.0f))
					armStates[side] = BACKWARD_STATE;
				else if (armAngles[side] <= -glm::radians(-15.0f))
					armStates[side] = FORWARD_STATE;

				// legs
				if (legStates[side] == FORWARD_STATE)
					legAngles[side] += animationspeed * 0.05f * dt;
				else
					legAngles[side] -= animationspeed * 0.05f * dt;

				// change state if exceeding angles
				if (legAngles[side] >= glm::radians(15.0f))
					legStates[side] = BACKWARD_STATE;
				else if (legAngles[side] <= glm::radians(-15.0f))
					legStates[side] = FORWARD_STATE;
			
			}

			
			float fRotatingDiff = fOldRotating - fRotationAngle;

			Head->update(newPosition, fRotationAngle, 0.0f, oldposition, bIsRotating);
			torso->update(newPosition, fRotationAngle, 0.0f, oldposition, bIsRotating);

			arm_left->update(newPosition, fRotationAngle, armAngles[LEFT], oldposition, bIsRotating);
			arm_right->update(newPosition, fRotationAngle, armAngles[RIGHT], oldposition, bIsRotating);
			leg_left->update(newPosition, fRotationAngle, legAngles[LEFT], oldposition, bIsRotating);
			leg_right->update(newPosition, fRotationAngle, legAngles[RIGHT], oldposition, bIsRotating);

		
	}
}

void Robot::Animated(bool a, int x)
{

  	bIsAnimated = a;
	switch (x)
	{
	case 0: // this is forward
		fDirection = MOVEFOWARD;
		break;

	case 1: // this is backwards
		fDirection = MOVEBACKWARD;
		break;
	case 2: // this is left
		fDirection = MOVELEFT;
		break;
	case 3: // this is right
		fDirection = MOVERIGHT;
		break;

	default:
		break;
	}
}
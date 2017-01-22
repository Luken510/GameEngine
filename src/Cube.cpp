#include "stdafx.h"
#include "cube.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

#include <glm/gtc/type_ptr.hpp>

using namespace ecr;

Cube::Cube(glm::vec3 vPos, vec3 vOrigin, float fOrient, vec3 vSize)
{


	GLfloat cubeVerticies[]{

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f,  
		0.5f,  0.5f,  0.5f,  
		0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f, -0.5f
	};


	int n = 108; // number of times to go around the normal function

	for (int i = 0; i < n; i += 3)
	{
		m_vVertexNormalTemp = evaluateNormal(vec3(cubeVerticies[i], cubeVerticies[i + 1], cubeVerticies[i + 2]));
		m_vVertexNormalTemp2[i] = m_vVertexNormalTemp.x;
		m_vVertexNormalTemp2[i + 1] = m_vVertexNormalTemp.y;
		m_vVertexNormalTemp2[i + 2] = m_vVertexNormalTemp.z;
	}


	mat4 translate = glm::translate(vec3(vPos.x, vPos.y, vPos.z));


	mat4 scale = glm::scale(vec3(vSize.x, vSize.y, vSize.z));

	mat4 rotate = glm::rotate(glm::radians(fOrient), vec3(0.0f, 1.0f, 0.0f));
	
	mat4 transform = translate * rotate  * scale;
	
	

	
	int s = 108; // number of vertices				   
								   // to calculate the new translated, scaled cube
	for (int i = 0; i < s; i += 3)
	{
		vec4 vert = vec4(cubeVerticies[(i)], cubeVerticies[(i + 1)], cubeVerticies[(i + 2)], 1.0f);
		vert = transform * vert;
		m_vPosition[(i)] = vert.x;
		m_vPosition[(i + 1)] = vert.y;
		m_vPosition[(i + 2)] = vert.z;

		vec4 norm = vec4(m_vVertexNormalTemp2[(i)], m_vVertexNormalTemp2[(i + 2)], m_vVertexNormalTemp2[(i + 3)], 1.0f);
		norm = transform * norm;
		m_vVertexNormal[(i)] = norm.x;
		m_vVertexNormal[(i + 1)] = norm.y;
		m_vVertexNormal[(i + 2)] = norm.z;
	}

	/////////////// SET THE VBOS
	gl::GenVertexArrays(1, &m_vaoHandle);
	gl::BindVertexArray(m_vaoHandle);

	gl::GenBuffers(2, m_vboHandle);

	gl::BindBuffer(gl::ARRAY_BUFFER, m_vboHandle[0]);
	gl::BufferData(gl::ARRAY_BUFFER,2* 216, m_vPosition, gl::STATIC_DRAW);
	gl::EnableVertexAttribArray(0);  // Vertex position
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
	

	gl::BindBuffer(gl::ARRAY_BUFFER, m_vboHandle[1]);
	gl::BufferData(gl::ARRAY_BUFFER, 2*216, m_vVertexNormal, gl::STATIC_DRAW);
	gl::VertexAttribPointer((GLuint)1, 3, gl::FLOAT, GLFW_FALSE, 0, ((GLubyte *)NULL + (0)));
	gl::EnableVertexAttribArray(1);  // Vertex normal


	gl::BindVertexArray(0);
	
}


Cube::~Cube()
{}

void Cube::render()
{


	gl::BindVertexArray(m_vaoHandle);
	//gl::DrawElements(gl::TRIANGLES, m_vNumOfIndicies, gl::UNSIGNED_INT, ((GLubyte *)NULL + (0)));
	gl::DrawArrays(gl::TRIANGLES, 0, 108);

}
void Cube::update(vec3 vposition, float frotateangle, float fnewAngle, vec3 robotpos, bool rotating )
{

	if (rotating == FALSE)
	{
		frotateangle = 0;
	}
	else if (rotating == TRUE)
	{
		vposition = vec3(0.0f, 0.0f, 0.0f);
	}

	mat4 anitmationRotate;

	std::cout << vposition.x << " " << vposition.y << " " << vposition.x << std::endl;
	mat4 TempTranslate = glm::translate(-robotpos);
	mat4 TempRotate = glm::rotate(glm::radians(frotateangle/10), vec3(0.0f, 1.0f, 0.0f));
	anitmationRotate = glm::rotate(glm::radians(fnewAngle), vec3(1.0f, 0.0f, 0.0f));
	mat4 TempTransform = TempRotate * TempTranslate;
	if (!fnewAngle == 0)
		mat4 TempTransform = anitmationRotate * TempRotate * TempTranslate;
	else
		mat4 TempTransform = TempRotate * TempTranslate;
	


	int y = 108; // number of vertices				   
				 // to calculate the new translated, scaled cube
	for (int i = 0; i < y; i += 3)
	{
		vec4 tempv = vec4(m_vPosition[i], m_vPosition[i + 1], m_vPosition[i + 2], 1.0f);
		tempv = TempTransform * tempv;
		m_vPosition[(i)] = tempv.x;
		m_vPosition[(i + 1)] = tempv.y;
		m_vPosition[(i + 2)] = tempv.z;

		vec4 tempnorm = vec4(m_vVertexNormal[(i)], m_vVertexNormal[(i + 2)], m_vVertexNormal[(i + 3)], 1.0f);
		tempnorm = TempTransform * tempnorm;
		m_vVertexNormal[(i)] = tempnorm.x;
		m_vVertexNormal[(i + 1)] = tempnorm.y;	
		m_vVertexNormal[(i + 2)] = tempnorm.z;  // have to set the robot to the origin, rotate then move back
	}

	vec3 vBackToNewPos = robotpos + vposition;

	mat4 BackToNewPos = glm::translate(vBackToNewPos);

	mat4 TempTransform2 = BackToNewPos;

	for (int i = 0; i < y; i += 3)
	{
		vec4 tempv2 = vec4(m_vPosition[i], m_vPosition[i + 1], m_vPosition[i + 2], 1.0f);
		tempv2 = TempTransform2 * tempv2;
		m_vPosition[(i)] = tempv2.x;
		m_vPosition[(i + 1)] = tempv2.y;
		m_vPosition[(i + 2)] = tempv2.z;

		vec4 tempnorm2 = vec4(m_vVertexNormal[(i)], m_vVertexNormal[(i + 2)], m_vVertexNormal[(i + 3)], 1.0f);
		tempnorm2 = TempTransform2 * tempnorm2;
		m_vVertexNormal[(i)] = tempnorm2.x;
		m_vVertexNormal[(i + 1)] = tempnorm2.y;
		m_vVertexNormal[(i + 2)] = tempnorm2.z;
	}


	gl::GenVertexArrays(1, &m_vaoHandle);
	gl::BindVertexArray(m_vaoHandle);

	gl::GenBuffers(2, m_vboHandle);

	gl::BindBuffer(gl::ARRAY_BUFFER, m_vboHandle[0]);
	gl::BufferData(gl::ARRAY_BUFFER, 2 * 216, m_vPosition, gl::STATIC_DRAW);
	gl::EnableVertexAttribArray(0);  // Vertex position
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));

	gl::BindVertexArray(0);
}

vec3 Cube::evaluateNormal(vec3 v0)
{
	float x1 = pow(v0.x, 2);
	float y1 = pow(v0.y, 2);
	float z1 = pow(v0.z, 2);
	float mag1 = glm::sqrt(x1 + y1 + z1);
	glm::vec3 dv = glm::vec3( (v0.x / mag1), (v0.y / mag1), (v0.z / mag1));

	return dv;

}
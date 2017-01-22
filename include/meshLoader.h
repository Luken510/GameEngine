#pragma once
#ifndef MESHLOADER_H
#define MESHLOADER_H
using namespace std;
#include <glm\glm.hpp>
#include "gl_core_4_3.hpp"
#include "glslprogram.h"
#include <string>
#include <vector>
#include <sstream>



	struct Vertex {
		glm::vec3 m_vPosition;
		glm::vec3 m_vNormal;
		glm::vec2 m_vTexCoords;
	};

	struct Texture {
		GLuint m_id;
		string sType;
		aiString sPath;
	};
namespace egf
{
	class Mesh {
	public:
		// this is the mesh data
		vector<Vertex> mv_Vertices;
		vector<GLuint> mv_Indices;
		vector<Texture> mv_Textures;

		Mesh(vector<Vertex> vVertices, vector<GLuint> vIndices, vector<Texture> vTextures);
		void Render(GLSLProgram* shader);

	private:

		GLuint VAO, VBO, EBO; // for rendering

		void setupMesh();

	};
}

#endif
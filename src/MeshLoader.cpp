#include "stdafx.h"
#include "meshLoader.h"

using namespace egf;

Mesh::Mesh(vector<Vertex> vVertices, vector<GLuint> VIndices, vector<Texture> vTextures)
{
	this->mv_Vertices = vVertices;
	this->mv_Indices = VIndices;
	this->mv_Textures = vTextures;
	this->setupMesh();
}

void Mesh::setupMesh()
{
	gl::GenVertexArrays(1, &this->VAO);
	gl::GenBuffers(1, &this->VBO);
	gl::GenBuffers(1, &this->EBO);

	gl::BindVertexArray(this->VAO); 

	gl::BindBuffer(gl::ARRAY_BUFFER, this->VBO); // setup data VBO
	gl::BufferData(gl::ARRAY_BUFFER, this->mv_Vertices.size() * sizeof(Vertex), &this->mv_Vertices[0], gl::STATIC_DRAW);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, this->EBO); // set up element VBO
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, this->mv_Indices.size() * sizeof(GLuint), &this->mv_Indices[0], gl::STATIC_DRAW);

	// Vertex Positions
	gl::EnableVertexAttribArray(0);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, sizeof(Vertex), (GLvoid*)0);

	// Vertex Normals
	gl::EnableVertexAttribArray(1);
	gl::VertexAttribPointer(1, 3, gl::FLOAT, FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, m_vNormal));

	// Vertex Texture Co-ords
	gl::EnableVertexAttribArray(2);
	gl::VertexAttribPointer(2, 2, gl::FLOAT, FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, m_vTexCoords));

	gl::BindVertexArray(0);

}

void Mesh::Render(GLSLProgram* shader)
{
	GLuint iDiffuseNr = 1;
	GLuint iSpecularNr = 1;
	
	for (GLuint i = 0; 1 < (this->mv_Textures.size() - 1); i++)
	{
		gl::ActiveTexture(gl::TEXTURE0 + i); // activating the proper texture unit before binding the data

		//get the texture number

		string sName = this->mv_Textures[i].sType;
		string sNumber = (sName == "texture_diffuse") ? std::to_string(iDiffuseNr++) : std::to_string(iSpecularNr);
		std::cout << "sName" << std::endl;
		std::cout << "sNumber" << std::endl;


		gl::Uniform1f(gl::GetUniformLocation(shader->getHandle(), ("material." + sName + sNumber).c_str()), i); // now finds the correct location in the shader using the above gluint to string function
		gl::BindTexture(gl::TEXTURE_2D, this->mv_Textures[i].m_id);
	}

	gl::ActiveTexture(gl::TEXTURE0);

	gl::BindVertexArray(this->VAO);
	gl::DrawElements(gl::TRIANGLES, this->mv_Indices.size(), gl::UNSIGNED_INT, 0);
	gl::BindVertexArray(0);
}
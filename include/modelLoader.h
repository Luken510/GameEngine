#pragma once
#ifndef MODELLOADER_H
#define MODELLOADER_H
#include "gl_core_4_3.hpp"
#include <glm\glm.hpp>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "glslprogram.h"
#include "meshLoader.h"



GLint TextureFromFile(const char* path, string directory);

namespace egf
{
	class Model
	{
	public:

		
		Model(GLchar* path);
		void Render(GLSLProgram* shader);

	private:

		vector<Mesh> mMeshes;
		string sDirectory;
		vector<Texture> tTexturesLoaded;
		
		void LoadModel(string sPath);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> tLoadMaterialTextures(aiMaterial* mat, aiTextureType type, string sTypeName);
		

	};
}

#endif // !MODELLOADER_H

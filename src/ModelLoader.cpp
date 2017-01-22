#include "stdafx.h"
#include "glslprogram.h"
#include "modelLoader.h"
#include "SOIL2/SOIL2.h"



using namespace egf;


Model::Model(GLchar* path) 

{
	this->LoadModel(path);

}


void Model::Render(GLSLProgram* shader)
{
	for (GLuint i = 0; i < this->mMeshes.size(); i++)
		this->mMeshes[i].Render(shader);

}

void Model::LoadModel(string sPath)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(sPath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	this->sDirectory = sPath.substr(0, sPath.find_last_of('/'));

	this->ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	// proces all of the node's meshes
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->mMeshes.push_back(this->ProcessMesh(mesh, scene));
	}
	// process all of its childrens if it has any and do the same
	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}

}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vVertices;
	vector<GLuint> vIndices;
	vector<Texture> vTextures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vVertex;

		glm::vec3 v3Vector; // assimp uses its own vector class that doesnt convert to glm's vec3

		v3Vector.x = mesh->mVertices[i].x;
		v3Vector.y = mesh->mVertices[i].y;
		v3Vector.z = mesh->mVertices[i].z;
		vVertex.m_vPosition = v3Vector;

		v3Vector.x = mesh->mNormals[i].x;
		v3Vector.y = mesh->mNormals[i].y;
		v3Vector.z = mesh->mNormals[i].z;
		vVertex.m_vNormal = v3Vector;

		if (mesh->mTextureCoords[0]) // if it has texture coords
		{
			glm::vec2 v2Vector;
			v2Vector.x = mesh->mTextureCoords[0][i].x;
			v2Vector.y = mesh->mTextureCoords[0][i].y;
			vVertex.m_vTexCoords = v2Vector;
		}
		else
			vVertex.m_vTexCoords = glm::vec2(0.0f, 0.0f);

		vVertices.push_back(vVertex);
	}
		
	// now to iterate through each of the mesh's faces and retrieve the indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		// retrieve all the indices of the face and store them in the idices vector
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			vIndices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN
		//diffuse
		vector<Texture> diffuseMaps = this->tLoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		vTextures.insert(vTextures.end(), diffuseMaps.begin(), diffuseMaps.end());
		//specular
		vector<Texture> specularMaps = this->tLoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");

		vTextures.insert(vTextures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vVertices, vIndices, vTextures);
}

vector<Texture> Model::tLoadMaterialTextures(aiMaterial* mat, aiTextureType type, string sTypeName)
{
	vector<Texture> textures;
	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{

		aiString str;
		mat->GetTexture(type, i, &str);
		GLboolean skip = false;
		for (GLuint j = 0; j < tTexturesLoaded.size(); j++)
		{
			if (tTexturesLoaded[j].sPath == str)
			{
				textures.push_back(tTexturesLoaded[j]);
				skip = TRUE;
				break;
			}
		} // if the texture hasn't already been loaded in
		if (!skip)
		{
			Texture tTexture;
			tTexture.m_id = TextureFromFile(str.C_Str(), this->sDirectory);
			tTexture.sType = sTypeName;
			tTexture.sPath = str;
			textures.push_back(tTexture);
		}
	}
	return textures;
}


GLint TextureFromFile(const char* path, string directory)
{

	std::cout << path << std::endl;
	//generate texture ID and load Texture data
	string filename = string(path);

	filename = directory + '/' + filename;
	GLuint tTextureID;

	gl::GenTextures(1, &tTextureID);
	int width, height;

	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	std::cout << image << std::endl;
	//Assign Texture to the ID

	gl::BindTexture(gl::TEXTURE_2D, tTextureID);
	gl::TexImage2D(gl::TEXTURE_2D, 0, gl::RGB, width, height, 0, gl::RGB, gl::UNSIGNED_BYTE, image);
	gl::GenerateMipmap(gl::TEXTURE_2D);

	// Parameters
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_S, gl::REPEAT);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_WRAP_T, gl::REPEAT);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MIN_FILTER, gl::LINEAR_MIPMAP_LINEAR);
	gl::TexParameteri(gl::TEXTURE_2D, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::BindTexture(gl::TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return tTextureID;
}

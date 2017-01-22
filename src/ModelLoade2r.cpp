/*#include "glslprogram.h"
#include "modelLoader.h"



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

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
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

	}

	// now to iterate through each of the mesh's faces and retrieve the indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		// retrieve all the indices of the face and store them in the idices vector
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			vIndices.push_back(face.mIndices[j]); // TO DO FROM HERE
	}

}

vector<Texture> tLoadMaterialTextures(aiMaterial* mat, aiTextureType type, string sTypeName);*/
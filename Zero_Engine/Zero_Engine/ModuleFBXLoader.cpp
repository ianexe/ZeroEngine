#include "Globals.h"
#include "Application.h"
#include "ModuleFBXLoader.h"

#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

#include "ModuleGOManager.h"

#include "Assimp\include\cimport.h"
#include "Assimp\include\scene.h"
#include "Assimp\include\postprocess.h"
#include "Assimp\include\cfileio.h"

#include "Glew\include\glew.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")
#pragma comment (lib, "Glew/libx86/glew32.lib")

#include "Devil\include\il.h"
#include "Devil\include\ilu.h"
#include "Devil\include\ilut.h"

#pragma comment (lib, "Devil/libx86/DevIL.lib")
#pragma comment (lib, "Devil/libx86/ILU.lib")
#pragma comment (lib, "Devil/libx86/ILUT.lib")

ModuleFBXLoader::ModuleFBXLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleFBXLoader::~ModuleFBXLoader()
{
}

bool ModuleFBXLoader::Init()
{
	bool ret = true;

	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	//Initializing DevIL
	ilInit();
	iluInit();
	ilutInit();

	ilutRenderer(ILUT_OPENGL);

	return ret;
}

bool ModuleFBXLoader::CleanUp()
{
	bool ret = true;

	aiDetachAllLogStreams();

	return ret;
}

vector<Mesh> ModuleFBXLoader::LoadMesh(const char* path)
{
	vector<Mesh> ret;

	//NOTE: Loading buff from FS, this may be changed with XML
	char* buff;
	uint size = App->fs->Load(path, &buff);

	const aiScene* scene = aiImportFileFromMemory(buff, size, aiProcessPreset_TargetRealtime_MaxQuality, NULL);

	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			Mesh m;
			aiMesh* new_mesh = scene->mMeshes[i];

			// copy vertices
			m.num_vertices = new_mesh->mNumVertices;
			m.vertices = new float[m.num_vertices * 3];
			memcpy(m.vertices, new_mesh->mVertices, sizeof(float) * m.num_vertices * 3);
			LOG("New mesh with %d vertices", m.num_vertices);

			// vertices to buffer
			glGenBuffers(1, (GLuint*)&(m.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, m.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m.num_vertices, m.vertices, GL_STATIC_DRAW);

			// copy indices
			if (new_mesh->HasFaces())
			{
				m.num_indices = new_mesh->mNumFaces * 3;
				m.indices = new uint[m.num_indices]; // assume each face is a triangle
				for (uint i = 0; i < new_mesh->mNumFaces; ++i)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
						memcpy(&m.indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
				}
				// indices to buffer
				glGenBuffers(1, (GLuint*)&(m.id_indices));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_indices);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m.num_indices, m.indices, GL_STATIC_DRAW);
			}

			
			// copy normals
			if (new_mesh->HasNormals())
			{
				m.num_normals = new_mesh->mNumVertices;
				m.normals = new float[m.num_normals * 3]; // assume each face is a triangle
				for (int i = 0; i < new_mesh->mNumVertices; ++i)
				{
					memcpy(&m.normals[i * 3], &new_mesh->mNormals[i].x, sizeof(float));
					memcpy(&m.normals[i * 3 + 1], &new_mesh->mNormals[i].y, sizeof(float));
					memcpy(&m.normals[i * 3 + 2], &new_mesh->mNormals[i].z, sizeof(float));
				}
				// normals to buffer
				glGenBuffers(1, (GLuint*)&(m.id_normals));
				glBindBuffer(GL_ARRAY_BUFFER, m.id_normals);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m.num_normals, m.normals, GL_STATIC_DRAW);
			}
			

			// copy UVs
			if (new_mesh->HasTextureCoords(0))
			{
				m.num_uvs = new_mesh->mNumVertices;
				m.uvs = new float[m.num_uvs * 2];
				for (int i = 0; i < new_mesh->mNumVertices; ++i)
				{
					memcpy(&m.uvs[i * 2], &new_mesh->mTextureCoords[0][i].x, sizeof(float));
					memcpy(&m.uvs[(i * 2) + 1], &new_mesh->mTextureCoords[0][i].y, sizeof(float));
				}
				// UVs to buffer
				glGenBuffers(1, (GLuint*)&(m.id_uvs));
				glBindBuffer(GL_ARRAY_BUFFER, m.id_uvs);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * m.num_uvs, m.uvs, GL_STATIC_DRAW);
			}
			

			ret.push_back(m);
		}
		aiReleaseImport(scene);
	}

	else
	{
		LOG("Error loading scene %s", path);
	}

	delete[] buff;

	return ret;
}

void ModuleFBXLoader::LoadMesh(const char* path, GameObject* go)
{
	GameObject* to_add = go;

	if (go == nullptr)
		to_add = App->go->root;

	//NOTE: Loading buff from FS, this may be changed with XML
	char* buff;
	uint size = App->fs->Load(path, &buff);

	const aiScene* scene = aiImportFileFromMemory(buff, size, aiProcessPreset_TargetRealtime_MaxQuality, NULL);

	aiVector3D translation;
	aiVector3D scaling;
	aiQuaternion rotation;

	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			if (go->FindComponent(COMP_MESH))
			{
				to_add = App->go->AddGameObject(go->parent);
			}

			Mesh m;
			aiMesh* new_mesh = scene->mMeshes[i];



			float3 pos(translation.x, translation.y, translation.z);
			float3 scale(scaling.x, scaling.y, scaling.z);
			Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);

			ComponentTransform* trans = (ComponentTransform*)to_add->AddComponent(COMP_TRANSFORM);
			trans->SetPosition(pos);
			trans->SetScale(scale);
			trans->SetRotation(rot);

			// copy vertices
			m.num_vertices = new_mesh->mNumVertices;
			m.vertices = new float[m.num_vertices * 3];
			memcpy(m.vertices, new_mesh->mVertices, sizeof(float) * m.num_vertices * 3);
			LOG("New mesh with %d vertices", m.num_vertices);

			// vertices to buffer
			glGenBuffers(1, (GLuint*)&(m.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, m.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m.num_vertices, m.vertices, GL_STATIC_DRAW);

			// copy indices
			if (new_mesh->HasFaces())
			{
				m.num_indices = new_mesh->mNumFaces * 3;
				m.indices = new uint[m.num_indices]; // assume each face is a triangle
				for (uint i = 0; i < new_mesh->mNumFaces; ++i)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
						memcpy(&m.indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
				}
				// indices to buffer
				glGenBuffers(1, (GLuint*)&(m.id_indices));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_indices);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m.num_indices, m.indices, GL_STATIC_DRAW);
			}


			// copy normals
			if (new_mesh->HasNormals())
			{
				m.num_normals = new_mesh->mNumVertices;
				m.normals = new float[m.num_normals * 3]; // assume each face is a triangle
				for (int i = 0; i < new_mesh->mNumVertices; ++i)
				{
					memcpy(&m.normals[i * 3], &new_mesh->mNormals[i].x, sizeof(float));
					memcpy(&m.normals[i * 3 + 1], &new_mesh->mNormals[i].y, sizeof(float));
					memcpy(&m.normals[i * 3 + 2], &new_mesh->mNormals[i].z, sizeof(float));
				}
				// normals to buffer
				glGenBuffers(1, (GLuint*)&(m.id_normals));
				glBindBuffer(GL_ARRAY_BUFFER, m.id_normals);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m.num_normals, m.normals, GL_STATIC_DRAW);
			}


			// copy UVs
			if (new_mesh->HasTextureCoords(0))
			{
				m.num_uvs = new_mesh->mNumVertices;
				m.uvs = new float[m.num_uvs * 2];
				for (int i = 0; i < new_mesh->mNumVertices; ++i)
				{
					memcpy(&m.uvs[i * 2], &new_mesh->mTextureCoords[0][i].x, sizeof(float));
					memcpy(&m.uvs[(i * 2) + 1], &new_mesh->mTextureCoords[0][i].y, sizeof(float));
				}
				// UVs to buffer
				glGenBuffers(1, (GLuint*)&(m.id_uvs));
				glBindBuffer(GL_ARRAY_BUFFER, m.id_uvs);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * m.num_uvs, m.uvs, GL_STATIC_DRAW);
			}

			ComponentMesh* add_mesh = (ComponentMesh*)to_add->AddComponent(COMP_MESH);
			add_mesh->SetMesh(m);

			if (scene->HasMaterials())
			{
				aiMaterial* material = scene->mMaterials[new_mesh->mMaterialIndex];
				uint numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);

				aiString path;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

				if (path.length > 1)
				{
					std::string str1 = path.data;
					str1.erase(0, 12);
					std::string str2 = "Game/Town/";
					str2 += str1;

					Texture* _tex = new Texture;
					_tex = LoadTexture(str2.c_str());

					ComponentMaterial* add_material = (ComponentMaterial*)to_add->AddComponent(COMP_MATERIAL);
					add_material->SetTexture(_tex);
				}
			}
		}
		aiReleaseImport(scene);
	}

	else
	{
		LOG("Error loading scene %s", path);
	}

	delete[] buff;

	//------------------------------------------
	/*
	GameObject* to_add = go;

	if (go == nullptr)
		return false;

	//NOTE: Loading buff from FS, this may be changed with XML
	char* buff;
	uint size = App->fs->Load(path, &buff);

	aiVector3D translation;
	aiVector3D scaling;
	aiQuaternion rotation;

	scene->mRootNode->mTransformation.Decompose(scaling, rotation, translation);

	float3 pos(translation.x, translation.y, translation.z);
	float3 scale(scaling.x, scaling.y, scaling.z);
	Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);

	ComponentTransform* trans = (ComponentTransform*)to_add->AddComponent(COMP_TRANSFORM);
	trans->SetPosition(pos);
	trans->SetScale(scale);
	trans->SetRotation(rot);

	if (scene != nullptr && scene->HasMeshes())
	{
		for (int i = 0; i < scene->mRootNode->mNumChildren; i++)
		{
			LoadNode(node->mChildren[i], scene, go);
		}
		aiReleaseImport(scene);
	}

	else
	{
	LOG("Error loading scene %s", path);
	}

	delete[] buff;
	*/
	//------------------------------------------
}

bool ModuleFBXLoader::LoadFBXRoot(const char* path, GameObject* go)
{
	if (go == nullptr)
		return false;

	//NOTE: Loading buff from FS, this may be changed with XML
	char* buff;
	uint size = App->fs->Load(path, &buff);

	const aiScene* scene = aiImportFileFromMemory(buff, size, aiProcessPreset_TargetRealtime_MaxQuality, NULL);

	aiVector3D translation;
	aiVector3D scaling;
	aiQuaternion rotation;

	scene->mRootNode->mTransformation.Decompose(scaling, rotation, translation);

	float3 pos(translation.x, translation.y, translation.z);
	float3 scale(scaling.x, scaling.y, scaling.z);
	Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);

	ComponentTransform* trans = (ComponentTransform*)go->AddComponent(COMP_TRANSFORM);
	trans->SetPosition(pos);
	trans->SetScale(scale);
	trans->SetRotation(rot);

	go->SetName(scene->mRootNode->mName.data);

	if (scene != nullptr)
	{
		for (int i = 0; i < scene->mRootNode->mNumChildren; ++i)
		{
			if (scene->mRootNode->mNumChildren > 0)
			{
				LoadNode(scene->mRootNode->mChildren[i], scene, go);
			}
		}
		aiReleaseImport(scene);
	}

	else
	{
		LOG("Error loading scene %s", path);
	}

	delete[] buff;

	return true;
}

void ModuleFBXLoader::LoadNode(aiNode* node, const aiScene* scene, GameObject* go)
{
	GameObject* new_go = App->go->AddGameObject(go);
	new_go->SetName(node->mName.data);
	
	for (int i = 0; i < node->mNumChildren; ++i)
	{
		if (node->mNumChildren > 0)
		{
			LoadNode(node->mChildren[i], scene, new_go);
		}
	}
	
	//----------------------------
	// Use scene->mNumMeshes to iterate on scene->mMeshes array
	if (node->mNumMeshes > 0)
	{
		for (int j = 0; j < node->mNumMeshes; j++)
		{
			if (new_go->FindComponent(COMP_MESH))
			{
				new_go = App->go->AddGameObject(go);
				new_go->SetName(node->mName.data);
			}
			Mesh m;
			aiMesh* new_mesh = scene->mMeshes[node->mMeshes[j]];

			aiVector3D translation;
			aiVector3D scaling;
			aiQuaternion rotation;
			node->mTransformation.Decompose(scaling, rotation, translation);
			float3 pos(translation.x, translation.y, translation.z);
			float3 scale(scaling.x, scaling.y, scaling.z);
			Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);

			ComponentTransform* trans = (ComponentTransform*)new_go->AddComponent(COMP_TRANSFORM);
			trans->SetPosition(pos);
			trans->SetScale(scale);
			trans->SetRotation(rot);

			// copy vertices
			m.num_vertices = new_mesh->mNumVertices;
			m.vertices = new float[m.num_vertices * 3];
			memcpy(m.vertices, new_mesh->mVertices, sizeof(float) * m.num_vertices * 3);
			LOG("New mesh with %d vertices", m.num_vertices);

			// vertices to buffer
			glGenBuffers(1, (GLuint*)&(m.id_vertices));
			glBindBuffer(GL_ARRAY_BUFFER, m.id_vertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m.num_vertices, m.vertices, GL_STATIC_DRAW);

			// copy indices
			if (new_mesh->HasFaces())
			{
				m.num_indices = new_mesh->mNumFaces * 3;
				m.indices = new uint[m.num_indices]; // assume each face is a triangle
				for (uint i = 0; i < new_mesh->mNumFaces; ++i)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
						memcpy(&m.indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
				}
				// indices to buffer
				glGenBuffers(1, (GLuint*)&(m.id_indices));
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.id_indices);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * m.num_indices, m.indices, GL_STATIC_DRAW);
			}


			// copy normals
			if (new_mesh->HasNormals())
			{
				m.num_normals = new_mesh->mNumVertices;
				m.normals = new float[m.num_normals * 3]; // assume each face is a triangle
				for (int i = 0; i < new_mesh->mNumVertices; ++i)
				{
					memcpy(&m.normals[i * 3], &new_mesh->mNormals[i].x, sizeof(float));
					memcpy(&m.normals[i * 3 + 1], &new_mesh->mNormals[i].y, sizeof(float));
					memcpy(&m.normals[i * 3 + 2], &new_mesh->mNormals[i].z, sizeof(float));
				}
				// normals to buffer
				glGenBuffers(1, (GLuint*)&(m.id_normals));
				glBindBuffer(GL_ARRAY_BUFFER, m.id_normals);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * m.num_normals, m.normals, GL_STATIC_DRAW);
			}


			// copy UVs
			if (new_mesh->HasTextureCoords(0))
			{
				m.num_uvs = new_mesh->mNumVertices;
				m.uvs = new float[m.num_uvs * 2];
				for (int i = 0; i < new_mesh->mNumVertices; ++i)
				{
					memcpy(&m.uvs[i * 2], &new_mesh->mTextureCoords[0][i].x, sizeof(float));
					memcpy(&m.uvs[(i * 2) + 1], &new_mesh->mTextureCoords[0][i].y, sizeof(float));
				}
				// UVs to buffer
				glGenBuffers(1, (GLuint*)&(m.id_uvs));
				glBindBuffer(GL_ARRAY_BUFFER, m.id_uvs);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * m.num_uvs, m.uvs, GL_STATIC_DRAW);
			}

			ComponentMesh* add_mesh = (ComponentMesh*)new_go->AddComponent(COMP_MESH);
			add_mesh->SetMesh(m);

			if (scene->HasMaterials())
			{
				aiMaterial* material = scene->mMaterials[new_mesh->mMaterialIndex];
				uint numTextures = material->GetTextureCount(aiTextureType_DIFFUSE);

				aiString path;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &path);

				if (path.length > 1)
				{
					std::string str1 = path.data;
					str1.erase(0, str1.find_last_of("\\")+1);

					std::string str2 = "Game/Textures/";
					str2 += str1;

					Texture* _tex = new Texture;
					_tex = LoadTexture(str2.c_str());

					ComponentMaterial* add_material = (ComponentMaterial*)new_go->AddComponent(COMP_MATERIAL);
					add_material->SetTexture(_tex);
				}
			}
		}
	}

	else
	{
		aiVector3D translation;
		aiVector3D scaling;
		aiQuaternion rotation;
		node->mTransformation.Decompose(scaling, rotation, translation);
		float3 pos(translation.x, translation.y, translation.z);
		float3 scale(scaling.x, scaling.y, scaling.z);
		Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);

		ComponentTransform* trans = (ComponentTransform*)new_go->AddComponent(COMP_TRANSFORM);
		trans->SetPosition(pos);
		trans->SetScale(scale);
		trans->SetRotation(rot);
	}
	//----------------------------

}

Texture* ModuleFBXLoader::LoadTexture(const char* path)
{
	Texture* ret = new Texture;

	uint image;

	ilGenImages(1, &image);
	ilBindImage(image);

	ilLoadImage(path);
	ret->width = ilGetInteger(IL_IMAGE_WIDTH);
	ret->height = ilGetInteger(IL_IMAGE_HEIGHT);

	ret->id = ilutGLBindTexImage();

	ilDeleteImages(1, &image);

	return ret;
}
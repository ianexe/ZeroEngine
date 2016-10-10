#include "Globals.h"
#include "Application.h"
#include "ModuleFBXLoader.h"

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

Texture ModuleFBXLoader::LoadTexture(const char* path)
{
	Texture ret;

	uint image;

	ilGenImages(1, &image);
	ilBindImage(image);

	ilLoadImage(path);
	iluFlipImage();
	ret.width = ilGetInteger(IL_IMAGE_WIDTH);
	ret.height = ilGetInteger(IL_IMAGE_HEIGHT);

	ret.id = ilutGLBindTexImage();

	ilDeleteImages(1, &image);

	return ret;
}
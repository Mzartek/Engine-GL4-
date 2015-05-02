#include "AssimpTool.hpp"
#include <Engine/tools/ControllerMemory.hpp>

const aiScene *Engine::AssimpTool::openFile(Assimp::Importer &importer, const GLchar *inFile)
{
	const aiScene *pScene = importer.ReadFile(inFile, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes);
	if (!pScene)
	{
		std::string error = "Failed to load model File: ";
		error.append(inFile + '\n');
		error.append(importer.GetErrorString());
		std::cerr << error << std::endl;
		abort();
	}

	return pScene;
}

std::pair<std::vector<Engine::StaticMesh::Vertex>, std::vector<GLuint>> Engine::AssimpTool::loadStaticVertices(const aiMesh *mesh)
{
	std::pair<std::vector<StaticMesh::Vertex>, std::vector<GLuint>> vertices;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
		const aiVector3D pPos = mesh->mVertices[i];
		const aiVector3D pTexCoord = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : Zero3D;
		const aiVector3D pNormal = mesh->HasNormals() ? mesh->mNormals[i] : Zero3D;
		const aiVector3D pTangent = mesh->HasTangentsAndBitangents() ? mesh->mTangents[i] : Zero3D;

		StaticMesh::Vertex newVertex = {
			{ pPos.x, pPos.y, pPos.z },
			{ pTexCoord.x, pTexCoord.y },
			{ pNormal.x, pNormal.y, pNormal.z },
			{ pTangent.x, pTangent.y, pTangent.z }
		};

		vertices.first.push_back(newVertex);
	}

	std::vector<GLuint> indices;
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		vertices.second.push_back(mesh->mFaces[i].mIndices[0]);
		vertices.second.push_back(mesh->mFaces[i].mIndices[1]);
		vertices.second.push_back(mesh->mFaces[i].mIndices[2]);
	}

	return vertices;
}

std::pair<std::vector<Engine::SkeletalMesh::Vertex>, std::vector<GLuint>> Engine::AssimpTool::loadSkeletalVertices(const aiMesh *mesh, std::map<GLuint, GLuint> &map_vertex)
{
	std::pair<std::vector<SkeletalMesh::Vertex>, std::vector<GLuint>> vertices;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
		const aiVector3D pPos = mesh->mVertices[i];
		const aiVector3D pTexCoord = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : Zero3D;
		const aiVector3D pNormal = mesh->HasNormals() ? mesh->mNormals[i] : Zero3D;
		const aiVector3D pTangent = mesh->HasTangentsAndBitangents() ? mesh->mTangents[i] : Zero3D;

		SkeletalMesh::Vertex newVertex = {
			{ pPos.x, pPos.y, pPos.z },
			{ pTexCoord.x, pTexCoord.y },
			{ pNormal.x, pNormal.y, pNormal.z },
			{ pTangent.x, pTangent.y, pTangent.z },
			{ 0, 0, 0, 0 }, { 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }, { 0, 0, 0, 0 }
		};

		map_vertex[i] = 0;

		vertices.first.push_back(newVertex);
	}

	std::vector<GLuint> indices;
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		vertices.second.push_back(mesh->mFaces[i].mIndices[0]);
		vertices.second.push_back(mesh->mFaces[i].mIndices[1]);
		vertices.second.push_back(mesh->mFaces[i].mIndices[2]);
	}

	return vertices;
}

Engine::Material *Engine::AssimpTool::loadMaterial(const aiMaterial *material, const std::string &dir, std::set<Engine::Object *> *tObject)
{
	Material *newMaterial = new_ref(Material);
	tObject->insert(newMaterial);

	const aiTextureType _textureType[] = {
		aiTextureType_DIFFUSE, aiTextureType_SPECULAR,
		aiTextureType_AMBIENT, aiTextureType_EMISSIVE,
		aiTextureType_SHININESS, aiTextureType_OPACITY,
		aiTextureType_HEIGHT, aiTextureType_NORMALS,
		aiTextureType_DISPLACEMENT, aiTextureType_LIGHTMAP,
	};

	// Textures
	for (GLuint i = 0; i < (sizeof _textureType / sizeof *_textureType); i++)
	{
		aiString path;
		if (material->GetTexture(_textureType[i], 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
		{
			std::string filePath = dir + path.C_Str();
			Texture2D *newTexture = new_ref(Texture2D);
			tObject->insert(newTexture);

			newTexture->loadFromFile(filePath.c_str());

			switch (_textureType[i])
			{
			case aiTextureType_DIFFUSE:
				newMaterial->setDiffuseTexture(newTexture);
				break;
			case aiTextureType_SPECULAR:
				newMaterial->setSpecularTexture(newTexture);
				break;
			case aiTextureType_AMBIENT:
				newMaterial->setAmbientTexture(newTexture);
				break;
			case aiTextureType_EMISSIVE:
				newMaterial->setEmissiveTexture(newTexture);
				break;
			case aiTextureType_SHININESS:
				newMaterial->setShininessTexture(newTexture);
				break;
			case aiTextureType_OPACITY:
				newMaterial->setOpacityTexture(newTexture);
				break;
			case aiTextureType_HEIGHT:
				newMaterial->setBumpMap(newTexture);
				break;
			case aiTextureType_NORMALS:
				newMaterial->setNormalMap(newTexture);
				break;
			case aiTextureType_DISPLACEMENT:
				newMaterial->setDisplacementMap(newTexture);
				break;
			case aiTextureType_LIGHTMAP:
				newMaterial->setLightMap(newTexture);
				break;
			default:
				break;
			}
		}
	}

	aiColor4D tmp;

	material->Get(AI_MATKEY_COLOR_DIFFUSE, tmp);
	newMaterial->setDiffuse(glm::vec3(tmp.r, tmp.g, tmp.b));

	material->Get(AI_MATKEY_COLOR_SPECULAR, tmp);
	newMaterial->setSpecular(glm::vec3(tmp.r, tmp.g, tmp.b));

	material->Get(AI_MATKEY_COLOR_AMBIENT, tmp);
	newMaterial->setAmbient(glm::vec3(tmp.r, tmp.g, tmp.b));

	material->Get(AI_MATKEY_COLOR_EMISSIVE, tmp);
	newMaterial->setEmissive(glm::vec3(tmp.r, tmp.g, tmp.b));

	material->Get(AI_MATKEY_SHININESS, tmp);
	newMaterial->setShininess(tmp.r);

	material->Get(AI_MATKEY_OPACITY, tmp);
	newMaterial->setOpacity(tmp.r);

	return newMaterial;
}

std::vector<glm::mat4> Engine::AssimpTool::loadBones(const aiMesh *mesh,
	GLuint &bone_index, std::vector<Engine::SkeletalMesh::Vertex> &vertices, std::map<GLuint, GLuint> &map_vertex)
{
	std::vector<glm::mat4> vector_vertices;
	aiMatrix4x4 tmp_matrix0;
	glm::mat4 tmp_matrix1;

	for (GLuint i = 0; i < mesh->mNumBones; i++)
	{
		tmp_matrix0 = mesh->mBones[i]->mOffsetMatrix.Transpose();
		memcpy(&tmp_matrix1, &tmp_matrix0, sizeof(glm::mat4));
		vector_vertices.push_back(tmp_matrix1);

		for (GLuint j = 0; j < mesh->mBones[i]->mNumWeights; j++)
		{
			GLuint vertex_index = mesh->mBones[i]->mWeights[j].mVertexId;
			GLuint index = map_vertex[vertex_index]++;

			if (index < 4)
			{
				vertices[vertex_index].index0[index] = bone_index;
				vertices[vertex_index].weight0[index] = mesh->mBones[i]->mWeights[j].mWeight;
			}
			else if (index < 8)
			{
				vertices[vertex_index].index0[index % 4] = bone_index;
				vertices[vertex_index].weight0[index % 4] = mesh->mBones[i]->mWeights[j].mWeight;
			}
			else
			{
				std::cerr << "No more space for bones" << std::endl;
				abort();
			}
		}

		bone_index++;
	}

	return vector_vertices;
}

Engine::Skeleton *Engine::AssimpTool::loadSkeleton(const aiScene *scene, const GLchar *name, std::set<Object *> *tObject)
{
	aiNode *root_node, *tmp_node0, *tmp_node1;
	Skeleton *root_skeleton, *tmp_skeleton0, *tmp_skeleton1;
	aiMatrix4x4 tmp_matrix;

	if (name != NULL)
		root_node = scene->mRootNode->FindNode(name);
	else
		root_node = scene->mRootNode;

	if (root_node == NULL) throw std::exception();

	root_skeleton = new_ref(Skeleton(std::string(root_node->mName.C_Str())));
	tObject->insert(root_skeleton);

	std::queue<aiNode *> queue0;
	std::queue<Skeleton *> queue1;

	queue0.push(root_node);
	queue1.push(root_skeleton);

	while (!queue0.empty() && !queue1.empty())
	{
		tmp_node0 = queue0.front();
		tmp_skeleton0 = queue1.front();

		tmp_matrix = tmp_node0->mTransformation.Transpose();
		memcpy(&tmp_skeleton0->matrix, &tmp_matrix, sizeof(glm::mat4));		

		for (GLuint i = 0; i < tmp_node0->mNumChildren; i++)
		{
			tmp_node1 = tmp_node0->mChildren[i];
			tmp_skeleton1 = new_ref(Skeleton(std::string(tmp_node1->mName.C_Str())));

			tmp_skeleton0->children.push_back(tmp_skeleton1);
			tmp_skeleton1->parent = tmp_skeleton1;
			
			queue0.push(tmp_node1);
			queue1.push(tmp_skeleton1);
		}

		queue0.pop();
		queue1.pop();
	}

	return root_skeleton;
}
#include "Helicopter.hpp"

Helicopter::Helicopter()
{
	_objectProgram = new_ref(Engine::ShaderProgram(
		"../share/Demo/shader/object/objectVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/object/objectGeom.glsl",
		"../share/Demo/shader/object/objectFrag.glsl"));

	_depthMapProgram = new_ref(Engine::ShaderProgram(
		"../share/Demo/shader/depthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/depthMap/depthMapFrag.glsl"));

	_model = new_ref(Engine::StaticModel(_objectProgram, _depthMapProgram));

	_model->loadFromFile("../share/Demo/resources/models/heli/corps.mobj");
	_model->sortMesh();
}

Helicopter::~Helicopter(void)
{
	release_ref(_objectProgram);
	release_ref(_depthMapProgram);
	release_ref(_model);
}

Engine::StaticModel *Helicopter::getModel(void) const
{
	return _model;
}
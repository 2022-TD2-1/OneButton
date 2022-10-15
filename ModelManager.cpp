#include "ModelManager.h"

void ModelManager::LoadAllModels()
{
	RegisterModel("cube", "Cube");
	RegisterModel("sphere", "Sphere");
	RegisterModel("pane", "Pane");
}

Model* ModelManager::Get(string key)
{
	return &modelMap.find(key)->second;
}

void ModelManager::RegisterModel(string modelName, string key)
{
	modelMap.emplace(key, Model(modelName));
}

void ModelManager::ClearModelMap()
{
	modelMap.clear();
}

map<string, Model> ModelManager::modelMap;
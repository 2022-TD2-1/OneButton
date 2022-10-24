#include "ModelManager.h"

void ModelManager::LoadAllModels()
{
	RegisterModel("cube", "Cube");
	RegisterModel("sphere", "Sphere");
	RegisterModel("pane", "Pane");
	RegisterModel("player", "Player");
	RegisterModel("boss", "Boss");
	RegisterModel("heart", "Heart");
	RegisterModel("skysphere", "Skysphere");
	RegisterModel("bullet", "Bullet");
	RegisterModel("rail", "Rail");
	RegisterModel("space", "Space");
	RegisterModel("knocker", "Knocker");
	RegisterModel("three", "Three");
	RegisterModel("one", "One");
	RegisterModel("two", "Two");
	RegisterModel("start", "Start");

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
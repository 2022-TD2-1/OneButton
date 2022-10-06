#pragma once
#include "Essentials.h"
#include "Model.h"

class ModelManager
{
public:
	static void LoadAllModels();
	static Model* Get(string key);

	static map<string, Model> modelMap;

	static void RegisterModel(string modelName, string key);

	static void ClearModelMap();
};
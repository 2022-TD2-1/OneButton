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
	RegisterModel("S", "S");
	RegisterModel("A", "A");
	RegisterModel("B", "B");
	RegisterModel("C", "C");
	RegisterModel("rank", "Rank");
	RegisterModel("gameover", "Gameover");
	RegisterModel("clear", "Clear");

}

void ModelManager::LoadAllSound() {
	SoundManager::LoadWave("Resources/SE_Bgm/boss.wav", "bossKnock");
	SoundManager::LoadWave("Resources/SE_Bgm/PlayerAttack.wav", "PlayerAttack");
	SoundManager::LoadWave("Resources/SE_Bgm/playerDamage.wav", "Damage");
	SoundManager::LoadWave("Resources/SE_Bgm/bossDead.wav", "BossDead");
	SoundManager::LoadWave("Resources/SE_Bgm/play.wav", "PlayBGM");
	SoundManager::LoadWave("Resources/SE_Bgm/result.wav", "ResultBGM");
	SoundManager::LoadWave("Resources/SE_Bgm/title.wav", "TitleBGM");
	SoundManager::LoadWave("Resources/SE_Bgm/button.wav", "Select");
	SoundManager::LoadWave("Resources/SE_Bgm/select.wav", "Enter");
	SoundManager::LoadWave("Resources/SE_Bgm/explosion.wav", "Explosion");
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
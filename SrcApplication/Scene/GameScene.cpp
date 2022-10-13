#include "GameScene.h"
#include "Input.h"
#include "RTVManager.h"
#include "wSwapChainManager.h"
#include "TextDrawer.h"
#include <ModelManager.h>

void GameScene::Init()
{
	wTextureManager::Init();
	ModelManager::LoadAllModels();
	wTextureManager::LoadTexture("Resources/white.png", "white");

	Light::directional.direction = Vec3(0, 0, 1);

	player = Player::Create();
	player->Init();

	player->model = ModelManager::Get("Cube");
	player->position = { 0,0,0 };

	boss = Boss::Create();
	boss->Init();

	camera.projectionMode = ProjectionMode::Perspective;
	camera.position = { 0, 0, -12.5 };
	camera.targetMode = CameraTargetMode::LookTo;
	camera.rotation= { 0, 0, 0 };

	camera.renderWidth = CommonParams::Win::width;
	camera.renderHeight = CommonParams::Win::height;

	camera.fov = PIf/2;
	camera.nearZ = 0.1f;
	camera.farZ = 1000.0f;
}

void GameScene::Update()
{
	player->Update();

	camera.UpdateMatrix();
}

void GameScene::DrawBack()
{
}

void GameScene::Draw3D()
{	
	Camera::Set(camera);

	player->Draw();
	boss->Draw();
}

void GameScene::DrawSprite()
{
	StringOptions dbgstrop;
	dbgstrop.fontOptions.resolution = 24;
	dbgstrop.size = 24;
	string debugstr = "PlayerOption::State = ";
	debugstr += to_string((int)player->opti.state);
	TextDrawer::DrawString(debugstr, 100, 100, Align::TopLeft, dbgstrop);
}
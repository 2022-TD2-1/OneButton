#include "TitleScene.h"

void TitleScene::Init()
{
	wTextureManager::Init();
	ModelManager::LoadAllModels();
	wTextureManager::LoadTexture("Resources/white.png", "white");

#pragma region カメラ
	camera.projectionMode = ProjectionMode::Perspective;
	camera.position = { 0, 0, -12.5 };
	camera.targetMode = CameraTargetMode::LookTo;
	camera.rotation = { 0, 0, 0 };

	camera.renderWidth = CommonParams::Win::width;
	camera.renderHeight = CommonParams::Win::height;

	camera.fov = PIf / 2;
	camera.nearZ = 0.1f;
	camera.farZ = 1000.0f;
#pragma endregion

	player.Init(&camera);

	player.model = ModelManager::Get("Cube");
	player.position = { 0,0,0 };
	//タイトル初期化
	testObj.model = ModelManager::Get("Cube");
	testObj.position = { 0,0,0 };


}

void TitleScene::Update()
{
	player.Update();
	//タイトル更新
	testObj.UpdateMatrix();

	camera.UpdateMatrix();
}

void TitleScene::DrawBack()
{
}

void TitleScene::Draw3D()
{
	Camera::Set(camera);

	player.Draw();
	//タイトル描画
	testObj.Draw();
}

void TitleScene::DrawSprite()
{
}

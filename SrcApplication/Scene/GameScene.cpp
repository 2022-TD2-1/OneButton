#include "GameScene.h"
#include "Input.h"
#include "RTVManager.h"
#include "wSwapChainManager.h"
#include "TextDrawer.h"
#include <ModelManager.h>
#include "SceneManager.h"
#include <ResultScene.h>
void GameScene::Init()
{
	wTextureManager::Init();
	ModelManager::LoadAllModels();
	wTextureManager::LoadTexture("Resources/white.png", "white");
	wTextureManager::LoadTexture("Resources/CircleGuide.png", "CircleGuide");

	timer_ = GameTimer::GetInstance();

	guide.model = ModelManager::Get("Rail");
	guide.position = { 0,0,0 };
	guide.scale = { 8,8,8 };
	guide.rotation = { 0,0,0 };
	guide.UpdateMatrix();

	Light::directional.direction = Vec3(0, 0, 1);

	player = Player::Create();
	player->Init();

	player->model = ModelManager::Get("Player");
	player->position = { 0,0,0 };

#pragma region カメラ初期化
	camera.projectionMode = ProjectionMode::Perspective;
	camera.position = { 0, 0, -12.5 };
	camera.targetMode = CameraTargetMode::LookTo;
	camera.rotation = { 0, 0, 0 };

	camera.renderWidth = CommonParams::Win::width;
	camera.renderHeight = CommonParams::Win::height;

	camera.fov = PIf / 2;
	camera.nearZ = 0.1f;
	camera.farZ = 1000.0f;
	camera.OriginalPosSet();
#pragma endregion

	boss = Boss::Create();
	boss->Init(&camera);

	SkyDome.model = ModelManager::Get("Skysphere");
	SkyDome.position = { 0,0,0 };
	SkyDome.scale = { 30,30,30 };
	SkyDome.UpdateMatrix();

	titleObj = TitleObj::Create();
	titleObj->Ini(&camera);
	spaceObj.model = ModelManager::Get("Space");
	spaceObj.position = { 0,-10,0 };
	spaceObj.scale = { 2,2,2 };
	
	spaceObj.UpdateMatrix();

	
}

void GameScene::Update()
{
	player->Update();
	camera.UpdateMatrix();
	if (gameState == GameState::Title_) {
		titleObj->Update();
		if (titleObj->GetDead()) {
			//タイトルオブジェを倒したらゲームシーンへ移る
			gameState = GameState::Gamescene_;
		}
	}
	//ゲーム
	if (gameState == GameState::Gamescene_) {
		if (Input::Key::Triggered(DIK_S))
		{
			player->health = 0;
		}
		if (Input::Key::Triggered(DIK_K))
		{
			boss->health = 1;
		}
		boss->Update();
		//リザルトシーンへ移る
		if (boss->isDead == true)
		{
			SceneManager::Transition<ResultScene>();
			return;
		}
		//リザルトシーンへ移る
		if (player->isDead == true)
		{
			SceneManager::Transition<ResultScene>();
			return;
		}

		
	}
	camera.Shake();
	SkyDome.rotation += {0.00025f, 0.0002f, 0.0001f};
	SkyDome.UpdateMatrix();
}

void GameScene::DrawBack()
{
}

void GameScene::Draw3D()
{
	Camera::Set(camera);

	player->Draw();
	guide.Draw("white");
	SkyDome.Draw();
	if (gameState == GameState::Title_) {
		titleObj->Draw();
	}
	if (gameState == GameState::Gamescene_) {
		boss->Draw();
	}

	spaceObj.Draw();

	
}

void GameScene::DrawSprite()
{
	float time = timer_->GetTimer();

	StringOptions dbgstrop;
	dbgstrop.fontOptions.resolution = 24;
	dbgstrop.size = 24;
	string debugstr;
	debugstr += "timer = ";
	debugstr += to_string(time);
	TextDrawer::DrawString(debugstr, 100, 100, Align::TopLeft, dbgstrop);

	/*if (player->opti.size() > 0) {
		string debugscl;
		debugscl += "opti::scale = ";
		debugscl += to_string(player->opti.back().scale.x);
		TextDrawer::DrawString(debugscl, 100, 140, Align::TopLeft, dbgstrop);
		string debugpw;
		debugpw += "opti::power = ";
		debugpw += to_string(player->opti.back().power);
		TextDrawer::DrawString(debugpw, 100, 180, Align::TopLeft, dbgstrop);
	}*/
}

void GameScene::SetState(int state)
{
	gameState = (GameState)state;
}

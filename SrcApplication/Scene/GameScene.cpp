#include "GameScene.h"
#include "Input.h"
#include "RTVManager.h"
#include "wSwapChainManager.h"
#include "TextDrawer.h"
#include <ModelManager.h>
#include "SceneManager.h"
#include <ResultScene.h>
#include <SoundManager.h>
void GameScene::Init()
{
	wTextureManager::Init();
	ModelManager::LoadAllModels();
	ModelManager::LoadAllSound();
	wTextureManager::LoadTexture("Resources/white.png", "white");
	wTextureManager::LoadTexture("Resources/CircleGuide.png", "CircleGuide");

#pragma region カメラ初期化
	camera.projectionMode = ProjectionMode::Perspective;
	camera.position = { 0, -3, -12.5 };
	camera.target = { 0,-1,0 };
	camera.targetMode = CameraTargetMode::LookAt;
	camera.rotation = { 0, 0, 0 };

	camera.renderWidth = CommonParams::Win::width;
	camera.renderHeight = CommonParams::Win::height;

	camera.fov = PIf / 2;
	camera.nearZ = 0.1f;
	camera.farZ = 1000.0f;
	camera.OriginalPosSet();
#pragma endregion
	timer_ = GameTimer::GetInstance();
	timer_->Ini();

	guide.model = ModelManager::Get("Rail");
	guide.position = { 0,0,0 };
	guide.scale = { 8,8,8 };
	guide.rotation = { 0,0,0 };
	guide.UpdateMatrix();

	Light::directional.direction = Vec3(0, 0, 1);

	player = Player::Create();
	player->Init(&camera);

	player->model = ModelManager::Get("Player");
	player->position = { 0,0,0 };

	RTVManager::CreateRenderTargetTexture(1280, 720, "aoeSpr");
	aoeSpr = Sprite("aoeSpr");

	boss = Boss::Create();
	boss->Init(&camera);
	boss->SetPlayer(player);

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

	SoundManager::StopBGM("ClearBGM");
	SoundManager::StopBGM("ResultBGM");
	SoundManager::PlayBGM("TitleBGM", true);
}

void GameScene::Update()
{
	//spaceオブジェ
	if (Input::Key::Down(DIK_SPACE))
	{
		if (spaceObj.scale.x >= 1.5f) {
			if (spaceObj.position.z < 3) {
				spaceObj.position.z += 0.01f;
			}
			spaceObj.scale += { -0.07f, -0.07f, -0.07f};
		}
	}
	else {
		if (spaceObj.position.z > 0) {
			spaceObj.position.z -= 0.01f;
		}
		if (spaceObj.scale.x < 2.0f) {
			spaceObj.scale += { 0.07f, 0.07f, 0.07f};
		}
	}
	spaceObj.UpdateMatrix();

	player->Update();
	camera.UpdateMatrix();
	boss->ShockwaveUpdate();
	if (gameState == GameState::Title_) {
		
		titleObj->Update();
		if (titleObj->GetDead()) {
			SoundManager::PlayBGM("PlayBGM", true);
			gameState = GameState::Gamescene_;
			player->opti.clear();
			boss->SetShockWave();
		}
	}
	//ゲーム
	if (gameState == GameState::Gamescene_) {
		//タイトルオブジェを倒したらゲームシーンへ移る
		SoundManager::StopBGM("TitleBGM");
#ifdef _DEBUG

		if (Input::Key::Triggered(DIK_S))
		{
			player->health = 0;
		}
		if (Input::Key::Triggered(DIK_K))
		{
			boss->health = 1;
		}

#endif // _DEBUG
		boss->Update();
		//リザルトシーンへ移る
		if (boss->isDead == true)
		{
			SoundManager::StopBGM("PlayBGM");
			SceneManager::Transition<ResultScene>();
			return;
		}
		//リザルトシーンへ移る
		if (player->isDead == true)
		{
			SoundManager::StopBGM("PlayBGM");
			SceneManager::Transition<ResultScene>();
			return;
		}

		
	}
	camera.Shake();
	SkyDome.rotation += {0.00025f, 0.0002f, 0.0001f};
	SkyDome.UpdateMatrix();

	aoeSpr.position = { 640.f, 360.f, 0 };
	aoeSpr.UpdateMatrix();
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

	RTVManager::SetRenderTargetToTexture("aoeSpr");

	Camera::Set(camera);
	boss->DrawAoEs();

	Camera::Set(camera);
	RTVManager::SetRenderTargetToBackBuffer(GetSCM()->swapchain->GetCurrentBackBufferIndex());
}

void GameScene::DrawSprite()
{
	float time = timer_->GetTimer();

	aoeSpr.Draw();

	player->DrawSprite();

	/*StringOptions dbgstrop;
	dbgstrop.fontOptions.resolution = 24;
	dbgstrop.size = 48;
	string debugstr;
	debugstr += "timer : ";
	debugstr += to_string(time);
	TextDrawer::DrawString(debugstr, 100, 100, Align::TopLeft, dbgstrop);*/

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

	timer_->DrawTimer();
}

void GameScene::SetState(int state)
{
	gameState = (GameState)state;
}

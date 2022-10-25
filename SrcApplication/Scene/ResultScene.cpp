#include <Parameters.h>
#include "ResultScene.h"
#include <SceneManager.h>
#include <TitleScene.h>
#include <GameScene.h>

void ResultScene::Init()
{
	timer_ = GameTimer::GetInstance();
#pragma region 数字読み込み
	numSprite[0] = Sprite("Resources/Numbers/zero.png", "zero");
	numSprite[1] = Sprite("Resources/Numbers/one.png", "one");
	numSprite[2] = Sprite("Resources/Numbers/two.png", "two");
	numSprite[3] = Sprite("Resources/Numbers/three.png", "three");
	numSprite[4] = Sprite("Resources/Numbers/four.png", "four");
	numSprite[5] = Sprite("Resources/Numbers/five.png", "five");
	numSprite[6] = Sprite("Resources/Numbers/six.png", "six");
	numSprite[7] = Sprite("Resources/Numbers/seven.png", "seven");
	numSprite[8] = Sprite("Resources/Numbers/eight.png", "eight");
	numSprite[9] = Sprite("Resources/Numbers/nine.png", "nine");
	dotSprite = Sprite("Resources/Numbers/point.png", "point");
#pragma endregion

	menuTxt[0] = Sprite("Resources/continueTxt.png", "continue");
	menuTxt[1] = Sprite("Resources/titleTxt.png", "title");
	menuTxt[0].position = {
		CommonParams::Win::width / 2,
		500,
		0
	};
	menuTxt[1].position = {
		CommonParams::Win::width / 2,
		600,
		0
	};
	selectSprite = Sprite("Resources/think.png", "select");
	selectSprite.position = {
		400,
		menuTxt[0].position.y,
		0
	};
	selectSprite.scale = { 0.1,0.1,0.1 };

	skyDome.model = ModelManager::Get("Skysphere");
	skyDome.position = { 0,0,0 };
	skyDome.scale = { 30,30,30 };
	skyDome.UpdateMatrix();

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

	UpdateNum();

	clearTime = timer_->GetTimer();
}

void ResultScene::Update()
{
	//メニューセレクト
	if (Input::Key::Triggered(DIK_UP))
	{
		isSelect = Menu::Continue;	//もう一度ボス戦へ
		//セレクト画像の座標
		selectSprite.position = {
		400,
		menuTxt[0].position.y,
		0
		};
	}
	else if (Input::Key::Triggered(DIK_DOWN))
	{
		isSelect = Menu::Title;		//タイトルに戻る
		//セレクト画像の座標
		selectSprite.position = {
		400,
		menuTxt[1].position.y,
		0
		};
	}
	//決定
	if (Input::Key::Triggered(DIK_SPACE)) {
		isReturn = true;
	}
	//決定したら以下の処理をする
	if (isReturn == true) {
		timer_->Ini();
		//コンティニューを選択した場合
		if (isSelect == Menu::Continue) {
			SceneManager::Transition<GameScene>();
			dynamic_cast<GameScene*>(SceneManager::currentScene.get())->SetState(1);
			return;
		}
		//タイトルを選択した場合
		else if (isSelect == Menu::Title) {
			SceneManager::Transition<GameScene>();
			dynamic_cast<GameScene*>(SceneManager::currentScene.get())->SetState(0);
			return;
		}
	}

	//デバッグ
	if (Input::Key::Triggered(DIK_1)) {
		clearTime++;
	}
	if (Input::Key::Triggered(DIK_2)) {
		clearTime--;
	}

	UpdateNum();

	

	//スプライト更新
	for (int i = 0; i < 10; i++) {
		numSprite[i].UpdateMatrix();
		if (i < 4) {
			displayNumSprite[i].UpdateMatrix();
		}
		if (i < 2) {
			menuTxt[i].UpdateMatrix();
		}
	}
	dotSprite.UpdateMatrix();
	selectSprite.UpdateMatrix();
	Rank();
	skyDome.rotation += {0.00025f, 0.0002f, 0.0001f};
	skyDome.UpdateMatrix();
}

void ResultScene::DrawBack()
{
}

void ResultScene::Draw3D()
{
	Camera::Set(camera);
	skyDome.Draw();
}

void ResultScene::DrawSprite()
{

	const int display[5] =
	{ displayNum[0],displayNum[1], displayNum[2], displayNum[3], displayNum[4] };
	for (int i = 0; i < 5; i++) {
		//数字を描画
		displayNumSprite[i].Draw();

		if (i < 2) {
			menuTxt[i].Draw();
		}
	}
	selectSprite.Draw();
	//小数点を描画
	dotSprite.Draw();

}

void ResultScene::UpdateNum()
{
	
	//時間がマイナスにならないように
	if (clearTime <= 0) {
		clearTime = 0;
	}
	//時間を代入する
	int time = (clearTime * 100);
	displayNum[0] = (time % 100000) / 10000;
	displayNum[1] = (time % 10000) / 1000;
	displayNum[2] = (time % 1000) / 100;
	displayNum[3] = (time % 100) / 10;
	displayNum[4] = (time % 10);
	
	const int display[5] =
	{ displayNum[0],displayNum[1], displayNum[2], displayNum[3], displayNum[4] };
	for (int i = 0; i < 5; i++) {
		if (i == 3) {
			//小数点の座標を代入
			dotSprite.position.x = 50 + (50 * i);
			dotSprite.position.y = 50;
			dotSprite.position.z = 0;
		}

		//数字の座標を代入
		if (i <= 2) {
			numSprite[display[i]].position.x = 50 + (50 * i);
			numSprite[display[i]].position.y = 50;
			numSprite[display[i]].position.z = 0;
			displayNumSprite[i] = numSprite[display[i]];	//表示用スプライトに代入
		}
		else {
			numSprite[display[i]].position.x = 50 + (50 * (i + 1));
			numSprite[display[i]].position.y = 50;
			numSprite[display[i]].position.z = 0;
			displayNumSprite[i] = numSprite[display[i]];	//表示用スプライトに代入
		}
	}

}

void ResultScene::Rank()
{
	if (clearTime <= 30) {		//A
		rank = 0;
	}
	else if (clearTime <= 50) {	//B
		rank = 1;
	}
	//以下適当に
}

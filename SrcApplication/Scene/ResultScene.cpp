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
	for (int i = 0; i < 10; i++) {
		numSprite[i].position = { -100,-150 };
	}


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
	menuTxt[0].brightness = { 0.5f, 1.0f, 1.0f, 1.0f };
	selectSprite = Sprite("Resources/allow.png", "select");
	selectSprite.position = {
		450,
		menuTxt[0].position.y,
		0
	};
	selectSprite.scale = { 0.5f, 0.5f, 0.5f };

	skyDome.model = ModelManager::Get("Skysphere");
	skyDome.position = { 0,0,0 };
	skyDome.scale = { 30,30,30 };
	skyDome.UpdateMatrix();

	rankObj[0].model = ModelManager::Get("S");
	rankObj[1].model = ModelManager::Get("A");
	rankObj[2].model = ModelManager::Get("B");
	rankObj[3].model = ModelManager::Get("C");

	for (int i = 0; i < 4; i++) {
		rankObj[i].position = { 5,0,0 };
		rankObj[i].scale.x = 10.f / (i + 2);
		rankObj[i].scale.y = 10.f / (i + 2);
		rankObj[i].scale.z = 10.f / (i + 2);
		rankObj[i].UpdateMatrix();
	}
	rankTxtObj.model = ModelManager::Get("Rank");
	rankTxtObj.position = { -3,0,0 };
	rankTxtObj.scale = { 3,3,3 };
	rankTxtObj.UpdateMatrix();
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

	setTimer = timer_->GetTimer();

	controlTime = 0;

	player_ = Player::GetCurrent();
	if (player_->isDead == false) {
		isResultState = false;	//クリアしたとき
		SoundManager::PlayBGM("ClearBGM", true);
	}
	else if (player_->isDead == true) {
		isResultState = true;	//ゲームおーべー
		SoundManager::PlayBGM("ResultBGM", true);
	}

	clearObj.model = ModelManager::Get("Clear");
	clearObj.position = { 0,8,0 };
	clearObj.rotation = { -(PI / 16),0,0 };
	clearObj.scale = { 3,3,3 };

	clearObj.UpdateMatrix();

	gameOverObj.model = ModelManager::Get("Gameover");
	gameOverObj.position = { 0,2,0 };
	gameOverObj.scale = { 3,3,3 };
	gameOverObj.UpdateMatrix();
}

void ResultScene::Update()
{
	if (isResultState == false) {
		const int maxT = 500;
		if (controlTime < 120) controlTime++;
		if (t >= maxT && controlTime >= 120) {

			//メニューセレクト
			if (Input::Key::Triggered(DIK_UP))
			{
				menuTxt[0].brightness = { 0.5f, 1.0f, 1.0f, 1.0f };
				menuTxt[1].brightness = {1.f, 1.f, 1.f, 1.0f};
				SoundManager::Play("Select");
				isSelect = Menu::Continue;	//もう一度ボス戦へ
				//セレクト画像の座標
				selectSprite.position = {
				450,
				menuTxt[0].position.y,
				0
				};
			}
			else if (Input::Key::Triggered(DIK_DOWN))
			{
				menuTxt[0].brightness = {1.f, 1.f, 1.f, 1.0f};
				menuTxt[1].brightness = { 0.5f, 1.0f, 1.0f, 1.0f };
				SoundManager::Play("Select");
				isSelect = Menu::Title;		//タイトルに戻る
				//セレクト画像の座標
				selectSprite.position = {
				450,
				menuTxt[1].position.y,
				0
				};
			}
			//決定
			if (Input::Key::Triggered(DIK_SPACE)) {
				SoundManager::Play("Enter");
				isReturn = true;
			}
			//決定したら以下の処理をする
			if (isReturn == true) {
				timer_->Ini();
				//コンティニューを選択した場合
				if (isSelect == Menu::Continue) {
					SceneManager::Transition<GameScene>();
					dynamic_cast<GameScene*>(SceneManager::currentScene.get())->SetState(1);
					SoundManager::PlayBGM("PlayBGM", true);
					return;
				}
				//タイトルを選択した場合
				else if (isSelect == Menu::Title) {
					SceneManager::Transition<GameScene>();
					dynamic_cast<GameScene*>(SceneManager::currentScene.get())->SetState(0);
					SoundManager::PlayBGM("TitleBGM", true);
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
		}
		else {
			if (Input::Key::Triggered(DIK_SPACE)) {
				SoundManager::Play("Enter");
				t = maxT;
			}
		}

		if (maxT == t)isDisplayRank = true;
		if (t < maxT)t++;

		for (int i = 0; i < 4; i++) {
			rankObj[i].rotation.y += 0.03f;
			rankObj[i].UpdateMatrix();
		}

		clearTime = Vec3::easeOutBack(t, 0, setTimer, maxT);

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
	else if (isResultState == true) {
		//メニューセレクト
		if (Input::Key::Triggered(DIK_UP))
		{
			menuTxt[0].brightness = { 0.5f, 1.0f, 1.0f, 1.0f };
			menuTxt[1].brightness = { 1.f, 1.f, 1.f, 1.0f };
			SoundManager::Play("Select");
			isSelect = Menu::Continue;	//もう一度ボス戦へ
			//セレクト画像の座標
			selectSprite.position = {
			450,
			menuTxt[0].position.y,
			0
			};
		}
		else if (Input::Key::Triggered(DIK_DOWN))
		{
			menuTxt[0].brightness = { 1.f, 1.f, 1.f, 1.0f };
			menuTxt[1].brightness = { 0.5f, 1.0f, 1.0f, 1.0f };
			SoundManager::Play("Select");
			isSelect = Menu::Title;		//タイトルに戻る
			//セレクト画像の座標
			selectSprite.position = {
			450,
			menuTxt[1].position.y,
			0
			};
		}
		//決定
		if (Input::Key::Triggered(DIK_SPACE)) {
			SoundManager::Play("Enter");
			isReturn = true;
		}
		//決定したら以下の処理をする
		if (isReturn == true) {
			timer_->Ini();
			//コンティニューを選択した場合
			if (isSelect == Menu::Continue) {
				SceneManager::Transition<GameScene>();
				dynamic_cast<GameScene*>(SceneManager::currentScene.get())->SetState(1);
				SoundManager::PlayBGM("PlayBGM", true);
				return;
			}
			//タイトルを選択した場合
			else if (isSelect == Menu::Title) {
				SceneManager::Transition<GameScene>();
				dynamic_cast<GameScene*>(SceneManager::currentScene.get())->SetState(0);
				SoundManager::PlayBGM("TitleBGM", true);
				return;
			}
		}
		for (int i = 0; i < 2; i++) {
			menuTxt[i].UpdateMatrix();
		}
		selectSprite.UpdateMatrix();
		Rank();
		skyDome.rotation += {0.00025f, 0.0002f, 0.0001f};
		skyDome.UpdateMatrix();
	}
}

void ResultScene::DrawBack()
{
}

void ResultScene::Draw3D()
{
	Camera::Set(camera);
	skyDome.Draw();
	if (isResultState == false) {
		if (isDisplayRank == true) {
			rankObj[rank].Draw();	//アルファベットオブジェ
		}
		rankTxtObj.Draw("white");	//RANKの文字オブジェ
		clearObj.Draw();
	}
	else if (isResultState == true) {
		gameOverObj.Draw();
	}
}

void ResultScene::DrawSprite()
{
	if (isResultState == false) {
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
	else {
		for (int i = 0; i < 2; i++) {
			menuTxt[i].Draw();
		}
		selectSprite.Draw();
	}

}

void ResultScene::UpdateNum()
{

	//時間がマイナスにならないように

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
			dotSprite.position.x = 515 + (50 * i);
			dotSprite.position.y = 250;
			dotSprite.position.z = 0;
		}

		//数字の座標を代入
		if (i <= 2) {
			numSprite[display[i]].position.x = 515 + (50 * i);
			numSprite[display[i]].position.y = 250;
			numSprite[display[i]].position.z = 0;
			displayNumSprite[i] = numSprite[display[i]];	//表示用スプライトに代入
		}
		else {
			numSprite[display[i]].position.x = 515 + (50 * (i + 1));
			numSprite[display[i]].position.y = 250;
			numSprite[display[i]].position.z = 0;
			displayNumSprite[i] = numSprite[display[i]];	//表示用スプライトに代入
		}
	}

}

void ResultScene::Rank()
{
	if (clearTime <= 40) {		//S
		rank = 0;
	}
	else if (clearTime <= 55) {	//A
		rank = 1;
	}
	else if (clearTime <= 70) {	//B
		rank = 2;
	}
	else if (clearTime <= 200) {	//C
		rank = 3;
	}
	//以下適当に
}

#include <Parameters.h>
#include "ResultScene.h"
#include <SceneManager.h>
#include <TitleScene.h>
#include <GameScene.h>

void ResultScene::Init()
{
#pragma region 数字読み込み
	numSprite[0] = Sprite("Resources/zero.png", "zero");
	numSprite[1] = Sprite("Resources/one.png", "one");
	numSprite[2] = Sprite("Resources/two.png", "two");
	numSprite[3] = Sprite("Resources/three.png", "three");
	numSprite[4] = Sprite("Resources/four.png", "four");
	numSprite[5] = Sprite("Resources/five.png", "five");
	numSprite[6] = Sprite("Resources/six.png", "six");
	numSprite[7] = Sprite("Resources/seven.png", "seven");
	numSprite[8] = Sprite("Resources/eight.png", "eight");
	numSprite[9] = Sprite("Resources/nine.png", "nine");
	dotSprite = Sprite("Resources/point.png", "point");
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
	UpdateNum();
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
		//コンティニューを選択した場合
		if (isSelect == Menu::Continue) {
			SceneManager::Transition<GameScene>();
			return;
		}
		//タイトルを選択した場合
		else if (isSelect == Menu::Title) {
			SceneManager::Transition<TitleScene>();
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
}

void ResultScene::DrawBack()
{
}

void ResultScene::Draw3D()
{
}

void ResultScene::DrawSprite()
{

	const int display[4] =
	{ displayNum[0],displayNum[1], displayNum[2], displayNum[3], };
	for (int i = 0; i < 4; i++) {
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
	displayNum[0] = (time % 10000) / 1000;
	displayNum[1] = (time % 1000) / 100;
	displayNum[2] = (time % 100) / 10;
	displayNum[3] = (time % 10);
	
	const int display[4] =
	{ displayNum[0],displayNum[1], displayNum[2], displayNum[3] };
	for (int i = 0; i < 4; i++) {
		if (i == 2) {
			//小数点の座標を代入
			dotSprite.position.x = 50 + (50 * i);
			dotSprite.position.y = 50;
			dotSprite.position.z = 0;
		}

		//数字の座標を代入
		if (i <= 1) {
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

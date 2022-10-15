#include "ResultScene.h"

void ResultScene::Init()
{
	//テスト用画像読み込み
	//testSprite = Sprite("test");
	testSprite = Sprite("Resources/one.png"	,"test");
	testSprite.position = { 128,128,0 };

	numSprite[0] = Sprite("Resources/zero.png"	, "zero");
	numSprite[1] = Sprite("Resources/one.png"	, "one");
	numSprite[2] = Sprite("Resources/two.png"	, "two");
	numSprite[3] = Sprite("Resources/three.png"	, "three");
	numSprite[4] = Sprite("Resources/four.png"	, "four");
	numSprite[5] = Sprite("Resources/five.png"	, "five");
	numSprite[6] = Sprite("Resources/six.png"	, "six");
	numSprite[7] = Sprite("Resources/seven.png"	, "seven");
	numSprite[8] = Sprite("Resources/eight.png"	, "eight");
	numSprite[9] = Sprite("Resources/nine.png"	, "nine");

	//testnumSprite = Sprite("Resources/zero.png", "zero");

	for (int i = 0; i < 10; i++) {
		numSprite[i].position.x = 50 + 50 * i;
		numSprite[i].position.y = 50;
		numSprite[i].position.z = 0;
	}
	//testnumSprite.position = { 50,50,0 };

	
}

void ResultScene::Update()
{
	testSprite.UpdateMatrix();

	for (int i = 0; i < 10; i++) {
		numSprite[i].UpdateMatrix();
	}
	//メニューセレクト
	if (Input::Key::Triggered(DIK_UP))
	{
		isSelect = Menu::Continue;	//もう一度ボス戦へ
	}
	else if (Input::Key::Triggered(DIK_DOWN))
	{
		isSelect = Menu::Title;		//タイトルに戻る
	}
	//決定
	if (Input::Key::Triggered(DIK_SPACE)) {
		isReturn = true;
	}
	//決定したら以下の処理をする
	if (isReturn == true) {
		//コンティニューを選択した場合
		if (isSelect == Menu::Continue) {
			
		}
		//タイトルを選択した場合
		else if (isSelect == Menu::Title) {
			
		}
	}


}

void ResultScene::DrawBack()
{
}

void ResultScene::Draw3D()
{
}

void ResultScene::DrawSprite()
{
	//testSprite.Draw();

	//numSprite[0].Draw();

	for (int i = 0; i < 10; i++) {
		numSprite[i].Draw();
	}
}

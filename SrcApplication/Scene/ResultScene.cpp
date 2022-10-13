#include "ResultScene.h"

void ResultScene::Init()
{
	//テスト用画像読み込み
	testSprite = Sprite("test");
	testSprite = Sprite("Resources/test.png","test");
	testSprite.position = { 128,128,0 };
}

void ResultScene::Update()
{
	testSprite.UpdateMatrix();


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
	testSprite.Draw();
}

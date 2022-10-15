#include "ResultScene.h"

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

	UpdateNum();
}

void ResultScene::Update()
{
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

	//デバッグ
	if (Input::Key::Triggered(DIK_W)) {
		testTime++;
	}
	if (Input::Key::Triggered(DIK_S)) {
		testTime--;
	}

	UpdateNum();

	//スプライト更新
	for (int i = 0; i < 10; i++) {
		numSprite[i].UpdateMatrix();
		if (i < 4) {
			displayNumSprite[i].UpdateMatrix();
		}
	}
	dotSprite.UpdateMatrix();


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
	}
	//小数点を描画
	dotSprite.Draw();

}

void ResultScene::UpdateNum()
{
	
	//時間がマイナスにならないように
	if (testTime <= 0) {
		testTime = 0;
	}
	//時間を代入する
	int time = (testTime * 100);
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

#include <Parameters.h>
#include "ResultScene.h"
#include <SceneManager.h>
#include <TitleScene.h>
#include <GameScene.h>

void ResultScene::Init()
{
#pragma region �����ǂݍ���
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
	//���j���[�Z���N�g
	if (Input::Key::Triggered(DIK_UP))
	{
		isSelect = Menu::Continue;	//������x�{�X���
		//�Z���N�g�摜�̍��W
		selectSprite.position = {
		400,
		menuTxt[0].position.y,
		0
		};
	}
	else if (Input::Key::Triggered(DIK_DOWN))
	{
		isSelect = Menu::Title;		//�^�C�g���ɖ߂�
		//�Z���N�g�摜�̍��W
		selectSprite.position = {
		400,
		menuTxt[1].position.y,
		0
		};
	}
	//����
	if (Input::Key::Triggered(DIK_SPACE)) {
		isReturn = true;
	}
	//���肵����ȉ��̏���������
	if (isReturn == true) {
		//�R���e�B�j���[��I�������ꍇ
		if (isSelect == Menu::Continue) {
			SceneManager::Transition<GameScene>();
			return;
		}
		//�^�C�g����I�������ꍇ
		else if (isSelect == Menu::Title) {
			SceneManager::Transition<TitleScene>();
			return;
		}
	}

	//�f�o�b�O
	if (Input::Key::Triggered(DIK_1)) {
		clearTime++;
	}
	if (Input::Key::Triggered(DIK_2)) {
		clearTime--;
	}

	UpdateNum();

	

	//�X�v���C�g�X�V
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
		//������`��
		displayNumSprite[i].Draw();

		if (i < 2) {
			menuTxt[i].Draw();
		}
	}
	selectSprite.Draw();
	//�����_��`��
	dotSprite.Draw();

}

void ResultScene::UpdateNum()
{
	
	//���Ԃ��}�C�i�X�ɂȂ�Ȃ��悤��
	if (clearTime <= 0) {
		clearTime = 0;
	}
	//���Ԃ�������
	int time = (clearTime * 100);
	displayNum[0] = (time % 10000) / 1000;
	displayNum[1] = (time % 1000) / 100;
	displayNum[2] = (time % 100) / 10;
	displayNum[3] = (time % 10);
	
	const int display[4] =
	{ displayNum[0],displayNum[1], displayNum[2], displayNum[3] };
	for (int i = 0; i < 4; i++) {
		if (i == 2) {
			//�����_�̍��W����
			dotSprite.position.x = 50 + (50 * i);
			dotSprite.position.y = 50;
			dotSprite.position.z = 0;
		}

		//�����̍��W����
		if (i <= 1) {
			numSprite[display[i]].position.x = 50 + (50 * i);
			numSprite[display[i]].position.y = 50;
			numSprite[display[i]].position.z = 0;
			displayNumSprite[i] = numSprite[display[i]];	//�\���p�X�v���C�g�ɑ��
		}
		else {
			numSprite[display[i]].position.x = 50 + (50 * (i + 1));
			numSprite[display[i]].position.y = 50;
			numSprite[display[i]].position.z = 0;
			displayNumSprite[i] = numSprite[display[i]];	//�\���p�X�v���C�g�ɑ��
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
	//�ȉ��K����
}

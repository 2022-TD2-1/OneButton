#include "ResultScene.h"

void ResultScene::Init()
{
#pragma region �����ǂݍ���
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
	dotSprite = Sprite("Resources/point.png", "point");
#pragma endregion
	
	//���Ԃ�������
	int time = (testTime * 100);
	displayNum[0] = (time % 10000) / 1000;
	displayNum[1] = (time % 1000) / 100;
	displayNum[2] = (time % 100) / 10;
	displayNum[3] = (time % 10);

	const int display[5] =
	{ displayNum[0],displayNum[1],0, displayNum[2], displayNum[3] };
	for (int i = 0; i < 5; i++) {
		if (i == 2) {
			//�����_�̍��W����
			dotSprite.position.x = 50 + (50 * i);
			dotSprite.position.y = 50;
			dotSprite.position.z = 0;
		}
		else {
			//�����̍��W����
			numSprite[display[i]].position.x = 50 + (50 * i);
			numSprite[display[i]].position.y = 50;
			numSprite[display[i]].position.z = 0;
		}
	}
}

void ResultScene::Update()
{
	//���j���[�Z���N�g
	if (Input::Key::Triggered(DIK_UP))
	{
		isSelect = Menu::Continue;	//������x�{�X���
	}
	else if (Input::Key::Triggered(DIK_DOWN))
	{
		isSelect = Menu::Title;		//�^�C�g���ɖ߂�
	}
	//����
	if (Input::Key::Triggered(DIK_SPACE)) {
		isReturn = true;
	}
	//���肵����ȉ��̏���������
	if (isReturn == true) {
		//�R���e�B�j���[��I�������ꍇ
		if (isSelect == Menu::Continue) {
			
		}
		//�^�C�g����I�������ꍇ
		else if (isSelect == Menu::Title) {
			
		}
	}

	//�X�v���C�g�X�V
	for (int i = 0; i < 10; i++) {
		numSprite[i].UpdateMatrix();
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
		//������`��
		numSprite[display[i]].Draw();
	}
	//�����_��`��
	dotSprite.Draw();
	
}

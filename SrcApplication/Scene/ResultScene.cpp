#include "ResultScene.h"

void ResultScene::Init()
{
	//�e�X�g�p�摜�ǂݍ���
	testSprite = Sprite("test");
	testSprite = Sprite("Resources/test.png","test");
	testSprite.position = { 128,128,0 };
}

void ResultScene::Update()
{
	testSprite.UpdateMatrix();


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

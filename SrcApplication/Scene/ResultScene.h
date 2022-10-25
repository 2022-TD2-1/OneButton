#pragma once
#include "IScene.h"
#include "Matrix.h"
#include "Model.h"
#include "Object3D.h"
#include "Sprite.h"
#include "Camera.h"
#include "Input.h"
#include <Player.h>
#include <Sprite.h>
#include <GameTimer.h>
using namespace Input;
class ResultScene
	: public IScene
{
public:

	void Init() override;
	void Update() override;
	void DrawBack() override;
	void Draw3D() override;
	void DrawSprite() override;

private:
	Camera camera;
	
	//�N���A���Ԃ�����ϐ�
	float clearTime = 03.31f;
	//�\������4�̐���������ϐ�
	float displayNum[5];
	//�\��������摜
	Sprite displayNumSprite[5];
	//�����摜
	Sprite numSprite[10];
	//�����_�摜
	Sprite dotSprite;
	//�e�L�X�g�摜
	Sprite menuTxt[2];
	Sprite selectSprite;

	void UpdateNum();	//�������X�V����

	int rank;
	void Rank();		//�N���A�^�C���ɉ����������N

	//����I�����Ă��邩
	enum class Menu {
		Continue,
		Title
	}isSelect = Menu::Continue;
	//����t���O
	bool isReturn = false;

	Object3D skyDome;

	GameTimer* timer_ = nullptr;

};


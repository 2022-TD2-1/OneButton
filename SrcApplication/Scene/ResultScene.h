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
	float testTime = 76.31f;
	//�\������4�̐���������ϐ�
	float displayNum[4];
	//�����摜
	Sprite numSprite[10];
	//�����_�摜
	Sprite dotSprite;

	//����I�����Ă��邩
	enum class Menu {
		Continue,
		Title
	}isSelect = Menu::Continue;
	//����t���O
	bool isReturn = false;

};


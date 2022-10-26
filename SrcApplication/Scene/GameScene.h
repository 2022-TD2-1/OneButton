#pragma once
#include "IScene.h"
#include "Matrix.h"
#include "Model.h"
#include "Object3D.h"
#include "Sprite.h"
#include "Camera.h"
#include "Input.h"
#include <Player.h>
#include <Boss.h>
#include <TitleObj.h>
#include <GameTimer.h>
#include <SoundManager.h>
using namespace Input;

class GameScene :
	public IScene
{
public:
	~GameScene() {};
	void Init() override;
	void Update() override;
	void DrawBack() override;
	void Draw3D() override;
	void DrawSprite() override;

	//別シーンから開始状態を設定
	void SetState(int state);

private:
	Player* player;

	Camera camera;

	Boss* boss;

	Object3D guide;

	Object3D SkyDome;

	TitleObj* titleObj;

	Object3D spaceObj;

	GameTimer* timer_ = nullptr;

	Sprite aoeSpr;

	

	enum GameState {
		Title_,
		Gamescene_
	}gameState = Title_;
};


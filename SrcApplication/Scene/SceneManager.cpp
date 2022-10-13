#include "SceneManager.h"
#include "GameScene.h"
#include "TestScene.h"
#include "TitleScene.h"
#include "Input.h"
#include "MonkeyScene.h"
#include "FrameRate.h"

void SceneManager::Init()
{
	Transition<GameScene>();
}

void SceneManager::Update()
{
	FrameRate::FrameStartWithWait();
	currentScene->Update();

	if (Input::Key::Triggered(DIK_R))
	{
		Transition<GameScene>();
	}
	if (Input::Key::Triggered(DIK_0))
	{
		Transition<TitleScene>();
	}

}

void SceneManager::Draw3D()
{
	currentScene->Draw3D();
}

void SceneManager::DrawSprite()
{
	currentScene->DrawSprite();
}

void SceneManager::DrawBack()
{
	currentScene->DrawBack();
}

template <class NextScene> void SceneManager::Transition()
{
	delete currentScene.release();
	Light::Init();
	currentScene = unique_ptr<NextScene>(new NextScene());
	currentScene->Init();
	FrameRate::InitMark();
}

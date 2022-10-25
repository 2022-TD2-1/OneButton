#include "Essentials.h"
#include "wWindow.h"
#include "wDirectX.h"
#include "Input.h"
#include "wSwapChainManager.h"
#include "wDepth.h"
#include "wShader.h"
#include "GPipeline.h"
#include "wTexture.h"
#include "Vec3.h"
#include "wConstBuffer.h"
#include "Object3D.h"
#include "Matrix.h"
#include "wRootSignature.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "TextDrawer.h"
#include "GPipelineManager.h"
#include <Parameters.h>
#include <chrono>
#include "GameTimer.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//����������
	srand(std::chrono::system_clock::now().time_since_epoch().count());
	/*�f�o�b�O�L����*/
#ifdef  _DEBUG
	ID3D12Debug1* debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
		debugController->SetEnableGPUBasedValidation(TRUE);
	}
#endif //  _DEBUG

	//�E�B���h�E�𐶐�
	{
		wWindow wwnd;
		wwnd.Create(L"DirectX", CommonParams::Win::width, CommonParams::Win::height);
		RegisterwWindow(wwnd, "Default");
	}

	/*DirectX����������*/
	InitWDX();
	HRESULT result;

	//Init Input
	Input::Key::Init();
	Input::Pad::Init();

	/*Init Draw*/
	//�_�u���o�b�t�@�����O�Ƃ�
	InitWSCM();
	InitWDepth();

	wTextureManager::Create();

	CreateAndInitRootSignature();

	GPipelineManager::CreateAll();

	/*Init Draw End*/
	Sprite::InitCommon();

	//Init Scene
	SceneManager::Init();

	GameTimer* timer = GameTimer::GetInstance();
	

	/*�f�o�b�O�L����*/
#ifdef  _DEBUG
	ComPtr<ID3D12InfoQueue> infoQueue;
	if (SUCCEEDED(GetWDX()->dev->QueryInterface(IID_PPV_ARGS(&infoQueue))))
	{
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
		infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
	}
#endif //  _DEBUG
	/*���[�v*/
	while (true)
	{
		if (GetWDX()->StartFrame()) break;
		Input::Key::Update();
		Input::Pad::Update();

		/*���t���[������*/
		timer->Update();
		/*�X�V����*/
		SceneManager::Update();
		/*�X�V���������܂�*/

		GetWDX()->PreDrawCommands();

		try{
			Light::UpdateLightData();
		}
		catch (PointLight::QuantityOverflow& e) {
			assert(false);
		}

		Light::Use();

		Sprite::PreSpriteDraw();
		SceneManager::DrawBack();

		Sprite::PostSpriteDraw();

		GetWDX()->PreDraw3D();

		SceneManager::Draw3D();

		Sprite::PreSpriteDraw();

		SceneManager::DrawSprite();

		Sprite::PostSpriteDraw();

		GetWDX()->PostDrawCommands();

		/*���t���[�����������܂�*/
		GetWDX()->EndFrame();

		/*DrawString�p�̃f�[�^�����*/
		TextDrawer::ReleaseDrawStringData();
	}
	/*���[�v�����܂�*/
	CloseAllwWindow();

	return 0;
}
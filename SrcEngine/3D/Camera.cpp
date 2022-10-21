#include <random>
#include "Camera.h"

Camera::Camera()
{
}

void Camera::SetRenderSize(UINT w, UINT h)
{
	renderWidth = w;
	renderHeight = h;
}

void Camera::ShakeSet(int time, float base, float power)
{
	shakeTime = time;
	maxShakeTime = shakeTime;
	basePower = base;
	power_ = power;
}

void Camera::Shake()
{
	Vec3 shakeDist{};
	Vec2 dist;
	if (shakeTime > 0) {
		shakeTime--;
		//乱数シード生成器
		std::random_device seed_gen;
		//メルセンヌ・ツイスターの乱数エンジン
		std::mt19937_64 engine(seed_gen());
		//振動の大きさ
		if (shakeTime > maxShakeTime * 0.8f) {
			dist = { -basePower * (power_ * 0.8f) , basePower * (power_ * 0.8f) };
		}
		else if (shakeTime > maxShakeTime * 0.6f) {
			dist = { -basePower * (power_ * 0.5f), basePower * (power_ * 0.5f) };
		}
		else if (shakeTime > maxShakeTime * 0.4f) {
			dist = { -basePower * (power_ * 0.2f), basePower * (power_ * 0.2f) };
		}
		else if (shakeTime > maxShakeTime * 0.2f) {
			dist = { -basePower * (power_ * 0.05f), basePower * (power_ * 0.05f) };
		}
		std::uniform_real_distribution<float> transDistX(dist.x, dist.y);
		std::uniform_real_distribution<float> transDistY(dist.x, dist.y);

		shakeDist.x = transDistX(engine);
		shakeDist.y = transDistX(engine);

		position = originalPos + shakeDist;
	}
	else {
		//元の座標を代入する
		position = originalPos;
	}

	

	UpdateMatrix();

}

void Camera::OriginalPosSet()
{
	originalPos = position;
}

void Camera::Set(Camera& camera)
{
	D3D12_VIEWPORT viewport{};

	viewport.Width = camera.renderWidth;
	viewport.Height = camera.renderHeight;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	GetWDX()->cmdList->RSSetViewports(1, &viewport);

	D3D12_RECT scissorrect{};

	scissorrect.left = 0;                                       // 切り抜き座標左
	scissorrect.right = scissorrect.left + camera.renderWidth;        // 切り抜き座標右
	scissorrect.top = 0;                                        // 切り抜き座標上
	scissorrect.bottom = scissorrect.top + camera.renderHeight;       // 切り抜き座標下

	GetWDX()->cmdList->RSSetScissorRects(1, &scissorrect);

	Matrix vMat = camera.targetMode == CameraTargetMode::LookAt ? 
		Matrix::ViewLookAt(camera.position, camera.target, camera.matWorld.ExtractAxisY()) : 
		Matrix::ViewLookTo(camera.position, camera.matWorld.ExtractAxisZ(), camera.matWorld.ExtractAxisY());

	Matrix pMat = camera.projectionMode == ProjectionMode::Perspective ? 
		Matrix::Projection(camera.fov, (float)camera.renderWidth / (float)camera.renderHeight, camera.nearZ, camera.farZ) :
		Matrix::ProjectionOrtho((float)camera.renderWidth, (float)camera.renderHeight, camera.nearZ, camera.farZ, 20);

	camera.cameraViewProjMatrixCB.contents->vproj = vMat * pMat;
	camera.cameraViewProjMatrixCB.contents->cameraPos = camera.position;

	GetWDX()->cmdList->SetGraphicsRootConstantBufferView(3, camera.cameraViewProjMatrixCB.buffer->GetGPUVirtualAddress());
}

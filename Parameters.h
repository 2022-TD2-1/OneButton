#pragma once

namespace PlayerParams {
	//移動量1につき何度移動するか
	constexpr float degPerMove = 1.25f;

	//回転半径
	constexpr float circleR = 8;

	//当てた時のダメージ
	constexpr int damage = 10;

	//Stateごとのタイマー用
	constexpr int backTime = 30;
	constexpr int attackTime = 30;
}

namespace BossParams {
	constexpr float bulletSpeed = 0.05f;
	//弾幕の発射間隔(ミリ秒)
	constexpr float bulletCD = 500;
	//弾幕の発射間隔(角度)
	constexpr float bulletDeg = 30;

	//レーザーの速度
	constexpr float laserSpeed = 3.141592f / 1800 * 1.25/2;
}

namespace CommonParams {
	namespace Win {
		constexpr int width = 1280;
		constexpr int height = 720;
	}
}

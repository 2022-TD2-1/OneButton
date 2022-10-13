#pragma once

namespace PlayerParams {
	//移動量1につき何度移動するか
	constexpr float degPerMove = 2;

	//回転半径
	constexpr float circleR = 8;

	//当てた時のダメージ
	constexpr int damage = 10;

	//Stateごとのタイマー用
	constexpr int backTime = 30;
	constexpr int attackTime = 30;
}

namespace CommonParams {
	namespace Win {
		constexpr int width = 1280;
		constexpr int height = 720;
	}
}

#pragma once

namespace PlayerParams {
	//移動量1につき何度移動するか
	constexpr float degPerMove = 2;

	//攻撃速度ごとの攻撃間隔(フレーム)
	constexpr int attackTime[4] = {16, 8, 4, 2};

	constexpr float circleR = 8;
}

namespace CommonParams {
	namespace Win {
		constexpr int width = 1280;
		constexpr int height = 720;
	}
}

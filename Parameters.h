#pragma once

namespace PlayerParams {
	//ˆÚ“®—Ê1‚É‚Â‚«‰½“xˆÚ“®‚·‚é‚©
	constexpr float degPerMove = 2;

	//UŒ‚‘¬“x‚²‚Æ‚ÌUŒ‚ŠÔŠu(ƒtƒŒ[ƒ€)
	constexpr int attackTime[4] = {16, 8, 4, 2};

	//‰ñ“]”¼Œa
	constexpr float circleR = 8;
}

namespace CommonParams {
	namespace Win {
		constexpr int width = 1280;
		constexpr int height = 720;
	}
}

#pragma once

namespace PlayerParams {
	//�ړ���1�ɂ����x�ړ����邩
	constexpr float degPerMove = 2;

	//�U�����x���Ƃ̍U���Ԋu(�t���[��)
	constexpr int attackTime[4] = {16, 8, 4, 2};

	//��]���a
	constexpr float circleR = 8;
}

namespace CommonParams {
	namespace Win {
		constexpr int width = 1280;
		constexpr int height = 720;
	}
}

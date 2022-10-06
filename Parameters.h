#pragma once

namespace PlayerParams {
	//�ړ���1�ɂ����x�ړ����邩
	constexpr float degPerMove = 1;

	//�U�����x���Ƃ̍U���Ԋu(�t���[��)
	constexpr int attackTime[4] = {16, 8, 4, 2};
}

namespace CommonParams {
	namespace Win {
		constexpr int width = 1280;
		constexpr int height = 720;
	}
}

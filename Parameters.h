#pragma once

namespace PlayerParams {
	//�ړ���1�ɂ����x�ړ����邩
	constexpr float degPerMove = 2;

	//��]���a
	constexpr float circleR = 8;

	//���Ă����̃_���[�W
	constexpr int damage = 10;

	//State���Ƃ̃^�C�}�[�p
	constexpr int backTime = 30;
	constexpr int attackTime = 30;
}

namespace CommonParams {
	namespace Win {
		constexpr int width = 1280;
		constexpr int height = 720;
	}
}

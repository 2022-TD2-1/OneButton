#pragma once

namespace PlayerParams {
	//�ړ���1�ɂ����x�ړ����邩
	constexpr float degPerMove = 1.25f;

	//��]���a
	constexpr float circleR = 8;

	//���Ă����̃_���[�W
	constexpr int damage = 10;

	//State���Ƃ̃^�C�}�[�p
	constexpr int backTime = 30;
	constexpr int attackTime = 30;
}

namespace BossParams {
	constexpr float bulletSpeed = 0.05f;
	//�e���̔��ˊԊu(�~���b)
	constexpr float bulletCD = 500;
	//�e���̔��ˊԊu(�p�x)
	constexpr float bulletDeg = 30;

	//���[�U�[�̑��x
	constexpr float laserSpeed = 3.141592f / 1800 * 1.25/2;
}

namespace CommonParams {
	namespace Win {
		constexpr int width = 1280;
		constexpr int height = 720;
	}
}

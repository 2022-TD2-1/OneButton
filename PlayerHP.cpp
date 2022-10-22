#include <ModelManager.h>
#include "PlayerHP.h"

void PlayerHP::Ini(float posX)
{
	hpObj.model = ModelManager::Get("Heart");
	hpObj.position.x = posX;
	hpObj.position.y = -10;
	hpObj.position.z = 0;
	hpObj.rotation = { 0,0,0 };
	hpObj.scale = { 0.7f,0.7f,0.7f };
	hpObj.UpdateMatrix();

	prePos = hpObj.position;
	preScl = hpObj.scale;
}

void PlayerHP::Update()
{

	t += 1;

	if (t < 60) {
		hpObj.position.y = Vec3::easeOutBack(t, prePos.y, 5, 60);
	}

	if (t < 120) {
		hpObj.scale.x = Vec3::easeInOutBack(t, preScl.x, -8, 120);
		hpObj.scale.y = Vec3::easeInOutBack(t, preScl.y, -8, 120);
		hpObj.scale.z = Vec3::easeInOutBack(t, preScl.z, -8, 120);
	}

	hpObj.rotation += { 0,0.3f,0 };

	if (hpObj.scale.x <= 0) {
		isDead = true;
	}

	hpObj.UpdateMatrix();
}

void PlayerHP::Draw()
{
	(*hpObj.brightnessCB.contents) = Float4{ 1.0f, 0.5f, 1.0f, 0.4f };
	hpObj.Draw("white");
}

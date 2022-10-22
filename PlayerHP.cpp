#include <ModelManager.h>
#include "PlayerHP.h"

void PlayerHP::Ini(float posX)
{
	hpObj.model = ModelManager::Get("Sphere");
	hpObj.position.x = posX;
	hpObj.position.y = -10;
	hpObj.position.z = 0;
	hpObj.rotation = { 0,0,0 };
	hpObj.scale = { 1,1,1 };
	hpObj.UpdateMatrix();
}

void PlayerHP::Update()
{
	if (hpObj.position.y <= -6) {
		hpObj.position.y += 0.2;

		if (hpObj.scale.x <= 2.5f) {
			hpObj.scale += {0.05, 0.05, 0.05};
		}
	}
	else {
		if (hpObj.scale.x > 0) {
			hpObj.scale.x -= 0.1;
			hpObj.scale.y -= 0.1;
			hpObj.scale.z -= 0.1;
		}
		else if (hpObj.scale.x <= 0) {
			hpObj.scale.x =0;
			hpObj.scale.y =0;
			hpObj.scale.z =0;

			isDead = true;
		}
	}
	
	hpObj.UpdateMatrix();
}

void PlayerHP::Draw()
{
	(*hpObj.brightnessCB.contents) = Float4{ 1.0f, 0.5f, 1.0f, 0.4f };
	hpObj.Draw("white");
}

#include "ModelManager.h"
#include "TitleObj.h"

void TitleObj::Ini()
{
	model = ModelManager::Get("Sphere");
	position = { 0,0,0 };
	scale = { 1,1,1 };

	UpdateMatrix();
}

void TitleObj::Update()
{

	col.x = position.x;
	col.y = position.y;
	col.r = scale.x;

	UpdateMatrix();
}

void TitleObj::Draw()
{
	Object3D::Draw();
}

void TitleObj::Hit(PlayerOption* other)
{
}

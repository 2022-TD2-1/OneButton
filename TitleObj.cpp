#include "ModelManager.h"
#include "TitleObj.h"

unique_ptr<TitleObj> TitleObj::current = nullptr;

void TitleObj::Ini()
{
	model = ModelManager::Get("Sphere");
	position = { 0,0,0 };
	scale = { 2,2,2 };

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
	health--;
}



TitleObj* TitleObj::Create()
{
	current = unique_ptr<TitleObj>(new TitleObj);
	return current.get();
}

TitleObj* TitleObj::GetCurrent()
{
	return current.get();
}

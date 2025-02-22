#pragma once
#include "IScene.h"
#include "wMath.h"
#include "Camera.h"
#include "Sprite.h"
#include "Billboard.h"
class TestScene :
    public IScene
{
public:
    ~TestScene() {};
    void Init() override;
    void Update() override;
    void DrawBack() override;
    void Draw3D() override;
    void DrawSprite() override;

private:
    Camera camera;
    Sprite cameraSpr;
    Camera xCam;
    Sprite xCamSpr;
    Camera yCam;
    Sprite yCamSpr;
    Camera zCam;
    Sprite zCamSpr;

    Camera finalScene;

    Object3D ray;
    BillboardY pane;

    Model mSphere;
    Model mCube;
    Model mPane;

    TextureKey whiteTex;

    Model sky;

    Object3D skysphere;
};


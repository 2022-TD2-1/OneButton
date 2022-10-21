#pragma once
#include "Object3D.h"

struct ConstBufferDataVProj {
    Matrix vproj;
    Float3 cameraPos;
};

enum class CameraTargetMode {
    LookAt,
    LookTo
};

enum class ProjectionMode {
    Orthographic,
    Perspective
};

class Camera :
    public Object3D
{
public:
    Camera();
    void SetRenderSize(UINT w, UINT h);

    

    Float3 target = {0.0f, 0.0f, 0.0f};

    float fov;

    UINT renderWidth;
    UINT renderHeight;

    float nearZ;
    float farZ;

    wConstBuffer<ConstBufferDataVProj> cameraViewProjMatrixCB;

    CameraTargetMode targetMode = CameraTargetMode::LookTo;

    static void Set(Camera& camera);

    ProjectionMode projectionMode = ProjectionMode::Perspective;

    void ShakeSetTime(int time, float base, float power);
    float basePower;
    float power_;

    void Shake();
    void OriginalPosSet();
    //シェイクする前の場所
    Vec3 originalPos;
    int maxShakeTime;
    int shakeTime = 0;
};


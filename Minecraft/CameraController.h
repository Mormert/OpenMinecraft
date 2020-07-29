#pragma once

#include "Camera.h"

class CameraController
{
public:
	static void MoveCameraBasedOnInput(Camera &camera, float dt);
};


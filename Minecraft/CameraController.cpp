#include "CameraController.h"

#include "InputManager.h"

void CameraController::MoveCameraBasedOnInput(Camera& camera, float dt)
{
	if (InputManager::GetKeyDown('A'))
	{
		camera.ProcessKeyboard(CAMERA_LEFT, dt);
	}

	if (InputManager::GetKeyDown('D'))
	{
		camera.ProcessKeyboard(CAMERA_RIGHT, dt);
	}

	if (InputManager::GetKeyDown('W'))
	{
		camera.ProcessKeyboard(CAMERA_FORWARD, dt);
	}

	if (InputManager::GetKeyDown('S'))
	{
		camera.ProcessKeyboard(CAMERA_BACKWARD, dt);
	}

	camera.ProcessMouseMovement(InputManager::GetMouseXDelta(), InputManager::GetMouseYDelta());
}
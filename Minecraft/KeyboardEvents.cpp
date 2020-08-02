#include "KeyboardEvents.h"

#include "InputManager.h"

#include "EngineStatus.h"
#include "InputState.h"

#include "Camera.h"

#include <iostream>

void ProcessMovement()
{
	Camera* camera = Camera::GetMainCamera();
	float dt = static_cast<float>(EngineStatus::GetDeltaTime());

	if (InputManager::GetKeyDown('A'))
	{
		camera->ProcessKeyboard(CAMERA_LEFT, dt);
	}

	if (InputManager::GetKeyDown('D'))
	{
		camera->ProcessKeyboard(CAMERA_RIGHT, dt);
	}

	if (InputManager::GetKeyDown('W'))
	{
		camera->ProcessKeyboard(CAMERA_FORWARD, dt);
	}

	if (InputManager::GetKeyDown('S'))
	{
		camera->ProcessKeyboard(CAMERA_BACKWARD, dt);
	}

	camera->ProcessMouseMovement(InputManager::GetMouseXDelta(),
		InputManager::GetMouseYDelta());
}

void ProcessInputState()
{
	if (InputManager::GetKeyDown('0'))
	{
		InputState::state.showDebugInfo = !InputState::state.showDebugInfo;
	}
}

void KeyboardEvents::ProcessKeyboardEvents()
{
	ProcessMovement();
	ProcessInputState();
}
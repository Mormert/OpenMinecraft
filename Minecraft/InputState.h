#pragma once

struct InputStateStruct
{
	bool showDebugInfo{ true };
	// volume, graphics settings etc etc to be added...
};

class InputState
{
public:
	static InputStateStruct state;
};


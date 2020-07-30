#pragma once

#include <string>

class BlockType
{
public:
	std::string blockName;
	float destructTime;

	void Init(unsigned int id);

	unsigned int GetVAO();

private:
	unsigned int VAO, VBO;

public:
	static BlockType *GetBlockType(unsigned int id);
	static void InitBlockTypes(const char *texturePath);

private:
	static BlockType blockTypeList[256];
	static unsigned int TextureID;
};
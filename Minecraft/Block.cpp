#include "Block.h"

#include "BlockType.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Block::Block(unsigned int id) : block_id{ id } {}

Block::Block() : block_id { 17 } {}

void Block::Draw(Shader *shader, int x, int y, int z)
{

	BlockType *blockType{ BlockType::GetBlockType(block_id) };

	glm::mat4 model{ 1.0f };
	model = glm::translate(model, glm::vec3{static_cast<float>(x),
		static_cast<float>(y),
		static_cast<float>(z)});

	shader->Use();
	shader->SetMat4("model", model);

	glBindVertexArray(blockType->GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 36);

}
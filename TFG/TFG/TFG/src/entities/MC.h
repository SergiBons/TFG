#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "objLoader.h"
#include "board/Board.h"


class MC
{
private:
	COBJModel m_ObOBJ;
	int m_jCounter;
	int m_checker;
	int m_surrounds[4];





public:
	glm::vec3 m_CenterPos;
	glm::mat4 m_ModelMatrix;
	int m_hp;
	int m_stagger;
	bool m_floored;
	glm::vec3 m_DirectionVector;
	MC();
	~MC();

	void DrawMC(unsigned int shaderID);
	void Attack();
	bool Move(int dir);
	void Read(Texture tex, Renderer rend, Shader shad);
	void Look();
	void Jump(int state);
	void UpdateStates(char* board, glm::mat4& view);




};
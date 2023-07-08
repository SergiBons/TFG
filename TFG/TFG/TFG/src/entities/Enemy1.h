#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "objLoader.h"
#include "board/Board.h"
#include <memory>


class Enemy
{
private:

	glm::vec3 m_target;
	glm::vec3 m_direction;
	glm::vec3 m_mid;
	float m_AccTime;
	float m_Scale;
	int m_Surrounds[4];
	bool m_falling;

public:
	glm::mat4 m_rotation;
	glm::vec3 m_CenterPos;
	glm::mat4 m_ModelMatrix;
	int m_hp;
	float m_stagger;
	bool m_floored;
	Enemy(float x, float z);
	~Enemy();
	int Attack(glm::vec3 mChPos, float deltaTime, int attackRange);
	bool Move(int dir);
	int UpdateStates(char* board, glm::vec3 mChPos, float deltaTime, int attackRange);
	//Triangular movement by default, if player in range, lounge slightly through

	int ReDamage(int DamageType);

};
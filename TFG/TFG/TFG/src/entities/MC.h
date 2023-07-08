#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "objLoader.h"
#include "board/Board.h"
#include <memory>


class MC
{
private:
	COBJModel m_ObOBJ[4];
	COBJModel m_hpModel[3];

	int m_checker;
	int m_surrounds[8];
	int m_interact;
	glm::vec3 m_lastCommonBlock;
	float m_invulnerability;
	std::unique_ptr<Shader> m_shad;




public:
	int m_jCounter;
	glm::mat4 m_LLM;
	glm::mat4 m_LRM;
	glm::vec3 m_CenterPos;
	glm::mat4 m_ModelMatrix;
	glm::mat4 m_Rotation;
	int m_hp;
	float m_stagger;
	bool m_floored;
	int m_attackRange;
	float m_AccTime;
	glm::vec3 m_DirectionVector;
	MC();
	~MC();
	void DrawMCA(unsigned int shaderID);
	void DrawMCB(unsigned int shaderID);
	void DrawMCLR(unsigned int shaderID);
	void DrawMCLL(unsigned int shaderID);
	void Attack(std::unique_ptr<Shader>& shad, float accTime ,char* board);
	bool Move(int dir, float deltaTime);
	bool Read(unsigned int shaderID);
	void Look();
	void Jump();
	void HealthDisplay(std::unique_ptr<Shader> &shad);
	void ReDamage(int DamageType, glm::mat4& view);
	void UpdateStates(char* board, glm::mat4& view, glm::vec3 MousePos, int sW, int sH, int dmg, float deltaTime);
	void AimToCursor(glm::vec3 MousePos, glm::mat4& view, int sW, int sH);

};
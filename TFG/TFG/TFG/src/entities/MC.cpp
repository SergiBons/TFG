#include "MC.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>


int TimeSet = -1;
float AnimationCycle = 0;
MC::MC()
{
	m_CenterPos = glm::vec3(0.0f, 0.0f, 0.0f);
	std::string nomFitxer = "res/Models/MC/MainCharB.obj";
	m_ObOBJ[0].LoadModel(const_cast<char*>(nomFitxer.c_str()));
	nomFitxer = "res/Models/MC/MainCharA.obj";
	m_ObOBJ[1].LoadModel(const_cast<char*>(nomFitxer.c_str()));
	nomFitxer = "res/Models/MC/MainCharLR.obj";
	m_ObOBJ[2].LoadModel(const_cast<char*>(nomFitxer.c_str()));
	nomFitxer = "res/Models/MC/MainCharLL.obj";
	m_ObOBJ[3].LoadModel(const_cast<char*>(nomFitxer.c_str()));
	nomFitxer = "res/Models/Tile1_14/Tile1_14.obj";
	m_hpModel[0].LoadModel(const_cast<char*>(nomFitxer.c_str()));
	nomFitxer = "res/Models/Tile1_13/Tile1_13.obj";
	m_hpModel[1].LoadModel(const_cast<char*>(nomFitxer.c_str()));
	nomFitxer = "res/Models/Tile1_12/Tile1_12.obj";
	m_hpModel[2].LoadModel(const_cast<char*>(nomFitxer.c_str()));
	m_DirectionVector = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ModelMatrix = glm::mat4(1.0f);
	m_hp = 3;
	m_jCounter = 0;
	m_AccTime = 0;
	m_stagger = 0;
	m_checker = -1;
	m_floored = true;
	m_interact = 0;
	m_invulnerability = 0;
	m_lastCommonBlock = glm::vec3(0);
	m_shad = nullptr;
	m_Rotation = glm::mat4(1.0f);
	m_attackRange = 0;
	for (int i = 0; i < 8; i++)
		m_surrounds[i] = 0;
}

MC::~MC()
{
}



void MC::DrawMCB(unsigned int shaderID)
{
	m_ObOBJ[0].draw_TriVAO_OBJ(shaderID);
}

void MC::DrawMCA(unsigned int shaderID)
{
	m_ObOBJ[1].draw_TriVAO_OBJ(shaderID);
}

void MC::DrawMCLR(unsigned int shaderID)
{
	m_ObOBJ[2].draw_TriVAO_OBJ(shaderID);
}

void MC::DrawMCLL(unsigned int shaderID)
{
	m_ObOBJ[3].draw_TriVAO_OBJ(shaderID);
}


void MC::Attack(std::unique_ptr<Shader>& shad, float accTime, char* board)
{
	
	if (TimeSet == -1.0f)
	{
		TimeSet = 1;
		m_AccTime = 0.0f;
	}
		const int boardWidth = 250;
	const int boardHeight = 20;
	const int boardSize = boardWidth * boardHeight;
	int floorCorrectedX = static_cast<int>(round(m_CenterPos.x));
	int floorCorrectedZ = static_cast<int>(round(m_CenterPos.z));
	int floorCorrectedY = (m_CenterPos.y < 7) ? ((m_CenterPos.y < 4) ? 0 : 1) : 2;


	if (m_surrounds[0] == 2) {
		board[floorCorrectedX + (floorCorrectedZ-1) * boardWidth + (2 - floorCorrectedY) * boardSize] = '1';
	}
	if (m_surrounds[1] == 2) {
		board[(floorCorrectedX + 1) + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize] = '1';
	}
	if (m_surrounds[2] == 2) {
		board[floorCorrectedX + (floorCorrectedZ+1) * boardWidth + (2 - floorCorrectedY) * boardSize] = '1';
	}
	if (m_surrounds[3] == 2) {
		board[(floorCorrectedX - 1) + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize] = '1';
	}
	if (m_surrounds[0] == 3) {
		board[floorCorrectedX + (floorCorrectedZ - 1) * boardWidth + (2 - floorCorrectedY) * boardSize] = '1';
		if (board[floorCorrectedX + (floorCorrectedZ - 2) * boardWidth + (2 - floorCorrectedY) * boardSize] == '0')
			board[floorCorrectedX + (floorCorrectedZ - 2) * boardWidth + (2 - floorCorrectedY) * boardSize] = '8';
		else
			if (board[floorCorrectedX + (floorCorrectedZ - 2) * boardWidth + (2 - floorCorrectedY) * boardSize] == '1')
				board[floorCorrectedX + (floorCorrectedZ - 2) * boardWidth + (2 - floorCorrectedY) * boardSize] = '3';
	}
	if (m_surrounds[1] == 3) {
		board[(floorCorrectedX + 1) + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize] = '1';
		if (board[(floorCorrectedX + 2) + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize] == '0')
			board[(floorCorrectedX + 2) + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize] = '8';
		else
			if (board[(floorCorrectedX + 2) + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize] == '1')
				board[(floorCorrectedX + 2) + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize] = '3';
	}
	if (m_surrounds[2] == 3) {
		board[floorCorrectedX + (floorCorrectedZ + 1) * boardWidth + (2 - floorCorrectedY) * boardSize] = '1';
		if (board[floorCorrectedX + (floorCorrectedZ + 2) * boardWidth + (2 - floorCorrectedY) * boardSize] == '0')
			board[floorCorrectedX + (floorCorrectedZ + 2) * boardWidth + (2 - floorCorrectedY) * boardSize] = '8';
		else
			if (board[floorCorrectedX + (floorCorrectedZ + 2) * boardWidth + (2 - floorCorrectedY) * boardSize] == '1')
				board[floorCorrectedX + (floorCorrectedZ + 2) * boardWidth + (2 - floorCorrectedY) * boardSize] = '3';
	}
	if (m_surrounds[3] == 3) {
		board[(floorCorrectedX - 1) + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize] = '1';
		if (board[(floorCorrectedX - 2) + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize] == '0')
			board[(floorCorrectedX - 2) + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize] = '8';
		else
			if (board[(floorCorrectedX - 2) + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize] == '1')
				board[(floorCorrectedX - 2) + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize] = '3';
	}




}

bool MC::Move(int dir, float deltaTime)
{
	float adjust = 3.333333333333f;
	float decim = 0.1f;
	int hVal[4] = { 0, 0, 0, 0 };

	if (m_CenterPos.y >= 3)
	{
		if (m_surrounds[4] == 1)
			hVal[0] = 4;
		if (m_surrounds[5] == 1)
			hVal[1] = 4;
		if (m_surrounds[6] == 1)
			hVal[2] = 4;
		if (m_surrounds[7] == 1)
			hVal[3] = 4;
	}
	else
	{
		if (m_surrounds[0] == 3 || m_surrounds[0] == 4 || m_surrounds[0] == 6)
			hVal[0] = 2;
		if (m_surrounds[1] == 3 || m_surrounds[1] == 4 || m_surrounds[1] == 6)
			hVal[1] = 2;
		if (m_surrounds[2] == 3 || m_surrounds[2] == 4 || m_surrounds[2] == 6)
			hVal[2] = 2;
		if (m_surrounds[3] == 3 || m_surrounds[3] == 4 || m_surrounds[3] == 6)
			hVal[3] = 2;

		if (m_surrounds[0] == 2 || m_surrounds[0] == 5)
			hVal[0] = 3;
		if (m_surrounds[1] == 2 || m_surrounds[1] == 5)
			hVal[1] = 3;
		if (m_surrounds[2] == 2 || m_surrounds[2] == 5)
			hVal[2] = 3;
		if (m_surrounds[3] == 2 || m_surrounds[3] == 5)
			hVal[3] = 3;
	}

	if (m_stagger <= 0) {
		float auxCycle = AnimationCycle;
		if (AnimationCycle > 2)
				auxCycle = 2-AnimationCycle;
		float value = 4.0f;
		float animationSpeed = 0.05f;
		float rotationAngle = 0; // Angle in radians
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0], m_ModelMatrix[3][1], m_ModelMatrix[3][2]));
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f/3));
		switch (dir)
		{
		case 0:
			decim = m_CenterPos.z - floor(m_CenterPos.z);
			if(decim > 0.90f)
			{
				if(hVal[0] <= m_CenterPos.y)
				{
					m_CenterPos.z -= value*deltaTime;
					m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.0f, -value * adjust * deltaTime));
					translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0], m_ModelMatrix[3][1], m_ModelMatrix[3][2] + auxCycle * animationSpeed));
					m_LLM = translationMatrix * rotationMatrix * scaleMatrix;
					translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0], m_ModelMatrix[3][1], m_ModelMatrix[3][2] - auxCycle * animationSpeed));
					m_LRM = translationMatrix * rotationMatrix * scaleMatrix;
					return true;
				}
			}
			else
			{
				m_CenterPos.z -= value * deltaTime;
				m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.0f, -value * adjust * deltaTime));
				translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0], m_ModelMatrix[3][1], m_ModelMatrix[3][2] + auxCycle * animationSpeed));
				m_LLM = translationMatrix * rotationMatrix * scaleMatrix;
				translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0], m_ModelMatrix[3][1], m_ModelMatrix[3][2] - auxCycle * animationSpeed));
				m_LRM = translationMatrix * rotationMatrix * scaleMatrix;
				return true;
			}
			break;
			
		case 1:
			decim = m_CenterPos.x - (int)m_CenterPos.x;
			if (decim > 0.90f)
			{
				if (hVal[3] <= m_CenterPos.y)
				{
					m_CenterPos.x -= value * deltaTime;
					m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(-value * adjust * deltaTime, 0.0f, 0.0f));
					translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0] + auxCycle * animationSpeed, m_ModelMatrix[3][1], m_ModelMatrix[3][2] ));
					m_LLM = translationMatrix * rotationMatrix * scaleMatrix;
					translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0] - auxCycle * animationSpeed, m_ModelMatrix[3][1], m_ModelMatrix[3][2] ));
					m_LRM = translationMatrix * rotationMatrix * scaleMatrix;
					return true;
				}
			}
			else
			{
				m_CenterPos.x -= value * deltaTime;
				m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(-value * adjust * deltaTime, 0.0f, 0.0f));
				translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0] + auxCycle * animationSpeed, m_ModelMatrix[3][1], m_ModelMatrix[3][2]));
				m_LLM = translationMatrix * rotationMatrix * scaleMatrix;
				translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0] - auxCycle * animationSpeed, m_ModelMatrix[3][1], m_ModelMatrix[3][2]));
				m_LRM = translationMatrix * rotationMatrix * scaleMatrix;
				return true;
			}
			break;
		case 2:
			decim = m_CenterPos.z - (int)m_CenterPos.z;
			if (decim < 0.10f)
			{
				if (hVal[2] <= m_CenterPos.y)
				{
					m_CenterPos.z += value * deltaTime;
					m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.0f, value * adjust * deltaTime));
					translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0], m_ModelMatrix[3][1], m_ModelMatrix[3][2] + auxCycle * animationSpeed));
					m_LLM = translationMatrix * rotationMatrix * scaleMatrix;
					translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0], m_ModelMatrix[3][1], m_ModelMatrix[3][2] - auxCycle * animationSpeed));
					m_LRM = translationMatrix * rotationMatrix * scaleMatrix;
					return true;
				}
			}
			else
			{
				m_CenterPos.z += value * deltaTime;
				m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.0f, value * adjust * deltaTime));
				translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0], m_ModelMatrix[3][1], m_ModelMatrix[3][2] + auxCycle * animationSpeed));
				m_LLM = translationMatrix * rotationMatrix * scaleMatrix;
				translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0], m_ModelMatrix[3][1], m_ModelMatrix[3][2] - auxCycle * animationSpeed));
				m_LRM = translationMatrix * rotationMatrix * scaleMatrix;
				return true;
			}
			break;
		case 3:
			decim = m_CenterPos.x - (int)m_CenterPos.x;
			if (decim < 0.10f)
			{
				if (hVal[1] <= m_CenterPos.y)
				{
					m_CenterPos.x += value * deltaTime;
					m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(value * adjust * deltaTime, 0.0f, 0.0f));
					translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0] + auxCycle * animationSpeed, m_ModelMatrix[3][1], m_ModelMatrix[3][2]));
					m_LLM = translationMatrix * rotationMatrix * scaleMatrix;
					translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0] - auxCycle * animationSpeed, m_ModelMatrix[3][1], m_ModelMatrix[3][2]));
					m_LRM = translationMatrix * rotationMatrix * scaleMatrix;
					return true;
				}
			}
			else
			{
				m_CenterPos.x += value * deltaTime;
				m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(value * adjust * deltaTime, 0.0f, 0.0f));
				translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0] + auxCycle * animationSpeed, m_ModelMatrix[3][1], m_ModelMatrix[3][2]));
				m_LLM = translationMatrix * rotationMatrix * scaleMatrix;
				translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_ModelMatrix[3][0] - auxCycle * animationSpeed, m_ModelMatrix[3][1], m_ModelMatrix[3][2]));
				m_LRM = translationMatrix * rotationMatrix * scaleMatrix;
				return true;
			}
			break;

		}
	}
	return false;
}

bool MC::Read(unsigned int shaderID)
{
	if (m_surrounds[0] == 6 || m_surrounds[1] == 6 || m_surrounds[2] == 6 || m_surrounds[3] == 6)
		return true;
	else
	{
		//HealthDisplay();
		return false;
	}

}

void MC::Jump()
{
	if (m_stagger <= 0 && m_floored)
	{ 
		m_jCounter = 1;
	}
}

void MC::HealthDisplay(std::unique_ptr<Shader>& shad)
{
	glm::mat4 auxGUI = glm::translate(m_ModelMatrix, glm::vec3(-1.0f, 3.0f, -0.25f));
	if (m_invulnerability > 0)
	{
		switch (m_hp)
		{
		case 1:
			auxGUI = glm::translate(m_ModelMatrix, glm::vec3(-1.0f, 3.0f, -0.25f));
			auxGUI = glm::scale(auxGUI, glm::vec3(0.5f, 0.5f, 0.5f));
			shad->SetUniformMat4f("modelMatrix", auxGUI);
			m_hpModel[2].draw_TriVAO_OBJ(shad->GetID());
			break;
		case 2:
			auxGUI = glm::translate(m_ModelMatrix, glm::vec3(-1.0f, 3.0f, -0.25f));
			auxGUI = glm::scale(auxGUI, glm::vec3(0.5f, 0.5f, 0.5f));
			shad->SetUniformMat4f("modelMatrix", auxGUI);
			m_hpModel[1].draw_TriVAO_OBJ(shad->GetID());
			auxGUI = glm::translate(auxGUI, glm::vec3(2.0f, 0.0f, 0.0f));
			shad->SetUniformMat4f("modelMatrix", auxGUI);
			m_hpModel[1].draw_TriVAO_OBJ(shad->GetID());
			break;
		case 3:
			auxGUI = glm::translate(m_ModelMatrix, glm::vec3(-1.0f, 3.0f, -0.25f));
			auxGUI = glm::scale(auxGUI, glm::vec3(0.5f, 0.5f, 0.5f));
			shad->SetUniformMat4f("modelMatrix", auxGUI);
			m_hpModel[0].draw_TriVAO_OBJ(shad->GetID());
			auxGUI = glm::translate(auxGUI, glm::vec3(2.0f, 0.0f, 0.0f));
			shad->SetUniformMat4f("modelMatrix", auxGUI);
			m_hpModel[0].draw_TriVAO_OBJ(shad->GetID());
			auxGUI = glm::translate(auxGUI, glm::vec3(2.0f, 0.0f, 0.0f));
			shad->SetUniformMat4f("modelMatrix", auxGUI);
			m_hpModel[0].draw_TriVAO_OBJ(shad->GetID());
			break;
		default:
			auxGUI = glm::translate(m_ModelMatrix, glm::vec3(-1.0f, 3.0f, -0.25f));
			auxGUI = glm::scale(auxGUI, glm::vec3(0.5f, 0.5f, 0.5f));
			shad->SetUniformMat4f("modelMatrix", auxGUI);
			m_hpModel[2].draw_TriVAO_OBJ(shad->GetID());
			break;
		}
	}
}


void MC::ReDamage(int DamageType, glm::mat4 &view)
{
	if (m_invulnerability <= 0)
	{
		switch (DamageType)
		{
		case 1:
			//map Fall
			m_hp -= 1;
			m_ModelMatrix = glm::mat4(1.0f);
			m_ModelMatrix = glm::translate(m_ModelMatrix, (m_lastCommonBlock + glm::vec3(0.2f, 1.0f, -0.5f)));
			m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(0.30f, 0.30f, 0.30f));
			m_invulnerability = 2;
			m_stagger = 1.5;
			view = glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			view = glm::translate(view, glm::vec3(-m_lastCommonBlock.x - 1, -7, -m_lastCommonBlock.z - 4));
			m_CenterPos = m_lastCommonBlock;
			break;
		case 2:
			//enemy damage
			m_hp -= 1;
			m_invulnerability = 3;
			m_stagger = 1;
			break;
		}
	}

}

void MC::UpdateStates(char* board, glm::mat4& view, glm::vec3 MousePos, int sW, int sH, int dmg, float deltaTime)
{
	AnimationCycle += deltaTime*10;
	m_attackRange = 0;
	const int boardWidth = 250;
	const int boardHeight = 20;
	const int boardSize = boardWidth * boardHeight;

	int floorCorrectedX = static_cast<int>(round(m_CenterPos.x));
	int floorCorrectedZ = static_cast<int>(round(m_CenterPos.z));
	int floorCorrectedY = (m_CenterPos.y < 7) ? ((m_CenterPos.y < 4) ? 0 : 1) : 2;

	int floorValue = static_cast<int>(board[floorCorrectedX + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize]) - '0';

	// SurroundCheck
	/*
	0	1	2
	3		4
	5	6	7
	*/
	int offset = (2 - floorCorrectedY) * boardSize;
	m_surrounds[0] = static_cast<int>(board[floorCorrectedX + (floorCorrectedZ - 1) * boardWidth + offset]) - '0';
	m_surrounds[1] = static_cast<int>(board[floorCorrectedX + 1 + floorCorrectedZ * boardWidth + offset]) - '0';
	m_surrounds[2] = static_cast<int>(board[floorCorrectedX + (floorCorrectedZ + 1) * boardWidth + offset]) - '0';
	m_surrounds[3] = static_cast<int>(board[floorCorrectedX - 1 + floorCorrectedZ * boardWidth + offset]) - '0';

	if (floorCorrectedY < 2)
	{
		offset = (2 - 1) * boardSize;
		m_surrounds[4] = static_cast<int>(board[floorCorrectedX + (floorCorrectedZ - 1) * boardWidth + offset]) - '0';
		m_surrounds[5] = static_cast<int>(board[floorCorrectedX + 1 + floorCorrectedZ * boardWidth + offset]) - '0';
		m_surrounds[6] = static_cast<int>(board[floorCorrectedX + (floorCorrectedZ + 1) * boardWidth + offset]) - '0';
		m_surrounds[7] = static_cast<int>(board[floorCorrectedX - 1 + floorCorrectedZ * boardWidth + offset]) - '0';
	}

	switch (floorValue)
	{
	case 1:
		if (m_CenterPos.y < 1.10 + 3 * floorCorrectedY)
		{
			m_floored = true;
			m_lastCommonBlock = glm::vec3(floorCorrectedX, 1, floorCorrectedZ);
		}
		else
			m_floored = false;
		break;
	case 8:
		if (m_CenterPos.y < 1.10 + 3 * floorCorrectedY)
		{
			m_floored = true;
			m_lastCommonBlock = glm::vec3(floorCorrectedX, 1, floorCorrectedZ);
		}
		else
			m_floored = false;
		break;
	case 2:
		m_floored = (m_CenterPos.y < 3.10 + 3 * floorCorrectedY);
		break;
	case 3:
		m_floored = (m_CenterPos.y < 2.10 + 3 * floorCorrectedY);
		break;
	case 4:
		m_floored = (m_CenterPos.y < 2.10 + 3 * floorCorrectedY);
		break;
	case 5:
		m_floored = (m_CenterPos.y < 3.10 + 3 * floorCorrectedY);
		break;
	case 6:
		m_floored = (m_CenterPos.y < 2.10 + 3 * floorCorrectedY);
		break;
	default:
		m_floored = false;
		break;
	}

	float jumpForce = 40.0f * deltaTime;
	float scaleAdjust = 0.3f;

	switch (m_jCounter)
	{
	case 1:
		m_checker = m_CenterPos.y;
		m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.4f * jumpForce, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.4f * scaleAdjust * jumpForce, 0.0f));
		m_CenterPos.y += 0.4f * scaleAdjust * jumpForce;
		m_jCounter = 2;
		break;
	case 2:
		m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.6f * jumpForce, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.6f * scaleAdjust * jumpForce, 0.0f));
		m_CenterPos.y += 0.6f * scaleAdjust * jumpForce;
		if (m_CenterPos.y >= m_checker + 1)
			m_jCounter = 3;
		break;
	case 3:
		m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.2f * jumpForce, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.2f * scaleAdjust * jumpForce, 0.0f));
		m_CenterPos.y += 0.2f * scaleAdjust * jumpForce;
		if (m_CenterPos.y >= m_checker + 1.5)
			m_jCounter = 0;
		break;
	default:
		if (!m_floored)
		{
			if (m_CenterPos.y >= m_checker + 1)
			{
				m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, -0.2f * jumpForce, 0.0f));
				view = glm::translate(view, glm::vec3(0.0f, 0.2f * scaleAdjust * jumpForce, 0.0f));
				m_CenterPos.y -= 0.2f * scaleAdjust * jumpForce;
			}
			else
			{
				if (m_CenterPos.y <= m_checker - 0.5)
				{
					m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, -0.8f * jumpForce, 0.0f));
					view = glm::translate(view, glm::vec3(0.0f, 0.8f * scaleAdjust * jumpForce, 0.0f));
					m_CenterPos.y -= 0.8f * scaleAdjust * jumpForce;
				}
				else
				{
					m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, -0.5f * jumpForce, 0.0f));
					view = glm::translate(view, glm::vec3(0.0f, 0.5f * scaleAdjust * jumpForce, 0.0f));
					m_CenterPos.y -= 0.5f * scaleAdjust * jumpForce;
				}
			}
		}
		else
		{
			if (m_CenterPos.y < 1 + 3 * floorCorrectedY)
			{
				m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 5.0f*deltaTime, 0.0f));
				view = glm::translate(view, glm::vec3(0.0f, -5.0f * scaleAdjust * deltaTime, 0.0f));
				m_CenterPos.y += 5.0f * scaleAdjust * deltaTime;
			}
		}
		break;
	}

	if (TimeSet != -1)
	{
		m_AccTime += deltaTime;
		m_attackRange = 2;
		m_stagger = 0.4;
	}
	if (m_AccTime > 0.25)
	{
		TimeSet = -1.0f;
	}
	if (dmg != 0)
		ReDamage(dmg, view);
	AimToCursor(MousePos, view, sW, sH);



	if (m_CenterPos.y < -2)
	{
		m_stagger == 2;
		ReDamage(1, view);
		m_invulnerability += 3;
	}
	if (m_invulnerability > 0)
		m_invulnerability -= 1*deltaTime;
	if (m_stagger > 0)
		m_stagger -= 1*deltaTime;
	m_AccTime += deltaTime;
	if (AnimationCycle >= 4)
		AnimationCycle = 0;
}

void MC::AimToCursor(glm::vec3 MousePos, glm::mat4& view, int sW, int sH)
{
	if (m_stagger <=0)
	{ 
		/*
		glm::vec3 Translation = glm::vec3(m_ModelMatrix[3][0], m_ModelMatrix[3][1], m_ModelMatrix[3][2]);
		glm::mat4 Proj = glm::perspective(1.0f, 960.0f / 540.0f, 0.1f, 100.0f);


		// Extract the translation factors
		glm::vec3 translation = glm::vec3(m_ModelMatrix[3]);

		// Extract the scale factors
		glm::vec3 scale;
		scale.x = glm::length(glm::vec3(m_ModelMatrix[0]));
		scale.y = glm::length(glm::vec3(m_ModelMatrix[1]));
		scale.z = glm::length(glm::vec3(m_ModelMatrix[2]));
		*/
		// Apply rotation around the Y-axis
		glm::vec3 rotationAxis(0.0f, 1.0f, 0.0f);
		m_Rotation = glm::rotate(glm::mat4(1.0f), -std::atan2(MousePos.y -sH/3, MousePos.x - sW*5/12), rotationAxis);
		}
}
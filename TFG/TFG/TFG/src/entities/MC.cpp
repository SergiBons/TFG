#include "MC.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

MC::MC()
{
	m_CenterPos = glm::vec3(0.0f, 0.0f, 0.0f);
	std::string nomFitxer = "res/Models/MC/MainChar.obj";
	m_ObOBJ.LoadModel(const_cast<char*>(nomFitxer.c_str()));
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
	m_stagger = 0;
	m_checker = -1;
	m_floored = true;
	m_interact = 0;
	m_invulnerability = 0;
	m_lastCommonBlock = glm::vec3(0);
	for (int i = 0; i < 8; i++)
		m_surrounds[i] = 0;
}

MC::~MC()
{
}

void MC::DrawMC(unsigned int shaderID)
{
	m_ObOBJ.draw_TriVAO_OBJ(shaderID);
}

void MC::Attack()
{
	if (m_stagger == 0)
		m_stagger++;
}

bool MC::Move(int dir)
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

	if (m_stagger <= 5) {
		switch (dir)
		{
		case 0:
			decim = m_CenterPos.z - floor(m_CenterPos.z);
			if(decim > 0.90f)
			{
				if(hVal[0] <= m_CenterPos.y)
				{
					m_CenterPos.z -= 0.075f;
					m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.0f, -0.075f * adjust));
					return true;
				}
			}
			else
			{
				m_CenterPos.z -= 0.075f;
				m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.0f, -0.075f * adjust));
				return true;
			}
			break;
			
		case 1:
			decim = m_CenterPos.x - (int)m_CenterPos.x;
			if (decim > 0.90f)
			{
				if (hVal[3] <= m_CenterPos.y)
				{
					m_CenterPos.x -= 0.075f;
					m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(-0.075f * adjust, 0.0f, 0.0f));
					return true;
				}
			}
			else
			{
				m_CenterPos.x -= 0.075f;
				m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(-0.075f * adjust, 0.0f, 0.0f));
				return true;
			}
			break;
		case 2:
			decim = m_CenterPos.z - (int)m_CenterPos.z;
			if (decim < 0.10f)
			{
				if (hVal[2] <= m_CenterPos.y)
				{
					m_CenterPos.z += 0.075f;
					m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.0f, 0.075f * adjust));
					return true;
				}
			}
			else
			{
				m_CenterPos.z += 0.075f;
				m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.0f, 0.075f * adjust));
				return true;
			}
			break;
		case 3:
			decim = m_CenterPos.x - (int)m_CenterPos.x;
			if (decim < 0.10f)
			{
				if (hVal[1] <= m_CenterPos.y)
				{
					m_CenterPos.x += 0.075f;
					m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.075f * adjust, 0.0f, 0.0f));
					return true;
				}
			}
			else
			{
				m_CenterPos.x += 0.075f;
				m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.075f * adjust, 0.0f, 0.0f));
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
		HealthDisplay();
		return false;
	}

}

void MC::Jump()
{
	if (m_stagger == 0 && m_floored)
	{ 
		m_jCounter = 1;
	}
}

void MC::HealthDisplay()
{
	int shaderID = 0;
	switch (m_hp)
	{
	case 1:
		glm::mat4 auxGUI = glm::translate(m_ModelMatrix, glm::vec3(-1.0f, 3.0f, -0.25f));
		auxGUI = glm::scale(auxGUI, glm::vec3(0.5f, 0.5f, 0.5f));
		//m_Shader->SetUniformMat4f("modelMatrix", auxGUI);
		m_hpModel[3].draw_TriVAO_OBJ(shaderID);
		auxGUI = glm::translate(auxGUI, glm::vec3(2.0f, 0.0f, 0.0f));
		//m_Shader->SetUniformMat4f("modelMatrix", auxGUI);
		m_hpModel[3].draw_TriVAO_OBJ(shaderID);
		auxGUI = glm::translate(auxGUI, glm::vec3(2.0f, 0.0f, 0.0f));
		//m_Shader->SetUniformMat4f("modelMatrix", auxGUI);
		m_hpModel[3].draw_TriVAO_OBJ(shaderID);
		break;
	case 2:

		break;
	default:

		break;
	}
}

void MC::ReDamage(int DamageType, glm::mat4 &view)
{
	switch (DamageType) 
	{
	case 1:
		m_hp -= 1;
		m_ModelMatrix = glm::mat4(1.0f);
		m_ModelMatrix = glm::translate(m_ModelMatrix, (m_lastCommonBlock + glm::vec3(0.2f, 1.0f, -0.5f)));
		m_ModelMatrix = glm::scale(m_ModelMatrix, glm::vec3(0.30f, 0.30f, 0.30f));
		m_invulnerability = 100;
		view = glm::rotate(glm::mat4(1.0f), glm::radians(60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = glm::translate(view, glm::vec3(-m_lastCommonBlock.x-1, -7, -m_lastCommonBlock.z-4));
		m_CenterPos = m_lastCommonBlock;
		HealthDisplay();
		break;



	}
}

void MC::UpdateStates(char* board, glm::mat4 &view)
{
	int FloorCorrectedX, FloorCorrectedY, FloorCorrectedZ;
	FloorCorrectedX = round(m_CenterPos.x);
	FloorCorrectedZ = round(m_CenterPos.z);
	if (m_CenterPos.y < 7)
	{
		if (m_CenterPos.y < 4)
			FloorCorrectedY = 0;
		else
			FloorCorrectedY = 1;
	}
	else
		FloorCorrectedY = 2;

	int floorValue = (int)board[FloorCorrectedX + FloorCorrectedZ * 250 + (2 - FloorCorrectedY) * 250 * 20] - 48;
	//std::cout << floorValue;
	//SurroundCheck
	/*
	0	1	2
	3		4
	5	6	7
	*/
		m_surrounds[0] = (int)board[FloorCorrectedX + (FloorCorrectedZ-1) * 250 + (2 - FloorCorrectedY) * 250 * 20] - 48;
		m_surrounds[1] = (int)board[FloorCorrectedX+1 + (FloorCorrectedZ) * 250 + (2 - FloorCorrectedY) * 250 * 20] - 48;
		m_surrounds[2] = (int)board[FloorCorrectedX + (FloorCorrectedZ +1) * 250 + (2 - FloorCorrectedY) * 250 * 20] - 48;
		m_surrounds[3] = (int)board[FloorCorrectedX-1 + (FloorCorrectedZ) * 250 + (2 - FloorCorrectedY) * 250 * 20] - 48;
		if (FloorCorrectedY < 2)
		{
			m_surrounds[4] = (int)board[FloorCorrectedX + (FloorCorrectedZ - 1) * 250 + (2 - 1) * 250 * 20] - 48;
			m_surrounds[5] = (int)board[FloorCorrectedX + 1 + (FloorCorrectedZ) * 250 + (2 - 1) * 250 * 20] - 48;
			m_surrounds[6] = (int)board[FloorCorrectedX + (FloorCorrectedZ + 1) * 250 + (2 - 1) * 250 * 20] - 48;
			m_surrounds[7] = (int)board[FloorCorrectedX - 1 + (FloorCorrectedZ) * 250 + (2 - 1) * 250 * 20] - 48;
		}

	switch (floorValue)
	{
	case 1:
		if (m_CenterPos.y < 1.10 + 3 * FloorCorrectedY)
		{
			m_floored = true;
			m_lastCommonBlock = glm::vec3(FloorCorrectedX, 1, FloorCorrectedZ);
		}
		else
			m_floored = false;
		break;
	case 2:
		if (m_CenterPos.y < 3.10 + 3* FloorCorrectedY)
				m_floored = true;
		else
			m_floored = false;
		break;
	case 3:
		if (m_CenterPos.y < 2.10 + 3 * FloorCorrectedY)
				m_floored = true;
		else
			m_floored = false;
		break;

	case 4:
		if (m_CenterPos.y < 2.10 + 3 * FloorCorrectedY)
				m_floored = true;
		else
			m_floored = false;
		break;
	case 5:
		if (m_CenterPos.y < 3.10 + 3 * FloorCorrectedY)
				m_floored = true;
		break;
	case 6:
		if (m_CenterPos.y < 2.10 + 3 * FloorCorrectedY)
				m_floored = true;
		break;
	default:
		m_floored = false;
		break;
	}
	
	float jumpForce = 0.75;
	float scaleAdjust = 0.3f;
	switch (m_jCounter)
	{
	case 1:
		m_checker = m_CenterPos.y;
		m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.4f* jumpForce, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.4f*scaleAdjust * jumpForce, 0.0f));
		m_CenterPos.y += 0.4f * scaleAdjust *jumpForce;
		m_jCounter = 2;
		break;
	case 2:
		m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.4f* jumpForce*1.5, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.4f*scaleAdjust * jumpForce*1.5, 0.0f));
		m_CenterPos.y += 0.4f * scaleAdjust * jumpForce*1.5;
		if (m_CenterPos.y >= m_checker + 1)
			m_jCounter = 3;
		break;
	case 3:
		m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.2f* jumpForce, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.2f* scaleAdjust * jumpForce, 0.0f));
		m_CenterPos.y += 0.2f * scaleAdjust * jumpForce;
		if (m_CenterPos.y >= m_checker + 1.5)
			m_jCounter = 0;
		break;
	default:
		if (m_floored == false)
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
					m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, -0.4f * jumpForce * 2, 0.0f));
					view = glm::translate(view, glm::vec3(0.0f, 0.4f * scaleAdjust * jumpForce * 2, 0.0f));
					m_CenterPos.y -= 0.4f * scaleAdjust * jumpForce * 2;
				}
				else
				{
					m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, -0.4f * jumpForce * 1.25, 0.0f));
					view = glm::translate(view, glm::vec3(0.0f, 0.4f * scaleAdjust * jumpForce * 1.25, 0.0f));
					m_CenterPos.y -= 0.4f * scaleAdjust * jumpForce * 1.25;
				}
			}
		}
		else
		{
			if (m_CenterPos.y < 1+3*FloorCorrectedY)
			{
				m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.1f, 0.0f));
				view = glm::translate(view, glm::vec3(0.0f, -0.1f * scaleAdjust, 0.0f));
				m_CenterPos.y += 0.1f * scaleAdjust;
			}
		}
		break;
	}
	if (m_CenterPos.y < -2)
	{
		m_stagger += 100;
		ReDamage(1, view);

	}

	if (m_stagger >0)
		m_stagger -= 1;
}


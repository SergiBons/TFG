#include "MC.h"
#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"

MC::MC()
{
	m_CenterPos = glm::vec3(0.0f, 0.0f, 0.0f);
	std::string nomFitxer = "res/Models/MC/MainChar.obj";
	m_ObOBJ.LoadModel(const_cast<char*>(nomFitxer.c_str()));
	m_DirectionVector = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ModelMatrix = glm::mat4(1.0f);
	m_hp = 0;
	m_jCounter = 0;
	m_stagger = 0;
	m_checker = -1;
	m_floored = true;
	for (int i = 0; i < 3; i++)
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
	if (m_stagger <= 5) {
		switch (dir)
		{
		case 0:
			m_CenterPos.z -= 0.075f;
			m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.0f, -0.075f * adjust));
			return true;
			break;
		case 1:
			m_CenterPos.x -= 0.075f;
			m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(-0.075f * adjust, 0.0f, 0.0f));
			return true;
			break;
		case 2:
			m_CenterPos.z += 0.075f;
			m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.0f, 0.075f * adjust));
			return true;
			break;
		case 3:
			m_CenterPos.x += 0.075f;
			m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.075f * adjust, 0.0f, 0.0f));
			return true;
			break;

		}
	}
	return false;
}

void MC::Read(Texture tex, Renderer rend, Shader shad)
{

}

void MC::Jump(int state)
{
	if (m_stagger == 0 && m_floored)
	{ 
		m_jCounter = 1;
	}
}

void MC::UpdateStates(char* board, glm::mat4 &view)
{
	int FloorCorrectedX, FloorCorrectedY, FloorCorrectedZ;
	FloorCorrectedX = round(m_CenterPos.x);
	FloorCorrectedZ = round(m_CenterPos.z);
	if (m_CenterPos.y < 20)
	{
		if (m_CenterPos.y < 10)
			FloorCorrectedY = 0;
		else
			FloorCorrectedY = 1;
	}
	else
		FloorCorrectedY = 2;

	int floorValue = (int)board[FloorCorrectedX + FloorCorrectedZ * 250 + (2 - FloorCorrectedY) * 250 * 20] - 48;

	//SurroundCheck


	switch (floorValue)
	{

	case 1:
		if (round(m_CenterPos.y) == 1 + 10* FloorCorrectedY)
			m_floored = true;
		else
			m_floored = false;
		break;
	case 2:
		if (round(m_CenterPos.y) == 4 + 10 * FloorCorrectedY)
			m_floored = true;
		else
			m_floored = false;
		break;
		break;
	case 3:
		if (round(m_CenterPos.y) == 4 + 10 * FloorCorrectedY)
			m_floored = true;
		else
			m_floored = false;
		break;

	case 4:
		if (round(m_CenterPos.y) == 4 + 10 * FloorCorrectedY)
			m_floored = true;
		else
			m_floored = false;
		break;
	case 5:
		if (round(m_CenterPos.y) == 7 + 10 * FloorCorrectedY)
			m_floored = true;
		else
			m_floored = false;
		break;
	case 6:
		if (round(m_CenterPos.y) == 4 + 10 * FloorCorrectedY)
			m_floored = true;
		else
			m_floored = false;
		break;

	default:
		m_floored = false;
		break;
	}
	
	switch (m_jCounter)
	{
	case 1:
		m_checker = m_CenterPos.y;
		m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.4f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.12f, 0.0f));
		m_CenterPos.y += 0.4f;
		m_jCounter = 2;
		break;
	case 2:
		m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.4f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.12f, 0.0f));
		m_CenterPos.y += 0.4f;
		if (floor(m_CenterPos.y) == m_checker + 2)
			m_jCounter = 3;
		break;
	case 3:
		m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, 0.2f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.06f, 0.0f));
		m_CenterPos.y += 0.2f;
		if (floor(m_CenterPos.y) == m_checker + 4)
			m_jCounter = 0;
		break;
	default:
		if (m_floored == false)
		{
			m_ModelMatrix = glm::translate(m_ModelMatrix, glm::vec3(0.0f, -0.2f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, 0.06f, 0.0f));
			m_CenterPos.y -= 0.2f;
		}
		break;
	}
	
	if (m_stagger >0)
		m_stagger -= 1;
}


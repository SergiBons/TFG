#include "Enemy1.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

bool isWithinDistance(double x1, double y1, double x2, double y2, double d) {
	double distance = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return distance <= d;
}

bool isWithinDistance3D(float x1, float y1, float z1, float x2, float y2, float z2, float distance) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	float dz = z2 - z1;

	float squaredDistance = dx * dx + dy * dy + dz * dz;
	float squaredThreshold = distance * distance;

	return squaredDistance <= squaredThreshold;
}

Enemy::Enemy(float x, float z)
{
    m_CenterPos.x = x;
    m_CenterPos.z = z;
    m_CenterPos.y = 1.0f;
    m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
    m_floored = true;
    m_stagger = 10;
    m_Scale = 1.0f/3;
    m_ModelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(m_CenterPos.x, m_CenterPos.y, m_CenterPos.z)),glm::vec3(m_Scale));
    m_hp = 2;
    m_rotation = glm::mat4(0.0f);
    m_target = glm::vec3(0.0f, 0.0f, 0.0f);
}

Enemy::~Enemy()
{
}

int Enemy::Attack(glm::vec3 mChPos)
{
	if (isWithinDistance3D(m_CenterPos.x, m_CenterPos.y, m_CenterPos.z, mChPos.x, mChPos.y, mChPos.z, 1))
	{
		m_stagger += 5;
		return 2;
	}
	else
	{
		double dx = mChPos.x - m_CenterPos.x;
		double dy = mChPos.z - m_CenterPos.z;

		float rotationAngle = std::atan2(dy, dx); // Angle in radians

		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_CenterPos.x, m_CenterPos.y, m_CenterPos.z));
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -(rotationAngle+glm::radians(90.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale));

		m_ModelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

		//m_stagger += 1;
		return 0;
	}
}

bool Enemy::Move(int dir)
{
	
    return false;
}



int Enemy::ReDamage(int DamageType)
{
	m_hp--;
	if (m_hp == 0)
	{
		return -1;
	}
	return 1;
}

int Enemy::UpdateStates(char* board, glm::vec3 mChPos)
{
    const int boardWidth = 250;
    const int boardHeight = 20;
    const int boardSize = boardWidth * boardHeight;

    int floorCorrectedX = static_cast<int>(round(m_CenterPos.x));
    int floorCorrectedZ = static_cast<int>(round(m_CenterPos.z));
    int floorCorrectedY = (m_CenterPos.y < 7) ? ((m_CenterPos.y < 4) ? 0 : 1) : 2;

    int floorValue = static_cast<int>(board[floorCorrectedX + floorCorrectedZ * boardWidth + (2 - floorCorrectedY) * boardSize]) - '0';


	switch (floorValue)
	{
	case 1:
		if (m_CenterPos.y < 1.10 + 3 * floorCorrectedY)
		{
			m_floored = true;
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
	if (isWithinDistance(m_CenterPos.x, m_CenterPos.z, mChPos.x, mChPos.z, 10))
	{
		m_target = mChPos;
		m_stagger += 1;
		
		return Attack(mChPos);
	}
	if (m_stagger > 0)
		m_stagger -= 1;
	return 0;
}

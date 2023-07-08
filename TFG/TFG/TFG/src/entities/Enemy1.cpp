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
	m_AccTime = 0.0f;
    m_CenterPos.x = x;
    m_CenterPos.z = z;
    m_CenterPos.y = 1.0f;
	m_mid.x = 0.0f;
	m_mid.z = 0.0f;
	m_mid.y = 1.0f;
    m_direction = glm::vec3(0.0f, 0.0f, 0.0f);
    m_floored = true;
    m_stagger = 1;
    m_Scale = 1.0f/3;
    m_ModelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(m_CenterPos.x, m_CenterPos.y, m_CenterPos.z)),glm::vec3(m_Scale));
    m_hp = 2;
    m_rotation = glm::mat4(0.0f);
    m_target = glm::vec3(-10.0f, 0.0f, 0.0f);
	m_falling = false;
}

Enemy::~Enemy()
{
}

int Enemy::Attack(glm::vec3 mChPos, float deltaTime, int attackRange=0)
{
	double dx = mChPos.x - m_CenterPos.x;
	double dy = mChPos.z - m_CenterPos.z;
	float rotationAngle = std::atan2(dy, dx); // Angle in radians
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_CenterPos.x, m_CenterPos.y, m_CenterPos.z));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), -(rotationAngle + glm::radians(90.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(m_Scale));
	if (isWithinDistance3D(m_CenterPos.x, m_CenterPos.y, m_CenterPos.z, mChPos.x, mChPos.y, mChPos.z, 1))
	{
		m_ModelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		return 2;
	}
	else
	{
		if (m_AccTime > 1)
		{
			if (m_mid.y == 1.0f)
			{
				int xDec = mChPos.x - m_CenterPos.x;
				int zDec = mChPos.z - m_CenterPos.z;
				if (std::abs(xDec) < std::abs(zDec))
				{
					if (zDec > 0)
					{
						m_target = glm::vec3(mChPos.x, 1, mChPos.z + 1);
					}
					else
					{
						m_target = glm::vec3(mChPos.x, 1, mChPos.z - 1);
					}
				}
				else
				{
					if (xDec > 0)
					{
						m_target = glm::vec3(mChPos.x + 1, 1, mChPos.z);
					}
					else
					{
						m_target = glm::vec3(mChPos.x - 1, 1, mChPos.z);
					}
				}
				m_mid.y = 0.0f;
				m_mid.x = m_CenterPos.x;
				m_mid.z = m_CenterPos.z;
			}
			float aux = (m_target.x - m_CenterPos.x);
			float auz = (m_target.z - m_CenterPos.z);
			if (!(auz <= 0 && (m_Surrounds[0] != 1 && m_Surrounds[0] != 0 && m_Surrounds[0] != 8)))
				if (!(auz >= 0 && (m_Surrounds[2] != 1 && m_Surrounds[2] != 0 && m_Surrounds[2] != 8)))
					if (!(aux >= 0 && (m_Surrounds[1] != 1 && m_Surrounds[1] != 0 && m_Surrounds[1] != 8)))
						if (!(aux <= 0 && (m_Surrounds[3] != 1 && m_Surrounds[3] != 0 && m_Surrounds[3] != 8)))
						{ 
							if ((abs(aux) + abs(auz)) >= 0.5)
							{
								glm::vec3 normalizedDirection = glm::normalize(glm::vec3(aux, 0.0f, auz));
								translationMatrix = glm::translate(translationMatrix, normalizedDirection * deltaTime * 7.0f);
								m_CenterPos = glm::vec3(translationMatrix[3][0], translationMatrix[3][1], translationMatrix[3][2]);
							}

						}
			if (m_AccTime > 3)
			{
				m_mid.y = 1.0f;
				m_mid.x = 0.0f;
				m_mid.z = 0.0f;
				m_AccTime = 0;
			}
		}
		m_ModelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	}
	return 0;
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

int Enemy::UpdateStates(char* board, glm::vec3 mChPos, float deltaTime, int attackRange)
{
	if (m_falling == true)
	{
		m_CenterPos.y = m_CenterPos.y - 5 * deltaTime;
		if (m_CenterPos.y <= -1)
			return -1;
	}
	if (m_hp == 0)
		return -1;
    const int boardWidth = 250;
    const int boardHeight = 20;
    const int boardSize = boardWidth * boardHeight;


	int floorCorrectedX = 2;
	int floorCorrectedY = 1;
	int floorCorrectedZ = 0;
    floorCorrectedX = static_cast<int>(round(m_CenterPos.x));
	floorCorrectedZ = static_cast<int>(round(m_CenterPos.z));
    floorCorrectedY = (m_CenterPos.y < 7) ? ((m_CenterPos.y < 4) ? 0 : 1) : 2;
	if (m_CenterPos.z > 20)
		return -1;
	if (m_CenterPos.z < 0)
		return -1;
	if (m_CenterPos.x > 200)
		return -1;
	if (m_CenterPos.x < 0)
		return -1;
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
	int offset = (2 - floorCorrectedY) * boardSize;
	m_Surrounds[0] = static_cast<int>(board[floorCorrectedX + (floorCorrectedZ - 1) * boardWidth + offset]) - '0';
	m_Surrounds[1] = static_cast<int>(board[floorCorrectedX + 1 + floorCorrectedZ * boardWidth + offset]) - '0';
	m_Surrounds[2] = static_cast<int>(board[floorCorrectedX + (floorCorrectedZ + 1) * boardWidth + offset]) - '0';
	m_Surrounds[3] = static_cast<int>(board[floorCorrectedX - 1 + floorCorrectedZ * boardWidth + offset]) - '0';
	if (floorValue == 0)
	{
		m_falling = true;
	}
	if (m_stagger <= 0)
	{
		if (isWithinDistance3D(m_CenterPos.x, m_CenterPos.y, m_CenterPos.z, mChPos.x, mChPos.y, mChPos.z, attackRange))
		{
			m_mid.y = 1.0f;
			m_hp -= 1;
			m_AccTime = 0.0f;
			m_stagger += 2;
		}
		if (isWithinDistance(m_CenterPos.x, m_CenterPos.z, mChPos.x, mChPos.z, 5))
		{
			m_AccTime += deltaTime;
			return Attack(mChPos, deltaTime, attackRange);
		}
		else
		{
			m_AccTime = 0;
			Move(0);
		}
		return 0;
	}
	m_stagger -= 1*deltaTime;
	return 0;
}

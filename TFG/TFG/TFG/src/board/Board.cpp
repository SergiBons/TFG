#include "Board.h"
#include "Texture.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "objLoader.h"
#include <iostream>
#include <cstdlib>


Board::Board(char level, char* Board, std::vector<char*> Presets):
	m_CurrentLevel(level), m_BoardLayout(Board), m_Presets(Presets)
{
	srand((unsigned)time(NULL));
	
}

Board::~Board()
{
}

void Board::print()
{
}

void Board::DrawBoard(glm::mat4 M, glm::mat4 V, glm::mat4 P)
{

}

void Board::genBoard()
{

	int size;
	int shapeX;
	int shapeY;
	switch (m_CurrentLevel) {
	case '0':
		size = 25;
		shapeY = 20;
		shapeX = 20 * size;
		char presetLayout[25][2];
		//(char*)malloc(3 * 20 * 20 * size * sizeof(char));
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 25; j++)
			{
				presetLayout[i][j] = rand() % m_Presets.size();
			}
		std::cout << m_Presets.front()[100];

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				for (int PrI = 0; PrI < 3; PrI++)
				{
					for (int PrJ = 0; PrJ < 10; PrJ++)
					{
						for (int PrK = 0; PrK < 10; PrK++)
						{
							if (PrJ < 1)
							{
								m_BoardLayout[PrK + PrJ * (10 * 25) + PrI * (10 * 10 * 25 * 2) + j * 10 + i * 10 * (10 * 25)] = rand() % 2 + 48;
							}
							else 
							{
								if (PrJ > 8) 
								{
									m_BoardLayout[PrK + PrJ * (10 * 25) + PrI * (10 * 10 * 25 * 2) + j * 10 + i * 10 * (10 * 25)] = rand() % 2 + 48;
								}
								else
								{
									if (PrK < 1)
									{
										m_BoardLayout[PrK + PrJ * (10 * 25) + PrI * (10 * 10 * 25 * 2) + j * 10 + i * 10 * (10 * 25)] = rand() % 2 + 48;
									}
									else
									{
										if (PrK > 8)
										{
											m_BoardLayout[PrK + PrJ * (10 * 25) + PrI * (10 * 10 * 25 * 2) + j * 10 + i * 10 * (10 * 25)] = rand() % 2 + 48;
										}
										else
										{
											int aux = presetLayout[i][j];
											char check = m_Presets[aux][(PrK-2) + 8 * (PrJ-2) + 8 * 8 * PrI];
											m_BoardLayout[PrK + PrJ * (10 * 25) + PrI * (10 * 10 * 25 * 2) + j * 10 + i * 10 * (10 * 25)] = m_Presets[aux][(PrK - 1) + 8 * (PrJ - 1) + 8 * 8 * PrI];
										}
									}
								}
							}
						}
					}
				}
			}
		}
		break;

	case '1':
		size = 7;
		break;
	}
}

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
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 25; j++)
			{
				presetLayout[i][j] = rand() % m_Presets.size();
			}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 21; j++)
			{
				for (int PrI = 0; PrI < 2; PrI++)
				{
					for (int PrJ = 0; PrJ < 10; PrJ++)
					{
						for (int PrK = 0; PrK < 10; PrK++)
						{
							if (PrJ < 1)
							{
								m_BoardLayout[PrK + PrJ * (10 * 25) + PrI * (10 * 10 * 25 * 2) + j * 10 + i * 10 * (10 * 25)] = 48;
							}
							else
							{
								if (PrJ > 8)
								{
									m_BoardLayout[PrK + PrJ * (10 * 25) + PrI * (10 * 10 * 25 * 2) + j * 10 + i * 10 * (10 * 25)] = 48;
								}
								else
								{
									if (PrK < 1)
									{
										m_BoardLayout[PrK + PrJ * (10 * 25) + PrI * (10 * 10 * 25 * 2) + j * 10 + i * 10 * (10 * 25)] = 48;
									}
									else
									{
										if (PrK > 8)
										{
											m_BoardLayout[PrK + PrJ * (10 * 25) + PrI * (10 * 10 * 25 * 2) + j * 10 + i * 10 * (10 * 25)] = 48;
										}
										else
										{
											int aux = presetLayout[i][j];
											char check = m_Presets[aux][(PrK - 1) + 8 * (PrJ - 1) + 8 * 8 * PrI];
											m_BoardLayout[PrK + PrJ * (10 * 25) + PrI * (10 * 10 * 25 * 2) + j * 10 + i * 10 * (10 * 25)] = m_Presets[aux][(PrK - 1) + 8 * (PrJ - 1) + 8 * 8 * PrI];
										}
									}
								}
							}
						}
					}
				}
				int PrI = 2;
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
										char check = m_Presets[aux][(PrK - 1) + 8 * (PrJ - 1) + 8 * 8 * PrI];
										m_BoardLayout[PrK + PrJ * (10 * 25) + PrI * (10 * 10 * 25 * 2) + j * 10 + i * 10 * (10 * 25)] = m_Presets[aux][(PrK - 1) + 8 * (PrJ - 1) + 8 * 8 * PrI];
									}
								}
							}
						}
					}
				}
						
					
				
			}
		}

		m_BoardLayout[0 + 19 * 250 + 2 * 250*20] = '1';
		m_BoardLayout[0 + 18 * 250 + 2 * 250*20] = '1';
		m_BoardLayout[0 + 17 * 250 + 2 * 250*20] = '1';
		m_BoardLayout[1 + 19 * 250 + 2 * 250*20] = '1';
		m_BoardLayout[1 + 18 * 250 + 2 * 250*20] = '1';
		m_BoardLayout[1 + 17 * 250 + 2 * 250*20] = '1';
		m_BoardLayout[2 + 19 * 250 + 2 * 250*20] = '1';
		m_BoardLayout[2 + 18 * 250 + 2 * 250*20] = '1';
		m_BoardLayout[2 + 17 * 250 + 2 * 250*20] = '1';
		break;

	case '1':
		size = 7;
		break;
	}
}

#pragma once
#include <vector>
#include <glm/glm.hpp>

class Board
{
private:
	char m_CurrentLevel;
	std::vector<std::vector<char>> m_BoardLayout;
	char m_Presets[9][9][10];
public:
	Board(const unsigned int* data, unsigned int count);
	~Board();


	unsigned int getCurrentLevel() const { return  m_CurrentLevel; }






	void DrawBoard(glm::mat4 M, glm::mat4 V, glm::mat4 P);
};
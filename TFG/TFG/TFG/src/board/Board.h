#pragma once
#include <vector>
#include <glm/glm.hpp>

class Board
{
private:
	char m_CurrentLevel;
	std::vector<char*>m_Presets;
public:
	char* m_BoardLayout;
	Board(char level, char* Board, std::vector<char*> Presets);
	~Board();


	unsigned int getCurrentLevel() const { return  m_CurrentLevel; }
	void print();
	void DrawBoard(glm::mat4 M, glm::mat4 V, glm::mat4 P);
	void genBoard();
};
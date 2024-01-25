#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Color.h"

class Grid
{
public:
    Grid();
    void Initialize();
    void Print();
    void Draw(sf::RenderWindow &window);
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearFullRows();
    int grid[20][10];
    void SetDifficulty(std::string difficulty);

private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int Rownum);
    int Rownum;
    int Colnum;
    int cellSize;
    std::vector<sf::Color> colors;
};

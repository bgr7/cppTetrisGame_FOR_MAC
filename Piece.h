#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Position.h"
#include "Color.h"

class Piece
{
public:
    Piece();
    void Draw(sf::RenderWindow &window, int offsetX, int offsetY);
    void Move(int rows, int columns);
    std::vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    void MoveToRow(int newRow);

    int GetRotationCount();

    void ResetRotationCount();
    int id;
    std::map<int, std::vector<Position>> cells;
    int rowOffset;
    int columnOffset;

private:
    int cellSize;
    int rotationState;
    std::vector<sf::Color> colors;

    int rotationCount = 0;
    static const int maxRotations = 5;
};

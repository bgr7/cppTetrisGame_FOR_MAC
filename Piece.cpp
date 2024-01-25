#include "Piece.h"
#include "Position.h"

Piece::Piece()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColorsA();
    rowOffset = 0;
    columnOffset = 0;
}

void Piece::Draw(sf::RenderWindow &window, int offsetX, int offsetY)
{
    vector<Position> tiles = GetCellPositions();
    for (Position item : tiles)
    {
        sf::RectangleShape rectangle(sf::Vector2f(cellSize - 1, cellSize - 1));
        rectangle.setPosition(item.column * cellSize + offsetX, item.row * cellSize + offsetY);
        rectangle.setFillColor(colors[id]);
        window.draw(rectangle);
    }
}

void Piece::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

vector<Position> Piece::GetCellPositions()
{
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Piece::Rotate()
{
    if (rotationCount < maxRotations)
    {
        rotationState++;
        if (rotationState == static_cast<int>(cells.size()))
        {
            rotationState = 0;
        }
        rotationCount++;
    }
}
void Piece::ResetRotationCount()
{
    rotationCount = 0;
}

int Piece::GetRotationCount()
{
    return rotationCount;
}
void Piece::MoveToRow(int newRow)
{
    rowOffset = newRow;
}

void Piece::UndoRotation()
{
    rotationState--;
    if (rotationState == -1)
    {
        rotationState = static_cast<int>(cells.size()) - 1;
    }
}

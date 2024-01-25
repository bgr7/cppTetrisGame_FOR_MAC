#include "Board.h"
#include <iostream>

Grid::Grid()
{
    Rownum = 20;
    Colnum = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize()
{
    for (int row = 0; row < Rownum; row++)
    {
        for (int column = 0; column < Colnum; column++)
        {
            grid[row][column] = 0;
        }
    }
}

void Grid::Print()
{
    for (int row = 0; row < Rownum; row++)
    {
        for (int column = 0; column < Colnum; column++)
        {
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw(sf::RenderWindow &window)
{
    for (int row = 0; row < Rownum; row++)
    {
        for (int column = 0; column < Colnum; column++)
        {
            int cellValue = grid[row][column];
            sf::RectangleShape rectangle(sf::Vector2f(cellSize - 1, cellSize - 1));
            rectangle.setPosition(column * cellSize + 11, row * cellSize + 11);
            rectangle.setFillColor(colors[cellValue]);
            window.draw(rectangle);
        }
    }
}
void Grid::SetDifficulty(std::string difficulty)
{
    if (difficulty == "Medium")
    {
        Rownum = 18;
        Colnum = 9;
    }
    else if (difficulty == "Hard")
    {
        Rownum = 16;
        Colnum = 8;
    }
    else if (difficulty == "Easy")
    {
        Rownum = 20;
        Colnum = 10;
    }
}

bool Grid::IsCellOutside(int row, int column)
{
    if (row >= 0 && row < Rownum && column >= 0 && column < Colnum)
    {
        return false;
    }
    return true;
}

bool Grid::IsCellEmpty(int row, int column)
{
    if (grid[row][column] == 0)
    {
        return true;
    }
    return false;
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for (int row = Rownum - 1; row >= 0; row--)
    {
        if (IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if (completed > 0)
        {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row)
{
    for (int column = 0; column < Colnum; column++)
    {
        if (grid[row][column] == 0)
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for (int column = 0; column < Colnum; column++)
    {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int Rownum)
{
    for (int column = 0; column < Colnum; column++)
    {
        grid[row + Rownum][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

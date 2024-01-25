#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

extern  sf::Color trans;
extern  sf::Color darkGrey;
extern  sf::Color green;
extern  sf::Color red;
extern  sf::Color orange;
extern  sf::Color yellow;
extern  sf::Color purple;
extern  sf::Color cyan;
extern  sf::Color blue;
extern  sf::Color lightBlue;
extern  sf::Color darkBlue;

std::vector<sf::Color> GetCellColors();
std::vector<sf::Color> GetCellColorsA();

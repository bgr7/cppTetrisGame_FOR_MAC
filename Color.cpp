#include "Color.h"
sf::Color trans = sf::Color(0, 0, 0, 0);
sf::Color darkGrey = sf::Color(32, 32, 32, 255);
sf::Color green = sf::Color(47, 230, 23, 255);
sf::Color red = sf::Color(232, 18, 18, 255);
sf::Color orange = sf::Color(226, 116, 17, 255);
sf::Color yellow = sf::Color(237, 234, 4, 255);
sf::Color purple = sf::Color(166, 0, 247, 255);
sf::Color cyan = sf::Color(21, 204, 209, 255);
sf::Color blue = sf::Color(13, 64, 216, 255);
sf::Color lightBlue = sf::Color(59, 85, 162, 255);
sf::Color darkBlue = sf::Color(30, 30, 100, 255);
sf::Color white = sf::Color(255, 255, 255, 255);
sf::Color black = sf::Color(0, 0, 0, 255);
sf::Color lightGrey = sf::Color(200, 200, 200, 255);
sf::Color grey = sf::Color(128, 128, 128, 255);

std::vector<sf::Color> GetCellColors()
{
    return {darkGrey, green, red, orange, yellow, purple, cyan, trans, blue, lightBlue, darkBlue, white, black, lightGrey};
}

std::vector<sf::Color> GetCellColorsA()
{
    return {darkGrey, green, red, orange, yellow, purple, cyan, blue, lightBlue, darkBlue, white, black, lightGrey};
}

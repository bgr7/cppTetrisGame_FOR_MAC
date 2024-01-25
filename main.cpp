#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Color.h"
#include <iostream>
#include "Piece.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 620), "BGR's Tetris");
    window.setFramerateLimit(300);

    sf::Font font;
    if (!font.loadFromFile("Font/roboto.ttf"))
    {
        std::cerr << "Error loading font file." << std::endl;
        return EXIT_FAILURE;
    }

    Game game;

    sf::Clock clock;
    sf::Clock flashClock;
    sf::Clock portalClock;
    bool isFlashActive = false;
    game.isPortalActive = false;

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float elapsedSeconds = elapsed.asSeconds();

        if (game.diff == "Easy")
        {
            game.SetBlockFallSpeed(4.0f);
            game.SetDifficulty("Easy");
        }
        else if (game.diff == "Medium")
        {
            game.SetBlockFallSpeed(7.0f);
            game.SetDifficulty("Medium");
            if (portalClock.getElapsedTime().asSeconds() > 5.0f)
            {

                game.isPortalActive = true;
                portalClock.restart();
            }

            if (game.isPortalActive && portalClock.getElapsedTime().asSeconds() < 3.0f)
            {
                // Draw the portal in the game class
                game.DrawPortal(window);
                window.display();
            }
            else
            {
                game.isPortalActive = false;
            }
        }
        else if (game.diff == "Hard")

        {
            game.SetDifficulty("Hard");

            game.SetBlockFallSpeed(12.0f);
            if (flashClock.getElapsedTime().asSeconds() > 5.0f)
            {

                isFlashActive = true;
                flashClock.restart();
            }

            if (isFlashActive && flashClock.getElapsedTime().asSeconds() < 2.0f)
            {

                sf::RectangleShape flashRectangle(sf::Vector2f(800, 620));
                flashRectangle.setPosition(0, 0);
                flashRectangle.setFillColor(sf::Color::White);
                window.draw(flashRectangle);
                window.display();
            }
            else
            {

                isFlashActive = false;
            }
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        game.HandleInput();

        game.MoveBlockDown(elapsedSeconds);

        window.clear(trans);

        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score");
        scoreText.setCharacterSize(30);
        scoreText.setPosition(365, 15);
        scoreText.setFillColor(sf::Color::White);
        window.draw(scoreText);

        sf::Text PointText;
        PointText.setFont(font);
        PointText.setString(std::to_string(game.score));
        PointText.setCharacterSize(40);
        PointText.setPosition(370, 45);
        PointText.setFillColor(sf::Color::Red);
        window.draw(PointText);

        sf::Text ControlsText;
        ControlsText.setFont(font);
        ControlsText.setString("CONTROLS");
        ControlsText.setCharacterSize(30);
        ControlsText.setPosition(565, 15);
        ControlsText.setFillColor(sf::Color::White);
        window.draw(ControlsText);

        sf::Text InstructionText;
        InstructionText.setFont(font);
        InstructionText.setString("Press \"M\" to pause and open menu\n\n"
                                  "Use Keyboard Arrows to move blocks\n\n"
                                  "Press \"Q\" to rotate block c_cwise\n\n"
                                  "Press \"E\" to rotate block cwise\n\n"
                                  "Press \"T\" to change theme\n\n"
                                  "Press \"D\" to change Difficulty\n\n"
                                  "Press \"H\" to hold the block \n\n"
                                  "Press \"R\" to restart game when game over");

        InstructionText.setCharacterSize(13);
        InstructionText.setPosition(520, 75);
        InstructionText.setFillColor(sf::Color(255, 255, 255));
        window.draw(InstructionText);

        sf::Text nextText;
        nextText.setFont(font);
        nextText.setString("Next");
        nextText.setCharacterSize(30);
        nextText.setPosition(370, 115);
        nextText.setFillColor(sf::Color(255, 255, 255));
        window.draw(nextText);

        sf::Text holdText;
        holdText.setFont(font);
        holdText.setString("Hold");
        holdText.setCharacterSize(30);
        holdText.setPosition(370, 345);
        holdText.setFillColor(sf::Color(255, 255, 255));
        window.draw(holdText);

        sf::Text rotateText;
        rotateText.setFont(font);
        rotateText.setString("Rotate Counter\n     (Limit : 5)");
        rotateText.setCharacterSize(30);
        rotateText.setPosition(540, 395);
        rotateText.setFillColor(sf::Color::White);
        window.draw(rotateText);

        sf::Text rcText;
        rcText.setFont(font);
        rcText.setString(std::to_string(game.getCurrentBlockRotationCount()));
        rcText.setCharacterSize(40);
        rcText.setPosition(615, 465);
        rcText.setFillColor(sf::Color::Green);
        window.draw(rcText);

        sf::Text DifficultyText;
        DifficultyText.setFont(font);
        DifficultyText.setString("Difficulty Level: ");
        DifficultyText.setCharacterSize(30);
        DifficultyText.setPosition(540, 315);
        DifficultyText.setFillColor(sf::Color::White);
        window.draw(DifficultyText);

        sf::Text DifLevelText;
        DifLevelText.setFont(font);
        DifLevelText.setString(game.diff);
        DifLevelText.setCharacterSize(40);
        DifLevelText.setPosition(595, 345);
        DifLevelText.setFillColor(sf::Color::Green);
        window.draw(DifLevelText);

        if (game.gameOver)
        {
            sf::Text gameOverText;
            gameOverText.setFont(font);
            gameOverText.setString("     GAME OVER!\nPress \"R\" to continue");
            gameOverText.setCharacterSize(30);
            gameOverText.setPosition(510, 510);
            gameOverText.setFillColor(sf::Color::Red);
            window.draw(gameOverText);
        }

        sf::RectangleShape nextRectangle(sf::Vector2f(170, 180));
        nextRectangle.setPosition(320, 155);
        nextRectangle.setFillColor(lightBlue);
        nextRectangle.setOutlineThickness(3);
        nextRectangle.setOutlineColor(sf::Color::Red);
        window.draw(nextRectangle);

        sf::RectangleShape holdRectangle(sf::Vector2f(170, 180));
        holdRectangle.setPosition(320, 400);
        holdRectangle.setFillColor(lightBlue);
        holdRectangle.setOutlineThickness(3);
        holdRectangle.setOutlineColor(sf::Color::Red);
        window.draw(holdRectangle);

        game.Draw(window);

        window.display();
    }

    return EXIT_SUCCESS;
}

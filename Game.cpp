#include "Game.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <sstream>

#include <fstream>
Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;

    score = 0;
    if (!music.openFromFile("Sounds/music.mp3"))
        std::cerr << "Failed to load music file!" << std::endl;
    music.play();
    if (!rotateBuffer.loadFromFile("Sounds/rotate.mp3"))
        std::cerr << "Failed to load rotate sound file!" << std::endl;
    if (!clearBuffer.loadFromFile("Sounds/clear.mp3"))
        std::cerr << "Failed to load clear sound file!" << std::endl;
    rotateSound.setBuffer(rotateBuffer);
    clearSound.setBuffer(clearBuffer);
    hardSound.setBuffer(hardBuffer);
    LoadScoreboard();
}

Game::~Game()
{
}

void Game::Draw(sf::RenderWindow &window)
{
    grid.Draw(window);
    currentBlock.Draw(window, 11, 11);

    if (holdPiece.id != -1)
    {
        holdPiece.Draw(window, 255, 290);
    }

    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(window, 255, 240);
        break;
    case 4:
        nextBlock.Draw(window, 255, 230);
        break;
    default:
        nextBlock.Draw(window, 270, 220);
        break;
    }
}

bool invertedColors = false;
void Game::ChangeTheme()
{
    invertedColors = !invertedColors;

    vector<sf::Color> originalColors = GetCellColors();

    for (size_t i = 0; i < originalColors.size(); ++i)
    {
        if (invertedColors)
        {

            originalColors[i] = sf::Color(255, 255, 255) - originalColors[i];
        }
        else
        {

            originalColors[i] = sf::Color(255, 255, 255) - originalColors[i];
        }
    }

    trans = originalColors[10];
    darkGrey = originalColors[0];
    green = originalColors[1];
    red = originalColors[2];
    orange = originalColors[3];
    yellow = originalColors[4];
    purple = originalColors[5];
    cyan = originalColors[6];
    blue = originalColors[7];
    lightBlue = originalColors[8];
    darkBlue = originalColors[9];
}

void Game::DrawPortal(sf::RenderWindow &window)
{
    sf::RectangleShape portalRectangle(sf::Vector2f(200, 10));
    portalRectangle.setPosition(50, 155);
    portalRectangle.setFillColor(sf::Color::Blue);
    window.draw(portalRectangle);

    BlockTouchesPortal();
}

void Game::BlockTouchesPortal()
{

    vector<Position> tiles = currentBlock.GetCellPositions();

    for (const Position &item : tiles)
    {
        if (item.row >= 155 && item.row <= 175)
        {

            currentBlock.Move(-100, 0);
            return;
        }
    }
}

void Game::HandleInput()
{
    static bool RPressedLastFrame = false;
    static bool leftPressedLastFrame = false;
    static bool rightPressedLastFrame = false;
    static bool downPressedLastFrame = false;
    static bool EPressedLastFrame = false;
    static bool DPressedLastFrame = false;
    static bool QPressedLastFrame = false;
    static bool TPressedLastFrame = false;
    static bool HPressedLastFrame = false;

    if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && !RPressedLastFrame)
    {
        gameOver = false;
        Reset();
        hcount = 0;
    }

    if (!gameOver)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !leftPressedLastFrame)
        {
            MoveBlockLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !rightPressedLastFrame)
        {
            MoveBlockRight();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !downPressedLastFrame)
        {
            MoveBlockDown();
            UpdateScore(0, 1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T) && !TPressedLastFrame)
        {
            ChangeTheme();
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) && !EPressedLastFrame)
        {
            RotateBlock();

            sf::SoundBuffer rotateBuffer;
            rotateBuffer.loadFromFile("Sounds/rotate.mp3");
            rotateSound.play();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !DPressedLastFrame)
        {
            if (dlevel == 1)
            {
                diff = "Easy";
                music.stop();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                sf::Sound Music;
                sf::SoundBuffer buffer;
                music.openFromFile("Sounds/music.mp3");

                music.play();
            }
            else if (dlevel == 2)
            {
                diff = "Medium";
                music.stop();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                sf::Sound Music;
                sf::SoundBuffer buffer;
                music.openFromFile("Sounds/music.mp3");

                music.play();
            }
            else if (dlevel == 3)
            {
                diff = "Hard";

                music.stop();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                sf::Sound Music;
                sf::SoundBuffer buffer;
                music.openFromFile("Sounds/hard.mp3");

                music.play();
            }
            else if (dlevel % 4 == 0)
            {
                dlevel = 1;
                diff = "Easy";
                music.stop();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                sf::Sound Music;
                sf::SoundBuffer buffer;
                music.openFromFile("Sounds/music.mp3");

                music.play();
            }
            dlevel++;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && !QPressedLastFrame)
        {
            RotateBlock();
            sf::Sound Music;
            sf::SoundBuffer rotateBuffer;
            rotateBuffer.loadFromFile("Sounds/rotate.mp3");
            rotateSound.play();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H) && !HPressedLastFrame)
        {
            if (hcount < 2)
            {

                if (holdPiece.id == -1)
                {
                    holdPiece = currentBlock;
                    currentBlock = nextBlock;
                    nextBlock = GetRandomBlock();
                }
                else
                {

                    std::swap(currentBlock, holdPiece);
                }
            }
            hcount++;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            sf::RenderWindow pause(sf::VideoMode(400, 400), "PAUSED");

            sf::RectangleShape resumeButton(sf::Vector2f(160, 50));
            sf::RectangleShape NewGameButton(sf::Vector2f(160, 50));
            sf::RectangleShape ScoreBoardButton(sf::Vector2f(160, 50));
            sf::RectangleShape ChangeThemeButton(sf::Vector2f(160, 50));
            sf::RectangleShape QuitButton(sf::Vector2f(160, 50));
            resumeButton.setPosition(100, 25);
            resumeButton.setFillColor(sf::Color::White);
            NewGameButton.setPosition(100, 85);
            NewGameButton.setFillColor(sf::Color::White);
            ScoreBoardButton.setPosition(100, 145);
            ScoreBoardButton.setFillColor(sf::Color::White);
            ChangeThemeButton.setPosition(100, 205);
            ChangeThemeButton.setFillColor(sf::Color::White);
            QuitButton.setPosition(100, 265);
            QuitButton.setFillColor(sf::Color::White);

            sf::Font font;
            font.loadFromFile("Font/roboto.ttf");
            sf::Text resumeText;
            resumeText.setFont(font);
            resumeText.setString("Resume");
            resumeText.setCharacterSize(20);
            resumeText.setPosition(120, 40);
            resumeText.setFillColor(sf::Color::Red);

            sf::Text NewGameText;
            NewGameText.setFont(font);
            NewGameText.setString("NewGame");
            NewGameText.setCharacterSize(20);
            NewGameText.setPosition(100, 100);
            NewGameText.setFillColor(sf::Color::Red);

            sf::Text ScoreBoardText;
            ScoreBoardText.setFont(font);
            ScoreBoardText.setString("Score Board");
            ScoreBoardText.setCharacterSize(20);
            ScoreBoardText.setPosition(100, 160);
            ScoreBoardText.setFillColor(sf::Color::Red);

            sf::Text ChangeThemeText;
            ChangeThemeText.setFont(font);
            ChangeThemeText.setString("Change Theme");
            ChangeThemeText.setCharacterSize(20);
            ChangeThemeText.setPosition(100, 220);
            ChangeThemeText.setFillColor(sf::Color::Red);

            sf::Text QuitText;
            QuitText.setFont(font);
            QuitText.setString("Quit");
            QuitText.setCharacterSize(20);
            QuitText.setPosition(100, 280);
            QuitText.setFillColor(sf::Color::Red);

            sf::RectangleShape EasyButton(sf::Vector2f(160, 50));
            sf::RectangleShape MediumButton(sf::Vector2f(160, 50));
            sf::RectangleShape HardButton(sf::Vector2f(160, 50));
            sf::RectangleShape addNewPieceButton(sf::Vector2f(160, 50));
            EasyButton.setPosition(100, 25);
            EasyButton.setFillColor(sf::Color::White);
            MediumButton.setPosition(100, 85);
            MediumButton.setFillColor(sf::Color::White);
            HardButton.setPosition(100, 145);
            HardButton.setFillColor(sf::Color::White);
            addNewPieceButton.setPosition(100, 205);
            addNewPieceButton.setFillColor(sf::Color::White);

            sf::Text difficultyText;
            difficultyText.setFont(font);
            difficultyText.setString("Select Difficulty");
            difficultyText.setCharacterSize(20);
            difficultyText.setPosition(100, 0);
            difficultyText.setFillColor(sf::Color::Red);
            sf::Text easyText;
            easyText.setFont(font);
            easyText.setString("Easy");
            easyText.setCharacterSize(20);
            easyText.setPosition(100, 40);
            easyText.setFillColor(sf::Color::Red);
            sf::Text hardText;
            hardText.setFont(font);
            hardText.setString("Hard");
            hardText.setCharacterSize(20);
            hardText.setPosition(100, 160);
            hardText.setFillColor(sf::Color::Red);
            sf::Text mediumText;
            mediumText.setFont(font);
            mediumText.setString("Medium");
            mediumText.setCharacterSize(20);
            mediumText.setPosition(100, 100);
            mediumText.setFillColor(sf::Color::Red);

            sf::Text addNewPieceText;
            addNewPieceText.setFont(font);
            addNewPieceText.setString("Add a New Piece");
            addNewPieceText.setCharacterSize(20);
            addNewPieceText.setPosition(100, 220);
            addNewPieceText.setFillColor(sf::Color::Blue);

            while (pause.isOpen())
            {
                sf::Event event;
                while (pause.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        pause.close();
                    }
                    else if (event.type == sf::Event::MouseButtonPressed)
                    {

                        sf::Vector2i mousePos = sf::Mouse::getPosition(pause);
                        if (resumeButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        {
                            pause.close();
                        }
                        else if (ChangeThemeButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        {
                            ChangeTheme();
                            pause.close();
                        }
                        else if (NewGameButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        {
                            Reset();
                            hcount = 0;

                            pause.close();
                            {
                                sf::RenderWindow gamesettings(sf::VideoMode(300, 300), "Game Settings");

                                while (gamesettings.isOpen())
                                {
                                    sf::Event event;
                                    while (gamesettings.pollEvent(event))
                                    {
                                        if (event.type == sf::Event::Closed)
                                        {
                                            gamesettings.close();
                                        }
                                        else if (event.type == sf::Event::MouseButtonPressed)
                                        {
                                            sf::Vector2i mousePos = sf::Mouse::getPosition(gamesettings);
                                            if (EasyButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                                            {
                                                diff = "Easy";
                                                music.stop();
                                                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                                sf::Sound Music;
                                                sf::SoundBuffer buffer;
                                                music.openFromFile("Sounds/music.mp3");

                                                music.play();
                                                gamesettings.close();
                                                pause.close();
                                            }
                                            if (MediumButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                                            {
                                                diff = "Medium";
                                                music.stop();
                                                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                                sf::Sound Music;
                                                sf::SoundBuffer buffer;
                                                music.openFromFile("Sounds/music.mp3");

                                                music.play();
                                                gamesettings.close();
                                                pause.close();
                                            }
                                            if (HardButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                                            {
                                                diff = "Hard";
                                                music.stop();
                                                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                                sf::Sound Music;
                                                sf::SoundBuffer buffer;
                                                music.openFromFile("Sounds/hard.mp3");

                                                music.play();
                                                gamesettings.close();
                                                pause.close();
                                            }
                                            if (addNewPieceButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                                            {
                                                AddCustomPiece();
                                                gamesettings.close();
                                                pause.close();
                                            }
                                        }
                                    }

                                    gamesettings.clear();

                                    gamesettings.draw(EasyButton);
                                    gamesettings.draw(HardButton);
                                    gamesettings.draw(MediumButton);
                                    gamesettings.draw(difficultyText);
                                    gamesettings.draw(easyText);
                                    gamesettings.draw(mediumText);
                                    gamesettings.draw(hardText);

                                    gamesettings.draw(addNewPieceButton);
                                    gamesettings.draw(addNewPieceText);
                                    pause.close();
                                    gamesettings.display();
                                }
                            }
                        }
                        else if (QuitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        {
                            std::exit(0);
                        }
                        else if (ScoreBoardButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        {
                            sf::RenderWindow scoreboard(sf::VideoMode(300, 300), "Score Board");

                            while (scoreboard.isOpen())
                            {
                                sf::Event event;
                                while (scoreboard.pollEvent(event))
                                {
                                    if (event.type == sf::Event::Closed)
                                    {
                                        scoreboard.close();
                                    }
                                    else if (event.type == sf::Event::MouseButtonPressed)
                                    {
                                        sf::Vector2i mousePos = sf::Mouse::getPosition(pause);
                                    }
                                }

                                scoreboard.clear();

                                sf::Font font;
                                font.loadFromFile("Font/roboto.ttf");

                                sf::Text scoreboardText;
                                scoreboardText.setFont(font);
                                scoreboardText.setCharacterSize(20);
                                scoreboardText.setPosition(50, 50);

                                vector<ScoreData> scoreboardData = LoadScoreboard();

                                std::sort(scoreboardData.begin(), scoreboardData.end(), [](const ScoreData &a, const ScoreData &b)
                                          { return a.score > b.score; });

                                size_t numEntries = std::min(scoreboardData.size(), static_cast<size_t>(5));

                                for (size_t i = 0; i < numEntries; ++i)
                                {
                                    const auto &entry = scoreboardData[i];
                                    scoreboardText.setString(entry.username + " - " + std::to_string(entry.score));
                                    scoreboard.draw(scoreboardText);
                                    scoreboardText.move(0, 30);
                                }

                                pause.close();
                                scoreboard.display();
                            }
                        }
                    }
                }

                pause.clear();

                pause.draw(resumeButton);
                pause.draw(NewGameButton);
                pause.draw(NewGameText);
                pause.draw(resumeText);
                pause.draw(ScoreBoardButton);
                pause.draw(ScoreBoardText);
                pause.draw(ChangeThemeButton);
                pause.draw(ChangeThemeText);
                pause.draw(QuitButton);
                pause.draw(QuitText);

                pause.display();
            }
        }
    }

    RPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R);
    leftPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    rightPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    downPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    EPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E);
    DPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    QPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
    TPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T);
    HPressedLastFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H);
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}
void Game::SetBlockFallSpeed(float speed)
{
    blockFallSpeed = speed;
}
void Game::AddCustomPiece()
{
    class CustomPiece : public Piece
    {
    public:
        CustomPiece()
        {
            id = 8;
            cells[0] = {Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0)};
            cells[1] = {Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2), Position(1, 2)};
            cells[2] = {Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0), Position(0, 1)};
            cells[3] = {Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2)};
            Move(0, 3);
        }
    };

    blocks.push_back(CustomPiece());
    isCustomOccurs = true;
}

void Game::MoveBlockDown(float elapsedSeconds)
{
    static float timeSinceLastMove = 0.0f;
    timeSinceLastMove += elapsedSeconds;

    if (!gameOver && timeSinceLastMove >= (1.0f / blockFallSpeed))
    {
        currentBlock.Move(1, 0);

        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }

        timeSinceLastMove = 0.0f;
    }
}

bool Game::IsBlockOutside()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();

        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.UndoRotation();
        }
        else
        {
        }
    }
}
std::string GetUsername()
{
    sf::RenderWindow userpopup(sf::VideoMode(400, 300), "Game Over!");

    sf::RectangleShape submitButton(sf::Vector2f(80, 40));
    submitButton.setPosition(160, 170);
    submitButton.setFillColor(sf::Color::White);

    sf::Font font;
    font.loadFromFile("Font/roboto.ttf");
    sf::Text writeText;
    writeText.setFont(font);
    writeText.setString("Game Over! Please enter your\n username and press enter\n before submit: (max 5 letters)");
    writeText.setCharacterSize(20);
    writeText.setPosition(40, 10);
    writeText.setFillColor(sf::Color::White);

    font.loadFromFile("Font/roboto.ttf");
    sf::Text submitText;
    submitText.setFont(font);
    submitText.setString("Submit");
    submitText.setCharacterSize(20);
    submitText.setPosition(175, 170);
    submitText.setFillColor(sf::Color::Red);

    font.loadFromFile("Font/roboto.ttf");
    sf::Text inputText;
    inputText.setFont(font);

    inputText.setCharacterSize(20);
    inputText.setPosition(120, 120);
    inputText.setFillColor(sf::Color::Red);

    while (userpopup.isOpen())
    {
        sf::Event event;
        while (userpopup.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                userpopup.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(userpopup);
                if (submitButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                {
                    return inputText.getString().toAnsiString();
                }
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == 8)
                {
                    std::string currentText = inputText.getString().toAnsiString();
                    if (!currentText.empty())
                    {
                        currentText.pop_back();
                        inputText.setString(currentText);
                    }
                }
                else if (event.text.unicode < 128)
                {
                    inputText.setString(inputText.getString() + static_cast<char>(event.text.unicode));
                }
            }
        }

        userpopup.clear();
        userpopup.draw(submitButton);
        userpopup.draw(inputText);
        userpopup.draw(submitText);
        userpopup.draw(writeText);
        userpopup.display();
    }

    return "";
}

void Game::LockBlock()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    currentBlock.ResetRotationCount();
    if (BlockFits() == false)
    {
        music.stop();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sf::Sound Music;
        sf::SoundBuffer buffer;
        music.openFromFile("Sounds/gameover.mp3");

        music.play();
        gameOver = true;
    }
    nextBlock = GetRandomBlock();

    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        sf::SoundBuffer clearBuffer;
        clearBuffer.loadFromFile("Sounds/clear.mp3");
        clearSound.play();

        UpdateScore(rowsCleared, 0);
    }
    if (gameOver)
    {

        std::string username = GetUsername();

        SaveScore(username, score);
    }
}

vector<ScoreData> Game::LoadScoreboard()
{
    vector<ScoreData> scoreboard;

    std::ifstream scoreboardFile("Score/sb.txt");

    if (scoreboardFile.is_open())
    {
        ScoreData data;
        while (scoreboardFile >> data.username >> data.score)
        {
            scoreboard.push_back(data);
        }
        scoreboardFile.close();
    }
    else
    {
        std::cerr << "Unable to open scoreboard file.\n";
    }

    return scoreboard;
}

void Game::SaveScore(const std::string &username, int score)
{
    std::ofstream scoreboardFile("Score/sb.txt", std::ios::app);

    if (scoreboardFile.is_open())
    {
        scoreboardFile << username << " " << score << "\n";
        scoreboardFile.close();
    }
    else
    {
        std::cerr << "Unable to open scoreboard file.\n";
    }
}

bool Game::BlockFits()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    music.stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    sf::Sound Music;
    sf::SoundBuffer buffer;
    music.openFromFile("Sounds/music.mp3");
    music.play();
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    hcount = 0;
    holdPiece = Piece();

    nextBlock = GetRandomBlock();
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }

    score += moveDownPoints;
}

vector<Piece> Game::GetAllBlocks()
{
    vector<Piece> allBlocks = {IPiece(), JPiece(), LPiece(), OPiece(), SPiece(), TPiece(), ZPiece()};
    allBlocks.insert(allBlocks.end(), customPieces.begin(), customPieces.end());
    return allBlocks;
}

Piece Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
        if (isCustomOccurs)
        {
            AddCustomPiece();
        }
    }
    int randomIndex = rand() % blocks.size();
    Piece block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}
void Game::SetDifficulty(std::string difficulty)
{
    grid.SetDifficulty(difficulty);
}

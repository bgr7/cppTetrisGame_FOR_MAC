#pragma once
#include "Board.h"
#include "Pieces.cpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
struct ScoreData
{
    std::string username;
    int score;
};
class Game
{
public:
    Game();
    ~Game();
    void Draw(sf::RenderWindow &window);
    void HandleInput();
    void MoveBlockDown();
    void HoldBlock();

    bool isPortalActive;
    void MoveBlockDown(float elapsedSeconds);

    void SetBlockFallSpeed(float speed);
    bool gameOver;
    std::string diff = "Easy";
    int score;
    sf::Music music;
    int getCurrentBlockRotationCount()
    {
        return currentBlock.GetRotationCount();
    }
    void SetDifficulty(std::string difficulty);
    void DrawPortal(sf::RenderWindow &window);

private:
    void MoveBlockLeft();
    void BlockTouchesPortal();
    float blockFallSpeed;
    void MoveBlockRight();
    Piece GetRandomBlock();
    std::vector<Piece> GetAllBlocks();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    bool isCustomOccurs;

    void ChangeTheme();
    void UpdateScore(int linesCleared, int moveDownPoints);
    Grid grid;
    std::vector<Piece> blocks;
    Piece currentBlock;
    Piece nextBlock;
    sf::SoundBuffer rotateBuffer;
    sf::SoundBuffer clearBuffer;
    sf::SoundBuffer hardBuffer;
    sf::Sound hardSound;
    sf::Sound rotateSound;
    sf::Sound clearSound;

    Piece holdPiece;
    bool canHold;
    int hcount = 0;
    int dlevel = 1;
    std::vector<Piece> customPieces;
    void AddCustomPiece();

    void SaveScore(const std::string &username, int score); // Added function to save score
    std::vector<ScoreData> LoadScoreboard();                // Added function to load scoreboard
};

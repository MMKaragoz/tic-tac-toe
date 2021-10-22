#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <array>

class Game
{
private:
    char board_values[9] = {'_', '_', '_', '_', '_', '_', '_', '_', '_'};
    std::string player1;
    std::string player2;
    char first_player_symbol;
    char second_player_symbol;
    std::string first_player;
    std::string second_player;
    int total_round;
    int which_round;
    std::string winner;
    bool finished;
    int filled_locations[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

public:
    Game(std::string player_1, std::string player_2);
    void showBoard();
    void showPlayers();
    void chooseFirstPlayer();
    int randomNumber(int from, int to);
    void startGame();
    void setFirstPlayer(std::string player);
    std::string getFirstPlayer();
    void setSecondPlayer(std::string player);
    std::string getSecondPlayer();
    void setSymbols(char symbol, std::string player);
    void setFirstPlayerSymbol(char symbol);
    char getFirstPlayerSymbol();
    void setSecondPlayerSymbol(char symbol);
    char getSecondPlayerSymbol();
    void chooseSymbol(std::string player);
    bool controlXOrO(char symbol);
    bool isGameFinished();
    bool controlGuessedNumber(int guess1, int guess2, int from, int to);
    void controlLocation(int location, char symbol);
    void setWhichRound(int round);
    int getWhichRound();
    void setWinner(std::string player);
    std::string getWinner();
};

#endif
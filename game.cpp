#include <iostream>
#include <string>
#include <cmath>
#include "game.h"

using namespace std;

Game::Game(string player_1, string player_2)
{
    setPlayer1(player_1);
    setPlayer2(player_2);
    setTotalRound(9);
    setWhichRound(1);
    setBoardValues();
    setFinished(false);
    showPlayers();
}

void Game::startGame()
{
    int location;

    chooseFirstPlayer();

    while ((getWhichRound() != getTotalRound() + 1) && !getFinished())
    {
        if (getWhichRound() % 2)
        {
            cout << getFirstPlayer() << " plays.\n";
            cout << "Please select a location for " << getFirstPlayerSymbol() << endl;
            cin >> location;
            controlLocation(location, getFirstPlayerSymbol());
        }
        else
        {
            cout << getSecondPlayer() << " plays.\n";
            cout << "Please select a location for " << getSecondPlayerSymbol() << endl;
            cin >> location;
            controlLocation(location, getSecondPlayerSymbol());
        }
        if (getWhichRound() >= 5 && isGameFinished())
        {
            playAgain();
        }

        if (getWhichRound() == getTotalRound() + 1)
        {
            cout << "Game is over. There is no winner.\n";
            playAgain();
        }
    }
}

void Game::showBoard()
{
    cout << "\nRound " << getWhichRound();
    cout << "\n-------------\n";
    for (int i = 0; i < 9; i += 3)
    {
        cout << "| " << board_values[i] << " | " << board_values[i + 1] << " | " << board_values[i + 2] << " |\n";
        cout << "-------------\n";
    }
}

void Game::showPlayers()
{
    cout << "\nPlayer 1: " << getPlayer1() << "\n";
    cout << "Player 2: " << getPlayer2() << "\n";
}

void Game::chooseFirstPlayer()
{
    int player1_guess = 0;
    int player2_guess = 0;
    int from = 0;
    int to = 10;
    int random_number = randomNumber(from, to);
    bool correctRange = false;

    while (!correctRange)
    {
        cout << getPlayer1() << " please guess number " << from << " to " << to << ".\n";
        cin >> player1_guess;

        cout << getPlayer2() << " please guess number " << from << " to " << to << ".\n";
        cin >> player2_guess;

        correctRange = controlGuessedNumber(player1_guess, player2_guess, from, to);
        if (correctRange)
        {
            cout << getPlayer1() << " guessed " << player1_guess << ".\n";
            cout << getPlayer2() << " guessed " << player2_guess << ".\n";
            cout << "Random number was " << random_number << ".\n";
            if (abs(player1_guess - random_number) < abs(player2_guess - random_number))
            {
                setFirstPlayer(getPlayer1());
                setSecondPlayer(getPlayer2());
                chooseSymbol(getPlayer1());
            }
            else if (abs(player2_guess - random_number) < abs(player1_guess - random_number))
            {
                setFirstPlayer(getPlayer2());
                setSecondPlayer(getPlayer1());
                chooseSymbol(getPlayer2());
            }
            else
            {
                cout << "\nYour guesses are the same distance from the number we keep. Please guess again.\n";
                correctRange = false;
            }
        }
    }
}

int Game::randomNumber(int from, int to)
{
    srand(time(0));
    int random_number = rand() % (to - from + 1) + from;

    return random_number;
}

void Game::chooseSymbol(string player)
{
    char symbol;
    bool isCorrectSymbol = false;
    cout << "\nSo " << player << " starts first.\n";

    while (!isCorrectSymbol)
    {
        cout << "Please choose your symbol (X or O).\n";
        cin >> symbol;
        isCorrectSymbol = controlXOrO(symbol);

        if (isCorrectSymbol)
        {
            if (player == getPlayer1())
            {
                setSymbols(symbol, getPlayer1());
            }
            else
            {
                setSymbols(symbol, getPlayer2());
            }
        }
    }
}

bool Game::controlXOrO(char symbol)
{

    if (symbol == 'x' || symbol == 'X' || symbol == 'o' || symbol == 'O')
    {
        return true;
    }

    return false;
}

bool Game::isGameFinished()
{
    char winner_symbol;

    for (int i = 0; i < 9; i += 3)
    {

        if (board_values[i] == board_values[i + 1] && board_values[i + 1] == board_values[i + 2])
        {
            winner_symbol = board_values[i + 1];
        }

        if (i == 0)
        {
            if (board_values[i] == board_values[i + 3] && board_values[i + 3] == board_values[i + 6])
            {
                winner_symbol = board_values[i + 3];
            }
            else if (board_values[i + 1] == board_values[i + 4] && board_values[i + 4] == board_values[i + 7])
            {
                winner_symbol = board_values[i + 4];
            }
            else if (board_values[i + 2] == board_values[i + 5] && board_values[i + 5] == board_values[i + 8])
            {
                winner_symbol = board_values[i + 5];
            }
        }

        if (i == 3)
        {
            if (board_values[i - 3] == board_values[i + 1] && board_values[i + 1] == board_values[i + 5])
            {
                winner_symbol = board_values[i + 1];
            }
            else if (board_values[i - 1] == board_values[i + 1] && board_values[i + 1] == board_values[i + 3])
            {
                winner_symbol = board_values[i + 1];
            }
        }

        if (winner_symbol == getSecondPlayerSymbol())
        {
            setFinished(true);
            setWinner(second_player);
            cout << endl
                 << getWinner() << " won!\n";
            return true;
        }
        else if (winner_symbol == getFirstPlayerSymbol())
        {
            setFinished(true);
            setWinner(first_player);
            cout << endl
                 << getWinner() << " won!\n";
            return true;
        }
    }
    return false;
}

bool Game::controlGuessedNumber(int guess1, int guess2, int from, int to)
{
    if (guess1 >= from && guess1 <= to && guess2 >= from && guess2 <= to)
    {
        return true;
    }
    return false;
}

void Game::controlLocation(int location, char symbol)
{

    if (filled_locations[location - 1] != location - 1)
    {
        setFilledLocations(location - 1, location - 1);
        setBoardValues(symbol, location - 1);
        showBoard();
        setWhichRound(which_round + 1);
    }
    else
    {
        cout << "Heyy, it's filled. Please select another location.\n";
    }
}

void Game::playAgain()
{
    char pressed = 'q';

    cout << "Press y to start the game again, press any key to exit the game.\n";
    cin >> pressed;
    if (pressed == 'Y' || pressed == 'y')
    {
        setFinished(false);
        setWhichRound(0);
        setFilledLocations();
        setBoardValues();
        chooseFirstPlayer();
    }
    else
    {
        setFinished(true);
    }
}

void Game::setPlayer1(std::string player)
{
    player1 = player;
}

string Game::getPlayer1()
{
    return player1;
}

void Game::setPlayer2(std::string player)
{
    player2 = player;
}

string Game::getPlayer2()
{
    return player2;
}

void Game::setBoardValues(char value, int index)
{
    if (index == -1)
    {
        for (int i = 0; i < 9; i++)
        {
            board_values[i] = value;
        }
    }
    else
    {
        board_values[index] = value;
    }
}

char *Game::getBoardValues()
{
    return board_values;
}

void Game::setFirstPlayer(string player)
{
    first_player = player;
}

string Game::getFirstPlayer()
{
    return first_player;
}

void Game::setSecondPlayer(string player)
{
    second_player = player;
}

string Game::getSecondPlayer()
{
    return second_player;
}

void Game::setSymbols(char symbol, string player)
{
    if (player == first_player)
    {
        setFirstPlayerSymbol(toupper(symbol));
        if (getFirstPlayerSymbol() == 'X')
        {
            setSecondPlayerSymbol('O');
        }
        else
        {
            setSecondPlayerSymbol('X');
        }
    }
    else
    {
        setSecondPlayerSymbol(toupper(symbol));
        if (getSecondPlayerSymbol() == 'X')
        {
            setFirstPlayerSymbol('O');
        }
        else
        {
            setFirstPlayerSymbol('X');
        }
    }
}

void Game::setFirstPlayerSymbol(char symbol)
{
    first_player_symbol = symbol;
}

char Game::getFirstPlayerSymbol()
{
    return first_player_symbol;
}

void Game::setSecondPlayerSymbol(char symbol)
{
    second_player_symbol = symbol;
}

char Game::getSecondPlayerSymbol()
{
    return second_player_symbol;
}

void Game::setWhichRound(int round)
{
    which_round = round;
}

int Game::getWhichRound()
{
    return which_round;
}

void Game::setWinner(string player)
{
    winner = player;
}

string Game::getWinner()
{
    return winner;
}

void Game::setFilledLocations(int value, int index)
{
    if (index == -1)
    {
        for (int i = 0; i < 9; i++)
        {
            filled_locations[i] = value;
        }
    }
    else
    {
        filled_locations[index] = value;
    }
}

int *Game::getFilledLocations()
{
    return filled_locations;
}

void Game::setFinished(bool state)
{
    finished = state;
}

bool Game::getFinished()
{
    return finished;
}

void Game::setTotalRound(int round)
{
    total_round = round;
}

int Game::getTotalRound()
{
    return total_round;
}

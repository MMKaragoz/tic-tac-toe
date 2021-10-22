#include <iostream>
#include <string>
#include <cmath>
#include "game.h"

using namespace std;

Game::Game(string player_1, string player_2)
{
    player1 = player_1;
    player2 = player_2;
    total_round = 9;
    which_round = 1;
    finished = false;
    showPlayers();
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
    cout << "\nPlayer 1: " << player1 << "\n";
    cout << "Player 2: " << player2 << "\n";
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
        cout << player1 << " please guess number " << from << " to " << to << ".\n";
        cin >> player1_guess;

        cout << player2 << " please guess number " << from << " to " << to << ".\n";
        cin >> player2_guess;

        correctRange = controlGuessedNumber(player1_guess, player2_guess, from, to);
        if (correctRange)
        {
            cout << player1 << " guessed " << player1_guess << ".\n";
            cout << player2 << " guessed " << player2_guess << ".\n";
            cout << "Random number was " << random_number << ".\n";
            if (abs(player1_guess - random_number) < abs(player2_guess - random_number))
            {
                setFirstPlayer(player1);
                setSecondPlayer(player2);
                chooseSymbol(player1);
            }
            else if (abs(player2_guess - random_number) < abs(player1_guess - random_number))
            {
                setFirstPlayer(player2);
                setSecondPlayer(player1);
                chooseSymbol(player2);
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

void Game::startGame()
{
    int location;

    chooseFirstPlayer();

    while ((getWhichRound() != total_round + 1) && !finished)
    {
        if (getWhichRound() % 2)
        {
            cout << first_player << " plays.\n";
            cout << "Please select a location for " << first_player_symbol << endl;
            cin >> location;
            controlLocation(location, first_player_symbol);
        }
        else
        {
            cout << second_player << " plays.\n";
            cout << "Please select a location for " << second_player_symbol << endl;
            cin >> location;
            controlLocation(location, second_player_symbol);
        }
        if (getWhichRound() >= 5 && isGameFinished())
        {
            break;
        }

        if (getWhichRound() == total_round)
        {
            cout << "Game is over.\n";
        }
    }
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
            if (player == player1)
            {
                setSymbols(symbol, player1);
            }
            else
            {
                setSymbols(symbol, player2);
            }
        }
    }
}

void Game::setSymbols(char symbol, string player)
{
    if (player == first_player)
    {
        setFirstPlayerSymbol(toupper(symbol));
        // first_player_symbol = toupper(symbol);
        if (first_player_symbol == 'X')
        {
            // second_player_symbol = 'O';
            setSecondPlayerSymbol('O');
        }
        else
        {
            // second_player_symbol = 'X';
            setSecondPlayerSymbol('X');
        }
    }
    else
    {
        // second_player_symbol = toupper(symbol);
        setSecondPlayerSymbol(toupper(symbol));
        if (second_player_symbol == 'X')
        {
            // first_player_symbol = 'O';
            setFirstPlayerSymbol('O');
        }
        else
        {
            // first_player_symbol = 'X';
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

        if (winner_symbol == second_player_symbol)
        {
            finished = true;
            setWinner(second_player);
            cout << endl
                 << getWinner() << " won!\n";
            return true;
        }
        else if (winner_symbol == first_player_symbol)
        {
            finished = true;
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
        filled_locations[location - 1] = location - 1;
        board_values[location - 1] = symbol;
        showBoard();
        which_round++;
        setWhichRound(which_round);
    }
    else
    {
        cout << "Heyy, it's filled. Please select another location.\n";
    }
}

int Game::getWhichRound()
{
    return which_round;
}

void Game::setWhichRound(int round)
{
    which_round = round;
}

void Game::setWinner(string player)
{
    winner = player;
}

string Game::getWinner()
{
    return winner;
}

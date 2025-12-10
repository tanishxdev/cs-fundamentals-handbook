// tic_tac_toe.cpp
// Simple console-based Tic-Tac-Toe game using basic OOP.
// 2 human players (X and O), 3x3 board, play via terminal input.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ----------------------------------------------------------
// Player class: represents a human player in the game
// ----------------------------------------------------------
class Player
{
private:
    string name; // name of the player (for display)
    char symbol; // 'X' or 'O'

public:
    // Constructor: set name and symbol at object creation
    Player(const string &name, char symbol) : name(name), symbol(symbol) {}

    // Getter for name
    string getName() const
    {
        return name;
    }

    // Getter for symbol
    char getSymbol() const
    {
        return symbol;
    }
};

// ----------------------------------------------------------
// Board class: represents the 3x3 Tic-Tac-Toe grid
// ----------------------------------------------------------
class Board
{
private:
    // 2D vector to store board cells
    // Each cell will be ' ', 'X', or 'O'
    vector<vector<char>> grid;

    // Board size: here we keep it 3, but could be generalized
    int size;

public:
    // Constructor: initialize a size x size board with spaces
    Board(int n = 3) : size(n)
    {
        grid = vector<vector<char>>(size, vector<char>(size, ' '));
    }

    // Display the board in a user-friendly format
    void printBoard() const
    {
        cout << "\nCurrent Board:\n";
        for (int i = 0; i < size; ++i)
        {
            // Print each row
            for (int j = 0; j < size; ++j)
            {
                cout << " " << grid[i][j] << " ";
                // Print vertical separators between columns
                if (j < size - 1)
                {
                    cout << "|";
                }
            }
            cout << "\n";
            // Print horizontal separator between rows
            if (i < size - 1)
            {
                for (int k = 0; k < size; ++k)
                {
                    cout << "---";
                    if (k < size - 1)
                    {
                        cout << "+";
                    }
                }
                cout << "\n";
            }
        }
        cout << "\n";
    }

    // Check if given (row, col) indices are within the board bounds
    bool isValidPosition(int row, int col) const
    {
        return (row >= 0 && row < size && col >= 0 && col < size);
    }

    // Check if a cell at (row, col) is empty (i.e., contains a space)
    bool isCellEmpty(int row, int col) const
    {
        if (!isValidPosition(row, col))
        {
            return false; // out of bounds is considered "not empty" for safety
        }
        return grid[row][col] == ' ';
    }

    // Place a symbol at the given (row, col)
    // Returns true if placement was successful, false if invalid
    bool placeSymbol(int row, int col, char symbol)
    {
        // First, validate the position
        if (!isValidPosition(row, col))
        {
            return false;
        }
        // Then check if the cell is empty
        if (!isCellEmpty(row, col))
        {
            return false;
        }
        // If valid and empty, place the symbol
        grid[row][col] = symbol;
        return true;
    }

    // Check if a given symbol has won the game
    bool checkWin(char symbol) const
    {
        // Check all rows
        for (int i = 0; i < size; ++i)
        {
            bool rowWin = true;
            for (int j = 0; j < size; ++j)
            {
                if (grid[i][j] != symbol)
                {
                    rowWin = false;
                    break;
                }
            }
            if (rowWin)
            {
                return true;
            }
        }

        // Check all columns
        for (int j = 0; j < size; ++j)
        {
            bool colWin = true;
            for (int i = 0; i < size; ++i)
            {
                if (grid[i][j] != symbol)
                {
                    colWin = false;
                    break;
                }
            }
            if (colWin)
            {
                return true;
            }
        }

        // Check main diagonal (top-left to bottom-right)
        bool mainDiagWin = true;
        for (int i = 0; i < size; ++i)
        {
            if (grid[i][i] != symbol)
            {
                mainDiagWin = false;
                break;
            }
        }
        if (mainDiagWin)
        {
            return true;
        }

        // Check anti-diagonal (top-right to bottom-left)
        bool antiDiagWin = true;
        for (int i = 0; i < size; ++i)
        {
            if (grid[i][size - 1 - i] != symbol)
            {
                antiDiagWin = false;
                break;
            }
        }
        if (antiDiagWin)
        {
            return true;
        }

        // If none of the lines had all same symbols, no win
        return false;
    }

    // Check if the board is completely filled (used for detecting draw)
    bool isFull() const
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (grid[i][j] == ' ')
                {
                    // Found at least one empty cell, not full
                    return false;
                }
            }
        }
        // No empty cell found -> board is full
        return true;
    }

    // Optional: reset board to empty state (not strictly required here)
    void reset()
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                grid[i][j] = ' ';
            }
        }
    }
};

// ----------------------------------------------------------
// Game class: controls the overall flow of the Tic-Tac-Toe game
// ----------------------------------------------------------
class Game
{
private:
    Board board;           // The game board
    Player player1;        // First player
    Player player2;        // Second player
    Player *currentPlayer; // Pointer to the player whose turn it is

public:
    // Constructor: initialize board and players
    Game()
        : board(3),                 // create a 3x3 board
          player1("Player 1", 'X'), // player 1 uses symbol 'X'
          player2("Player 2", 'O')  // player 2 uses symbol 'O'
    {
        // At the beginning, let player1 start
        currentPlayer = &player1;
    }

    // Switch the current player pointer from one to the other
    void switchPlayer()
    {
        if (currentPlayer == &player1)
        {
            currentPlayer = &player2;
        }
        else
        {
            currentPlayer = &player1;
        }
    }

    // Main game loop
    void start()
    {
        cout << "Welcome to Tic-Tac-Toe (3x3)!\n";
        cout << player1.getName() << " will be '" << player1.getSymbol() << "'.\n";
        cout << player2.getName() << " will be '" << player2.getSymbol() << "'.\n\n";

        // Infinite loop until we break when game is over
        while (true)
        {
            // Display the board at the start of each turn
            board.printBoard();

            // Ask the current player for their move
            cout << currentPlayer->getName() << "'s turn. Symbol: " << currentPlayer->getSymbol() << "\n";
            cout << "Enter row and column (1-based indexing, e.g., 1 1 for top-left): ";

            int rowInput, colInput;
            cin >> rowInput >> colInput;

            // Convert from 1-based input to 0-based indices used internally
            int row = rowInput - 1;
            int col = colInput - 1;

            // Try to place the symbol on the board
            bool moveSuccessful = board.placeSymbol(row, col, currentPlayer->getSymbol());

            if (!moveSuccessful)
            {
                // If placement failed, it means invalid position or already occupied
                cout << "Invalid move. Please try again.\n\n";
                // Do not switch player, ask same player again
                continue;
            }

            // After a successful move, check if the current player has won
            if (board.checkWin(currentPlayer->getSymbol()))
            {
                board.printBoard();
                cout << currentPlayer->getName() << " wins the game!\n";
                break; // end the game loop
            }

            // If no win, check if the board is full -> draw
            if (board.isFull())
            {
                board.printBoard();
                cout << "The game is a draw. No more empty cells.\n";
                break; // end the game loop
            }

            // If no win and not draw, switch to the other player and continue the loop
            switchPlayer();
        }

        cout << "Game Over.\n";
    }
};

// ----------------------------------------------------------
// main function: entry point of the program
// ----------------------------------------------------------
int main()
{
    // Create a Game object
    Game game;

    // Start the game loop
    game.start();

    return 0; // Indicate successful program termination
}

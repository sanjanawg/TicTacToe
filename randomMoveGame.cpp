#include <iostream>
#include <cstdlib> // For rand()
using namespace std;

char board[3][3];
const char player = 'X';
const char ai = 'O';
char winner = ' ';

// Reset the board to its initial state
void resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Print the current state of the board
void printBoard() {
    cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    cout << "--|---|--\n";
    cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    cout << "--|---|--\n";
    cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n\n";
}

// Player's move
void playerMove() {
    int x, y;
    do {
        cout << "Enter row (1-3): ";
        cin >> x;
        cout << "Enter column (1-3): ";
        cin >> y;
        x--; // Convert to 0-based index
        y--;
        if (x < 0 || x >= 3 || y < 0 || y >= 3) {
            cout << "Invalid input. Please try again.\n";
        } else if (board[x][y] != ' ') {
            cout << "Position already taken. Please try again.\n";
        } else {
            board[x][y] = player;
            break;
        }
    } while (true);
}

// Check for a winner
char checkWinner() {
    for (int i = 0; i < 3; i++) {
        // Check rows
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        }
        // Check columns
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i];
        }
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    }
    return ' '; // No winner yet
}

// Print the winner or declare a draw
void printWinner(char winner) {
    if (winner == player) {
        cout << "You won the match!\n";
    } else if (winner == ai) {
        cout << "AI won the match!\n";
    } else {
        cout << "It's a draw... :(\n";
    }
}

// Check the number of free spaces left on the board
int checkFreeSpace() {
    int fs = 9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                fs--;
            }
        }
    }
    return fs;
}

// AI's move
void aiMove() {
    int x, y;
    if (checkFreeSpace() > 0) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        board[x][y] = ai;
    }
}

// Main function
int main() {
    resetBoard();
    while (winner == ' ' && checkFreeSpace() > 0) {
        printBoard();
        playerMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpace() == 0) {
            break;
        }
        aiMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpace() == 0) {
            break;
        }
    }
    printBoard();
    printWinner(winner);
    return 0;
}

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits.h>
using namespace std;

int board[9]; 
int turn = 1; // Tracks the current turn

// Display the Tic-Tac-Toe board
void display_table() {
    cout << "+---+---+---+\n";
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        if (board[i] == 2) {
            cout << " ";  // Empty
        } else if (board[i] == 3) {
            cout << "O";  // User
        } else if (board[i] == 5) {
            cout << "X";  // Computer
        }
        if (i % 3 == 2) {
            cout << " |\n+---+---+---+\n";
        }
    }
}

// Function to check if a player has won
bool check_winner(int mark) {
    int win_combinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
        {0, 4, 8}, {2, 4, 6}              // Diagonals
    };
    int product = (mark == 5) ? 125 : 27;  // Computer (5^3) or User (3^3)
    
    for (auto &comb : win_combinations) {
        if (board[comb[0]] * board[comb[1]] * board[comb[2]] == product) {
            return true;
        }
    }
    return false;
}

// Heuristic evaluation of the board for Minimax
int rate() {
    int score = 0;

    // Center control
    if (board[4] == 5) score += 4;  
    if (board[4] == 3) score -= 4;  

    // Corner control
    int corners[4] = {0, 2, 6, 8};
    for (int c : corners) {
        if (board[c] == 5) score += 3;
        if (board[c] == 3) score -= 3;
    }
    int edges[4] = {1, 3, 5, 7};
    for (int e : edges) {
        if (board[e] == 5) score += 1;  
        if (board[e] == 3) score -= 1;  
    }

    return score;
}

// Minimax algorithm
int minimax(int depth, bool isMaximizing) {
    if (check_winner(5)) return 10;  // Computer wins
    if (check_winner(3)) return -10; // User wins

    bool isDraw = true;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 2) {
            isDraw = false;
            break;
        }
    }
    if (isDraw) return 0; 

    if (depth >= 5) return rate(); // Limit depth for efficiency

    if (isMaximizing) {
        int bestScore = INT_MIN;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == 2) {
                board[i] = 5; // Simulate computer move
                bestScore = max(bestScore, minimax(depth + 1, false));
                board[i] = 2; // Undo move
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == 2) {
                board[i] = 3; // Simulate user move
                bestScore = min(bestScore, minimax(depth + 1, true));
                board[i] = 2; // Undo move
            }
        }
        return bestScore;
    }
}

// Computer's move using Minimax
int get_computer_move() {
    int bestMove = -1, bestScore = INT_MIN;

    for (int i = 0; i < 9; ++i) {
        if (board[i] == 2) {
            board[i] = 5; // Simulate move
            int score = minimax(0, false);
            board[i] = 2; // Undo move

            if (score > bestScore) {
                bestScore = score;
                bestMove = i + 1; // Convert 0-based to 1-based
            }
        }
    }

    return bestMove;
}

// Execute a move
void Go(int pos, int mark) {
    board[pos - 1] = mark; // Update the board
    display_table();
    turn++;
}

int main() {
    srand(time(0));

    // Initialize the board with empty spaces
    for (int i = 0; i < 9; ++i)
        board[i] = 2;

    cout << "\nTic Tac Toe - User (O) vs Computer (X)\n\n";
    display_table();
    cout << '\n';

    // Ask if the user wants to go first
    cout << "Do you want to go first? (y/n): ";
    char choice;
    cin >> choice;
    bool userFirst = (choice == 'y' || choice == 'Y');

    bool tie = true;
    int pos;

    // Game loop for 9 possible moves
    for (int i = 0; i < 9; ++i) {
        if ((i % 2 == 0) == userFirst) {
            // User's turn
            cout << "O (User), it's your turn. Enter position (1-9): ";
            while (true) {
                cin >> pos;
                if (pos < 1 || pos > 9 || board[pos - 1] != 2) {
                    cout << "Invalid position, try again: ";
                } else {
                    break;
                }
            }
            Go(pos, 3); // Mark 'O'
        } else {
            // Computer's turn
            cout << "X (Computer) is making a move...\n";
            pos = get_computer_move();
            Go(pos, 5); // Mark 'X'
        }

        // Check for a winner
        if (check_winner(5)) {
            cout << "X (Computer) wins!\n";
            tie = false;
            break;
        } else if (check_winner(3)) {
            cout << "O (User) wins!\n";
            tie = false;
            break;
        }
    }

    if (tie) {
        cout << "It's a tie!\n";
    }

    return 0;
}

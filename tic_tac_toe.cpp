#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int board[9];  // Array representing the board (1-9)
int turn = 1;  // Tracks the current turn

// Function to display the Tic-Tac-Toe board
void display_table() {
    cout << "+---+---+---+\n";
    for (int i = 0; i < 9; i++) {
        cout << "| ";
        if (board[i] == 2) {
            cout << " ";  // Empty
        } else if (board[i] == 3) {
            cout << "X";  // User
        } else if (board[i] == 5) {
            cout << "O";  // Computer
        }
        if (i % 3 == 2) {
            cout << " |\n+---+---+---+\n";
        }
    }
}

// Function to convert a position (1-9) to coordinates (row, col)
pair<int, int> get_coordinates_from_position(int position) {
    int row = (position - 1) / 3; 
    int col = (position - 1) % 3; 
    return {row, col};
}

// Function to check if a player has won by multiplying squares in rows/cols/diags
bool check_winner(int player) {
    int win_combinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
        {0, 4, 8}, {2, 4, 6}              // Diagonals
    };
    int product = (player == 1) ? 27 : 125;  // For 'X' (3^3) and 'O' (5^3)
    
    for (auto &comb : win_combinations) {
        if (board[comb[0]] * board[comb[1]] * board[comb[2]] == product) {
            return true;
        }
    }
    return false;
}

// Function to find a winning move or block the opponent's winning move
int posswin(int mark) {
    int win_combinations[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // Columns
        {0, 4, 8}, {2, 4, 6}              // Diagonals
    };
    
    for (auto &comb : win_combinations) {
        int product = board[comb[0]] * board[comb[1]] * board[comb[2]];
        if (product == mark * mark * 2) {
            // Find the empty spot (which has value 2)
            for (int i : comb) {
                if (board[i] == 2) {
                    return i + 1;  // Return 1-based position
                }
            }
        }
    }
    return 0;
}

// Function to handle moves for both user and computer
void Go(int pos, int mark) {
    board[pos - 1] = mark;  // Update board
    display_table();
    turn++;
}

// Strategy-based function to determine the computer's move
int make2() {
    if (board[4] == 2) return 5;  // Center square
    if (board[0] == 2) return 1;  // Corner square
    if (board[2] == 2) return 3;
    if (board[6] == 2) return 7;
    if (board[8] == 2) return 9;
    return 0;  // No strategic move found
}

// Function to get the computer's move
int get_computer_move() {
    // If computer can win
    int move = posswin(5);  // 5 is 'O' (computer)
    if (move) return move;

    // If player can win, block them
    move = posswin(3);  // 3 is 'X' (user)
    if (move) return move;

    // Strategy for first few moves
    if (turn == 2) {
        return make2();
    }

    // Otherwise, take the next available square
    for (int i = 0; i < 9; ++i) {
        if (board[i] == 2) {
            return i + 1;
        }
    }

    return -1;  // Shouldn't happen
}

int main() {
    srand(time(0));

    // Initialize the board with empty spaces (2 for empty, 3 for X, 5 for O)
    for (int i = 0; i < 9; ++i)
        board[i] = 2;

    cout << "\nTic Tac Toe - Computer vs User\n\n";
    display_table();
    cout << '\n';

    char userMark = 'X', computerMark = 'O';
    bool userFirst = true;
    
    // Ask the user if they want to go first
    cout << "Do you want to go first? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'n' || choice == 'N') {
        userFirst = false;
    }

    bool tie = true;
    int pos;
    
    // Main game loop for 9 possible moves
    for (int i = 0; i < 9; ++i) {
        int playerNum = (userFirst ? i % 2 : (i + 1) % 2);  
        char mark = (playerNum == 0 ? userMark : computerMark);

        if (playerNum == 0) {
            // User's turn
            cout << mark << " (User), it's your turn. Enter position (1-9): ";
            while (true) {
                cin >> pos;
                
                if (pos < 1 || pos > 9 || board[pos - 1] != 2) {
                    cout << "Invalid position, try again: ";
                    continue;
                } else {
                    break;
                }
            }
            Go(pos, 3);  // Mark 'X' as 3
        } else {
            // Computer's turn
            cout << mark << " (Computer) is making a move...\n";
            pos = get_computer_move();
            Go(pos, 5);  // Mark 'O' as 5
        }

        // Check if the current player has won
        if (check_winner(playerNum + 1)) {
            cout << mark << " is the victor!\n";
            tie = false;
            break;
        }
    }

    if (tie) {
        cout << "It's a tie!\n";
    }
    
    return 0;
}

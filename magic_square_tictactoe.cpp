#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

char board[3][3];              

// Function to display the Tic-Tac-Toe board
void display_table() {
    cout << "+---+---+---+\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << "| " << board[i][j] << " ";
        }
        cout << "|\n";
        cout << "+---+---+---+\n";
    }
}

// Function to check if a player has won (using magic square logic)
bool check_winner(const vector<int> &prevMoves, int curMove) {
    for (unsigned i = 0; i + 1 < prevMoves.size(); ++i) {
        for (unsigned j = i + 1; j < prevMoves.size(); ++j) {
            if (prevMoves[i] + prevMoves[j] + curMove == 15) {
                return true;
            }
        }
    }
    return false;
}

// Function to convert a position (1-9) to coordinates (row, col)
pair<int, int> get_coordinates_from_position(int position) {
    int row = (position - 1) / 3; 
    int col = (position - 1) % 3; 
    return {row, col};
}

// Function to find a winning move or block the opponent's winning move
int posswin(const vector<int> &magicMoves, const int magicSquare[], char mark) {
    // Iterate over all possible positions (1-9)
    for (int i = 1; i <= 9; ++i) {
        auto [row, col] = get_coordinates_from_position(i);  // Convert position to row, col
        if (board[row][col] != ' ') continue;  // Skip filled squares
        
        int currentValue = magicSquare[i - 1];  // Get the magic square value for this position
        
        // Check combinations of two previous moves
        for (unsigned j = 0; j < magicMoves.size(); ++j) {
            for (unsigned k = j + 1; k < magicMoves.size(); ++k) {
                if (magicMoves[j] + magicMoves[k] + currentValue == 15) {
                    return i;  // Return the position that completes the winning move
                }
            }
        }
    }
    
    return 0;  // No winning move found
}

// Function to get the computer's move
int get_computer_move(const vector<int> magicMoves[], const int magicSquare[]) {
    // Check if the computer can win
    int move = posswin(magicMoves[1], magicSquare, 'O');  // Check for computer's win
    if (move) return move;

    // Check if the player can win and block them
    move = posswin(magicMoves[0], magicSquare, 'X');  // Check for player's win to block
    if (move) return move;

    // Otherwise, make the next available move
    for (int i = 1; i <= 9; ++i) {
        auto [x, y] = get_coordinates_from_position(i);
        if (board[x][y] == ' ') {
            return i;
        }
    }

    return -1;  // No move available (shouldn't happen)
}

int main() {
    srand(time(0));

    // Initialize the board with empty spaces
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = ' ';

    cout << "\nTic Tac Toe - Computer vs User\n\n";
    display_table();
    cout << '\n';

    // Magic square values corresponding to positions 1-9
    int magicSquare[9] = {8, 1, 6, 3, 5, 7, 4, 9, 2};
    vector<int> magicMoves[2];  
    
    char userMark = 'X', computerMark = 'O';
    bool userFirst = true;
    
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
                
                if (pos < 1 || pos > 9) {
                    cout << "Position must be an integer between 1 and 9. Try again: ";
                    continue;
                }

                auto [x, y] = get_coordinates_from_position(pos);
                
                if (board[x][y] != ' ') {
                    cout << "Filled box! Enter a different value: ";
                } else {
                    break;
                }
            }
        } else {
            // Computer's turn
            cout << mark << " (Computer) is making a move...\n";
            pos = get_computer_move(magicMoves, magicSquare); 
        }

        // Update the board with the player's move
        auto [x, y] = get_coordinates_from_position(pos);
        board[x][y] = mark;
        display_table();

        // Get the corresponding magic square value for the current move
        int square = magicSquare[pos - 1]; 
        
        // Check if the current player has won
        if (check_winner(magicMoves[playerNum], square)) {
            cout << "We have a winner!\n";
            cout << mark << " is the victor!\n";
            tie = false;
            break;
        }

        // Store the magic square value for the current player's move
        magicMoves[playerNum].push_back(square);
    }

    if (tie) {
        cout << "It's a tie!\n";
    }
    
    return 0;
}

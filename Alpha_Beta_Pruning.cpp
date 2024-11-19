#include <iostream>
#include <vector>
#include <limits>
using namespace std;

vector<int> board(9, 2);

void display() {
    for (int i = 0; i < 9; i++) {
        if (i == 3 || i == 6) {
            cout << endl;
        }
        if (board[i] == 3) {
            cout << "X ";
        } else if (board[i] == 5) {
            cout << "O ";
        } else {
            cout << "- ";
        }
    }
    cout << endl;
}

int check_win(const vector<int>& board) {
    for (int i = 0; i < 3; i++) {

        if (board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2]) {
            if (board[i * 3] == 3) return 100;
            else if (board[i * 3] == 5) return -100;
        }

        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            if (board[i] == 3) return 100;
            else if (board[i] == 5) return -100;
        }
    }

    if (board[0] == board[4] && board[4] == board[8]) {
        if (board[0] == 3) return 100;
        else if (board[0] == 5) return -100;
    }
    if (board[2] == board[4] && board[4] == board[6]) {
        if (board[2] == 3) return 100;
        else if (board[2] == 5) return -100;
    }
    return 0;
}

int posswinX(const vector<int>& board) {
    for (int i = 0; i <= 6; i += 3) { 
        if (board[i] * board[i+1] * board[i+2] == 18) {
            return 1; 
        }
    }

    for (int i = 0; i < 3; i++) {
        if (board[i] * board[i+3] * board[i+6] == 18) {
            return 1; 
        }
    }

    if (board[0] * board[4] * board[8] == 18) {
        return 1; 
    }

    if (board[2] * board[4] * board[6] == 18) {
        return 1; 
    }

    return 0; 
}

int posswinO(const vector<int>& board) {
    for (int i = 0; i <= 6; i += 3) { 
        if (board[i] * board[i+1] * board[i+2] == 50) {
            return 1; 
        }
    }

    for (int i = 0; i < 3; i++) { 
        if (board[i] * board[i+3] * board[i+6] == 50) {
            return 1; 
        }
    }

    if (board[0] * board[4] * board[8] == 50) {
        return 1; 
    }

    if (board[2] * board[4] * board[6] == 50) {
        return 1; 
    }

    return 0; 
}


bool draw() {
    for (int spot : board) {
        if (spot == 2) return false; 
    }
    return true; 
}

int rate(const vector<int>& b) {
    int score = 0;

    int xWinPos = posswinX(b);
    if (xWinPos != 0) score += 50; 

    int oWinPos = posswinO(b);
    if (oWinPos != 0) score -= 50; 


    if (b[4] == 3) score += 7; 
    if (b[4] == 5) score -= 7; 

    int corners[] = {b[0], b[2], b[6], b[8]};
    for (int corner : corners) {
        if (corner == 3) score += 3; 
        if (corner == 5) score -= 3; 
    }

    int edges[] = {b[1], b[3], b[5], b[7]};
    for (int edge : edges) {
        if (edge == 3) score += 1;
        if (edge == 5) score -= 1; 
    }

    return score; 
}

vector<int> move_gen(const vector<int>& board) {
    vector<int> moves;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 2) { 
            moves.push_back(i);
        }
    }
    return moves;
}
int count = 0;
int minimax(vector<int>& board, int depth, int maxDepth,int use_score,int pass_score,bool isTopLevel = false) {
    count++;
    int score = check_win(board);
    if (score != 0) return -1; 
    if (draw()) return -1; 
    if (depth >= maxDepth) return rate(board); 

    int bestMove = -1;
    vector<int> moves = move_gen(board);

    for (int move : moves) {
        board[move] = (depth % 2 == 0) ? 3 : 5; 
        int currentScore = -minimax(board, depth + 1, maxDepth,-pass_score,-use_score); 
        board[move] = 2;
        if (currentScore > pass_score) {
            pass_score = currentScore;
            bestMove = move;
        }
        if(pass_score>=use_score){
            break;
        }
    }

    return isTopLevel ? bestMove : pass_score;
}

void computermove(int maxDepth) {
    if (board[4] == 2) {
        board[4] = 3; 
    } else {
        int use_score = 1000;
        int pass_score = -1000;

        int bestMove = minimax(board, 0, maxDepth,use_score,pass_score,true);
        if (bestMove != -1) {
            board[bestMove] = 3; 
        }
    }

    display();
    if (check_win(board) == 100) {
        cout << "Computer (X) wins!" << endl;
    } else if (draw()) {
        cout << "It's a draw!" << endl;
    }
}

void usermove(int maxDepth) {
    int n;
    while (true) {
        cout << endl;
        cout << "Enter the block number for your move (1-9): ";
        cin >> n;
        n--; 
        if (board[n] == 2) {
            board[n] = 5; 
            display();
            if (check_win(board) == -100) {
                cout << "You (O) win!" << endl;
                return;
            }
            if (draw()) {
                cout << "It's a draw!" << endl;
                return;
            }
            cout << endl << "Computer's move:" << endl;
            computermove(maxDepth); 
            if (check_win(board) == 100) {
                cout << "Computer (X) wins!" << endl;
                return;
            }
            if (draw()) {
                cout << "It's a draw!" << endl;
                return;
            }
        } else {
            cout << "Invalid move! Please try again." << endl;
        }
    }
}

int main() {
    char choice;
    cout << "Do you want to play first? (y/n): ";
    cin >> choice;
    cout << "Enter depth: ";
    int depth;
    cin >> depth;
    if (choice == 'y' || choice == 'Y') {
        usermove(depth);
    } else {
        computermove(depth); 
        usermove(depth); 
    }
    cout << "Number of minimax calls: " << count << endl;
    return 0;
}

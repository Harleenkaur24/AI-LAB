#include <iostream>
#include <vector>
using namespace std;

void attack(vector<vector<int>>& board, int i, int j, int m, int n) {
    int moves[8][2] = {{-2, -1}, {-1, -2}, {-2, 1}, {-1, 2}, {1, -2}, {2, -1}, {1, 2}, {2, 1}};
    for (auto move : moves) {
        int new_i = i + move[0];
        int new_j = j + move[1];
        if (new_i >= 0 && new_i < m && new_j >= 0 && new_j < n) {
            board[new_i][new_j] = 2;
        }
    }
}

bool can_place(const vector<vector<int>>& board, int i, int j) {
    if(board[i][j] == 0){
        return true;
    }    
    return false;
}

void place(vector<vector<int>>& board, int i, int j, int m, int n) {
    board[i][j] = 3;
    attack(board, i, j, m, n);
}

void display(const vector<vector<int>>& board, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if(board[i][j] == 2){
            cout << "A" << "  ";
        }
        if(board[i][j] == 3){
            cout << "K"<< "  ";
        }
        if(board[i][j] == 0){
            cout << "-" << "  ";
        }
        }
       
        cout << endl;
    }
    cout << endl;
}

void kn(vector<vector<int>> board, int k, int st_i, int st_j, int m, int n) {
    if (k == 0) {
        display(board, m, n);
        return;
    }

    for (int i = st_i; i < m; i++) {
        for (int j = st_j; j < n; j++) {
            if (can_place(board, i, j)) {
                vector<vector<int>> new_board = board; 
                place(new_board, i, j, m, n);
                kn(new_board, k - 1, i, j , m, n);
            }
        }
        st_j = 0;
    }
}

int main() {
    cout << "Enter the number of rows of the board: ";
    int m;
    cin >> m;
    cout << "Enter the number of columns of the board: ";
    int n;
    cin >> n;


    vector<vector<int>> board(m, vector<int>(n, 0));

    cout << "Enter the number of knights you want to place: ";
    int k;
    cin >> k;

    kn(board, k, 0, 0, m, n);

    return 0;
}

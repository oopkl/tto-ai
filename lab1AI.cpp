#include <iostream>
#include <limits>

using namespace std;

struct Move {
    int row, col;
};

char human = 'X', computer = 'O';
    
bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

int evaluate(char b[3][3], int depth) { //evaluation function calculates score
    // check rows
    for (int row = 0; row < 3; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == human)
                return -10 + depth;
            else if (b[row][0] == computer)
                return 10 - depth;
        }
    }

    // check cols
    for (int col = 0; col < 3; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == human)
                return -10 + depth;
            else if (b[0][col] == computer)
                return 10 - depth;
        }
    }

    // check diagonals
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2]) {
        if (b[0][0] == human)
            return -10 + depth;
        else if (b[0][0] == computer)
            return 10 - depth;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == human)
            return -10 + depth;
        else if (b[0][2] == computer)
            return 10 - depth;
    }

    return 0;
}

int minimax(char board[3][3], int depth, bool isMax) { //computer- maximizing player, human-minimizing player
    int score = evaluate(board, depth);

    if (score == 10 || score == -10)
        return score;

    if (!isMovesLeft(board))
        return 0;

    if (isMax) {
        int best = -numeric_limits<int>::max();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = computer;
                    best = max(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
    
    
     else {
        int best = numeric_limits<int>::max();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = human;
                    best = min(best, minimax(board, depth + 1, !isMax));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

Move findBestMove(char board[3][3]) {
    int bestVal = -numeric_limits<int>::max(); //initialize to -infinity
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = computer;
                int moveVal = minimax(board, 0, false);
                board[i][j] = '_';

                if (moveVal > bestVal) {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

void printBoard(char board[3][3]) {

    cout << "-------------\n";

    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }

}

bool checkWin(char player, char board[3][3]) {
    // check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || 
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }
    
    // check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || 
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;

    return false;
}

int main() {
    char board[3][3] = {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };
    printBoard(board);

    int flag=0; //flag=0 means computer's turn and flag=1 is human's turn


    while (isMovesLeft(board)) {
        
        if(flag==0){ 
            Move computerMove = findBestMove(board);
            board[computerMove.row][computerMove.col] = computer;
            printBoard(board);
            if (checkWin(computer, board)) {
                cout << "Computer wins!\n";
                break;
            }
            if (!isMovesLeft(board))
                break;
        }

        int humanRow, humanCol;
        cout << "Enter your move (row and column): ";
        cin >> humanRow >> humanCol;
        if (board[humanRow][humanCol] != '_') {
            cout << "Invalid move! Try again.\n";
            flag=1; 
            continue;
        }

        board[humanRow][humanCol] = human;
        printBoard(board);
        if (checkWin(human, board)) {
            cout << "You win!\n";
            break;
        }
        flag=0;
    }
    
    if (!checkWin(computer, board) && !checkWin(human, board))
        cout << "It's a draw!\n";

    return 0;
}

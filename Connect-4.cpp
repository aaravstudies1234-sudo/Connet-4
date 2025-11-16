#include <iostream>
#include <vector>
#include <ctime>
struct Move {
    int row, col;
};
void drawboard(char board[6][7]){
    std::cout << std::endl;
    for(int i = 0; i < 6; i++){
        std::cout << "| ";
        for(int j = 0; j < 7; j++){
            std::cout << board[i][j] << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
    std::cout << "  1   2   3   4   5   6   7  " << std::endl;
}
bool undoLastTwoMoves(char board[6][7], std::vector<Move> &history) {
    if (history.size() < 2) {
        std::cout << "Not enough moves to undo!\n";
        return false;
    }
    Move compMove = history.back();
    history.pop_back();
    board[compMove.row][compMove.col] = ' ';
    Move playerMove = history.back();
    history.pop_back();
    board[playerMove.row][playerMove.col] = ' ';
    std::cout << "Undo complete!\n";
    return true;
}
bool playerMoveInput(char board[6][7], char player, std::vector<Move> &history){
    std::string input;
    while (true) {
        std::cout << "Enter column (1-7) or U to undo: ";
        std::cin >> input;
        if (input == "U" || input == "u") {
            return false;
        }
        if (input.size() != 1 || input[0] < '1' || input[0] > '7') {
            std::cout << "Invalid input! Try again.\n";
            continue;
        }
        int col = input[0] - '1';
        for (int i = 5; i >= 0; i--) {
            if (board[i][col] == ' ') {
                board[i][col] = player;
                history.push_back({i, col});
                return true;
            }
        }

        std::cout << "Column full! Try again.\n";
    }
}
void computermove_easy(char board[6][7], char computer, std::vector<Move> &history){
    srand(time(NULL));
    while (true) {
        int col = rand() % 7;
        for (int r = 5; r >= 0; r--) {
            if (board[r][col] == ' ') {
                board[r][col] = computer;
                history.push_back({r, col});
                return;
            }
        }
    }
}
void computermove(char board[6][7], char computer, char player, std::vector<Move> &history) {
    srand(time(NULL));
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 4; j++){
            int playerCount = 0, emptyCol = -1;
            for (int k = 0; k < 4; k++){
                if (board[i][j + k] == player) playerCount++;
                else if (board[i][j + k] == ' ') emptyCol = j + k;
            }
            if (playerCount == 3 && emptyCol != -1){
                int rowToPlace = -1;
                for (int r = 5; r >= 0; r--){
                    if (board[r][emptyCol] == ' '){
                        rowToPlace = r;
                        break;
                    }
                }
                if (rowToPlace != -1){
                    board[rowToPlace][emptyCol] = computer;
                    history.push_back({rowToPlace, emptyCol});
                    return;
                }
            }
        }
    }
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 3; i++){
            int playerCount = 0, emptyRow = -1;

            for (int k = 0; k < 4; k++){
                if (board[i + k][j] == player) playerCount++;
                else if (board[i + k][j] == ' ') emptyRow = i + k;
            }
            if (playerCount == 3 && emptyRow != -1) {
                if (emptyRow == 5 || board[emptyRow + 1][j] != ' ') {
                    board[emptyRow][j] = computer;
                    history.push_back({emptyRow, j});
                    return;
                }
            }
        }
    }
    while (true) {
        int col = rand() % 7;
        for (int r = 5; r >= 0; r--) {
            if (board[r][col] == ' ') {
                board[r][col] = computer;
                history.push_back({r, col});
                return;
            }
        }
    }
}
void computermove_hard(char board[6][7], char computer, char player, std::vector<Move> &history){
    srand(time(NULL));
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 4; j++){
            int compCount = 0, emptyCol = -1;
            for (int k = 0; k < 4; k++){
                if (board[i][j+k] == computer) compCount++;
                else if (board[i][j+k] == ' ') emptyCol = j+k;
            }
            if (compCount == 3 && emptyCol != -1){
                for (int r = 5; r >= 0; r--){
                    if (board[r][emptyCol] == ' '){
                        board[r][emptyCol] = computer;
                        history.push_back({r, emptyCol});
                        return;
                    }
                }
            }
        }
    }
    computermove(board, computer, player, history);
}
bool checkwinner(char board[6][7], char player){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            if(board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3] == player){
                return true;
            }
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 7; j++){
            if(board[i][j] == player && board[i+1][j] == player && board[i+2][j] == player && board[i+3][j] == player){
                return true;
            }
        }
    }
    for(int i = 3; i < 6; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == player && board[i-1][j+1] == player && board[i-2][j+2] == player && board[i-3][j+3] == player){
                return true;
            }
        }
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == player && board[i+1][j+1] == player && board[i+2][j+2] == player && board[i+3][j+3] == player){
                return true;
            }
        }
    }
    return false;
}
bool checktie(char board[6][7]){
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    std::cout << "It's a tie!" << std::endl;
    return true;
}
int main(){
    char board[6][7];
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++){
            board[i][j] = ' ';
        }
    }
    std::vector<Move> history;
    int difficulty;
    std::cout << "Select difficulty: 1 = Easy | 2 = Normal | 3 = Hard: ";
    std::cin >> difficulty;
    char player = 'X';
    char computer = 'O';
    drawboard(board);
    while (true) {
        if (!playerMoveInput(board, player, history)) {
            if (undoLastTwoMoves(board, history))
                drawboard(board);
            continue;
        }
        drawboard(board);
        if (checkwinner(board, player)) {
            std::cout << "You win!\n";
            break;
        }
        if (checktie(board)) break;
        if (difficulty == 1) 
            computermove_easy(board, computer, history);
        else if (difficulty == 2) 
            computermove(board, computer, player, history);
        else 
            computermove_hard(board, computer, player, history);
        drawboard(board);
        if (checkwinner(board, computer)) {
            std::cout << "Computer wins!\n";
            break;
        }
        if (checktie(board)) break;
    }
    return 0;
}

#include <iostream>
#include <ctime>
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
void playermove(char board[6][7], char player){
    int col;
    while(true){
        std::cout << "Enter the column you want to drop the mark (1-7): ";
        std::cin >> col;
        col--;
        if(col < 0 || col > 6){
            std::cout << "Invalid Mark! TRy again" << std::endl;
            continue;
        }
        for(int i = 5; i >= 0; i--){
            if(board[i][col] == ' '){
                board[i][col] = player;
                return;
            }
        }
        std::cout << "Column full try again" << std::endl;
    }
}
void computermove(char board[6][7], char computer, char player) {
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
                    return;
                }
            }
        }
    }
    while (true) {
        int col = rand() % 7;
        int rowToPlace = -1;
        for (int r = 5; r >= 0; r--) {
            if (board[r][col] == ' ') {
                rowToPlace = r;
                break;
            }
        }
        if (rowToPlace != -1) {
            board[rowToPlace][col] = computer;
            return;
        }
    }
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
    char player = 'X';
    char computer = 'O';
    bool running = true;
    drawboard(board);
    while(running){
       playermove(board, player);
       drawboard(board);
        if (checkwinner(board, player)){
            std::cout << "You win!" << std::endl;
            break; 
        }
        else if(checkwinner(board, computer)){
            std::cout << "Computer wins!" << std::endl;
        }
        else if (checktie(board)) break;
        computermove(board, computer, player);
        drawboard(board);
        if (checkwinner(board, player)){
            std::cout << "You win!" << std::endl;
            break;
        }
        else if(checkwinner(board, computer)){
            std::cout << "Computer wins!" << std::endl;
        }
        else if (checktie(board)) break; 
    }
    return 0;
}
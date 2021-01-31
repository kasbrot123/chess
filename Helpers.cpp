#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include "Helpers.h"




int Code(int z, int x) {
    return z*10 + x;
}



int char_to_num(char letter) {
    
    if (letter == 'a')
        return 0;
    if (letter == 'b')
        return 1;
    if (letter == 'c')
        return 2;
    if (letter == 'd')
        return 3;
    if (letter == 'e')
        return 4;
    if (letter == 'f')
        return 5;
    if (letter == 'g')
        return 6;
    if (letter == 'h')
        return 7;

    // compiler warning
    return -1;

}


Coordinates coordsMove(std::string Input) {

    Coordinates move;
    std::stringstream ss;
    int y1, y2;
    move.x1 = char_to_num(Input[0]);
    move.x2 = char_to_num(Input[3]);

    ss << Input[1] << ' ' << Input[4];
    ss >> y1 >> y2;
    move.z1 = 8-y1;
    move.z2 = 8-y2;

    return move;
}

std::string moveToString(Coordinates move) {
    std::string input;
    std::string numbers[8] = {"8", "7", "6", "5", "4", "3", "2", "1"};
    std::string letters[8] = {"a", "b", "c", "d", "e", "f", "g", "h"};

    input = letters[move.x1] + numbers[move.z1] + "-" + letters[move.x2] + numbers[move.z2];

    return input;
}



std::vector<std::vector<int>> init_board(void) {
    
    //int main_figures[8] = {4, 2, 3, 5, 6, 3, 2, 4};
    std::vector<int> main_figures = {4, 2, 3, 5, 6, 3, 2, 4};
    std::vector<int> pawns = {1,1,1,1,1,1,1,1};
    std::vector<int> main_figures2 = {-4, -2, -3, -5, -6, -3, -2, -4};
    std::vector<int> pawns2 = {-1,-1,-1,-1,-1,-1,-1,-1};
    std::vector<int> empty = {0,0,0,0,0,0,0,0};

    //int board[8][8];
    std::vector<std::vector<int>> board;
    board.push_back(main_figures2);
    board.push_back(pawns2);
    board.push_back(empty);
    board.push_back(empty);
    board.push_back(empty);
    board.push_back(empty);
    board.push_back(pawns);
    board.push_back(main_figures);

    return board;

}


void print_moves(std::vector<std::string> &Turns_str) {
        int num_turn = 1;
        for (unsigned int i = 0; i < Turns_str.size(); i++){
            if (i % 2 == 0) {
                std::cout << num_turn << ". ";
                num_turn++;

                std::cout << Turns_str[i] << ", ";
            } else {
                std::cout << Turns_str[i] << " ";
            }
            
        }
    
}


int SumBoard(std::vector<std::vector<int>> Board) {

    int sum;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sum = sum + abs(Board[i][j]);
        }
    }

    return sum;
}

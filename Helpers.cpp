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


// coordinates in 0..7
int on_board(int x, int y) {

    if (x < 0 || x > 7 || y < 0 || y > 7)
        return 0;
    
    return 1;
}


std::vector<std::vector<int>> move_figure(std::vector<std::vector<int>> Board, Coordinates Move, int enPassant_logic) {

  
    int figure, dir;

    figure = Board[Move.z1][Move.x1];
    dir = figure/abs(figure);
    Board[Move.z1][Move.x1] = 0;
    Board[Move.z2][Move.x2] = figure;

    //if (enPassant_logic) 
    //    Board[Move.z2+dir][Move.x2] = 0;

    return Board;
}
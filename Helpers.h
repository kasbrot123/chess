#ifndef HELPERS_H
#define HELPERS_H


struct Coordinates {
    int x1;
    int x2;
    int z1;
    int z2;
};

int Code(int z, int x);
int char_to_num(char letter);
Coordinates coordsMove(std::string Input);
int on_board(int x, int y);
void move_figure(int (&Board)[8][8], Coordinates Move, int enPassant_logic);
std::string moveToString(Coordinates move);

#endif
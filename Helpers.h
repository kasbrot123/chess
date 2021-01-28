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
std::string moveToString(Coordinates move);
std::vector<std::vector<int>> init_board(void);
void print_moves(std::vector<std::string> &Turns_str);



#endif
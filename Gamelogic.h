#ifndef VALIDATION_H
#define VALIDATION_H


struct Coordinates;
std::vector<int> valid_moves(std::vector<std::vector<int>> Board, int x, int z, std::string lastMove, int &en_passant_move);
int false_move(std::string Input, std::vector<std::vector<int>> Board, std::string &Message, int Player, std::string LastMove, int &enPassant);
std::vector<std::vector<int>> move_figure(std::vector<std::vector<int>> Board, Coordinates Move, int enPassant_logic);
int on_board(int x, int y);


#endif
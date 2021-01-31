#ifndef GAMELOGIC_H
#define GAMELOGIC_H


struct Coordinates;
std::vector<int> possible_moves(std::vector<std::vector<int>> Board, int x, int z, std::string lastMove, int &en_passant_move);
std::vector<int> Valid_moves(std::vector<std::vector<int>> Board, int x, int z, std::string lastMove, int &en_passant_move);
int false_move(std::string Input, std::vector<std::vector<int>> Board, std::string &Message, int Player, std::string LastMove, int &enPassant);
std::vector<std::vector<int>> move_figure(std::vector<std::vector<int>> Board, Coordinates Move, int enPassant_logic);
int on_board(int x, int y);
int Check(std::vector<std::vector<int>> Board, int Player);
int CheckMate(std::vector<std::vector<int>> Board, int Player);


#endif
#ifndef COMPUTER_H
#define COMPUTER_H

struct Coordinates;
void copy(const int Board[8][8], int (&Board_new)[8][8]);
int calculateScore(const int (&Board)[8][8], int Player);
int bestMove(std::vector<std::vector<int>> Board, int Player, int depth, int max_depth, std::string LastMove, Coordinates &Best);


#endif
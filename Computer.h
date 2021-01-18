#ifndef COMPUTER_H
#define COMPUTER_H

struct Coordinates;

int calculateScore(const int (&Board)[8][8], int Player);
int bestMove(std::vector<std::vector<int>> Board, int Player, int depth, int max_depth, std::string LastMove, Coordinates &Best, int &summe);


#endif
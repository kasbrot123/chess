#ifndef INPUTS_H
#define INPUTS_H


int whichPlayer(std::string &Title, int (&players)[2]);
int inputHuman(int Player, std::string &input, std::string message);
int inputComputer(std::vector<std::vector<int>> Board, int Player, std::string &input, std::string LastMove);

#endif
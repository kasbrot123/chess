#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <cmath>

#include "Computer.h"
#include "Gamelogic.h"
#include "Helpers.h"






int calculateScore(std::vector<std::vector<int>> Board, int Player) {

    int Score = 0;
    int New;
    int figure;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            figure = Board[i][j];
            New = figure*figure*figure*figure*figure*Player;

            Score = Score + New;
        }
    }

    //return 1;
    return Score;
}



int bestMove(std::vector<std::vector<int>> Board, int Player, int depth, int max_depth, std::string LastMove, Coordinates &Best, int &summe) {

    int max_decisions = 10;  // number of best moves for recursive call
    int figure;
    int en_passant_logic = 0;
    std::vector<std::pair<Coordinates, int>> moves_and_scores;
    std::vector<int> moves_one_figure;
    std::vector<int> moves_best;
    std::vector<std::vector<int>> Board_new;
    Coordinates Move;
    Coordinates best_next;
    int Score;
    int n_moves_and_scores;
    int Score_max = 0;
    int n_best;

    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            
            figure = Board[i][j];
            if (Player*figure > 0) {

                
                moves_one_figure = valid_moves(Board, j, i, LastMove, en_passant_logic);

                for (unsigned int m = 0; m < moves_one_figure.size(); m++) {

                    Move.x1 = j;
                    Move.z1 = i;
                    Move.x2 = moves_one_figure[m] % 10;
                    Move.z2 = moves_one_figure[m] / 10;

                    Board_new = move_figure(Board, Move, en_passant_logic); // long run error
                    Score = calculateScore(Board_new, Player);

                    moves_and_scores.push_back(std::make_pair(Move, Score));

                    summe++;
                }



            }

        }
    }


    n_moves_and_scores = moves_and_scores.size();
    if (n_moves_and_scores == 0) {
        Move.x1 = -1;
        Best = Move;
        return 0;
    }

    std::sort(std::begin(moves_and_scores), std::end(moves_and_scores), [&](const auto& a, const auto& b)
    {
        return a.second > b.second;
    });


    if (depth == max_depth) {
        Best = moves_and_scores[0].first;
        return moves_and_scores[0].second;
    } else {
        if (n_moves_and_scores < max_decisions) {
            n_best = n_moves_and_scores;
        } else {
            n_best = max_decisions;
        }


        depth = depth + 1;

        for (int i = 0; i < n_best; i++) {
            
            Board_new = move_figure(Board, moves_and_scores[i].first, en_passant_logic);
            Score = bestMove(Board_new, -Player, depth, max_depth, moveToString(moves_and_scores[i].first), best_next, summe) + moves_and_scores[i].second;
            //std::cout << "score " << Score << std::endl;
            if (i == 0) {
                Score_max = Score;
                Best = moves_and_scores[i].first;
            }
            if (Score > Score_max) {
                Score_max = Score;
                Best = moves_and_scores[i].first;
            } else if (Score == Score_max) {
                if ((rand() % 100) < 15) { // 15% probability -> mean at ca. 5 = n_best/2 
                    Score_max = Score;
                    Best = moves_and_scores[i].first;
                }
            }
        }

    }

    return Score_max;
}


int Check(std::vector<std::vector<int>> Board, int Player) {

    //int check = 0;
    int figure;
    int king;
    int enpassent_dummy = 0;
    std::vector<int> moves;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            figure = Board[i][j];
            if (figure * Player == 6) {
                king = i*10 + j;

                i = 8;
                j = 8;
            }
        }
    }


    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            if (Board[i][j] == 0) {
                continue;
            }
            
            moves = valid_moves(Board, j, i, "X0-X0", enpassent_dummy);

            
            for (unsigned int k = 0; k < moves.size(); k++) {
                if (moves[k] == king) {
                    return 1;
                }

            }
            
        }
    }
    
    

    return 0;


}




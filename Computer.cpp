#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <cmath>

#include "Computer.h"
#include "Validation.h"
#include "Helpers.h"





std::vector<std::vector<int>> copy(std::vector<std::vector<int>> Board) {

    std::vector<std::vector<int>> Board_new;
    std::vector<int> empty = {0,0,0,0,0,0,0,0};
    for (int i = 0; i < 8; i++) {
        Board_new.push_back(empty);
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Board_new[i][j] = Board[i][j];
        }
    }

    return Board_new;
}

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

    return 1;
    return Score;
}



int bestMove(std::vector<std::vector<int>> Board, int Player, int depth, int max_depth, std::string LastMove, Coordinates &Best) {

    int max_decisions = 10;
    int figure;
    int en_passant_logic = 0;
    std::vector<std::pair<Coordinates, int>> moves_and_scores;
    std::vector<int> moves_one_figure;
    std::vector<int> moves_best;
    //int Board_new[8][8];
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
                    
                    Board_new = copy(Board);
                    move_figure(Board_new, Move, en_passant_logic);
                    
                    Score = calculateScore(Board_new, Player);
                    moves_and_scores.push_back(std::make_pair(Move, Score));

                }



            }

        }
    }

    n_moves_and_scores = moves_and_scores.size();
    if (n_moves_and_scores == 0) {
        Move.x1 = 0;
        Best = Move;
        return 0;
    }


    std::sort(std::begin(moves_and_scores), std::end(moves_and_scores), [&](const auto& a, const auto& b)
    {
        return a.second > b.second;
    });

    //Best = moves_and_scores[0].first;
    //std::cout << moves_and_scores[0].second << std::endl;
    //return moves_and_scores[0].second;

    //std::cout << "depth " << depth << std::endl;
    //std::cout << "n_moves " << n_moves_and_scores << std::endl;
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
            
            Board_new = copy(Board);
            move_figure(Board_new, moves_and_scores[i].first, en_passant_logic);
            Score = bestMove(Board_new, -Player, depth, max_depth, moveToString(moves_and_scores[i].first), best_next) + moves_and_scores[i].second;

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



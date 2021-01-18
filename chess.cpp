#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Computer.h"
#include "Plotting.h"
#include "Helpers.h"
#include "Validation.h"
#include "Inputs.h"







int false_move(std::string Input, std::vector<std::vector<int>> Board, std::string &Message, int Player, std::string LastMove, int &enPassant) {
    
    // invalid input length (e2-e4)
    Message = "Not the right format, e.g. e2-e4";
    if (Input.length() != 5)
        return 1;


    Coordinates move;
    move = coordsMove(Input);
    
    int x1, x2, z1, z2;
    x1 = move.x1;
    x2 = move.x2;
    z1 = move.z1;
    z2 = move.z2;
    int figure = Board[z1][x1];


    // invalid letters or numbers
    Message = "wrong input numbers or letters";
    if (!on_board(x1, z1))
        return 1;
    if (!on_board(x2, z2))
        return 1;


    // no figure pickables
    Message = "no figure at this place";
    if (figure == 0)
        return 1;
    
    // wrong player
    Message = "wrong player figure";
    if (figure < 0 && Player == 1)
        return 1;
    if (figure > 0 && Player == -1)
        return 1;


    // invalid move
    Message = "invalid move";
    int enPassantMove;
    std::vector<int> moves = valid_moves(Board, x1, z1, LastMove, enPassantMove);
    int move_possible = 0;

    for (unsigned int i = 0; i < moves.size(); i++) {
        std::cout << "moving " << moves[i] << std::endl;
        if (moves[i] == Code(z2, x2)) {
            move_possible = 1;
            if (enPassantMove == Code(z2, x2))
                enPassant = true;
            //break;
        }
    }

    if (!move_possible)
        return 1;

    
    Message = "";
    return 0;
}






int main(void) {

    
    std::string title = "";
    int players[2] = {0, 0};


    if (whichPlayer(title, players))
        return 1;

    
    //int main_figures[8] = {4, 2, 3, 5, 6, 3, 2, 4};
    std::vector<int> main_figures = {4, 2, 3, 5, 6, 3, 2, 4};
    std::vector<int> pawns = {1,1,1,1,1,1,1,1};
    std::vector<int> main_figures2 = {-4, -2, -3, -5, -6, -3, -2, -4};
    std::vector<int> pawns2 = {-1,-1,-1,-1,-1,-1,-1,-1};
    std::vector<int> empty = {0,0,0,0,0,0,0,0};

    //int board[8][8];
    std::vector<std::vector<int>> board;
    board.push_back(main_figures2);
    board.push_back(pawns2);
    board.push_back(empty);
    board.push_back(empty);
    board.push_back(empty);
    board.push_back(empty);
    board.push_back(pawns);
    board.push_back(main_figures);
    /*
    for (int i = 0; i<8; i++) {
        for (int j = 0; j<8; j++) {
            
            if (i == 0) {
                board[i][j] = -main_figures[j];
            } else if (i == 1) {
                board[i][j] = -1;
            } else if (i == 6) {
                board[i][j] = 1;
            } else if (i == 7) {
                board[i][j] = main_figures[j];
            } else {
                board[i][j] = 0;
            }


        }
    }
    */

    std::vector<Coordinates> turns;
    std::vector<std::string> turns_str;
    std::string input;
    std::string message = "";
    input = "";
    int player = 1;
    int enPassant;
    std::string prevMove = "X0-X0";
    Coordinates move;
    int PlayerType;



    while (true) {

        // clear screen
        //system ("CLS");


        // print board
        plot_board(board, title);
        
        // print moves
        int num_turn = 1;
        for (unsigned int i = 0; i < turns_str.size(); i++){
            if (i % 2 == 0) {
                std::cout << num_turn << ". ";
                num_turn++;

                std::cout << turns_str[i] << ", ";
            } else {
                std::cout << turns_str[i] << " ";
            }
            
        }



        // input or computer

        PlayerType = players[(3-player)/2-1];
        if (!PlayerType) {
            //std::cout << "Human player" << std::endl;
            inputHuman(player, input, message);
        } else {
            //inputHuman(player, input, message);
            inputComputer(board, player, input, prevMove);
        }

        // quit game
        if (input == "quit") {
            break;
            //running = false;
        }
        
        // help page
        if (input == "help") {
            std::string dummy;
            system("CLS");
            print_help();
            std::cin.ignore();
            std::cin.get();
            continue;
        }



        // action

        
        enPassant = false;
        if (turns.size() > 0) {
            prevMove = turns_str.back();
        }


        // validate turn
        if (false_move(input, board, message, player, prevMove, enPassant)) {
            //message = "invalid turn, repeat input";
            continue;
        }

        // everything is correct
        move = coordsMove(input);
        turns.push_back(move);
        turns_str.push_back(input);
        player = -player;

        move_figure(board, move, enPassant);

 

    }

    return 0;
}
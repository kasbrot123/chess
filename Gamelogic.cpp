#include <iostream>
#include <vector>
#include <sstream>

#include "Gamelogic.h"
#include "Helpers.h"



// coordinates in 0..7
int on_board(int x, int y) {

    if (x < 0 || x > 7 || y < 0 || y > 7)
        return 0;
    
    return 1;
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
            
            moves = possible_moves(Board, j, i, "X0-X0", enpassent_dummy);

            
            for (unsigned int k = 0; k < moves.size(); k++) {
                if (moves[k] == king) {
                    return 1;
                }

            }
            
        }
    }
    
    

    return 0;


}


int NextCheck(std::vector<std::vector<int>> Board, int x1, int z1, int x2, int z2) {

    std::vector<std::vector<int>> new_board;
    Coordinates move;
    int player = Board[z1][x1];
    player = player/abs(player);
    move.x1 = x1;
    move.x2 = x2;
    move.z1 = z1;
    move.z2 = z2;

    new_board = move_figure(Board, move, 0);

    return Check(new_board, player);

}



int CheckMate(std::vector<std::vector<int>> Board, int Player) {

    std::vector<int> any_valid_moves;
    int en_passent_dummy = 0;
    if (Check(Board, Player)) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (Board[i][j]*Player > 0) {

                    any_valid_moves = Valid_moves(Board, j, i, "X0-X0", en_passent_dummy);
                    if (any_valid_moves.size() > 0) {
                        //std::cout << "one possible zxzx" << i << j << any_valid_moves[0] << std::endl;
                        return 0;
                    }

                }
            }
        }

        return 1;
    }

    return 0;
}



std::vector<int> possible_moves(std::vector<std::vector<int>> Board, int x, int z, std::string lastMove, int &en_passant_move) {

    int figure, dir;


    figure = Board[z][x];
    dir = -figure/abs(figure); //direction for index "i" for player 1/2

    std::vector<int> moves;

    // pawn
    if (abs(figure) == 1) {
        
        if (on_board(z+dir, x) && (Board[z+dir][x] == 0))
            moves.push_back((z+dir)*10+x);
        if (on_board(z+dir*2, x) && (Board[z+dir][x] == 0) && (Board[z+dir*2][x] == 0) && ((z*dir+7)%7==1))
            moves.push_back((z+dir*2)*10+x);
        if (on_board(z+dir, x-1) && (Board[z+dir][x-1] * dir > 0))
            moves.push_back((z+dir)*10+x-1);
        if (on_board(z+dir, x+1) && (Board[z+dir][x+1] * dir > 0))
            moves.push_back((z+dir)*10+x+1);

        // en passant
        std::stringstream ss;
        int a, b;
        int logic_passant;
        ss << lastMove[1] << " " << lastMove[4];
        ss >> a >> b;

        logic_passant = (char_to_num(lastMove[0]) == (x-1)) && (char_to_num(lastMove[3]) == (x-1)) && (abs(a - b) == 2);
        //std::cout << "enpassant " << on_board(z, x-1) << (Board[z][x-1]) << std::endl;
        if (((z*dir+7)%7==4) && on_board(z, x-1) && (abs(Board[z][x-1]) == 1) && logic_passant) {
            moves.push_back((z+dir)*10+x-1);
            en_passant_move = (z+dir)*10+x-1;
        }
        logic_passant = (char_to_num(lastMove[0]) == (x+1)) && (char_to_num(lastMove[3]) == (x+1)) && (abs(a - b) == 2);
        if (((z*dir+7)%7==4) && on_board(z, x+1) && (abs(Board[z][x+1])) == 1 && logic_passant) {
            moves.push_back((z+dir)*10+x+1);
            en_passant_move = (z+dir)*10+x+1;
        }
        
    }

    // knight
    if (abs(figure) == 2) {

        if (on_board(z+2, x-1) && Board[z+2][x-1] * dir >= 0)
            moves.push_back((z+2)*10+(x-1));
        if (on_board(z+2, x+1) && Board[z+2][x+1] * dir >= 0)
            moves.push_back((z+2)*10+(x+1));
        if (on_board(z+1, x-2) && Board[z+1][x-2] * dir >= 0)
            moves.push_back((z+1)*10+(x-2));
        if (on_board(z+1, x+2) && Board[z+1][x+2] * dir >= 0)
            moves.push_back((z+1)*10+(x+2));
        if (on_board(z-2, x-1) && Board[z-2][x-1] * dir >= 0)
            moves.push_back((z-2)*10+(x-1));
        if (on_board(z-2, x+1) && Board[z-2][x+1] * dir >= 0)
            moves.push_back((z-2)*10+(x+1));
        if (on_board(z-1, x-2) && Board[z-1][x-2] * dir >= 0)
            moves.push_back((z-1)*10+(x-2));
        if (on_board(z-1, x+2) && Board[z-1][x+2] * dir >= 0)
            moves.push_back((z-1)*10+(x+2));

    }

    // bishop and queen
    if (abs(figure) == 3 || abs(figure) == 5) {

        for (int i = 1; i < 8; i++) {
            if (on_board(z+i, x+i) && Board[z+i][x+i] * dir >= 0)
                moves.push_back((z+i)*10 + x+i);
            if (on_board(z+i, x+i) && Board[z+i][x+i] * dir != 0)
                break;
        }

        for (int i = 1; i < 8; i++) {
            if (on_board(z+i, x-i) && Board[z+i][x-i] * dir >= 0)
                moves.push_back((z+i)*10 + x-i);
            if (on_board(z+i, x-i) && Board[z+i][x-i] * dir != 0)
                break;
        }

        for (int i = 1; i < 8; i++) {
            if (on_board(z-i, x+i) && Board[z-i][x+i] * dir >= 0)
                moves.push_back((z-i)*10 + x+i);
            if (on_board(z-i, x+i) && Board[z-i][x+i] * dir != 0)
                break;
        }

        for (int i = 1; i < 8; i++) {
            if (on_board(z-i, x-i) && Board[z-i][x-i] * dir >= 0)
                moves.push_back((z-i)*10 + x-i);
            if (on_board(z-i, x-i) && Board[z-i][x-i] * dir != 0)
                break;
        }
    }

    // rook and queen
    if (abs(figure) == 4 || abs(figure) == 5) {

        for (int i = 1; i < 8; i++) {
            if (on_board(z, x+i) && Board[z][x+i] * dir >= 0)
                moves.push_back((z)*10 + x+i);
            if (on_board(z, x+i) && Board[z][x+i] * dir != 0)
                break;
        }

        for (int i = 1; i < 8; i++) {
            if (on_board(z, x-i) && Board[z][x-i] * dir >= 0)
                moves.push_back((z)*10 + x-i);
            if (on_board(z, x-i) && Board[z][x-i] * dir != 0)
                break;
        }

        for (int i = 1; i < 8; i++) {
            if (on_board(z+i, x) && Board[z+i][x] * dir >= 0)
                moves.push_back((z+i)*10 + x);
            if (on_board(z+i, x) && Board[z+i][x] * dir != 0)
                break;
        }

        for (int i = 1; i < 8; i++) {
            if (on_board(z-i, x) && Board[z-i][x] * dir >= 0)
                moves.push_back((z-i)*10 + x);
            if (on_board(z-i, x) && Board[z-i][x] * dir != 0)
                break;
        }
    }


    // king
    if (abs(figure) == 6) {

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {

                if (i == 0 && j == 0)
                    continue;
                if (on_board(z+i, x+j) && Board[z+i][x+j] * dir >= 0)
                    moves.push_back((z+i)*10+x+j);
            }
        }

    }


    return moves;
}


std::vector<int> Valid_moves(std::vector<std::vector<int>> Board, int x, int z, std::string lastMove, int &en_passant_move) {

    int x2, z2;
    std::vector<int> possible;
    std::vector<int> valid;
    int en_passent = 0;
    possible = possible_moves(Board, x, z, lastMove, en_passent);

    for (unsigned int i = 0; i < possible.size(); i++) {
        x2 = possible[i] % 10;
        z2 = possible[i] / 10;
        
        if (!NextCheck(Board, x, z, x2, z2))
            valid.push_back(possible[i]);

    }

    return valid;

}


std::vector<std::vector<int>> move_figure(std::vector<std::vector<int>> Board, Coordinates Move, int enPassant_logic) {

  
    int figure;
    //int dir;
    


    figure = Board[Move.z1][Move.x1];
    
    if (abs(figure) == 1 && (Move.z2 == 0 || Move.z2 == 7)) {
        figure = 5;
    }
    
    //std::cout << "out of if" << std::endl;
    //dir = figure/abs(figure);
    Board[Move.z1][Move.x1] = 0;
    Board[Move.z2][Move.x2] = figure;

    //if (enPassant_logic) 
    //    Board[Move.z2+dir][Move.x2] = 0;

    return Board;
}


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
    std::vector<int> moves = Valid_moves(Board, x1, z1, LastMove, enPassantMove);
    int move_possible = 0;
    std::vector<std::vector<int>> future_board;


    for (unsigned int i = 0; i < moves.size(); i++) {
        //std::cout << "moving " << moves[i] << std::endl;
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






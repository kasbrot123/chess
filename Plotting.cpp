#include <iostream>
#include <vector>

#include "Plotting.h"




void print_help(void) {

    std::cout << "This is the help page. " << std::endl;
    std::cout << std::endl;
    std::cout << "help ... shows the help page" << std::endl;
    std::cout << "quit ... exit game" << std::endl;
    std::cout << std::endl;
    std::cout << "press any key to return" << std::endl;

}



void plot_board(std::vector<std::vector<int>> Board, std::string Title) {

    int figure;

    char figures_black[] = " bsltdk";
    char figures_white[] = " BSLTDK";

    std::cout << Title << std::endl;
    std::cout << std::endl;
    for (int i = 0; i<8; i++) {
        std::cout << "   +---+---+---+---+---+---+---+---+" << std::endl;
        std::cout << " " << 8-i << " ";
        for (int j = 0; j<8; j++) {

            figure = Board[i][j];
            if (figure <= 0) {
                std::cout << "| " << figures_black[-figure] << " ";
            } else {
                std::cout << "| " << figures_white[figure] << " ";
            }
            

        }
        std::cout << "|" << std::endl;        
    }
    std::cout << "   +---+---+---+---+---+---+---+---+" << std::endl;
    std::cout << "     A   B   C   D   E   F   G   H  " << std::endl;
    std::cout << std::endl;

}



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
    std::string lefty = " ";
    std::string righty = " ";

    std::cout << Title << std::endl;
    std::cout << std::endl;
    for (int i = 0; i<8; i++) {
        std::cout << "   +------+------+------+------+------+------+------+------+" << std::endl;
        if (i % 2 == 0) {
        std::cout << "   |+----+|      |+----+|      |+----+|      |+----+|      |" << std::endl;

        } else {
        std::cout << "   |      |+----+|      |+----+|      |+----+|      |+----+|" << std::endl;

        }
        
        std::cout << " " << 8-i << " ";
        
        for (int j = 0; j<8; j++) {
          if ((i+j) % 2 == 0) {
            lefty = "||";
            righty = " |";
          } else {
            lefty = "| ";
            righty = "  ";
          }

            figure = Board[i][j];
            if (figure <= 0) {
                std::cout << lefty << "  " << figures_black[-figure] << righty;
            } else {
                std::cout << lefty << "  " << figures_white[figure] << righty;
            }
            
            
        }
        std::cout << "|" << std::endl;
        if (i % 2 == 0) {
        std::cout << "   |+----+|      |+----+|      |+----+|      |+----+|      |" << std::endl;
        } else {
        std::cout << "   |      |+----+|      |+----+|      |+----+|      |+----+|" << std::endl;
        }

    }
    std::cout << "   +------+------+------+------+------+------+------+------+" << std::endl;
    std::cout << "       A      B      C      D      E      F      G      H   " << std::endl;
    std::cout << std::endl;

}

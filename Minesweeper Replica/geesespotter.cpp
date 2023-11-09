#include <iostream>
#include "geesespotter.h"

char * create_board(std::size_t x_dim, std::size_t y_dim){
    int size = x_dim*y_dim;
    char* array;
    array = new char[size];
    for(std::size_t i = 0; i < size; i++){
        array[i] = 0;
    }
    return array;
}
void clean_board(char * board){
    delete[] board;
    board = nullptr;
}
void print_board(char * board, std::size_t x_dim, std::size_t y_dim){
    int hidden = 1 << 5;
    int marked = 1 << 4;

    for(std::size_t i = 0; i < y_dim; i++){
        for(std::size_t j = 0; j < x_dim; j++){
            if((board[j+x_dim*i]&marked)){
                std::cout<<"M";
            }
            else if((board[j+x_dim*i]&hidden)){
                std::cout<<"*";
            }
            else{
                std::cout<<(board[j+x_dim*i]&15);
            }
        }
        std::cout<<std::endl;
    }
    
}

void hide_board(char * board, std::size_t x_dim, std::size_t y_dim){
    int size = x_dim*y_dim;
    int hidden = 1 << 5;
    for(std::size_t i = 0; i < size; i++){
        board[i] = board[i] | hidden;
    }
}
int mark(char * board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc){
    int marked = 1 << 4;
    int hidden = 1 << 5;

    for(std::size_t i = 0; i < y_dim; i++){
        for(std::size_t j = 0; j < x_dim; j++){
            if((j == x_loc) && (i == y_loc)){
                if((board[j + x_dim*i]&hidden) == 0){
                    return 2;
                }
                else{
                    board[j + x_dim*i] ^= marked;
                    return 0;
                }
            }
        }
    }
}
int check(std::size_t x, std::size_t y,std::size_t i);
int check(std::size_t x, std::size_t y,std::size_t i){
    //top left
        if(i==0){
            return 0;
        }
    //top right
        else if(i==(x-1)){
            return 1;
        }
    //bottom left
        else if(i == (x*(y-1))){
            return 2;
        }
    //bottom right
        else if(i == (x*y-1)){
            return 3;
        }
    //top row
        else if((i>0)&&(i<x-1)){
            return 4;
        }
    //bottom row
        else if((i>(x*(y-1)))&&(i<(x*y-1))){
            return 5;
        }
    //left col
        else if((i%x)==0){
            return 6;
        }
    //right col
        else if(((i+1)%x)==0){
            return 7;
        }
    //middle of grid
        else{
            return 8;
        }
}
void compute_neighbours(char *board, std::size_t x_dim, std::size_t y_dim){
    int size = x_dim * y_dim;
    for(std::size_t i = 0; i < size; i++){
        if((board[i] & 15) != 9){
            int geese = 0;
            if(x_dim == 1){
                if(i == 0){
                    if((board[i + 1] & 15) == 9){
                        geese++;
                    }
                }
                else if(i == (y_dim - 1)){
                    if((board[i - 1] & 15) == 9){
                        geese++;
                    }
                }
                else{
                    if((board[i - 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i + 1] & 15) == 9){
                        geese++;
                    }
                }
            }
            else if (y_dim == 1){
                if(i == 0){
                    if((board[i + 1] & 15) == 9){
                        geese++;
                    }
                }
                else if(i == (x_dim - 1)){
                    if((board[i - 1] & 15) == 9){
                        geese++;
                    }
                }
                else{
                    if((board[i - 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i + 1] & 15) == 9){
                        geese++;
                    }
                }
            }
            else{
                if(check(x_dim, y_dim, i) == 0){
                    if((board[1] & 15) == 9){
                        geese++;
                    }
                    if((board[x_dim] & 15) == 9){
                        geese++;
                    }
                    if((board[x_dim + 1] & 15) == 9){
                        geese++;
                    }
                }
                else if(check(x_dim, y_dim, i) == 1){
                    if((board[i - 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i + x_dim] & 15) == 9){
                        geese++;
                    }
                    if ((board[i + x_dim - 1] & 15) == 9){
                        geese++;
                    }
                }
                else if(check(x_dim, y_dim, i) == 2){
                    if((board[i + 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i - x_dim] & 15) == 9){
                        geese++;
                    }
                    if((board[i - x_dim + 1] & 15) == 9){
                        geese++;
                    }
                }
                else if(check(x_dim, y_dim, i) == 3){
                    if((board[i - 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i - x_dim] & 15) == 9){
                        geese++;
                    }
                    if((board[i - x_dim - 1] & 15) == 9){
                        geese++;
                    }
                }
                else if(check(x_dim, y_dim, i) == 4){
                    if((board[i - 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i + 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i + x_dim - 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i + x_dim] & 15) == 9){
                        geese++;
                    }
                    if((board[i + x_dim + 1] & 15) == 9){
                        geese++;
                    }
                }
                else if(check(x_dim, y_dim, i) == 5){
                    if((board[i - 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i + 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i - x_dim - 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i - x_dim] & 15) == 9){
                        geese++;
                    }
                    if ((board[i - x_dim + 1] & 15) == 9){
                        geese++;
                    }
                }
                else if(check(x_dim, y_dim, i) == 6){
                    if((board[i - x_dim] & 15) == 9){
                        geese++;
                    }
                    if((board[i - x_dim + 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i + 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i + x_dim] & 15) == 9){
                        geese++;
                    }
                    if((board[i + x_dim + 1] & 15) == 9){
                        geese++;
                    }
                }
                else if(check(x_dim, y_dim, i) == 7){
                    if((board[i - x_dim] & 15) == 9){
                        geese++;
                    }
                    if((board[i - x_dim - 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i - 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i + x_dim] & 15) == 9){
                        geese++;
                    }
                    if((board[i + x_dim - 1] & 15) == 9){
                        geese++;
                    }
                } 
                else if(check(x_dim, y_dim, i) == 8){
                    if((board[i - x_dim - 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i - x_dim] & 15) == 9){
                        geese++;
                    }
                    if((board[i - x_dim + 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i - 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i + 1] & 15) == 9){
                        geese++;
                    }
                    if((board[i + x_dim - 1] & 15) == 9){
                        geese++;
                    }
                    if ((board[i + x_dim] & 15) == 9){
                        geese++;
                    }
                    if((board[i + x_dim + 1] & 15) == 9){
                        geese++;
                    }
                }          
            }
            board[i] |= geese;
        }
    }
}

bool is_game_won(char * board, std::size_t x_dim, std::size_t y_dim){
    int size = x_dim*y_dim;
    int hidden = 1 << 5;
    for(std::size_t i = 0; i < size; i++){
        if(((board[i]&15) != 9) && ((board[i]&hidden) == hidden)){
            return false;
            
        }
    }
    return true;
}
int reveal(char * board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc, std::size_t y_loc){
    int hidden = 1<<5;
    int mark = 1<<4;
    for(std::size_t i = 0; i < y_dim; i++){
        for(std::size_t j = 0; j < x_dim; j++){
            if((j == x_loc) && (i == y_loc)){
                if((board[j + x_dim*i]&mark) == mark){
                    return 1;
                }
                else if((board[j + x_dim*i]&15) == 9){
                    board[j + x_dim*i] ^= hidden;
                    return 9;
                }
                else if((board[j + x_dim*i]&hidden) == 0){
                    return 2;
                }
                else if((board[j + x_dim*i]&15) == 0){
                    board[j + x_dim*i] ^= hidden;
                    if(check(x_dim,y_dim,j+x_dim*i)==0){
                        if(((board[j + x_dim*i + 1]&mark)==0) && ((board[j + x_dim*i + 1]&hidden)==hidden)){
                            board[j + x_dim*i + 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i + x_dim]&mark)==0) && ((board[j + x_dim*i + x_dim]&hidden)==hidden)){
                            board[j + x_dim*i + x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i + 1 + x_dim]&mark)==0) && ((board[j + x_dim*i + x_dim + 1]&hidden)==hidden)){
                            board[j + x_dim*i + 1 + x_dim] ^= hidden;
                        }
                    }
                    else if(check(x_dim,y_dim,j+x_dim*i)==1){
                        if(((board[j + x_dim*i - 1]&mark)==0) && ((board[j + x_dim*i - 1]&hidden)==hidden)){
                            board[j + x_dim*i - 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i - x_dim]&mark)==0) && ((board[j + x_dim*i - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i - x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i - 1 - x_dim]&mark)==0) && ((board[j + x_dim*i - 1 - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i - 1 - x_dim] ^= hidden;
                        }
                    }
                    else if(check(x_dim, y_dim, j + x_dim * i) == 2){
                        if(((board[j + x_dim*i + 1]&mark)==0) && ((board[j + x_dim*i + 1]&hidden)==hidden)){
                            board[j + x_dim*i + 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i - x_dim]&mark)==0) && ((board[j + x_dim*i - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i - x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i + 1 - x_dim]&mark)==0) && ((board[j + x_dim*i + 1 - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i + 1 - x_dim] ^= hidden;
                        }
                    }
                    else if(check(x_dim, y_dim, j + x_dim * i) == 3){
                        if(((board[j + x_dim*i - 1]&mark)==0) && ((board[j + x_dim*i - 1]&hidden)==hidden)){
                            board[j + x_dim*i - 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i - x_dim]&mark)==0) && ((board[j + x_dim*i - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i - x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i - 1 - x_dim]&mark)==0) && ((board[j + x_dim*i - 1 - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i - 1 - x_dim] ^= hidden;
                        }
                    }
                    else if(check(x_dim, y_dim, j + x_dim * i) == 4){
                        if(((board[j + x_dim*i + 1]&mark)==0) && ((board[j + x_dim*i + 1]&hidden)==hidden)){
                            board[j + x_dim*i + 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i - 1]&mark)==0) && ((board[j + x_dim*i - 1]&hidden)==hidden)){
                            board[j + x_dim*i - 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i + 1 + x_dim]&mark)==0) && ((board[j + x_dim*i + 1 + x_dim]&hidden)==hidden)){
                            board[j + x_dim*i + 1 + x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i + x_dim]&mark)==0) && ((board[j + x_dim*i + x_dim]&hidden)==hidden)){
                            board[j + x_dim*i + x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i + x_dim - 1]&mark)==0) && ((board[j + x_dim*i + x_dim - 1]&hidden)==hidden)){
                            board[j + x_dim*i + x_dim - 1] ^= hidden;
                        }
                    }
                    else if(check(x_dim, y_dim, j + x_dim * i) == 5){
                        if(((board[j + x_dim*i + 1]&mark)==0) && ((board[j + x_dim*i + 1]&hidden)==hidden)){
                            board[j + x_dim*i + 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i - 1]&mark)==0) && ((board[j + x_dim*i - 1]&hidden)==hidden)){
                            board[j + x_dim*i - 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i + 1 - x_dim]&mark)==0) && ((board[j + x_dim*i + 1 - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i + 1 - x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i - x_dim]&mark)==0) && ((board[j + x_dim*i - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i - x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i - x_dim - 1]&mark)==0) && ((board[j + x_dim*i - x_dim - 1]&hidden)==hidden)){
                            board[j + x_dim*i - x_dim - 1] ^= hidden;
                        }
                    }
                    else if(check(x_dim, y_dim, j + x_dim * i) == 6){
                        if(((board[j + x_dim*i + 1]&mark)==0) && ((board[j + x_dim*i + 1]&hidden)==hidden)){
                            board[j + x_dim*i + 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i - x_dim]&mark)==0) && ((board[j + x_dim*i - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i - x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i + 1 + x_dim]&mark)==0) && ((board[j + x_dim*i + x_dim]&hidden)==hidden)){
                            board[j + x_dim*i + 1 + x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i - x_dim + 1]&mark)==0) && ((board[j + x_dim*i - x_dim + 1]&hidden)==hidden)){
                            board[j + x_dim*i - x_dim + 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i + x_dim]&mark)==0) && ((board[j + x_dim*i + x_dim]&hidden)==hidden)){
                            board[j + x_dim*i + x_dim] ^= hidden;
                        }
                    }
                    else if(check(x_dim, y_dim, j + x_dim * i) == 7){
                        if(((board[j + x_dim*i - 1]&mark)==0) && ((board[j + x_dim*i - 1]&hidden)==hidden)){
                            board[j + x_dim*i - 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i - 1 - x_dim]&mark)==0) && ((board[j + x_dim*i - 1 - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i - 1 - x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i - 1 + x_dim]&mark)==0) && ((board[j + x_dim*i - 1 + x_dim]&hidden)==hidden)){
                            board[j + x_dim*i - 1 + x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i - x_dim]&mark)==0) && ((board[j + x_dim*i - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i - x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i + x_dim]&mark)==0) && ((board[j + x_dim*i + x_dim]&hidden)==hidden)){
                            board[j + x_dim*i + x_dim] ^= hidden;
                        }
                    }
                    else if(check(x_dim, y_dim, j + x_dim * i) == 8){
                        if(((board[j + x_dim*i + 1]&mark)==0) && ((board[j + x_dim*i + 1]&hidden)==hidden)){
                            board[j + x_dim*i + 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i - 1]&mark)==0) && ((board[j + x_dim*i - 1]&hidden)==hidden)){
                            board[j + x_dim*i - 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i + x_dim]&mark)==0) && ((board[j + x_dim*i + x_dim]&hidden)==hidden)){
                            board[j + x_dim*i + x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i + x_dim - 1]&mark)==0) && ((board[j + x_dim*i + x_dim - 1]&hidden)==hidden)){
                            board[j + x_dim*i + x_dim - 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i + x_dim + 1]&mark)==0) && ((board[j + x_dim*i + x_dim + 1]&hidden)==hidden)){
                            board[j + x_dim*i + x_dim + 1] ^= hidden;
                        }
                        if(((board[j + x_dim*i - x_dim]&mark)==0) && ((board[j + x_dim*i - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i - x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i - 1 - x_dim]&mark)==0) && ((board[j + x_dim*i - 1 - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i - 1 - x_dim] ^= hidden;
                        }
                        if(((board[j + x_dim*i + 1 - x_dim]&mark)==0) && ((board[j + x_dim*i + 1 - x_dim]&hidden)==hidden)){
                            board[j + x_dim*i + 1 - x_dim] = hidden;
                        }
                    }
                }
                else{
                    board[j + x_dim*i] ^= hidden;
                    return 0;
                }
            }
        }
    }
}
#pragma once

#include <array>

class TicTacToe
{
private:
    char board[10];
    bool is_x_turn;
    bool check_game_over() const;

public:
    TicTacToe() { reset(); }
    void reset();
    void move(int idx);
    char get_player() const { return is_x_turn ? 'X' : 'O'; }
    const char* get_board() const { return board; }
};

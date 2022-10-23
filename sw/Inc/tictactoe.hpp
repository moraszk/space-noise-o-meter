#pragma once

#include <array>

class TicTacToe
{
private:
    std::array<char, 10> board;
    bool is_x_turn;
    bool check_game_over() const;

public:
    TicTacToe() { reset(); }
    void reset();
    void move(int idx);
    char get_player() const { return is_x_turn ? 'X' : 'O'; }
    const auto& get_board() const { return board; }
};

#include "tictactoe.hpp"

void TicTacToe::reset()
{
    for (int i = 0; i < 9; i++)
    {
        board[i] = ' ';
    }
    board[9] = '\0';
    is_x_turn = true;
}

void TicTacToe::move(int idx)
{
    if (1 <= idx && idx <= 9 && board[idx - 1] == ' ')
    {
        board[idx - 1] = is_x_turn ? 'X' : 'O';
        is_x_turn = !is_x_turn;
    }
}

bool TicTacToe::check_game_over() const
{
    for (int i = 0; i < 3; i++)
    {
        // columns
        if (board[i] != ' ' && board[i] == board[i + 3] && board[i + 3] == board[i + 6])
        {
            return true;
        }
        // rows
        if (board[i * 3] != ' ' && board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2])
        {
            return true;
        }
    }
    // diagonal (top left to bottom right)
    if (board[4] != ' ' && board[0] == board[4] && board[0] == board[8])
    {
        return true;
    }
    // diagonal (top right to bottom left)
    if (board[4] != ' ' && board[2] == board[4] && board[2] == board[6])
    {
        return true;
    }

    // check if there is a free space
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == ' ')
        {
            return false;
        }
    }
    return true;
}

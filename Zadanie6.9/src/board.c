#include "board.h"
#include <stdio.h>
#include <stdlib.h>

//create_board errors
#define SUCCESS 0
#define FAIL 1
#define ALLOCATE_FAIL 2

int create_board(struct board_t **board, int width, int height)
{
    if (board == NULL || width < 1 || height < 1)
        return FAIL;

    *board = (struct board_t *)calloc(1, sizeof(struct board_t));
    if (*board == NULL)
        return ALLOCATE_FAIL;

    (*board)->width = width;
    (*board)->height = height;
    (*board)->is_init = 0;

    (*board)->board = (char **)calloc(height, sizeof(char *));
    if ((*board)->board == NULL)
        return free(*board), ALLOCATE_FAIL;

    for (int i = 0; i < height; i++)
    {
        *((*board)->board + i) = (char *)calloc(width + 1, sizeof(char));
        if (*((*board)->board + i) == NULL)
        {
            for (int j = 0; j < i; j++)
                free(*((*board)->board + j));
            return free((*board)->board), free(*board), ALLOCATE_FAIL;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            *(*((*board)->board + i) + j) = '.';
        *(*((*board)->board + i) + width) = '\0';
    }

    (*board)->move_player_down = move_player_down;
    (*board)->move_player_left = move_player_left;
    (*board)->move_player_right = move_player_right;
    (*board)->move_player_up = move_player_up;

    return SUCCESS;
}

void display_board(const struct board_t *board)
{
    if (board == NULL || board->height < 1 || board->width < 1)
        return;

    for (int i = 0; i < board->height; i++)
    {
        for (int j = 0; j < board->width; j++)
            printf("%c", *(*(board->board + i) + j));
        printf("\n");
    }
}

void free_board(struct board_t *board)
{
    if (board == NULL || board->height < 1 || board->width < 1)
        return;

    for (int i = 0; i < board->height; i++)
        free(*(board->board + i));
    free(board->board);
    free(board);
}

int set_player(struct board_t *board, int x, int y)
{
    if (board == NULL || board->board == NULL || board->height < 1 || board->width < 1 || x < 0 || y < 0 || x >= board->width || y >= board->height || board->is_init)
        return FAIL;

    board->player.x = x;
    board->player.y = y;

    *(*(board->board + y) + x) = '@';
    board->is_init = 1;

    return SUCCESS;
}

struct board_t *move_player_up(struct board_t *board)
{
    if (board == NULL || board->board == NULL || board->height < 1 || board->width < 1 || board->player.x < 0 || board->player.y < 0 || board->player.x >= board->width || board->player.y >= board->height || !board->is_init)
        return NULL;

    if (board->player.y == 0)
        board->player.y = board->height - 1;
    else
        board->player.y = board->player.y - 1;

    int pos_player_y = board->player.y;
    int pos_player_x = board->player.x;

    for (int i = 0; i < board->height; i++)
    {
        for (int j = 0; j < board->width; j++)
            *(*(board->board + i) + j) = '.';
    }

    *(*(board->board + pos_player_y) + pos_player_x) = '@';

    return board;
}

struct board_t *move_player_down(struct board_t *board)
{
    if (board == NULL || board->board == NULL || board->height < 1 || board->width < 1 || board->player.x < 0 || board->player.y < 0 || board->player.x >= board->width || board->player.y >= board->height || !board->is_init)
        return NULL;

    if (board->player.y == board->height - 1)
        board->player.y = 0;
    else
        board->player.y = board->player.y + 1;

    int pos_player_y = board->player.y;
    int pos_player_x = board->player.x;

    for (int i = 0; i < board->height; i++)
    {
        for (int j = 0; j < board->width; j++)
            *(*(board->board + i) + j) = '.';
    }

    *(*(board->board + pos_player_y) + pos_player_x) = '@';

    return board;
}

struct board_t *move_player_left(struct board_t *board)
{
    if (board == NULL || board->board == NULL || board->height < 1 || board->width < 1 || board->player.x < 0 || board->player.y < 0 || board->player.x >= board->width || board->player.y >= board->height || !board->is_init)
        return NULL;

    if (board->player.x == 0)
        board->player.x = board->width - 1;
    else
        board->player.x = board->player.x - 1;

    int pos_player_y = board->player.y;
    int pos_player_x = board->player.x;

    for (int i = 0; i < board->height; i++)
    {
        for (int j = 0; j < board->width; j++)
            *(*(board->board + i) + j) = '.';
    }

    *(*(board->board + pos_player_y) + pos_player_x) = '@';

    return board;
}

struct board_t *move_player_right(struct board_t *board)
{
    if (board == NULL || board->board == NULL || board->height < 1 || board->width < 1 || board->player.x < 0 || board->player.y < 0 || board->player.x >= board->width || board->player.y >= board->height || !board->is_init)
        return NULL;

    if (board->player.x == board->width - 1)
        board->player.x = 0;
    else
        board->player.x = board->player.x + 1;

    int pos_player_y = board->player.y;
    int pos_player_x = board->player.x;

    for (int i = 0; i < board->height; i++)
    {
        for (int j = 0; j < board->width; j++)
            *(*(board->board + i) + j) = '.';
    }

    *(*(board->board + pos_player_y) + pos_player_x) = '@';

    return board;
}
#include "board.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define FAILED_TO_ALLOCATE_MEMORY 8

#define ALLOCATE_FAIL 2

int main()
{
	int error, width, height;
	printf("Enter width and height of the board: ");
	error = scanf("%d %d", &width, &height);
	if (error != 2)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (width < 1 || height < 1)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;

	struct board_t *board;
	error = create_board(&board, width, height);
	if (error == ALLOCATE_FAIL)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	int x, y;
	printf("Enter player's initial coordinates (x, y): ");
	error = scanf("%d %d", &x, &y);
	if (error != 2)
		return printf("Incorrect input"), free_board(board), INCORRECT_INPUT;
	if (x < 0 || x >= width || y < 0 || y >= height)
		return printf("Incorrect input data"), free_board(board), INCORRECT_INPUT_DATA;

	while (getchar() != '\n'); //clear buffer

	set_player(board, x, y);
	display_board(board);

	char choice;
	while (1)
	{
		printf("Choose your action: ");
		scanf("%c", &choice);
		while (getchar() != '\n'); //clear buffer

		if (choice == 'q')
			break;

		switch (choice)
		{
		case 'w':
			board = board->move_player_up(board);
			display_board(board);
			break;
		case 's':
			board = board->move_player_down(board);
			display_board(board);
			break;
		case 'd':
			board = board->move_player_right(board);
			display_board(board);
			break;
		case 'a':
			board = board->move_player_left(board);
			display_board(board);
			break;
		default:
			printf("Incorrect choice\n");
			break;
		}
	}
	free_board(board);

	return SUCCESS;
}
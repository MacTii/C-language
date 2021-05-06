#ifndef __BOARD_H__
#define __BOARD_H__

struct point_t
{
    int x;
    int y;
};

struct board_t
{
    //pozycja gracza
    struct point_t player;

    // wskanik na plansz, wiersze powinny by zakoczone terminatorem
    char **board;

    // szeroko oraz wysoko planszy do gry
    int width;
    int height;

    // flaga informujca o tym, czy gracz zosta dodany do planszy, czy nie
    unsigned char is_init : 1;

    // Funkcja odpowiada za poruszenie gracza o jedn komrk w gr.
    // W przypadku dojcia do krawdzi gracz powinien znale si w ostatnim wierszu planszy.
    struct board_t *(*move_player_up)(struct board_t *);

    // funkcja odpowiada za poruszenie gracza o jedn komrk w d.
    // W przypadku dojcia do krawdzi gracz powinien znale si w pierwszym wierszu planszy.
    struct board_t *(*move_player_down)(struct board_t *);

    // funkcja odpowiada za poruszenie gracza o jedn komrk w lewo.
    // W przypadku dojcia do krawdzi gracz powinien znale si w ostatniej kolumnie planszy.
    struct board_t *(*move_player_left)(struct board_t *);

    // funkcja odpowiada za poruszenie gracza o jedn komrk w prawo.
    // W przypadku dojcia do krawdzi gracz powinien znale si w pierwszej kolumnie planszy.
    struct board_t *(*move_player_right)(struct board_t *);
};

int create_board(struct board_t **board, int width, int height);
void display_board(const struct board_t *board);
void free_board(struct board_t *board);
int set_player(struct board_t *board, int x, int y);

struct board_t *move_player_up(struct board_t *);
struct board_t *move_player_down(struct board_t *);
struct board_t *move_player_left(struct board_t *);
struct board_t *move_player_right(struct board_t *);

#endif // !__BOARD_H__
int turn(int current_turn);

int coords_nbs_dictionary (char chr);
int coords_ltr_dictionary (char chr);

typedef struct {int x1; int y1; int x2; int y2;} Coords;
Coords translate_coords(char* input);
void print_coords(Coords coords);

int IsItWin();

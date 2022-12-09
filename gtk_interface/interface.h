#define PAWN_NB 14

typedef struct {int x; int y;} Pion;

void onDestroy(GtkWidget *widget, gpointer data);
void onDraw(GtkWidget *widget, gpointer data);

void clear(cairo_t *cr);
void draw(cairo_t *cr);

gboolean startDraw(GtkWidget *widget, cairo_t *cr, gpointer data);

void onActivateEntry(GtkEntry* entry, gpointer data);

void setPlayerColor(char color);
void setTurnColor(char color);
void setTurnNumber(int turn);
void setLastMove(int** move);

int button_clicked;

void drawPawn (char color, int index, int* position);
void drawBoard(Plateau board);
void clearBoard();

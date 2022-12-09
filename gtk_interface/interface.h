#define PIECE_NB 14

typedef struct {int x; int y;} Pion;

void onDestroy(GtkWidget *widget, gpointer data);
void onDraw(GtkWidget *widget, gpointer data);

void clear(cairo_t *cr);
void draw(cairo_t *cr);

gboolean startDraw(GtkWidget *widget, cairo_t *cr, gpointer data);
void drawPiece (cairo_t *cr, char color, Pion position);

void onActivateEntry(GtkEntry* entry, gpointer data);

void setPlayerColor(char color);
void setTurnColor(char color);
void setTurnNumber(int turn);
void setLastMove(int** move);

int button_clicked;

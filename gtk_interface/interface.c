#include <math.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "../global.h"
#include "interface.h"
#include "../move.h"
#include "logic_main.h"

// Déclaration de la fenêtre et de ses éléments
GtkWidget* window;
GtkWidget* overlay;
GtkWidget* bgImage;
GtkWidget* menu_overlay;
GtkWidget* menu_bg_image;
GtkWidget* main_h_box;
GtkWidget* main_v_box;
GtkWidget* turn_v_box;
GtkWidget* move_v_box;
GtkWidget* buttons_v_box;

GtkWidget* text_title;
GtkWidget* text_player_id;
GtkWidget* text_turn_id;
GtkWidget* text_turn_nb;
GtkWidget* field_move;
GtkWidget* text_last_move;
GtkWidget* drawButton;
GtkWidget* quitButton;

GtkWidget* pawnsBlack[PAWN_NB];
GtkWidget* pawnsWhite[PAWN_NB];

int nb_turn;

int main(int argc, char **argv)
{
	GameData game_data;
	gtk_init(&argc, &argv); // Initialisation de GTK+
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);						// Création de la fenêtre
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	// Centrage de la fenêtre sur l'écran
	gtk_window_set_default_size(GTK_WINDOW(window), 820, 600);			// Taille de la fenêtre
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);				// Impossibilité de redimensionner la fenêtre
	gtk_window_set_title(GTK_WINDOW(window), "Abalone");				// Titre de la fenêtre

	main_h_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);			// Création d'une boîte horizontale
	gtk_container_add(GTK_CONTAINER(window), main_h_box);				// Insertion de la boîte hor. dans la fenêtre
	
	main_v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 30);				// Création de la boîte verticale principale (pour le menu)
	gtk_widget_set_margin_top(main_v_box, 20);							// Change la marge du haut du menu
	gtk_widget_set_margin_bottom(main_v_box, 20);						// Change la marge du bas du menu
	gtk_widget_set_margin_start(main_v_box, 20);						// Change la marge de gauche du menu
	gtk_widget_set_margin_end(main_v_box, 20);							// Change la marge de droite du menu
	
	turn_v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);				// Création de la sous-partie du menu concernant le tour actuel
	move_v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);				// Création de la sous-partie du menu concernant les déplacements
	buttons_v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);			// Création de la sous-partie du menu concernant les boutons
	
	overlay = gtk_overlay_new();										// Création d'une boîte overlay
	gtk_box_pack_start(GTK_BOX(main_h_box), overlay, FALSE, FALSE, 0);	// Insertion de l'overlay dans la boîte hor.
		
    bgImage = gtk_image_new_from_file("background.png");				// Affectation de l'image d'arrière-plan
    gtk_container_add(GTK_CONTAINER(overlay), bgImage);					// Insertion de l'arrière-plan dans la boîte
	
	for (int i = 0; i < PAWN_NB; i++) {
		pawnsBlack[i] = gtk_image_new_from_file("pawn_black.png");
		pawnsWhite[i] = gtk_image_new_from_file("pawn_white.png");
		gtk_overlay_add_overlay (GTK_OVERLAY(overlay), pawnsBlack[i]);
		gtk_overlay_add_overlay (GTK_OVERLAY(overlay), pawnsWhite[i]);
		
		gtk_widget_set_halign(pawnsBlack[i], GTK_ALIGN_START);
		gtk_widget_set_valign(pawnsBlack[i], GTK_ALIGN_START);
		gtk_widget_set_halign(pawnsWhite[i], GTK_ALIGN_START);
		gtk_widget_set_valign(pawnsWhite[i], GTK_ALIGN_START);
	}
	clearBoard(pawnsBlack, pawnsWhite);
	menu_overlay = gtk_overlay_new();										// Création de l'overlay du menu
	gtk_box_pack_start(GTK_BOX(main_h_box), menu_overlay, FALSE, FALSE, 0);	// Insertion de l'overlay dans la boîte hor.
	
	menu_bg_image = gtk_image_new_from_file("background_menu.png");		// Affectation de l'image d'arrière-plan du menu
    gtk_container_add(GTK_CONTAINER(menu_overlay), menu_bg_image);		// Insertion de l'arrière-plan dans la boîte
	
	text_title = gtk_label_new(NULL);									// Création du 1er label (titre)
	gchar* str = g_locale_to_utf8("<span foreground=\"#af6725\" font=\"20\"><b>Abalone</b></span>", -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(text_title), str);
	g_free(str);	
	gtk_box_pack_start(GTK_BOX(main_v_box), text_title, FALSE, FALSE, 0);		// Insertion dans main_v_box
	
	text_player_id = gtk_label_new(NULL);										// Création du 2e label (vous êtes ...)
	str = g_locale_to_utf8("<span foreground=\"#e7b17f\" font=\"13\"><b>Vous êtes les <span foreground=\"#FFF\">●</span></b></span>", -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(text_player_id), str);
	g_free(str);
	gtk_box_pack_start(GTK_BOX(main_v_box), text_player_id, FALSE, FALSE, 0);	// Insertion dans main_v_box
	
	text_turn_id = gtk_label_new(NULL);											// Création du 3e label (au tour de ...)
	str = g_locale_to_utf8("<span foreground=\"#e7b17f\" font=\"13\"><b>Tour des <span foreground=\"#000\">●</span></b></span>", -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(text_turn_id), str);
	g_free(str);
	gtk_box_pack_start(GTK_BOX(turn_v_box), text_turn_id, FALSE, FALSE, 0);	// Insertion dans turn_v_box
	
	text_turn_nb = gtk_label_new(NULL);										// Création du 4e label (tour n°_)
	str = g_locale_to_utf8("<span foreground=\"#e7b17f\">Tour 1</span>", -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(text_turn_nb), str);
	g_free(str);
	gtk_box_pack_start(GTK_BOX(turn_v_box), text_turn_nb, FALSE, FALSE, 0);	// Insertion dans turn_v_box
	
	gtk_box_pack_start(GTK_BOX(main_v_box), turn_v_box, FALSE, TRUE, 0);	// Insertion de turn_v_box dans main_v_box
	
	field_move = gtk_entry_new();															// Création de la zone de texte (pour écrire les coups)
	gtk_entry_set_max_length(GTK_ENTRY(field_move), 5);										// Nombre maximum de caractères dans le champ
	gtk_entry_set_placeholder_text(GTK_ENTRY(field_move), "Entrez un coup (X0:Y0)");		// Placeholder du champ
	gtk_entry_set_alignment(GTK_ENTRY(field_move), 0.5);									// Centre le texte du champ
	gtk_entry_set_max_width_chars(GTK_ENTRY(field_move), 9);								// Largeur maximale du champ
	gtk_entry_set_width_chars(GTK_ENTRY(field_move), 9);									// Largeur maximale du champ
	g_signal_connect(G_OBJECT(field_move), "activate", G_CALLBACK(onActivateEntry), &game_data);	// Connexion au signal "activate"
	gtk_box_pack_start(GTK_BOX(move_v_box), field_move, FALSE, FALSE, 0);					// Insertion dans move_v_box	
	
	text_last_move = gtk_label_new(NULL);										// Création du 5e label (dernier déplacement)
	str = g_locale_to_utf8("<span foreground=\"#e7b17f\">Dernier coup :</span>", -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(text_last_move), str);
	g_free(str);
	gtk_box_pack_start(GTK_BOX(move_v_box), text_last_move, FALSE, FALSE, 0);	// Insertion dans move_h_box

	gtk_box_pack_start(GTK_BOX(main_v_box), move_v_box, FALSE, FALSE, 0);	// Insertion de move_v_box dans main_v_box
	
	drawButton = gtk_button_new_with_label("Dessiner");									// Création du bouton "Dessiner"
	g_signal_connect(G_OBJECT(drawButton), "clicked", G_CALLBACK(onDraw), NULL);// Connexion du signal "clicked"
	gtk_box_pack_start(GTK_BOX(buttons_v_box), drawButton, FALSE, FALSE, 0);			// Insertion du bouton "Dessiner" dans la boîte ver.
	
	quitButton = gtk_button_new_with_label("Quitter");										// Création du bouton "Quitter"
	g_signal_connect(G_OBJECT(quitButton), "clicked", G_CALLBACK(gtk_main_quit), NULL);		// Connexion du signal "clicked"
	gtk_box_pack_start(GTK_BOX(buttons_v_box), quitButton, FALSE, FALSE, 0);				// Insertion du bouton "Quitter" dans la boîte ver.
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(onDestroy), NULL);				// Connexion du signal "destroy"
	
	gtk_box_pack_end(GTK_BOX(main_v_box), buttons_v_box, FALSE, FALSE, 0);	// Insertion de buttons_v_box dans main_v_box
	
	gtk_overlay_add_overlay (GTK_OVERLAY(menu_overlay), main_v_box);		// Insertion du menu dans l'overlay du menu
	
	gtk_widget_show_all(window);										// Affichage de la fenêtre et de ses éléments
	
	game_data = init('b');
	drawBoard(game_data.board);
	gtk_main();															// Démarrage de la boucle d'évènements principale
	return EXIT_SUCCESS;
}

void onActivateEntry(GtkEntry* entry, GameData* gd) {
	char* text = (char*)gtk_entry_get_text(GTK_ENTRY(entry));						// Récupération du texte contenu dans le GtkEntry
	Move move;
	translateMove(move, text);
	if (move[0][0] == ERROR) return;
	nextTurn(gd, move);
}

void onDestroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void onDraw(GtkWidget *widget, gpointer data) {
	clearBoard();
	Board board = {
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, EMPTY},
    {EMPTY, EMPTY, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, EMPTY, EMPTY},
    {EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
	};
	drawBoard(board);
}

void setPlayerColor(char color) {
	char* color_str = malloc(4);
	char* final_str = malloc(104);
	
	switch(color) {
		case BLACK: strcpy(color_str, "000"); break;
		case WHITE: strcpy(color_str, "FFF"); break;
		default: return;
	}
	strcpy(final_str, "<span foreground=\"#e7b17f\" font=\"13\"><b>Vous êtes les <span foreground=\"#");
	
	strcat(final_str, color_str);
	strcat(final_str, "\">●</span></b></span>");
	gchar* str = g_locale_to_utf8((gchar*)final_str, -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(text_player_id), str);
	g_free(str);
}

void setTurnColor(char color) {
	char* color_str = malloc(4);
	char* final_str = malloc(104);
	
	switch(color) {
		case BLACK: strcpy(color_str, "000"); break;
		case WHITE: strcpy(color_str, "FFF"); break;
		default: return;
	}
	strcpy(final_str, "<span foreground=\"#e7b17f\" font=\"13\"><b>Tour des <span foreground=\"#");
	
	strcat(final_str, color_str);
	strcat(final_str, "\">●</span></b></span>");
	gchar* str = g_locale_to_utf8((gchar*)final_str, -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(text_turn_id), str);
	g_free(str);
}

void setTurnNumber(int turn) {
	char* turn_str = malloc(2);
	char* final_str = malloc(43);
	sprintf(turn_str, "%i", turn);
	strcpy(final_str, "<span foreground=\"#e7b17f\">Tour ");
	
	strcat(final_str, turn_str);
	strcat(final_str, "</span>");
	gchar* str = g_locale_to_utf8((gchar*)final_str, -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(text_turn_nb), str);
	g_free(str);
}

void setLastMove(Move move) {
	char* move_str = malloc(6);
	char* final_str = malloc(63);
	strcpy(move_str, translateMoveReverse(move));
	strcpy(final_str, "<span foreground=\"#e7b17f\">Dernier coup : <b>");
	strcat(final_str, move_str);
	strcat(final_str, "</b></span>");
	gchar* str = g_locale_to_utf8((gchar*)final_str, -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(text_last_move), str);
	g_free(str);
}

void drawPawn (char color, int index, int* position) {
	if (index >= PAWN_NB) {
		printf("Error: Pawn n°%i of color %c doesn't exist", index, color);
		return;
	}
	
	// -22 = 36 (bordure) + 8 (padding) - 66 (taille d'une case)
	switch(color) {
		case BLACK:
			gtk_image_set_from_file (GTK_IMAGE(pawnsBlack[index]), "pawn_black.png");
			gtk_widget_set_margin_start(pawnsBlack[index], -22 + (position[0] * 66));
			gtk_widget_set_margin_top(pawnsBlack[index], -22 + (position[1] * 66));
			break;
		case WHITE:
			gtk_image_set_from_file (GTK_IMAGE(pawnsWhite[index]), "pawn_white.png");
			gtk_widget_set_margin_start(pawnsWhite[index], -22 + (position[0] * 66));
			gtk_widget_set_margin_top(pawnsWhite[index], -22 + (position[1] * 66));
			break;
		default: printf("Error: Incorrect color"); return;
	}
}

void drawBoard(Board board) {
	int counter_blacks = 0, counter_whites = 0;
	int coords[2];
	for (int i = 1; i <= MAX_I - 2; i++) {
		for (int j = 1; j <= MAX_J - 2; j++) {
			switch(board[i][j]) {
				case BLACK:
					coords[1] = i; coords[0] = j;
					drawPawn(BLACK, counter_blacks, coords);
					counter_blacks ++;
					break;
				case WHITE:
					coords[1] = i; coords[0] = j;
					drawPawn(WHITE, counter_whites, coords);
					counter_whites ++;
					break;
				default: continue;
			}
		}
	}	
}

void clearBoard() {
	for(int i = 0; i < PAWN_NB; i++) {
		gtk_image_set_from_file (GTK_IMAGE(pawnsBlack[i]), "pawn_empty.png");
		gtk_image_set_from_file (GTK_IMAGE(pawnsWhite[i]), "pawn_empty.png");
		gtk_widget_set_margin_start(pawnsBlack[i], 0);
		gtk_widget_set_margin_top(pawnsBlack[i], 0);
		gtk_widget_set_margin_start(pawnsWhite[i], 0);
		gtk_widget_set_margin_top(pawnsWhite[i], 0);
	}
}

GameData init(char mode) {
	GameData gd = {.board = {
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, EMPTY},
        {EMPTY, EMPTY, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, EMPTY, EMPTY},
        {EMPTY, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    }};
    
	switch(mode) {
		case 'b': gd.me = BLACK; break;
		case 'w': gd.me = WHITE; break;
		default: gd.me = BLACK; break;
	}
	gd.current_player = BLACK;
	setPlayerColor(gd.me);
	setTurnColor(gd.current_player);
    gd.nb_turn = 1;
	return gd;
}
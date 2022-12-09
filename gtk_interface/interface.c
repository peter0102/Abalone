#include <math.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include "interface.h"
#include "../deplacement.h"

Pion blancs[PIECE_NB];
Pion noirs[PIECE_NB];

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
GtkWidget* drawing_area;

GtkWidget* text_title;
GtkWidget* text_player_id;
GtkWidget* text_turn_id;
GtkWidget* text_turn_nb;
GtkWidget* field_move;
GtkWidget* text_last_move;
GtkWidget* drawButton;
GtkWidget* quitButton;

GtkWidget* piecesBlack[PIECE_NB];
GtkWidget* piecesWhite[PIECE_NB];

int main(int argc, char **argv)
{
	button_clicked = FALSE;
	
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

	drawing_area = gtk_drawing_area_new();								// Création de la zone de dessin
	gtk_widget_set_size_request(drawing_area, 600, 600);				// Taille minimale de la zone de dessin
	gtk_overlay_add_overlay (GTK_OVERLAY(overlay), drawing_area);		// Insertion de la zone de dessin dans l'overlay
	
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
	g_signal_connect(G_OBJECT(field_move), "activate", G_CALLBACK(onActivateEntry), NULL);	// Connexion au signal "activate"
	gtk_box_pack_start(GTK_BOX(move_v_box), field_move, FALSE, FALSE, 0);					// Insertion dans move_v_box	
	
	text_last_move = gtk_label_new(NULL);										// Création du 5e label (dernier déplacement)
	str = g_locale_to_utf8("<span foreground=\"#e7b17f\">Dernier coup : XX:XX</span>", -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(text_last_move), str);
	g_free(str);
	gtk_box_pack_start(GTK_BOX(move_v_box), text_last_move, FALSE, FALSE, 0);	// Insertion dans move_h_box

	gtk_box_pack_start(GTK_BOX(main_v_box), move_v_box, FALSE, FALSE, 0);	// Insertion de move_v_box dans main_v_box
	
	drawButton = gtk_button_new_with_label("Dessiner");									// Création du bouton "Dessiner"
	g_signal_connect(G_OBJECT(drawButton), "clicked", G_CALLBACK(onDraw), drawing_area);// Connexion du signal "clicked"
	gtk_box_pack_start(GTK_BOX(buttons_v_box), drawButton, FALSE, FALSE, 0);				// Insertion du bouton "Dessiner" dans la boîte ver.
	g_signal_connect(drawing_area, "draw", G_CALLBACK(startDraw), NULL);				// Connexion du signal "draw"
	
	quitButton = gtk_button_new_with_label("Quitter");										// Création du bouton "Quitter"
	g_signal_connect(G_OBJECT(quitButton), "clicked", G_CALLBACK(gtk_main_quit), NULL);		// Connexion du signal "clicked"
	gtk_box_pack_start(GTK_BOX(buttons_v_box), quitButton, FALSE, FALSE, 0);					// Insertion du bouton "Quitter" dans la boîte ver.
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(onDestroy), NULL);				// Connexion du signal "destroy"
	
	gtk_box_pack_end(GTK_BOX(main_v_box), buttons_v_box, FALSE, FALSE, 0);	// Insertion de buttons_v_box dans main_v_box
	
	gtk_overlay_add_overlay (GTK_OVERLAY(menu_overlay), main_v_box);		// Insertion du menu dans l'overlay du menu
	
	gtk_widget_show_all(window);										// Affichage de la fenêtre et de ses éléments
	gtk_main();															// Démarrage de la boucle d'évènements principale
	return EXIT_SUCCESS;
}

void onActivateEntry(GtkEntry* entry, gpointer data) {
	const gchar* text;
	text = gtk_entry_get_text(GTK_ENTRY(entry));						// Récupération du texte contenu dans le GtkEntry
}

void onDestroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void onDraw(GtkWidget *widget, gpointer data)
{
	GtkWidget* drawing_area = data;
	button_clicked = TRUE;
	/* Now invalidate the affected region of the drawing area. */
	gtk_widget_queue_draw(drawing_area);
}

void clear(cairo_t *cr)
{
	/* Save current context */
	cairo_save(cr);
	cairo_set_source_rgba(cr, 0, 0, 0, 0);
	cairo_paint(cr);

	/* Restore context */
	cairo_restore(cr);
}

void draw(cairo_t *cr)
{
	cairo_save(cr);		// Sauvegarde du contexte
	Pion test1 = {1, 1};
	Pion test2 = {2, 2};
	drawPiece(cr, 'b', test1);
	drawPiece(cr, 'w', test2);
	/* Restore context */
	cairo_restore(cr);
}

gboolean startDraw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	clear(cr);
	if (button_clicked) {
		draw(cr);
	}
	return FALSE;
}

void drawPiece (cairo_t *cr, char color, Pion position) {
	switch(color) {
		case 'b': cairo_set_source_rgb(cr, 0, 0, 0); break;
		case 'w': cairo_set_source_rgb(cr, 1, 1, 1); break;
		default: printf("Error: Incorrect color"); return;
	}
	// -15 = 20 (bordure) - 35 (moitié d'une case)
	cairo_arc(cr, (-15 + (position.x * 70)), (-15 + (position.y * 70)), 25, 0, 2 * M_PI);
	cairo_fill (cr);
}

void setPlayerColor(char color) {
	char* color_str = malloc(4);
	char* final_str = malloc(104);
	
	switch(color) {
		case 'b': strcpy(color_str, "000"); break;
		case 'w': strcpy(color_str, "FFF"); break;
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
		case 'b': strcpy(color_str, "000"); break;
		case 'w': strcpy(color_str, "FFF"); break;
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

void setLastMove(int** move) {
	char* move_str = malloc(5);
	char* final_str = malloc(54);
	strcpy(final_str, "<span foreground=\"#e7b17f\">Dernier coup : ");
	strcpy(move_str, translateMoveReverse(move));
	strcat(final_str, move_str);
	strcat(final_str, "</span>");
	gchar* str = g_locale_to_utf8((gchar*)final_str, -1, NULL, NULL, NULL);
	gtk_label_set_markup(GTK_LABEL(text_last_move), str);
	g_free(str);
}

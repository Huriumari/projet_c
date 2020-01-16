#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc, char **argv){

    GtkWidget * window;
    GtkWidget * layout;
    GtkWidget * button;
    GtkWidget * windowScroll;
    GtkAdjustment * adjustmentHeightComponents;
    GtkAdjustment * adjustmentWidthComponents;

    gtk_init(&argc,&argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK+ 3.22");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 800);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    adjustmentWidthComponents = gtk_adjustment_new(2000, 0, 2000, 10, 10, 150);
    adjustmentHeightComponents = gtk_adjustment_new(750, 0, 1400, 10, 10, 150);
    windowScroll = gtk_scrolled_window_new(adjustmentWidthComponents, adjustmentHeightComponents);
	gtk_scrolled_window_set_overlay_scrolling(GTK_SCROLLED_WINDOW(windowScroll), 0);
    gtk_container_add(GTK_CONTAINER(window), windowScroll);

    layout = gtk_layout_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(windowScroll), layout);

    button = gtk_button_new_with_label("Yo");
    gtk_layout_put(GTK_LAYOUT(layout), button, 50, 50);
    
    gchar * sUtf8;
    GtkWidget* p_Label;
	sUtf8 = g_locale_to_utf8("La Bibliothèque GTK+ à bien été Installée !", -1, NULL, NULL, NULL);
    p_Label = gtk_label_new(sUtf8);
    g_free(sUtf8);
	gtk_container_add(GTK_CONTAINER(layout), p_Label);

    gtk_widget_show_all(window);

    gtk_main();

    return EXIT_SUCCESS;

}
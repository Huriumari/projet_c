#ifndef LOGICSIMBUTINC_H
# define LOGICSIMBUTINC_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

typedef struct	data_s{
		GtkWidget * window;
		GtkWidget * widget;
		int test;
}				data_t;

//extern data_t * data;

GtkWidget * componentsButton(char *path);

GtkWidget * gtkWindow(int *argc, char ***argv);
void menubar(GtkWidget * window, GtkWidget * vBox);
void toolbar(GtkWidget * vBox);
void componentsPart(GtkWidget * vBox, GtkWidget * grid, GtkWidget * window);
void workingPart(GtkWidget * vBox, GtkWidget * grid);

void isClicked(void);
void dragComponents(gpointer data);

#endif

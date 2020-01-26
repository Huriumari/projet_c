#ifndef LOGICSIMBUTINC_H
# define LOGICSIMBUTINC_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

typedef struct	pos_s{
		double x;
		double y;
}				pos_t;

typedef struct	data_s{
		GtkWidget * window;
		char * imgPath;
		GtkWidget * workingLayout;
		pos_t pos;
}				data_t;



//extern data_t * data;

GtkWidget * componentsButton(char *path);

GtkWidget * gtkWindow(int *argc, char ***argv);
void menubar(GtkWidget * window, GtkWidget * vBox);
void toolbar(GtkWidget * vBox);
void componentsPart(GtkWidget * vBox, GtkWidget * grid, GtkWidget * window, GtkWidget * workingLayout);
GtkWidget * workingPart(GtkWidget * vBox, GtkWidget * grid);

void * mousePos(GtkWidget * mouse, GdkEvent *event, gpointer data);
void isClicked(GtkWidget * comp, gpointer data);
void dragComponents(GtkWidget* comp, gpointer data);

#endif

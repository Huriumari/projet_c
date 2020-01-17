#ifndef LOGICSIMBUTINC_H
# define LOGICSIMBUTINC_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#define WIDTH_IMG 106
#define HEIGHT_IMG 106

GtkWidget * gtkWindow(int *argc, char ***argv);
void menubar(GtkWidget * window, GtkWidget * vBox);
void toolbar(GtkWidget * Vbox);
void workingPart(GtkWidget * vBox);
void createBackground(GtkWidget * layoutBoxMain, GtkWidget * image, guint * widthLayout, guint * heightLayout);

#endif

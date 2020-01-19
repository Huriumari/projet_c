#ifndef LOGICSIMBUTINC_H
# define LOGICSIMBUTINC_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

GtkWidget * gtkWindow(int *argc, char ***argv);
void menubar(GtkWidget * window, GtkWidget * vBox);
void toolbar(GtkWidget * vBox);
void workingPart(GtkWidget * vBox);

#endif

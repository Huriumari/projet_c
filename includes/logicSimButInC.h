#ifndef LOGICSIMBUTINC_H
# define LOGICSIMBUTINC_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

#define WIDTH_IMG 106
#define HEIGHT_IMG 106

void interfaceInit(int argc, char **argv);
void createBackground(GtkWidget * layoutBoxMain, GtkWidget * image, guint * widthLayout, guint * heightLayout);

#endif

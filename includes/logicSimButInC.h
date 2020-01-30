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

typedef struct	component_s{
	size_t				id;
	GtkWidget			*img;
	pos_t				pos;
	struct component_s 	*next;
}				component_t;

typedef struct	data_s{
	GtkWidget	*window;
	char		*imgPath;
	GtkWidget	*workingLayout;
	component_t	*component;
}				data_t;


GtkWidget	*componentsButton(char *path);

GtkWidget	*gtkWindow(int *argc, char ***argv);
void		menubar(GtkWidget * window, GtkWidget * vBox);
void		toolbar(GtkWidget * vBox);
void		componentsPart(GtkWidget * grid, GtkWidget * window, GtkWidget * workingLayout);
GtkWidget	*workingPart(GtkWidget * grid);

void		mousePos(GtkWidget * mouse, GdkEvent *event, gpointer data);
void		isClicked(GtkWidget * comp, gpointer data);
void		dragComponents(GtkWidget* comp, gpointer data);

size_t		new_component_id(void);
void		add_component(data_t *data, char *path_img, double x, double y);
int			remove_component(data_t *data, double mouse_x, double mouse_y);

#endif

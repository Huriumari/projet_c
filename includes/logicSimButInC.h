#ifndef LOGICSIMBUTINC_H
#define LOGICSIMBUTINC_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

typedef struct	pos_s{
	double x;
	double y;
}				pos_t;

typedef struct	part_s{
	pos_t		pos;
	char		type;
}				part_t;

typedef struct	component_s{
	size_t				id;
	GtkWidget			*img;
	char				*name;
	pos_t				pos;
	struct component_s 	*next;
	char				number_parts;
	char				is_select;
	part_t				*parts;
}				component_t;

typedef struct	data_s{
	GtkWidget	*window;
	char		*imgPath;
	GtkWidget	*workingLayout;
	component_t	*component;
	char		***option;
}				data_t;


GtkWidget	*componentsButton(char *path);

GtkWidget	*gtkWindow(int *argc, char ***argv);
void		menubar(GtkWidget * window, GtkWidget * vBox);
void		toolbar(GtkWidget * vBox, data_t *data);
void		componentsPart(data_t *data, GtkWidget * grid, GtkWidget * window, GtkWidget * workingLayout);
GtkWidget	*workingPart(GtkWidget * grid);

void		mousePos(GtkWidget * mouse, GdkEvent *event, gpointer data);
void		isClicked(GtkWidget * comp, gpointer data);
void		dragComponents(GtkWidget* comp, gpointer data);

size_t		new_component_id(size_t c);
void		add_component(data_t *data, char *path_img, double x, double y);
int			remove_component(data_t *data, double mouse_x, double mouse_y);

void		print_option(char ***option);
char		*get_option(char ***option, char *key);
char		***create_option(char *key, char *data);
char		***add_option(char ***option, char *key, char *data);
char		***read_option_file(void);

part_t		*gimme_parts(char *component_name, char *n, double mouse_x, double mouse_y);
void		select_component(data_t *data, double x, double y);

#endif


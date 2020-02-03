#include "logicSimButInC.h"

size_t	new_component_id(size_t c){
	static size_t id = 0;

	if (c)
		id = c + 1;
	return id++;
}

void	add_component(data_t *data, char *path_img, double x, double y){
	component_t	*component;
	GdkPixbuf 	*pb;
	char		buffer[255];

	component = malloc(sizeof(component_t));
	if (component != NULL){
		component->next = data->component;
		component->name = malloc(sizeof(char) * strlen(path_img));
		strcpy(component->name, path_img);
		component->is_select = 0;
		data->component = component;

		strcat(strcat(strcat(strcpy(buffer,get_option(data->option,"component_img_path")),"/"),path_img),".png");
		component->img = gtk_image_new_from_file(buffer);

		pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
		component->pos.x = x;
		component->pos.y = y;
		component->id = new_component_id(0);
		component->parts = gimme_parts(component->name, &(component->number_parts), x, y);
		gtk_layout_put(GTK_LAYOUT(data->workingLayout), component->img, component->pos.x  - (double)gdk_pixbuf_get_width(pb) / 2, component->pos.y - (double)gdk_pixbuf_get_height(pb) / 2);
		gtk_widget_show_all(data->workingLayout);
	}
}

void	delete_component_widget(data_t * data, component_t *component){
	gtk_widget_destroy(GTK_WIDGET(component->img));
	gtk_widget_show_all(data->workingLayout);
}

int		remove_component(data_t *data, double mouse_x, double mouse_y){
	component_t	*component = data->component;
	component_t *prev;
	GdkPixbuf 	*pb;
	double		x,y;

	while (component != NULL){
		pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
		x = gdk_pixbuf_get_width(pb);
		y = gdk_pixbuf_get_height(pb);
		if (mouse_x > component->pos.x - (double)(x/2)
		&&	mouse_x < component->pos.x + (double)(x/2)
		&&	mouse_y > component->pos.y - (double)(y/2)
		&&	mouse_y < component->pos.y + (double)(y/2)){
			if (component == data->component){
				prev = component;
				data->component = data->component->next;
			}else{
				prev = data->component;
				while (prev->next != NULL && prev->next != component)
					prev = prev->next;
				if (prev->next == NULL)
					return 0;
				prev->next = prev->next->next;
			}
			delete_component_widget(data,component);
			free(component->name);
			free(component);
			return 1;
		}
		component = component->next;
	}
	return 0;
}

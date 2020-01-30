#include "logicSimButInC.h"

size_t	new_component_id(){
	static size_t id = 0;

	return id++;
}

void	add_component(data_t *data, char *path_img, double x, double y){
	component_t	*component;
	GdkPixbuf 	*pb;

	component = malloc(sizeof(component_t));
	component->img = gtk_image_new_from_file(path_img);
	pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
	component->pos.x = x;
	component->pos.y = y;
	component->id = new_component_id();
	component->next = data->component;
	data->component = component;

	gtk_layout_put(GTK_LAYOUT(data->workingLayout), component->img, component->pos.x  - (double)gdk_pixbuf_get_width(pb) / 2, component->pos.y - (double)gdk_pixbuf_get_height(pb) / 2);
	gtk_widget_show_all(data->workingLayout);
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
			}
			delete_component_widget(data,component);
			return 1;
		}
		component = component->next;
	}
	return 0;
}

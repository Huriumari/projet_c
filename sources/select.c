#include "logicSimButInC.h"

char	is_above_component(component_t *component, double mouse_x, double mouse_y){
	GdkPixbuf 	*pb;
	double		x,y;

	pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
	x = (double)gdk_pixbuf_get_width(pb);
	y = (double)gdk_pixbuf_get_height(pb);
		if (mouse_x > component->pos.x - x/2
		&&	mouse_x < component->pos.x + x/2
		&&	mouse_y > component->pos.y - y/2
		&&	mouse_y < component->pos.y + y/2){
			return 1;
		}
		return 0;
}

void	select_component(data_t *data, double x, double y){
	component_t	*component;

	component = data->component;
	while (component != NULL){
		if (is_above_component(component, x, y)){
			component->is_select = 1;
			select_visual(data, component, x, y);
		}
		else
			if (component->is_select){
				component->is_select = 0;
				deselect_visual(data, component, x, y);
			}
	component = component->next;
	}
}

void select_visual(data_t *data, component_t *component, double x, double y){
	
	GtkWidget *frame;
	GdkPixbuf 	*pb;

	pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
	
	frame = gtk_frame_new(NULL);
	component->frame = frame;
	remove_component(data, x, y);
	gtk_container_add(GTK_CONTAINER(frame), component->img);
	g_object_unref(component->img);
	gtk_layout_put(GTK_LAYOUT(data->workingLayout), frame, component->pos.x  - (double)gdk_pixbuf_get_width(pb) / 2, component->pos.y - (double)gdk_pixbuf_get_height(pb) / 2);
	gtk_widget_show_all(data->workingLayout);

}

void deselect_visual(data_t *data, component_t *component, double x, double y){

	GdkPixbuf 	*pb;

	pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
	
	remove_component(data, x, y);
	gtk_layout_put(GTK_LAYOUT(data->workingLayout), component->img, component->pos.x  - (double)gdk_pixbuf_get_width(pb) / 2, component->pos.y - (double)gdk_pixbuf_get_height(pb) / 2);
	g_object_unref(component->img);
	gtk_widget_show_all(data->workingLayout);

}
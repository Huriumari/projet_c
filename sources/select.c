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
		if (is_above_component(component, x, y))
			component->is_select = 1;
			else
				if (component->is_select)
					component->is_select = 0;
	component = component->next;
	}
}
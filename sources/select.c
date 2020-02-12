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
		if (is_above_component(component, x, y) && component->is_select != 1){
			component->is_select = 1;
			g_object_ref(component->img);
			gtk_container_remove(GTK_CONTAINER(data->workingLayout), component->img);
			select_visual(data, component);

		}
		else
			if (component->is_select){
				component->is_select = 0;
				g_object_ref(component->img);
				gtk_container_remove(GTK_CONTAINER(component->frameEventBox), component->frame);
				gtk_widget_destroy(component->frameEventBox);
				unselect_visual(data, component);
			}
	component = component->next;
	}
}

void select_visual(data_t *data, component_t *component){
	
	GtkWidget *frame;
	GdkPixbuf 	*pb;
	GtkWidget *eventBox;

	pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
	eventBox = gtk_event_box_new();
	
	frame = gtk_frame_new(NULL);
	component->frame = frame;
	component->frameEventBox = eventBox;
	gtk_container_add(GTK_CONTAINER(eventBox), frame);
	gtk_container_add(GTK_CONTAINER(frame), component->img);
	g_object_unref(component->img);
	gtk_layout_put(GTK_LAYOUT(data->workingLayout), eventBox, component->pos.x  - (double)gdk_pixbuf_get_width(pb) / 2, component->pos.y - (double)gdk_pixbuf_get_height(pb) / 2);
	gtk_widget_show_all(data->workingLayout);

	g_signal_connect(G_OBJECT(component->frameEventBox), "button-press-event", G_CALLBACK(mouse_pressed), data);
	g_signal_connect(G_OBJECT(data->workingLayout), "scroll-event", G_CALLBACK(mouse_scroll), NULL);
	g_signal_connect(G_OBJECT(component->frameEventBox), "motion-notify-event", G_CALLBACK(mouse_move), data);
	gtk_widget_add_events(eventBox, GDK_BUTTON_PRESS_MASK | GDK_SCROLL_MASK | GDK_BUTTON1_MOTION_MASK);
	

}

void unselect_visual(data_t *data, component_t *component){

	GdkPixbuf 	*pb;

	pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
	
	gtk_layout_put(GTK_LAYOUT(data->workingLayout), component->img, component->pos.x  - (double)gdk_pixbuf_get_width(pb) / 2, component->pos.y - (double)gdk_pixbuf_get_height(pb) / 2);
	g_object_unref(component->img);
	gtk_widget_show_all(data->workingLayout);

}
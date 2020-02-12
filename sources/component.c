//autor: Clement BOSSARD, Clement K-R
//date: 17/12/2019 - 12/02/2020
//Ce fichier contient les fonctions poour la creation et supression de composant

#include "logicSimButInC.h"

size_t	new_component_id(size_t c){
	static size_t id = 0;

	if (c)
		id = c + 1;
	return id++;
}

void	delete_component_widget(data_t * data, component_t *component){
	gtk_widget_destroy(GTK_WIDGET(component->img));
	if (component->is_select)
		gtk_widget_destroy(component->frame);
	gtk_widget_show_all(data->workingLayout);
}

void	destroy_component(data_t *data, component_t *component){
	delete_component_widget(data, component);
	free(component->name);
	if (component->parts != NULL)
		free(component->parts);
	free(component);
}

void	add_component(data_t *data, char *path_img, double x, double y){
	component_t	*component;
	GdkPixbuf 	*pb;
	char		buffer[255];

	component = malloc(sizeof(component_t));
	if (component != NULL){
		component->name = malloc(sizeof(char) * (strlen(path_img) + 1));
		strcpy(component->name, path_img);
		component->is_select = 0;
		component->next = NULL;

		strcat(strcat(strcat(strcpy(buffer,get_option(data->option,"component_img_path")),"/"),path_img),".png");
		component->img = gtk_image_new_from_file(buffer);

		pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
		component->pos.x = x;
		component->pos.y = y;
		component->id = new_component_id(0);
		add_action(data, "ADD", component, NULL);
		component->parts = gimme_parts(component->name, &(component->number_parts), x, y);
		gtk_layout_put(GTK_LAYOUT(data->workingLayout), component->img, component->pos.x  - (double)gdk_pixbuf_get_width(pb) / 2, component->pos.y - (double)gdk_pixbuf_get_height(pb) / 2);
		component->next = data->component;
		data->component = component;
		gtk_widget_show_all(data->workingLayout);

	}
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
		if ((mouse_x > component->pos.x - (double)(x/2)
		&&	mouse_x < component->pos.x + (double)(x/2)
		&&	mouse_y > component->pos.y - (double)(y/2)
		&&	mouse_y < component->pos.y + (double)(y/2))){
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
			component->next = NULL;
			add_action(data, "SUPPR", component, NULL);
			destroy_component(data, component);
			return 1;
		}
		component = component->next;
	}
	return 0;
}

int	delete_selected_components(GtkWidget *widget, data_t *data){

	component_t	*component = data->component;
	component_t *prev;

	if(widget)
		widget++;


	while (component != NULL){
		if (component->is_select){
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
			component->next = NULL;
			add_action(data, "SUPPR", component, NULL);
			destroy_component(data, component);
			return 1;
		}
		component = component->next;
	}
	return 0;	
}
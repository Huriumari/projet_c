//autor: Clement BOSSARD, Clement K-R
//date: 17/12/2019 - 12/02/2020
//Ce fichier contient les fonctions necessaire pour le retour en arriere

#include "logicSimButInC.h"

void	clear_action(data_t *data){
	action_t	*action;

	while (data->action != NULL){
		action = data->action->next;
		remove_action(data->action);
		data->action = action;
	}
}

void	add_component_data(action_t *action, component_t *component){
	component_data_t	*component_data;

	component_data = malloc(sizeof(component_data_t));
	component_data->name = malloc(sizeof(char) * (strlen(component->name) + 1));
	strcpy(component_data->name, component->name);
	component_data->pos.x = component->pos.x;
	component_data->pos.y = component->pos.y;
	component_data->id = component->id;
	component_data->next = action->component_data;
	action->component_data = component_data;
}

void	add_action(data_t *data, char *name, component_t *component, link_t *link){
	action_t	*action;

	action = malloc(sizeof(action_t));
	action->next = data->action;
	data->action = action;
	action->component_data = NULL;
	strcpy(action->action,name);
	while (component != NULL){
		add_component_data(action, component);
		component = component->next;
	}
	if (link == NULL){
		action->link = get_link_linked_to(data, action->component_data->id);
		remove_visual(data, action->link);
	}
	else if (!strcmp(name, "ADD")){
		action->link = malloc(sizeof(link_t));
		action->link->id = link->id;
		link->next = NULL;
	}
}

void	remove_action(action_t *action){
	component_data_t	*component_data, *next;
	link_t 				*link;

	component_data = action->component_data;
	while(component_data != NULL){
		next = component_data->next;
		free(component_data->name);
		free(component_data);
		component_data = next;
	}
	while (action->link != NULL){
		link = action->link->next;
		free(action->link);
		action->link = link;
	}
	free(action);
}

void	appli_action(GtkWidget	*undo, data_t *data){
	component_data_t	*component_data;
	action_t			*action;
	link_t 				*link;

	if (undo)
		undo++;

	if (data->action != NULL){
		action = data->action;
		component_data = action->component_data;
		link = action->link;
		if (!strcmp(action->action, "SUPPR")){
			while(component_data != NULL){
				add_component(data, component_data->name, component_data->pos.x, component_data->pos.y);
				component_data = component_data->next;
			}
			while (link != NULL){
				visual_linking(data, link);
				if (link->next == NULL){
					link->next = data->link;
					data->link = action->link;
					action->link = NULL;
					link = NULL;
				}else
					link = link->next;
			}
		}else if(!strcmp(action->action, "ADD")){
			while (component_data != NULL){
				remove_component(data, component_data->pos.x, component_data->pos.y);
				component_data = component_data->next;
			}
			while(link != NULL){
				remove_this_link(data, link->id);
				link = link->next;
			}
		}
		data->action = action->next;
		remove_action(action);
	}
}
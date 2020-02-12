#include "logicSimButInC.h"

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

void	add_action(data_t *data, char *name, component_t *component){
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
}

void	remove_action(action_t *action){
	component_data_t	*component_data, *next;;

	component_data = action->component_data;
	while(component_data != NULL){
		next = component_data->next;
		free(component_data->name);
		free(component_data);
		component_data = next;
	}
	free(action);
}

void	appli_action(data_t *data){
	component_data_t	*component_data;
	action_t			*action;
	if (data->action != NULL){
		action = data->action;
		component_data = action->component_data;
		if (!strcmp(action->action, "SUPPR")){
			while(component_data != NULL){
				add_component(data, component_data->name, component_data->pos.x, component_data->pos.y);
				component_data = component_data->next;
			}
		}else if(!strcmp(action->action, "ADD")){
			while (component_data != NULL){
				remove_component(data, component_data->pos.x, component_data->pos.y);
				component_data = component_data->next;
			}			
		}
		data->action = action->next;
		remove_action(action);
	}
}
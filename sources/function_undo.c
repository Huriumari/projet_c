#include "logicSimButInC.h"

void	add_action(data_t *data, char *name, component_t *component){
	action_t	*action;

	action = malloc(sizeof(action_t));
	action->next = data->action;
	
}
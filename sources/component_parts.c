#include "logicSimButInC.h"

void		set_part(part_t *part, double x, double y, char type){
	part->pos.x = x;
	part->pos.y = y;
	part->type = type;
	part->used = 0;
}

part_t		*get_BASIC_parts(double mouse_x, double mouse_y){
	part_t	*parts = malloc(sizeof(part_t) * 3);
	if (parts == NULL)
		return NULL;
	set_part(parts, mouse_x + (double)34., mouse_y + (double)0., 'o');
	set_part(parts + 1, mouse_x - (double)34., mouse_y - (double)6., 'i');
	set_part(parts + 2, mouse_x - (double)34., mouse_y + (double)6., 'i');
	return parts;	
}

part_t		*get_OUTPUT_part(double mouse_x, double mouse_y){
	part_t	*parts = malloc(sizeof(part_t) * 3);
	if (parts == NULL)
		return NULL;
	set_part(parts, mouse_x , mouse_y, 'i');
	return parts;
}

part_t		*get_INPUT_part(double mouse_x, double mouse_y){
	part_t	*parts = malloc(sizeof(part_t) * 3);
	if (parts == NULL)
		return NULL;
	set_part(parts, mouse_x , mouse_y, 'i');
	return parts;
}


part_t		*gimme_parts(char *component_name, char *n, double mouse_x, double mouse_y){
	if (!strcmp(component_name,"AND")
	||	!strcmp(component_name,"NAND")
	||	!strcmp(component_name,"NOR")
	||	!strcmp(component_name,"OR")
	||	!strcmp(component_name,"XOR")
	||	!strcmp(component_name,"AND")){
		*n = 3;
		return get_BASIC_parts(mouse_x, mouse_y);
	}
	if (!strcmp(component_name,"INPUT_OFF")){
		*n = 1;
		return get_INPUT_part(mouse_x, mouse_y);
	}
	if (!strcmp(component_name,"OUTPUT_OFF")){
		*n = 1;
		return get_OUTPUT_part(mouse_x, mouse_y);
	}
	*n = 0;
	return NULL;
}
#include "logicSimButInC.h"

void		set_part(part_t *part, double x, double y, char type){
	part->pos.x = x;
	part->pos.y = y;
	part->type = type;
}

part_t		*get_BASIC_parts(double mouse_x, double mouse_y){
	part_t	*parts = malloc(sizeof(part_t) * 3);
	if (parts == NULL)
		return NULL;
	set_part(parts, mouse_x + (double)34., (double)0., 'o');
	set_part(parts + 1, mouse_x - (double)34., mouse_y - (double)6., 'i');
	set_part(parts + 2, mouse_x - (double)34., mouse_y + (double)6., 'i');
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
	return NULL;
}
#include "logicSimButInC.h"

void	new_layout(data_t *data){
	clear_component(data);
	clear_link(data);
}

void	callback_new_layout(GtkWidget *widget, data_t *data){
	if (widget)
		widget++;
	new_layout(data);
}

char	*set_save_file_name(char *path){
	char	*str = strrchr(path, '.');
	char	*result;
	char	extension[] = ".clements";

	if (str == NULL){
		result = malloc(sizeof(char) * (strlen(path) + (strlen(extension) + 1)));
		strcat(strcpy(result,path),extension);
		return result;
	}
	result = malloc(sizeof(char) * ( str - path + strlen(extension) + 1));
	strncpy(result,path, str - path);
	result[str - path + 1] = '\0';
	strcat(result, extension);
	return result;
}

int		save(data_t *data, char *path){
	FILE		*file;
	component_t	*component;

	path = set_save_file_name(path);
	file = fopen(path,"w+");
	if (file == NULL)
		return 0;
	component = data->component;
	while(component != NULL){
		fprintf(file, "%lu:%lf:%lf:%s\n",
				component->id,
				component->pos.x,
				component->pos.y,
				component->name);
		component = component->next;
	}
	fclose(file);
	return 1;
}

void	clear_component(data_t *data){
	component_t		*component, *next;

	component = data->component;
	data->component = NULL;

	while(component != NULL){
		next = component->next;
		destroy_component(data, component);
		component = next;
	}
	
}

void	print_component(component_t component){
	printf("%lu\n%s\n%lf\n%lf\n",
				component.id,
				component.name,
				component.pos.x,
				component.pos.y);
}

int		load(data_t *data, char *path){
	FILE		*file;
	component_t	*component;;
	size_t		max_id = 0;
	char		buffer[255];
	char		*ptr;

	file = fopen(path, "r");
	if (file == NULL)
		return 0;
	component = malloc(sizeof(component_t));
	component->name = malloc(sizeof(char) * 20);
	if (component == NULL)
		return 0;
	new_layout(data);
	while(fgets(buffer,255,file),!feof(file)){
		if (buffer[strlen(buffer) - 1] == '\n')
			buffer[strlen(buffer) - 1] = '\0';
		ptr = strrchr(buffer,':');
		*ptr = '\0';
		strcpy(component->name,ptr+1);

		ptr = strrchr(buffer,':');
		*ptr = '\0';
		sscanf(ptr+1,"%lf",&(component->pos.y));

		ptr = strrchr(buffer,':');
		*ptr = '\0';
		sscanf(ptr+1,"%lf",&(component->pos.x));

		sscanf(buffer,"%lu",&(component->id));

		if (component->id > max_id)
			max_id = component->id;
		//print_component(component[0]);
		add_component(data, component->name, component->pos.x, component->pos.y);
		data->component->id = component->id;
	}
	new_component_id(max_id);
	free((component->name));
	free(component);
	fclose(file);
	return 1;
}
#include "logicSimButInC.h"

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
		fprintf(file, "%lu:%s:%lf:%lf\n",
				component->id,
				component->name,
				component->pos.x,
				component->pos.y);
		component = component->next;
	}
	fclose(file);
	free(path);
	return 1;
}

void	clear_component(data_t *data){
	component_t		*component, *next;

	component = data->component;
	data->component = NULL;

	while(component){
		next = component->next;
		gtk_widget_destroy(GTK_WIDGET(component->img));
		free(component);
		component = next;
	}
}

int		load(data_t *data, char *path){
	FILE		*file;
	component_t	*component;;
	size_t		max_id = 0;

	file = fopen(path, "r");
	if (file == NULL)
		return 0;
	component = malloc(sizeof(component));
	if (component == NULL)
		return 0;
	clear_component(data);
	while(!feof(file)){
		fscanf(file, "%lu:%s:%lf:%lf\n",
				&(component->id),
				component->name,
				&(component->pos.x),
				&(component->pos.y));
		if (component->id > max_id)
			max_id = component->id;
		add_component(data, component->name, component->pos.x, component->pos.y);
	}
	new_component_id(max_id);
	free(component);
	return 1;
}
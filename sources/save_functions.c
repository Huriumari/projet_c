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
	int			i;

	path = set_save_file_name(path);
	file = fopen(path,"w+");
	if (file == NULL)
		return 0;
	component = data->component;
	while(component != NULL){
		fprintf(file, "%lu:%s:%lf:%lf:%d",
				component->id,
				component->name,
				component->pos.x,
				component->pos.y,
				(int)component->number_parts);
		for (i = 0 ; i < (int)component->number_parts ; i++)
			fprintf(file,":%lf:%lf:%c",
				component->parts[i].pos.x,
				component->parts[i].pos.y,
				component->parts[i].type);
		fprintf(file,"\n");
		component = component->next;
	}
	fclose(file);
	free(path);
	return 1;
}
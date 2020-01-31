#include "logicSimButInC.h"

char	*set_save_file_name(char *path){
	char	*str = strrchr(path, '.');
	char	*result;
	char	extension[] = ".clements";
	if (str == NULL){
		result = malloc(sizeof(char) * (strlen(path) + (sizeof(extension) + 1)));
		strcat(strcpy(result,path),);
		return result;
	}
	result = malloc(sizeof(char) * ( str - path + sizeof(extension) + 1));
	strncpy(result,path, str - path);
	result[str - path + 1] = '\0';
	strcat(result,extension);
}

int		save(data_t *data, char *path){
	FILE		*file;
	component_t	*component;

	path = set_save_file_name(path);
	file = fopen(path,"w+");
	if (file == NULL)
		return 0;
	first = data->component;
	while(component != NULL){
		fprintf("")

	}

	fclose(file);
	free(path);
	return 1;
}
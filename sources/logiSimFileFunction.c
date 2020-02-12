//autor: Clement BOSSARD, Clement K-R
//date: 17/12/2019 - 12/02/2020
//Ce fichier contient les fonctions de lecture du fichier option.txt


#include "logicSimButInC.h"

void	print_option(char ***option){
	int		n;

	if (option != NULL){
		n = 0;
		while(option[n] != NULL){
			printf("%d %s : %s\n", n, option[n][0], option[n][1]);
			n++;
		}
	}
}

char	*get_option(char ***option, char *key){
	int		n;

	if (option == NULL)
		return NULL;
	n = 0;
	while (option[n] != NULL){
		if (!strcmp(option[n][0],key))
			return option[n][1];
		n++;
	}
	return NULL;
}


char	***create_option(char *key, char *data){
	char ***new_option;

	new_option = malloc(sizeof(char**) * 2);
	if (new_option == NULL)
	return NULL;

	new_option[1] = NULL;
	new_option[0] = malloc(sizeof(char*) * 2);
	if (new_option[0] == NULL)
	return NULL;

	new_option[0][0] = malloc(sizeof(char) * strlen(key) + 1);
	if (new_option[0][0] == NULL)
		return NULL;
	strcpy(new_option[0][0],key);

	new_option[0][1] = malloc(sizeof(char) * strlen(data) + 1);
	if (new_option[0][1] == NULL)
		return NULL;
	strcpy(new_option[0][1], data);

	return new_option;
}

char	***add_option(char ***option, char *key, char *data){
	char	***new_option;
	size_t	n,i;

	if (key == NULL || !*key)
		return option;
	if (option == NULL)
		return create_option(key, data);

	n = 0;
	while (option[n] != NULL)
		n++;
	new_option = malloc(sizeof(char***) * (n + 2));
	new_option[n+1] = NULL;
	for(i = 0 ; i < n ; i++)
		new_option[i] = option[i];

	new_option[i] = malloc(sizeof(char*) * 2);
	if (new_option[i] == NULL)
		return NULL;

	new_option[i][0] = malloc(sizeof(char) * strlen(key) + 1);
	if (new_option[i][0] == NULL)
		return NULL;
	strcpy(new_option[i][0],key);

	new_option[i][1] = malloc(sizeof(char) * strlen(data) + 1);
	if (new_option[i][1] == NULL)
		return NULL;
	strcpy(new_option[i][1], data);

	free(option);
	return new_option;
}

char	***read_option_file(){
	FILE	*file;
	char	***option;
	char	buffer[255];
	char	key_buffer[255];
	char	data_buffer[255];
	char	*ptr;

	option = NULL;
	file = fopen("options.txt","rb");
	if (file == NULL)
		return NULL;
	while ( ptr = fgets(buffer, 255, file), !feof(file)){
		if ( (ptr = strchr(buffer,':') )){
			if (buffer[strlen(buffer) - 1] == '\n')
				buffer[strlen(buffer) - 1] = '\0';
			strcpy(data_buffer,ptr+1);
			*ptr = '\0';
			strcpy(key_buffer,buffer);
			option = add_option(option,key_buffer,data_buffer);
		}
	}
	fclose(file);
	return option;
}
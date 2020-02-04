#include "logicSimButInC.h"

#define MAX_SIZE_GTK_KEY 9

char key_shortcuts(char *option){
        
    char *string;
    char *result;
    char key;


    string = strrchr(option, '+');

    result = malloc(sizeof(char) * MAX_SIZE_GTK_KEY);
    string[strlen(string)] = '\0'; 
    strcpy(result, string + 1);
    key = (char)*result;
    free(result);
    
    //printf("%d\n", key);
    return key;

}

//SHIFT : 1, CTRL: 4, ALT: 8
guint mask_shortcuts(char *option){

    char  *ptr, *buffer;
    char  **result;
    guint  key;
    int i;

    buffer = malloc(sizeof(char) * strlen(option) + 1);
    strcpy(buffer, option);
    for (i = 0, ptr = buffer; *ptr ; ptr++)
        if (*ptr == '+')
            i++;
           
    result = malloc(sizeof(char*) * (i + 2));
    result[i+1] = NULL;

    i = 0;
    while ((ptr = strrchr(buffer,'+')) != NULL){

        *ptr = '\0';
        ptr++;
        result[i] = malloc(sizeof(char) * (strlen(ptr) + 1));
        strcpy(result[i], ptr);
        i++;

    }
    result[i] = malloc(strlen(buffer) + 1);
    buffer[strlen(buffer)] = '\0';
    strcpy(result[i], buffer);
    free(buffer);

    key = get_gdk_mask(result);
    i = 0;
    while(result[i] != NULL){
        free(result[i]);
        i++;
    }
    free(result);

    //printf("%u\n", key);
    return key;
}

guint get_gdk_mask(char **array){
    
    int i = 0;
    guint key = 0;

    while(array[i] != NULL){
        i++;
    }
    
    i -= 1;
    
    while(i >= 1){

        //printf("%s\n", array[i]);

        if(strcmp(array[i], "shift") == 0)
            key += GDK_SHIFT_MASK;
        else if(strcmp(array[i], "ctrl") == 0)
            key += GDK_CONTROL_MASK;
        else if(strcmp(array[i], "alt") == 0)
            key += 8;

        i--;
    }

    return key;

}
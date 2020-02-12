//autor: Clement BOSSARD, Clement K-R
//date: 17/12/2019 - 12/02/2020
//Ce fichier contient les fonctions pour la creation des raccourcies clavier


#include "logicSimButInC.h"


void    print_array(char **array){
    if (array == NULL){
        printf("NULL\n");
    }else{
        while (*array != NULL){
            printf("%s\n", *array);
            array++;
        }
    }
}

void    free_split(char **bind){
    int    i = 0;

    while (bind[i] != NULL){
        free(bind[i]);
        i++;
    }
    free(bind);
}

char    **split_bind(char *bind){
    char    *ptr, *buffer;
    char    **result;
    int     i;

    buffer = malloc(sizeof(char) * strlen(bind) + 1);
    strcpy(buffer, bind);
    for (i = 0, ptr = buffer; *ptr ; ptr++)
        if (*ptr == '+')
            i++;
    if(!i){
        free(buffer);
        return NULL;
    }

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
    strcpy(result[i], buffer);
    free(buffer);
    return result;
}

char    is_shotcut_used(guint mask, guint key){
    static guint    shortcut_used[MAX_NB_SHORTCUT][2] = {0};
    int             i = 0;

    if (key == 0)
        return 1;
    while (shortcut_used[i][1] && i < MAX_NB_SHORTCUT){
        if (shortcut_used[i][0] == mask && shortcut_used[i][1] == key)
            return 1;
        i++;
    }
    shortcut_used[i][0] = mask;
    shortcut_used[i][1] = key;
    return 0;
}

void    create_shortcut(data_t *data, GtkAccelGroup *accel_group, GtkWidget *widget, char *name){

    guint  mask, key;
    char    **array;

    array = split_bind(get_option(data->option, name));
    key = check_key_binding(key_shortcuts(array), name);
    mask = check_mask(get_gdk_mask(array),name);

    if (!is_shotcut_used(mask, key))
        gtk_widget_add_accelerator(widget, "activate", accel_group, key, mask, GTK_ACCEL_VISIBLE);
    free_split(array);
}

char    key_shortcuts(char **option){
    
    char    key = 0;
    int     i = 0;

    if (option == NULL)
        return 0;
    while (option[i] != NULL){
        if (strlen(option[i]) == 1){
            if (key)
                return 0;
            else
                key = option[i][0];
        }
        i++;
    }
    if(key < 'a' || key > 'z')
        return 0;
    return key;
}

//SHIFT : 1, CTRL: 4, ALT: 8

guint   get_gdk_mask(char **array){
    
    int i = 0;
    guint mask = 0;

    while(array[i] != NULL){


        if(strcmp(array[i], "shift") == 0)
            mask += GDK_SHIFT_MASK;
        else if(strcmp(array[i], "ctrl") == 0)
            mask += GDK_CONTROL_MASK;
        else if(strcmp(array[i], "alt") == 0)
            mask += 8;
        else if (strlen(array[i]) != 1)
            return 0;
        i++;
    }
    return mask;

}

int    check_key_binding(int key, char *name){
    
    if (!key){
        printf("Incorrect key binding for : %s, Choose a key between a and z to bind correctly the shortcut\n", name);
        if(strcmp(name, "new") == 0)
            key = 'n';
        if(strcmp(name, "open") == 0)
            key = 'o';
        if(strcmp(name, "save") == 0 || strcmp(name, "saveAs") == 0)
            key = 's';
        if(strcmp(name, "quit") == 0)
            key = 'q';  
    }
    return key;
}

guint   check_mask(int mask, char *name){
    
    if(strcmp(name, "new") == 0)
        mask == '0'?mask = GDK_CONTROL_MASK, printf("Incorrect mask for key binding: %s, There is only three masks : SHIFT, CTRL, ALT\n", name):mask;
    if(strcmp(name, "open") == 0)
        mask == '0'?mask = GDK_CONTROL_MASK, printf("Incorrect mask for key binding: %s, There is only three masks : SHIFT, CTRL, ALT\n", name):mask;
    if(strcmp(name, "save") == 0)
        mask == '0'?mask = GDK_CONTROL_MASK, printf("Incorrect mask for key binding: %s, There is only three masks : SHIFT, CTRL, ALT\n", name):mask;
    if(strcmp(name, "saveAs") == 0)
        mask == '0'?mask = GDK_CONTROL_MASK + GDK_SHIFT_MASK, printf("Incorrect mask for key binding: %s, There is only three masks : SHIFT, CTRL, ALT\n", name):mask;
    if(strcmp(name, "quit") == 0)
        mask == '0'?mask = GDK_CONTROL_MASK, printf("Incorrect mask for key binding: %s, There is only three masks : SHIFT, CTRL, ALT\n", name):mask;

    return mask;

}
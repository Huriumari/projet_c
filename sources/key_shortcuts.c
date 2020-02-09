#include "logicSimButInC.h"

#define MAX_SIZE_GTK_KEY 9

void    free_split(char **bind){
    char    *ptr;
    
    ptr = *bind;
    while (*ptr){
        free(ptr);
        ptr++;
    }
    free(bind);
}

char    **split_bind(char *bind){
    char  *ptr, *buffer;
    char  **result;
    int i;

    buffer = malloc(sizeof(char) * strlen(option) + 1);
    strcpy(buffer, option);
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

void    create_shortcut(data_t *data, GtkAccelGroup *accel_group, GtkWidget *widget, char *name){

    guint  mask, key;

    GDK_KEY_o
    static guint shortcut_used[5][2] = {0};
    char    **array;

    array = split_bind(get_option(data->option, "new"));

    key = check_key_binding(key_shortcuts(), "new");
    mask = check_mask(mask_shortcuts(get_option(data->option, "new")),"new");

    gtk_widget_add_accelerator(new, "activate", accel_group, key, mask, GTK_ACCEL_VISIBLE);

    gtk_widget_add_accelerator(open, "activate", accel_group, check_key_binding(key_shortcuts(get_option(data->option, "open")), "open"), check_mask(mask_shortcuts(get_option(data->option, "open")), "open"), GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(save, "activate", accel_group, check_key_binding(key_shortcuts(get_option(data->option, "save")),"save"), check_mask(mask_shortcuts(get_option(data->option, "save")), "save"), GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(saveAs, "activate", accel_group, check_key_binding(key_shortcuts(get_option(data->option, "saveAs")), "saveAs"), check_mask(mask_shortcuts(get_option(data->option, "saveAs")), "saveAs"), GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(quit, "activate", accel_group, check_key_binding(key_shortcuts(get_option(data->option, "quit")), "quit"), check_mask(mask_shortcuts(get_option(data->option, "quit")), "quit"), GTK_ACCEL_VISIBLE);
}

char    key_shortcuts(char **option){
    
    char    key;
    char    *ptr;
    if (option == NULL)
        return 0;

    if(key < 'a' || key > 'z')
        return 0;
    return key;
}

//SHIFT : 1, CTRL: 4, ALT: 8
guint   mask_shortcuts(char *option){

    

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

guint   get_gdk_mask(char **array){
    
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
        else
            return 0;
        i--;
    }

    return key;

}

int    check_key_binding(int key, char *name){
    
    if(strcmp(name, "new") == 0)
        key == 0?key = 'n', printf("Incorrect key binding for : %s, Choose a key between a and z to bind correctly the shortcut\n", name):key;
    if(strcmp(name, "open") == 0)
        key == 0?key = 'o', printf("Incorrect key binding for : %s, Choose a key between a and z to bind correctly the shortcut\n", name):key;
    if(strcmp(name, "save") == 0 || strcmp(name, "saveAs") == 0)
        key == 0?key = 's', printf("Incorrect key binding for : %s, Choose a key between a and z to bind correctly the shortcut\n", name):key;
    if(strcmp(name, "quit") == 0)
        key == 0?key = 'q', printf("Incorrect key binding for : %s, Choose a key between a and z to bind correctly the shortcut\n", name):key;
    
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
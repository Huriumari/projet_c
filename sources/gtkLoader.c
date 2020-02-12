//autor: Clement BOSSARD, Clement K-R
//date: 17/12/2019 - 12/02/2020
//Ce fichier contient une fonction pour creer un bouton


#include "logicSimButInC.h"

GtkWidget * componentsButton(char *path){

    GtkWidget * button;
    GtkWidget * img;

    button = gtk_button_new();
    img = gtk_image_new_from_file(path);
    gtk_button_set_image(GTK_BUTTON(button), img);

    return button;

}
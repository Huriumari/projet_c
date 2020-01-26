#include "logicSimButInC.h"

void * mousePos(GtkWidget * mouse, GdkEvent *event, gpointer gtk_data){

    GtkWidget * img;
    GtkWidget * workingLayout;
    GdkEventButton* mouse_click = (GdkEventButton *) event;
    data_t * data = (data_t *)gtk_data;
 
    workingLayout = data->workingLayout;
    data->pos.x = mouse_click->x;
    data->pos.y = mouse_click->y;
    //fprintf(stdout, "Mouse coordinates (%lf, %lf)\n", data->pos.x, data->pos.y);
    
    img = gtk_image_new_from_file(data->imgPath);
    gtk_layout_put(GTK_LAYOUT(workingLayout), img, data->pos.x, data->pos.y);
    gtk_widget_show_all(workingLayout);

}

void isClicked(GtkWidget * comp, gpointer gtk_data){

    data_t * data = (data_t *)gtk_data;
    
    if(strcmp(gtk_widget_get_name(comp), "compAND") == 0){
        data->imgPath = "/home/esgi/Documents/ProjetC/img/components/AND.png";
    }
    else if(strcmp(gtk_widget_get_name(comp), "compNAND") == 0){
		data->imgPath = "/home/esgi/Documents/ProjetC/img/components/NAND.png";
    }
    else if(strcmp(gtk_widget_get_name(comp), "compOR") == 0){
		data->imgPath = "/home/esgi/Documents/ProjetC/img/components/OR.png";
    }
    else if(strcmp(gtk_widget_get_name(comp), "compNOR") == 0){
		data->imgPath = "/home/esgi/Documents/ProjetC/img/components/NOR.png";
    }
    else if(strcmp(gtk_widget_get_name(comp), "compXOR") == 0){
		data->imgPath = "/home/esgi/Documents/ProjetC/img/components/XOR.png";
    }

}

void dragComponents(GtkWidget* comp, gpointer gtk_data){
    GtkWidget * workingLayout;

    data_t * data = (data_t *)gtk_data;
    workingLayout = data->workingLayout;

    //printf("%s\n", data->imgPath);

    gtk_widget_add_events(workingLayout, GDK_BUTTON_PRESS_MASK);
    //g_signal_connect_after(G_OBJECT(workingLayout), "delete-event", G_CALLBACK(delete_event), NULL) ;
    g_signal_connect(G_OBJECT(workingLayout), "button-press-event", G_CALLBACK(mousePos), data) ;
    
    
}
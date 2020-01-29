#include "logicSimButInC.h"

void * mousePos(GtkWidget * mouse, GdkEvent *event, gpointer gtk_data){
    GdkEventButton* mouse_click = (GdkEventButton *) event;
    data_t      *data = (data_t *)gtk_data;
    char        is_on_another_comp;
    component_t *component;
    GdkPixbuf   *pb;
    double      x,y;

    is_on_another_comp = 0;
    //fprintf(stdout, "Mouse coordinates (%lf, %lf)\n", data->pos.x, data->pos.y);
    
    if(data->imgPath != NULL){
        component = data->component;
        while (!is_on_another_comp && component != NULL){
            pb = gtk_image_get_pixbuf(GTK_IMAGE(component->img));
            x = gdk_pixbuf_get_width(pb);
            y = gdk_pixbuf_get_height(pb);
            if (mouse_click->x > component->pos.x - (double)(x)
            &&  mouse_click->x < component->pos.x + (double)(x)
            &&  mouse_click->y > component->pos.y - (double)(y)
            &&  mouse_click->y < component->pos.y + (double)(y))
                is_on_another_comp = 1;
            component = component->next;
        }
        if (!is_on_another_comp)
            add_component(data, data->imgPath, mouse_click->x, mouse_click->y);
    }
    if (!is_on_another_comp)
        data->imgPath = NULL;

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
    g_signal_connect(G_OBJECT(workingLayout), "button-press-event", G_CALLBACK(mousePos), data);    
}
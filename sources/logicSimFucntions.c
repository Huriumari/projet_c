#include "logicSimButInC.h"

gboolean mousePos(GtkWidget * widget, GdkEvent *event, data_t * data){

    GtkWidget * img;
    GtkWidget * workingLayout;
    GdkEventButton* mouse_click = (GdkEventButton *) event;
 
    workingLayout = data->workingLayout;
    data->pos.x = mouse_click->x;
    data->pos.y = mouse_click->y;
    //fprintf(stdout, "Mouse coordinates (%lf, %lf)\n", data->pos.x, data->pos.y);
    
    img = gtk_image_new_from_file(data->imgPath);
    gtk_layout_put(GTK_LAYOUT(workingLayout), img, data->pos.x, data->pos.y);
    gtk_widget_show_all(workingLayout);

    return TRUE;

}

void isClicked(void){}

void dragComponents(GtkWidget* button, data_t * data){
    GtkWidget * workingLayout;

    workingLayout = data->workingLayout;


    gtk_widget_add_events(workingLayout, GDK_BUTTON_PRESS_MASK);
    //g_signal_connect_after(G_OBJECT(workingLayout), "delete-event", G_CALLBACK(delete_event), NULL) ;
    g_signal_connect(G_OBJECT(workingLayout), "button-press-event", G_CALLBACK(mousePos), data) ;
    
    //printf("%s\n", gtk_widget_get_name(data->workingLayout));
    
}
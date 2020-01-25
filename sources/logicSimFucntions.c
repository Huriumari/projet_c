#include "logicSimButInC.h"

void * mousePos(GtkWidget * widget, GdkEvent *event, data_t * data){

    GdkEventButton* mouse_click = (GdkEventButton *) event;
 
    //fprintf(stdout, "Mouse coordinates (%lf, %lf)\n", mouse_click->x, mouse_click->y);
    data->pos.x = mouse_click->x;
    data->pos.y = mouse_click->y;
    fprintf(stdout, "Mouse coordinates (%lf, %lf)\n", data->pos.x, data->pos.y);

}

void isClicked(void){}

void dragComponents(GtkWidget* button, data_t * data){
    GtkWidget * img;
    GtkWidget * workingLayout;
    pos_t pos;

    workingLayout = data->workingLayout;


    gtk_widget_add_events(workingLayout, GDK_BUTTON_PRESS_MASK);
    //g_signal_connect_after(G_OBJECT(workingLayout), "delete-event", G_CALLBACK(delete_event), NULL) ;
    g_signal_connect(G_OBJECT(workingLayout), "button-press-event", G_CALLBACK(mousePos), &pos) ;

    fprintf(stdout, "Mouse coordinates (%lf, %lf)\n", data->pos.x, data->pos.y);
    printf("%s", data->imgPath);
    img = gtk_image_new_from_file(data->imgPath);
    printf("%s\n", gtk_widget_get_name(data->workingLayout));
    gtk_layout_put(GTK_LAYOUT(workingLayout), img, 50, 50);
    gtk_widget_show_all(workingLayout);

}
#include "logicSimButInC.h"

void isClicked(void){}

void dragComponents(GtkWidget* button, data_t * data){
    GtkWidget * img;
    GtkWidget * workingLayout;

    workingLayout = data->workingLayout;
    //data_t *data = gtk_data;
    img = gtk_image_new_from_file(data->imgPath);
    printf("%d\n", data->test);
    gtk_layout_put(GTK_LAYOUT(workingLayout), img, 50, 50);

}
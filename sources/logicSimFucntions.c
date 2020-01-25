#include "logicSimButInC.h"

void isClicked(void){}

void dragComponents(GtkWidget* button, data_t * data){
    GtkWidget * img;
    //data_t *data = gtk_data;
    img = gtk_button_get_image(GTK_BUTTON(data->widget));
    printf("%d\n", data->test);

}
#include "logicSimButInC.h"

void isClicked(void){}

void dragComponents(gpointer gtk_data){
    
    data_t *data = (data_t *)gtk_data;
    //printf("%s\n", gtk_widget_get_name(data->widget));
    printf("%d\n", data->test);

}
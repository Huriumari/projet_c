/*
	Programme de simulation de composants logiques.
	Clément Bossard & Clément K-R
*/

#include "logicSimButInC.h"

int main(int argc,char **argv)
{
	GtkWidget* window;
	GtkWidget* vBox;
    
	window = gtkWindow(&argc, &argv);
	
	vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add(GTK_CONTAINER(window), vBox);
	menubar(window, vBox);

	toolbar(vBox);

	workingPart(vBox);

	gtk_widget_show_all(window);

    gtk_main();

    return EXIT_SUCCESS;
}
/*
	Programme de simulation de composants logiques.
	Clément Bossard & Clément K-R
*/

#include "logicSimButInC.h"


int main(int argc,char **argv)
{
	GtkWidget* window;
	GtkWidget* vBox;
	GtkWidget* grid;
	GtkWidget* workingLayout;
    
	window = gtkWindow(&argc, &argv);
	
	vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add(GTK_CONTAINER(window), vBox);
	menubar(window, vBox);

	toolbar(vBox);

	grid = gtk_grid_new();
	gtk_container_set_border_width (GTK_CONTAINER (grid), 5);
    gtk_box_pack_start(GTK_BOX(vBox), grid, TRUE, TRUE, 0);

	workingLayout = workingPart(vBox, grid);
	componentsPart(vBox, grid, window, workingLayout);
	

	gtk_widget_show_all(window);

    gtk_main();

    return EXIT_SUCCESS;
}
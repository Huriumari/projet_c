//autor: Clement BOSSARD, Clement K-R
//date: 17/12/2019 - 12/02/2020
//Ce fichier contient les fonctions necessaire pour l'utilisation des fenetre de dialogue

#include "logicSimButInC.h"

void openDialogWindow(GtkWidget *widget, data_t *data){

  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;
  gchar *filename;

  if(widget)
    widget++;

  dialog = gtk_file_chooser_dialog_new ("Open File", NULL, action, ("_Cancel"), GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);

  res = gtk_dialog_run (GTK_DIALOG (dialog));

  if (res == GTK_RESPONSE_ACCEPT){
      
      GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
      filename = gtk_file_chooser_get_filename (chooser);
      data->filename = filename;
      load(data, filename);
      //fonction à appeller pour open (avec la variable filename)
      data->filename = NULL;
      g_free (filename);
    }
  
  gtk_widget_destroy (dialog);

}

void  saveDialogWindow(GtkWidget *widget, data_t *data){

  GtkWidget *dialog;
  GtkFileChooser *chooser;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  gint res;
  gchar *filename;

  if(widget)
    widget++;

  dialog = gtk_file_chooser_dialog_new ("Save File", NULL, action, ("_Cancel"), GTK_RESPONSE_CANCEL, ("_Save"), GTK_RESPONSE_ACCEPT, NULL);
  chooser = GTK_FILE_CHOOSER (dialog);

  gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

  if (!(data->filename))
    gtk_file_chooser_set_current_name (chooser, ("Untitled document"));
  else
    gtk_file_chooser_set_filename (chooser, data->filename);

  res = gtk_dialog_run (GTK_DIALOG (dialog));

  if (res == GTK_RESPONSE_ACCEPT){
      filename = gtk_file_chooser_get_filename (chooser);
      //fonction à appeller pour save avec le nom contenue dans "filename"
      save(data,filename);
      g_free (filename);
    }
  
  gtk_widget_destroy (dialog);

}

void  saveAsDialogWindow(GtkWidget *widget, data_t *data){

  GtkWidget *dialog;
  GtkFileChooser *chooser;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  gint res;
  gchar *filename;

  if(widget)
    widget++;

  dialog = gtk_file_chooser_dialog_new ("Save File", NULL, action, ("_Cancel"), GTK_RESPONSE_CANCEL, ("_Save"), GTK_RESPONSE_ACCEPT, NULL);
  chooser = GTK_FILE_CHOOSER (dialog);

  gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

  if(!(data->filename))
    gtk_file_chooser_set_current_name (chooser, ("Untitled document"));
  else
    gtk_file_chooser_set_current_name (chooser, data->filename);

  res = gtk_dialog_run (GTK_DIALOG (dialog));

  if (res == GTK_RESPONSE_ACCEPT){
      filename = gtk_file_chooser_get_filename (chooser);
      //fonction à appeller pour saveAs avec le nom contenue dans "filename"
      save(data, filename);
      g_free (filename);
    }

  gtk_widget_destroy (dialog);

}

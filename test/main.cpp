#include <gtk/gtk.h>

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *grid;

  //création fenetre
  window = gtk_application_window_new (app);
  //titre
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  //taille
  
  gtk_container_set_border_width (GTK_CONTAINER (window), 200);

//Here we construct the container that is going pack our buttons 
  grid = gtk_grid_new ();

   // Pack the container in the window
  gtk_container_add (GTK_CONTAINER (window), grid);
  
  //nom du bouton
  button = gtk_button_new_with_label ("Hello World");
  //appel de la fonction avec le clic
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  //destruction de la fenetre
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  
  // Place the first button in the grid cell (0, 0)
  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);


  

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  gtk_grid_attach (GTK_GRID (grid), button, 100, 100, 200, 200);


  //affichage?
  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

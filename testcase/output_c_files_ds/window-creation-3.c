#include <gt/gt.h>

int
main(int argc, char *argv[])
{
  GtkWidget *window;

  gtk_init(&arg, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect (window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show(window);
  gtk_main();

  return 0;
}

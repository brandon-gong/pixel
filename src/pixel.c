#include <gtk/gtk.h>

#define WIDTH 900
#define HEIGHT 600

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent *event,
                              gpointer data     ) {
    return FALSE;
}

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {

    gtk_init (&argc, &argv);

    GtkWidget *window;
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (window, "delete-event", G_CALLBACK (delete_event), NULL);
    g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 0);

    GdkRectangle r;
    gdk_monitor_get_geometry(
        gdk_display_get_monitor(
            gdk_display_get_default(), 0), &r);

    gtk_window_set_resizable(GTK_WINDOW (window), FALSE);
    gtk_window_set_default_size(GTK_WINDOW (window), r.width, r.height);
    // gtk_window_move(GTK_WINDOW (window),
    //                 (r.width / 2 - WIDTH / 2),
    //                 (r.height / 2 - HEIGHT / 2));
    gtk_window_set_title(GTK_WINDOW (window), "Pixel v0.1.0");
    gtk_window_set_icon_from_file(GTK_WINDOW (window), "../res/icon.png", NULL);
    gtk_widget_show (window);

    gtk_main ();
    return 0;
}

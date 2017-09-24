#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>

#define WIDTH r.width
#define HEIGHT r.height

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent *event,
                              gpointer data     ) {
    return FALSE;
}

static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

static void on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    GtkWidget *win = gtk_widget_get_toplevel(widget);

      int width, height;
      gtk_window_get_size(GTK_WINDOW(win), &width, &height);

      cairo_set_line_width(cr, 9);
      cairo_set_source_rgb(cr, 0.69, 0.19, 0);

      cairo_translate(cr, width/2, height/2);
      cairo_arc(cr, 0, 0, 50, 0, 2 * M_PI);
      cairo_stroke_preserve(cr);

      cairo_set_source_rgb(cr, 0.3, 0.4, 0.6);
      cairo_fill(cr);
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
    gtk_window_set_default_size(GTK_WINDOW (window), WIDTH, HEIGHT);
    gtk_window_move(GTK_WINDOW (window),
        (r.width / 2 - WIDTH / 2),
        (r.height / 2 - HEIGHT / 2));
    gtk_window_set_title(GTK_WINDOW (window), "Pixel v0.1.0");
    gtk_window_set_icon_from_file(GTK_WINDOW (window), "../res/icon.png", NULL);

    GtkWidget *drawing_area;
    drawing_area = gtk_drawing_area_new();
    g_signal_connect (G_OBJECT (drawing_area), "draw", G_CALLBACK (on_draw),
    NULL);

    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    gtk_widget_show(drawing_area);
    gtk_widget_show(window);

    gtk_main ();
    return 0;
}

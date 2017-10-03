#include <gtk/gtk.h>
#include <cairo.h>
#include <pango/pangocairo.h>

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

static void on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    GtkWidget *win = gtk_widget_get_toplevel(widget);
    int window_width, window_height, node_width, node_height;
    gtk_window_get_size(GTK_WINDOW(win), &window_width, &window_height);
    node_width = 200;
    node_height = 100;
    PangoLayout *layout;
    PangoFontDescription *desc;
    layout = pango_cairo_create_layout(cr);
    pango_layout_set_text(layout, "Output RTF", -1);
    desc = pango_font_description_from_string("Monospace Regular 10");
    pango_layout_set_font_description(layout, desc);
    pango_font_description_free(desc);
    cairo_set_line_width(cr, 3);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_translate(cr, (window_width / 2 - node_width / 2),
                        (window_height / 2 - node_height / 2));
    cairo_rectangle(cr, 0, 0, node_width, node_height);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, 0.89, 0.855, 0.788);
    cairo_fill_preserve(cr);
    cairo_restore(cr);
    cairo_save(cr);
    cairo_move_to(cr, (window_width / 2 - node_width / 2 + 5),
                        (window_height / 2 - node_height / 2 + 5));
    pango_cairo_show_layout (cr, layout);
    cairo_restore(cr);
    cairo_save(cr);
    cairo_new_path(cr);
    cairo_move_to(cr, (window_width / 2 - node_width / 2 - 1),
                        (window_height / 2 - node_height / 2 + 30));
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_width(cr, 10);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_close_path(cr);
    cairo_stroke(cr);
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

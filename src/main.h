#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>
#include <gtk/gtk.h>
#include <errno.h>
#include <string.h>
#include <glib/gstdio.h>
#include <gdk/gdkkeysyms.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct {
  GtkWidget *window;
  GtkWidget *button;
  GtkTextBuffer *buffer;
  GtkWidget *textbox;
  GtkWidget *box;
  GtkWidget *scrolled_window;
} Console;


static void query (void);
static void run   (const gchar      *name,
                   gint              nparams,
                   const GimpParam  *param,
                   gint             *nreturn_vals,
                   GimpParam       **return_vals);
static void js_fu_submit (GtkWidget *widget,
                          GtkTextBuffer *buffer);


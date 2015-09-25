#include <libgimp/gimp.h>

/* Declare functions */

static void   query     (void);
static void   run       (const gchar      *name,
                         gint             nparams,
                         const GimpParam  *param,
                         gint             *nreturn_vals,
                         GimpParam        **return_vals);

const GimpPlugInInfo PLUG_IN_INFO = 
{
  NULL,       /* Init */
  NULL,       /* Quit */
  query,      /* Query */
  run         /* Run */
};

MAIN ()

static void query (void) {
  static GimpParamDef args[] = {
    { GIMP_PDB_INT32, "run-mode", "Run Mode" },
    { GIMP_PDB_IMAGE, "image", "Input image" },
    { GIMP_PDB_DRAWABLE, "drawable", "Input drawable"}
  };

  gimp_install_procedure (
      "test-plug-in",
      "This is a simple test",
      "Displays some words in a dialog",
      "Pratyusha Gupta",
      "Pratyusha Gupta",
      "2015",
      "_Test",
      "RGB*, GRAY*",
      GIMP_PLUGIN,
      G_N_ELEMENTS (args), 0,
      args, NULL);

  gimp_plugin_menu_register ("test-plug-in",
      "/Filters/Misc");
}

static void run (const gchar *name, gint nparams, const GimpParam *param,
    gint *nreturn_vals, GimpParam **return_vals) {

  /* To Do */

}

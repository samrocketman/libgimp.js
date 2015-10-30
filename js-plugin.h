/*
 * Copyright/Licensing information.
 */

/* inclusion guard */
#ifndef __JS_PLUGIN_H__
#define __JS_PLUGIN_H__

#include <glib-object.h>
/*
 * Potentially, include other headers on which this header depends.
 */

G_BEGIN_DECLS

/*
 * Type declaration.
 */
#define JS_TYPE_PLUGIN js_plugin_get_type ()
G_DECLARE_FINAL_TYPE (JsPlugin, js_plugin, JS, PLUGIN, GObject)

/*
 * Method definitions.
 */
ViewerFile *viewer_file_new (void);

G_END_DECLS

#endif /* __JS_PLUGIN_H__ */
/* -*- Mode: c; c-basic-offset: 4 -*- 
 *
 * GOBject Introspection for JavaScript plugins. 
 *
 */

#ifndef __JS_PLUGIN_H__
#define __JS_PLUGIN_H__

#include <glib.h>
#include <glib-object.h>

#define JS_PLUGIN_TYPE		\
    (js_plugin_get_type())
#define JS_PLUGIN(o)			\
    (G_TYPE_CHECK_INSTANCE_CAST ((o), JS_PLUGIN_TYPE, JsPlugin))
#define JS_PLUGIN_CLASS(c)		\
    (G_TYPE_CHECK_CLASS_CAST ((c), JS_PLUGIN_TYPE, JsPluginClass))
#define JS_IS_PLUGIN(o)		\
    (G_TYPE_CHECK_INSTANCE_TYPE ((o), JS_PLUGIN_TYPE))
#define JS_IS_PLUGIN_CLASS(c)		\
    (G_TYPE_CHECK_CLASS_TYPE ((c),  JS_PLUGIN_TYPE))
#define JS_PLUGIN_GET_CLASS(o)	\
    (G_TYPE_INSTANCE_GET_CLASS ((o), JS_PLUGIN_TYPE, JsPluginClass))

typedef struct _JsPlugin		JsPlugin;
typedef struct _JsPluginPrivate	    JsPluginPrivate;
typedef struct _JsPluginClass		JsPluginClass;

struct _JsPlugin {
    GObject parent;
};

struct _JsPluginClass {
    GObjectClass parent;
};

GType		js_plugin_get_type	() G_GNUC_CONST;

JsPlugin*	js_plugin_new		(void);

void		js_plugin_greet	(JsPlugin *plugin);

#endif /* __JS_PLUGIN_H__ */

/* -*- Mode: c; c-basic-offset: 4 -*- 
 *
 * GOBject Introspection Tutorial 
 * 
 * Written in 2013 by Simon Kågedal Reimer <skagedal@gmail.com>
 *
 * To the extent possible under law, the author have dedicated all
 * copyright and related and neighboring rights to this software to
 * the public domain worldwide. This software is distributed without
 * any warranty.
 *
 * CC0 Public Domain Dedication:
 * http://creativecommons.org/publicdomain/zero/1.0/
 */

#ifndef __JS_GREETER_H__
#define __JS_GREETER_H__

#include <glib.h>
#include <glib-object.h>

#define JS_GREETER_TYPE		\
    (js_greeter_get_type())
#define JS_GREETER(o)			\
    (G_TYPE_CHECK_INSTANCE_CAST ((o), JS_GREETER_TYPE, JsGreeter))
#define JS_GREETER_CLASS(c)		\
    (G_TYPE_CHECK_CLASS_CAST ((c), JS_GREETER_TYPE, JsGreeterClass))
#define JS_IS_GREETER(o)		\
    (G_TYPE_CHECK_INSTANCE_TYPE ((o), JS_GREETER_TYPE))
#define JS_IS_GREETER_CLASS(c)		\
    (G_TYPE_CHECK_CLASS_TYPE ((c),  JS_GREETER_TYPE))
#define JS_GREETER_GET_CLASS(o)	\
    (G_TYPE_INSTANCE_GET_CLASS ((o), JS_GREETER_TYPE, JsGreeterClass))

typedef struct _JsGreeter		JsGreeter;
typedef struct _JsGreeterPrivate	JsGreeterPrivate;
typedef struct _JsGreeterClass		JsGreeterClass;

struct _JsGreeter {
    GObject parent;
};

struct _JsGreeterClass {
    GObjectClass parent;
};

GType		js_greeter_get_type	() G_GNUC_CONST;

JsGreeter*	js_greeter_new		(void);

void		js_greeter_greet	(JsGreeter *greeter);

#endif /* __JS_GREETER_H__ */

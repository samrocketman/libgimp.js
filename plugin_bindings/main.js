const JsPlugin = imports.gi.JsPlugin; 

let greeter = new JsPlugin.JsPlugin({ greetee: 'JavaScript programmer' });
greeter.greet();

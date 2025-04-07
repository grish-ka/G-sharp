// // TODO: make builtin functions for a window and add them to the SDK :3
// #include <X11/Xlib.h>
// #include "include/scope.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "include/GUI.h"
// #include "include/visitor.h"

// // XEvent event;
// // Display* display = XOpenDisplay(NULL);
// // Window w = XCreateSimpleWindow(display, DefaultRootWindow(display), 50, 50, 250, 250, 1, BlackPixel(display, 0), WhitePixel(display, 0));
// // XMapWindow(display, w);
// // XSelectInput(display, w, ExposureMask);

// // for (;;) {
// //     XNextEvent(display, &event);
// //     if (event.type == Expose) {
// //         XDrawString(display, w, DefaultGC(display, 0), 100, 100, "Thanks for Watching!", 20);
// //     }
// // }

// static AST_T* builtin_function_new_window(visitor_T* visitor, AST_T** args, int args_size) {
//     // for (int i = 0; i < args_size; i++)
//     // {
//     //     AST_T* visited_ast = visitor_visit(visitor, args[i]);

//     //     switch (visited_ast->type)
//     //     {
//     //         case AST_STRING: printf("%s\n", visited_ast->string_value); break;
//     //         default: printf("%p\n", visited_ast); break;
//     //     }
//     // }

//     XEvent event;
//     Display* display = XOpenDisplay(NULL);
//     Window w = XCreateSimpleWindow(display, DefaultRootWindow(display), 50, 50, 250, 250, 1, BlackPixel(display, 0), WhitePixel(display, 0));
//     XMapWindow(display, w);
//     XSelectInput(display, w, ExposureMask);

//     for (;;) {
//         XNextEvent(display, &event);
//         if (event.type == Expose) {
//             // XDrawString(display, w, DefaultGC(display, 0), 100, 100, "Thanks for Watching!", 20);
//         }
//     }

//     return init_ast(AST_NOOP);
// }
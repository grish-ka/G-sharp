#include "include/visitor.h"
#include "include/scope.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/io.h"
#include "include/strfuncs.h"
#include <X11/Xlib.h>

// TODO: fix include

static AST_T* builtin_function_print(visitor_T* visitor, AST_T** args, int args_size)
{
    for (int i = 0; i < args_size; i++)
    {
        AST_T* visited_ast = visitor_visit(visitor, args[i]);

        switch (visited_ast->type)
        {
            case AST_STRING: printf("%s\n", visited_ast->string_value); break;
            default: printf("%p\n", visited_ast); break;
        }
    }

    return init_ast(AST_NOOP);
}

static AST_T* builtin_function_new_window(visitor_T* visitor, AST_T** args, int args_size) {
    for (int i = 0; i < args_size; i++)
    {
        
        AST_T* width = visitor_visit(visitor, args[0]);
        AST_T* height = visitor_visit(visitor, args[1]);
        // case AST_STRING: printf("%s\n", visited_ast->string_value); break;
        XEvent event;
        Display* display = XOpenDisplay(NULL);
        Window w = XCreateSimpleWindow(display, DefaultRootWindow(display), 50, 50, width, height, 1, BlackPixel(display, 0), WhitePixel(display, 0));
        XMapWindow(display, w);
        XSelectInput(display, w, ExposureMask);
    
        for (;;) {
            XNextEvent(display, &event);
            if (event.type == Expose) {
            }
        } break;
        
    }

    return init_ast(AST_NOOP);
}

// static AST_T* builtin_function_exit(visitor_T* visitor, AST_T** args, int args_size)
// {
//     for (int i = 0; i < args_size; i++)
//     {
//         AST_T* visited_ast = visitor_visit(visitor, args[i]);

//         switch (visited_ast->type)
//         {
//             case AST_STRING: exit(atoi(visited_ast)); break;
//             default: exit(0); break;
//         }
//     }
//     exit(0);
//     return init_ast(AST_NOOP);
// }

static AST_T* builtin_function_custom(visitor_T* visitor, AST_T** args, int args_size) //base function
{
    for (int i = 0; i < args_size; i++)
    {
        AST_T* visited_ast = visitor_visit(visitor, args[i]);

        switch (visited_ast->type)
        {
            case AST_STRING: printf("%s\n", visited_ast->string_value); break;
            default: printf("examples in G-sharp/examples\n"); break;
        }
    }

    return init_ast(AST_NOOP);
}

static AST_T* builtin_function_include(visitor_T* visitor, AST_T** args, int args_size)
{
    
    AST_T* visited_ast = visitor_visit(visitor, args[0]);
    AST_T* visited_ast2 = visitor_visit(visitor, args[1]);

    switch (visited_ast->type)
    {
        case AST_STRING: printf("%s will be included\n", visited_ast->string_value);
        const char* content =strcat(get_file_contents(visited_ast->string_value), "\n");
        if (visited_ast2->string_value == "") {printf("Enter self file here");};
        char* filepath = visited_ast2->string_value; const char* prefilecontent = get_file_contents(filepath);
        char* statement[100];
        sprintf(statement, "include(%s, %s)", visited_ast, visited_ast2);
        prefilecontent = strremove(prefilecontent, statement);
        printf("The contents are: \n%s\n", content); addfilecontent(filepath, content, prefilecontent); break;
        default: printf("please enter a file\n");break; 
    }
    

    return init_ast(AST_NOOP);
}

visitor_T* init_visitor()
{
    visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));

    return visitor;
}

AST_T* visitor_visit(visitor_T* visitor, AST_T* node)
{
    switch (node->type)
    {
        case AST_VARIABLE_DEFINITION: return visitor_visit_variable_definition(visitor, node); break;
        case AST_FUNCTION_DEFINITION: return visitor_visit_function_definition(visitor, node); break;
        case AST_VARIABLE: return visitor_visit_variable(visitor, node); break;
        case AST_FUNCTION_CALL: return visitor_visit_function_call(visitor, node); break;
        case AST_STRING: return visitor_visit_string(visitor, node); break;
        case AST_COMPOUND: return visitor_visit_compound(visitor, node); break;
        case AST_NOOP: return node; break;
    }

    printf("Uncaught statement of type `%d`\n", node->type);
    exit(1);

    return init_ast(AST_NOOP);
}

AST_T* visitor_visit_variable_definition(visitor_T* visitor, AST_T* node)
{
    scope_add_variable_definition(
        node->scope,
        node        
    ); 

    return node;
}

AST_T* visitor_visit_function_definition(visitor_T* visitor, AST_T* node)
{
    scope_add_function_definition(
        node->scope,
        node        
    );

    return node;
}

AST_T* visitor_visit_variable(visitor_T* visitor, AST_T* node)
{
    AST_T* vdef = scope_get_variable_definition(
        node->scope,
        node->variable_name
    );
    
    if (vdef != (void*) 0)
        return visitor_visit(visitor, vdef->variable_definition_value);

    printf("Undefined variable `%s`\n", node->variable_name);
    exit(1);
}

AST_T* visitor_visit_function_call(visitor_T* visitor, AST_T* node)
{
    if (strcmp(node->function_call_name, "print") == 0)
    {
        return builtin_function_print(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }

    if (strcmp(node->function_call_name, "example") == 0)
    {
        return builtin_function_custom(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }

    if (strcmp(node->function_call_name, "newwindow") == 0)
    {
        return builtin_function_new_window(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }

    if (strcmp(node->function_call_name, "include") == 0)
    {
        return builtin_function_include(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }

    AST_T* fdef = scope_get_function_definition(
        node->scope,
        node->function_call_name
    );

    if (fdef == (void*)0)
    {
        printf("Undefined method `%s`\n", node->function_call_name);
        exit(1);
    }

    for (int i = 0; i < (int) node->function_call_arguments_size; i++)
    {
        // grab the variable from the function definition arguments
        AST_T* ast_var = (AST_T*) fdef->function_definition_args[i];

        // grab the value from the function call arguments
        AST_T* ast_value = (AST_T*) node->function_call_arguments[i];

        // create a new variable definition with the value of the argument
        // in the function call.
        AST_T* ast_vardef = init_ast(AST_VARIABLE_DEFINITION);
        ast_vardef->variable_definition_value = ast_value;

        // copy the name from the function definition argument into the new
        // variable definition
        ast_vardef->variable_definition_variable_name = (char*) calloc(strlen(ast_var->variable_name) + 1, sizeof(char));
        strcpy(ast_vardef->variable_definition_variable_name, ast_var->variable_name);

        // push our variable definition into the function body scope.
        scope_add_variable_definition(fdef->function_definition_body->scope, ast_vardef);
    }
    
    return visitor_visit(visitor, fdef->function_definition_body);
}

AST_T* visitor_visit_string(visitor_T* visitor, AST_T* node)
{
    return node;
}

AST_T* visitor_visit_compound(visitor_T* visitor, AST_T* node)
{
    for (int i = 0; i < node->compound_size; i++)
    {
        visitor_visit(visitor, node->compound_value[i]);
    }

    return init_ast(AST_NOOP);
}
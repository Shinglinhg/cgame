/*
*   Configuration Macros:
*
*   put this in ONE source (.c) file before including this header:
*   #define CGAME_IMPLEMENTATION
*
*   define CG_REQUIRE_PREFIX : Prevents omitting the 'cg' namespace/prefix
*   define NO_LIBC           : Prevents including headers from C's std library (will crash if you don't provide replacements)
*/

#ifndef CGAME_H
#define CGAME_H

#ifndef NO_LIBC
    #include <stdint.h>
    #include <stdbool.h>
    #ifndef RGFW_BOOL_DEFINED
        typedef bool RGFW_bool;
        #define RGFW_BOOL_DEFINED
    #endif
#endif

#ifdef RGFW_MACOS
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#ifdef CGAME_IMPLEMENTATION
    #define RGFW_IMPLEMENTATION
    #define RGFW_OPENGL
#endif

#include "RGFW.h"

typedef RGFW_event cg_Event;
typedef RGFW_glContext cg_GLContext;

typedef struct { float x, y; } cg_vec2;
typedef struct { int x, y; } cg_ivec2;
typedef struct { unsigned x, y; } cg_uvec2;
typedef struct { float x, y, z; } cg_vec3;
typedef struct { int x, y, z; } cg_ivec3;
typedef struct { unsigned x, y, z; } cg_uvec3;

typedef struct {
    bool initialized;
    bool running;
    uint16_t width;
    uint16_t height;
    const char* title;
    RGFW_window* win;
} cg_Window;

typedef struct {
    cg_uvec2 pos;
} cg_MouseState;

typedef struct {
    bool initialized;
    cg_MouseState mouse;
} cg_Input;

typedef struct {
    cg_Window window;
    cg_GLContext* gl_ctx;
    cg_Input input;
    RGFW_event rgfw_event;
    cg_Event* current_event;
} cg_Game;


#ifdef USE_LOCAL_CONTEXT
    #define CONTEXT_ARG_ONLY cg_Game *ctx
    #define CONTEXT_ARG   cg_Game *ctx,
#else
    extern cg_Game *ctx;
    #define CONTEXT_ARG_ONLY void
    #define CONTEXT_ARG   /* nothing */
#endif

#ifdef USE_LOCAL_CONTEXT
    void cg_game_init(CONTEXT_ARG int width, int height, const char* title);
    void cg_window_init(CONTEXT_ARG int width, int height, const char* title);
    void cg_opengl_init(CONTEXT_ARG RGFW_glHints *gl_hints);
    void cg_input_init(CONTEXT_ARG_ONLY);

    void cg_game_deinit(CONTEXT_ARG_ONLY);

    inline bool cg_is_window_open(CONTEXT_ARG_ONLY);

    void cg_begin_frame(CONTEXT_ARG_ONLY);
    void cg_end_frame(CONTEXT_ARG_ONLY);

    inline cg_Event* cg_get_event(CONTEXT_ARG_ONLY);

    inline cg_uvec2 cg_mouse_get_pos(CONTEXT_ARG_ONLY);
    inline unsigned cg_mouse_get_x(CONTEXT_ARG_ONLY);
    inline unsigned cg_mouse_get_y(CONTEXT_ARG_ONLY);
#else // USE_LOCAL_CONTEXT
    void cg_game_init(int width, int height, const char* title);
    void cg_window_init(int width, int height, const char* title);
    void cg_opengl_init(RGFW_glHints *gl_hints);
    void cg_input_init();

    void cg_game_deinit();

    inline bool cg_is_window_open();

    void cg_begin_frame();
    void cg_end_frame();

    inline cg_Event* cg_get_event();

    inline cg_uvec2 cg_mouse_get_pos();
    inline unsigned cg_mouse_get_x();
    inline unsigned cg_mouse_get_y();
#endif // USE_LOCAL_CONTEXT

#ifdef CGAME_IMPLEMENTATION
#   include "cgame_impl.c"
#endif

#endif // CGAME_H
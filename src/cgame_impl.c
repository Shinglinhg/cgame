#ifndef CGAME_IMPLEMENTATION
#include "cgame.h"
#endif

#ifndef USE_LOCAL_CONTEXT
static cg_Game g_global_ctx;
cg_Game* ctx = &g_global_ctx;
#endif

void cg_game_init(CONTEXT_ARG int width, int height, const char* title)
{
    static RGFW_glHints default_hints = { 0 };
    #ifndef USE_LOCAL_CONTEXT
        *ctx = (cg_Game){0};
        cg_window_init(width, height, title);
        cg_opengl_init(&default_hints);
        cg_input_init();
    #else
        cg_window_init(ctx, width, height, title);
        cg_opengl_init(ctx, &default_hints);
        cg_input_init(ctx);
    #endif
}

void cg_window_init(CONTEXT_ARG int width, int height, const char* title)
{
    ctx->window = (cg_Window){
        .initialized = true
    };
    ctx->window.running = true;
    ctx->window.width = width;
    ctx->window.height = height;
    ctx->window.title = title;
    ctx->window.win = RGFW_createWindow(title, 0, 0, width, height, RGFW_windowCenter | RGFW_windowNoResize);
}

void cg_opengl_init(CONTEXT_ARG RGFW_glHints *gl_hints)
{
    ctx->gl_ctx = RGFW_window_createContext_OpenGL(ctx->window.win, gl_hints);
    RGFW_window_makeCurrentContext_OpenGL(ctx->window.win);
}

void cg_input_init(CONTEXT_ARG_ONLY)
{
    ctx->input = (cg_Input){
        .initialized = true,
        .mouse = (cg_MouseState){
            .pos = {0.,0.}
        }
    };
}

void cg_game_deinit(CONTEXT_ARG_ONLY)
{
    ctx->window.running = false;
    RGFW_window_close(ctx->window.win);
}

void cg_begin_frame(CONTEXT_ARG_ONLY)
{
    if (RGFW_window_shouldClose(ctx->window.win) == RGFW_TRUE) {
        ctx->window.running = false;
        return;
    }

    // Update internal game state
    ctx->current_event = RGFW_window_checkEvent(ctx->window.win, &ctx->rgfw_event) == RGFW_TRUE ? (cg_Event*)&ctx->rgfw_event : NULL;
    RGFW_window_getMouse(ctx->window.win, (int*)&ctx->input.mouse.pos.x, (int*)&ctx->input.mouse.pos.y);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void cg_end_frame(CONTEXT_ARG_ONLY)
{
    RGFW_window_swapBuffers_OpenGL(ctx->window.win);
    glFlush();
}

bool cg_is_window_open(CONTEXT_ARG_ONLY) { return ctx->window.running; }
cg_Event* cg_get_event(CONTEXT_ARG_ONLY) { return ctx->current_event; }

cg_uvec2 cg_mouse_get_pos(CONTEXT_ARG_ONLY) { return ctx->input.mouse.pos; }
unsigned cg_mouse_get_x(CONTEXT_ARG_ONLY) { return ctx->input.mouse.pos.x; }
unsigned cg_mouse_get_y(CONTEXT_ARG_ONLY) { return ctx->input.mouse.pos.y; }

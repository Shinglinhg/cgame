#define CGAME_IMPLEMENTATION // since it is a single header library
#include <cgame.h>

int main() {
    cg_game_init(1280, 720, "Hello, world"); // call the "contsructor"

    while (cg_is_window_open()) {
        cg_begin_frame();

        cg_Event* event = cg_get_event();
        if (event) {
            if (event->type == RGFW_mouseButtonPressed && event->button.value == RGFW_mouseLeft) {
                printf("You clicked at x: %d, y: %d\n", cg_mouse_get_x(), cg_mouse_get_y());
            }
        }

        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
            glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
            glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
        glEnd();

        cg_end_frame();
    }
    cg_game_deinit();
    return 0;
}
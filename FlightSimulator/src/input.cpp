#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"
#include "airplane.h"

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        // switch (key) {
        // case GLFW_KEY_C:
        // rectangle_rot_status = !rectangle_rot_status;
        // break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        //// do something ..
        // break;
        // default:
        // break;
        // }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
    case 'Q':
    case 'q':
        quit(window);
        break;
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            click_status=click::BOMB;
            system("aplay -c 1 -t wav -q sound/Arrow+Swoosh+1.wav&");
            return;
        }
        else if (action == GLFW_RELEASE) {
            click_status=click::NOTHING; 
        }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        if (action == GLFW_PRESS) {
            click_status=click::MISSILE;
            system("aplay -c 1 -t wav -q sound/Arrow+Swoosh+1.wav&");
            return;
        }
        else if (action == GLFW_RELEASE) {
            click_status=click::NOTHING;
        }
        break;
    default:
        break;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if(yoffset == 1)
    {
        screen_zoom += 0.1;
        screen_zoom = min(4.0f,screen_zoom);
    }
    else if(yoffset == -1)
    {
        screen_zoom -= 0.1;
        screen_zoom = max(0.5f,screen_zoom);
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    glm::vec3 cursor_position(xpos,ypos,0);
    // printf("x:%lf,y:%lf\n",xpos,ypos);
    cursor_position_x=xpos;
    cursor_position_y=ypos;
}
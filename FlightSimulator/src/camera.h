#include "main.h"

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
    Camera() {}
    Camera(glm::vec3 position);
    void change();
    bool changing;
    glm::vec3 eye,target,up;
    float angle;
    int mode;
    void tick(glm::vec3 position,float rotation,float roll);
};

#endif // CAMERA_H
#include "main.h"

class Display {
public:
    Display() {}
    Display(int n,glm::vec3 pos);
    void update(int n){this->n=n;}
    glm::vec3 position;
    void draw();
    int n;
private:
    VAO *up;
    VAO *middle;
    VAO *down;
    VAO *upleft;
    VAO *upright;
    VAO *downleft;
    VAO *downright;
};

Display::Display(int n,glm::vec3 pos) {
    this->position = pos;
    this->n = n;
    float length=0.06;
    GLfloat vertex_buffer_data_up[]= {
        0*length,2*length,0,
        1*length,2*length,0,
    };
    
    GLfloat vertex_buffer_data_middle[]= {
        0*length,1*length,0,
        1*length,1*length,0,
    };

    GLfloat vertex_buffer_data_down[]= {
        0*length,0*length,0,
        1*length,0*length,0,
    };

    GLfloat vertex_buffer_data_upright[]= {
        1*length,1*length,0,
        1*length,2*length,0,
    };

    GLfloat vertex_buffer_data_upleft[]= {
        0*length,1*length,0,
        0*length,2*length,0,
    };

    GLfloat vertex_buffer_data_downleft[]= {
        0*length,0*length,0,
        0*length,1*length,0,
    };

    GLfloat vertex_buffer_data_downright[]= {
        1*length,0*length,0,
        1*length,1*length,0,
    };

    this->up = create3DObject(GL_LINES, 2, vertex_buffer_data_up, COLOR_BLACK, GL_FILL);
    this->middle = create3DObject(GL_LINES, 2, vertex_buffer_data_middle, COLOR_BLACK, GL_FILL);
    this->down = create3DObject(GL_LINES, 2, vertex_buffer_data_down, COLOR_BLACK, GL_FILL);

    this->upright = create3DObject(GL_LINES, 2, vertex_buffer_data_upright, COLOR_BLACK, GL_FILL);
    this->upleft = create3DObject(GL_LINES, 2, vertex_buffer_data_upleft, COLOR_BLACK, GL_FILL);
    this->downleft = create3DObject(GL_LINES, 2, vertex_buffer_data_downleft, COLOR_BLACK, GL_FILL);
    this->downright = create3DObject(GL_LINES, 2, vertex_buffer_data_downright, COLOR_BLACK, GL_FILL);
}

void Display::draw() {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP =  Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->n==2||this->n==3||this->n==5||this->n==6||this->n==7||this->n==8||this->n==9||this->n==0)
        draw3DObject(this->up);
    if(this->n==2||this->n==3||this->n==4||this->n==5||this->n==6||this->n==8||this->n==9)
        draw3DObject(this->middle);
    if(this->n==2||this->n==3||this->n==5||this->n==6||this->n==8||n==0)
        draw3DObject(this->down);
    if(this->n==1||this->n==2||this->n==3||this->n==4||this->n==7||this->n==8||this->n==9||this->n==0)
        draw3DObject(this->upright);
    if(this->n==4||this->n==5||this->n==6||this->n==8||this->n==9||this->n==0)
        draw3DObject(this->upleft);
    if(this->n==2||this->n==6||this->n==8||this->n==0)
        draw3DObject(this->downleft);
    if(this->n==1||this->n==3||this->n==4||this->n==5||this->n==6||this->n==7||this->n==8||this->n==9||this->n==0)
        draw3DObject(this->downright);
}

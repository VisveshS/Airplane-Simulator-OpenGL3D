#include "main.h"

#ifndef EXPLOSION_H
#define EXPLOSION_H

class Explosion {
public:
	Explosion() {}
	double explosion_instant;
	float dimension;
	float size;
	Explosion(glm::vec3 position,color_t color)
	{
	    this->explosion_instant=glfwGetTime();
    	// system("aplay -c 1 -t wav -q sound/Explosion+7.wav&");
    	this->position=position;
		this->dimension=1;
		this->size=0.1;
		int n=10;
	    GLfloat vertex_buffer_data[200];
	    for(int i=0;i<n;i++)
	    {
	    	vertex_buffer_data[i*9+0]=cos(2*(i*2)*M_PI/n);    	vertex_buffer_data[i*9+1]=sin(2*(i*2)*M_PI/n);    	vertex_buffer_data[i*9+2]=0.5;
	    	vertex_buffer_data[i*9+3]=cos(2*(i*2+1)*M_PI/n);    	vertex_buffer_data[i*9+4]=sin(2*(i*2+1)*M_PI/n);    	vertex_buffer_data[i*9+5]=0.5;
	    	vertex_buffer_data[i*9+6]=0;			    	vertex_buffer_data[i*9+7]=0;			    	vertex_buffer_data[i*9+8]=0;
	    }
    	for(int i=0;i<9*n;i++)
    		vertex_buffer_data[i]*=dimension;
		this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
	}
	glm::vec3 position;
	void draw(glm::mat4 VP) {
		Matrices.model = glm::mat4(1.0f);
		glm::mat4 translate = glm::translate (this->position);
		glm::mat4 scale = glm::scale (V(size,size,size));
		Matrices.model *= translate*scale;
		glm::mat4 MVP = VP * Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(this->object);
	}
	void tick()
	{
		size+=0.3;
	}
private:
	VAO *object;
};

#endif // EXPLOSION_H
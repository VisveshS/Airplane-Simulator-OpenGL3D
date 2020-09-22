#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H
#define dimensions 0.2

class Missile {
public:
	Missile() {}
	Missile(glm::vec3 position,float angle)
	{
		float speed = 1;
		this->position=position;
		this->velocity=V(speed*cos(angle*M_PI/180.0),speed*sin(angle*M_PI/180.0),-0.2);
	    GLfloat vertex_buffer_data[220];
	    color_t ballcolor=COLOR_YELLOW;int j,n=10;

		for(int i=0;i<=n;i++){j=i*2;j*=3;	vertex_buffer_data[j+0]=0*cos(i*2*M_PI/n);		vertex_buffer_data[j+1]=0*sin(i*2*M_PI/n);		vertex_buffer_data[j+2]=1;}
		for(int i=0;i<=n;i++){j=i*2+1;j*=3;	vertex_buffer_data[j+0]=sqrt(0.5)*cos(i*2*M_PI/n);	vertex_buffer_data[j+1]=sqrt(0.5)*sin(i*2*M_PI/n);	vertex_buffer_data[j+2]=sqrt(0.5);}
		for(int i=0;i<3*2*(n+1);i++)		vertex_buffer_data[i]*=dimensions*1;
		this->object[0]=create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, ballcolor, GL_FILL);

		for(int i=0;i<=n;i++){j=i*2;j*=3;	vertex_buffer_data[j+0]=sqrt(0.5)*cos(i*2*M_PI/n);		vertex_buffer_data[j+1]=sqrt(0.5)*sin(i*2*M_PI/n);		vertex_buffer_data[j+2]=sqrt(0.5);}
		for(int i=0;i<=n;i++){j=i*2+1;j*=3;	vertex_buffer_data[j+0]=cos(i*2*M_PI/n);	vertex_buffer_data[j+1]=sin(i*2*M_PI/n);	vertex_buffer_data[j+2]=0;}
		for(int i=0;i<3*2*(n+1);i++)		vertex_buffer_data[i]*=dimensions*1;
		this->object[1]=create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, ballcolor, GL_FILL);

		for(int i=0;i<=n;i++){j=i*2;j*=3;	vertex_buffer_data[j+0]=cos(i*2*M_PI/n);		vertex_buffer_data[j+1]=sin(i*2*M_PI/n);		vertex_buffer_data[j+2]=0;}
		for(int i=0;i<=n;i++){j=i*2+1;j*=3;	vertex_buffer_data[j+0]=sqrt(0.5)*cos(i*2*M_PI/n);	vertex_buffer_data[j+1]=sqrt(0.5)*sin(i*2*M_PI/n);	vertex_buffer_data[j+2]=-sqrt(0.5);}
		for(int i=0;i<3*2*(n+1);i++)		vertex_buffer_data[i]*=dimensions*1;//1.5	
		this->object[2]=create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, ballcolor, GL_FILL);

		for(int i=0;i<=n;i++){j=i*2;j*=3;	vertex_buffer_data[j+0]=sqrt(0.5)*cos(i*2*M_PI/n);		vertex_buffer_data[j+1]=sqrt(0.5)*sin(i*2*M_PI/n);		vertex_buffer_data[j+2]=-sqrt(0.5);}
		for(int i=0;i<=n;i++){j=i*2+1;j*=3;	vertex_buffer_data[j+0]=0*cos(i*2*M_PI/n);	vertex_buffer_data[j+1]=0*sin(i*2*M_PI/n);	vertex_buffer_data[j+2]=-1;}
		for(int i=0;i<3*2*(n+1);i++)		vertex_buffer_data[i]*=dimensions*1;
		this->object[3]=create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, ballcolor, GL_FILL);
	}
	glm::vec3 position,velocity;
	void draw(glm::mat4 VP) {
		Matrices.model = glm::mat4(1.0f);
		glm::mat4 translate = glm::translate (this->position);
		Matrices.model *= translate;
		glm::mat4 MVP = VP * Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		for(int i=0;i<4;i++)draw3DObject(this->object[i]);
	}
	void tick()
	{
		float gravity=0.01;
		this->position+=this->velocity;
		this->velocity-=V(0,0,gravity);
	}
private:
	VAO *object[4];
};

#endif // MISSILE_H
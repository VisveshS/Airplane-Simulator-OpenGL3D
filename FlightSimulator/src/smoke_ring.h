#include "main.h"

#ifndef SMOKE_RING_H
#define SMOKE_RING_H
#define dimensions 0.2

class SmokeRing {
public:
	SmokeRing(){}
	glm::vec3 position;
	float angle;
	color_t color;
	bool redeemed=false;
	bool inring=false;
	SmokeRing(glm::vec3 position,float angle,color_t color)
	{
		this->position=position;
		this->angle=angle;
		this->color=color;
		this->constructRing();
	}
	void constructRing()
	{
		GLfloat vertex_buffer_data[500];
		int i,n=60,j;
		for(int i=0;i<=n;i++)
		{
			j=i*2;
			j*=3;
			vertex_buffer_data[j+0]=cos(i*2*M_PI/n);
			vertex_buffer_data[j+1]=sin(i*2*M_PI/n);
			vertex_buffer_data[j+2]=0;
		}
		for(int i=0;i<=n;i++)
		{
			j=i*2+1;
			j*=3;
			vertex_buffer_data[j+0]=0.8*cos(i*2*M_PI/n);
			vertex_buffer_data[j+1]=0.8*sin(i*2*M_PI/n);
			vertex_buffer_data[j+2]=0.1;
		}
		this->object[0] = create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, color, GL_FILL);	
		for(int i=0;i<=n;i++)
		{
			j=i*2;
			j*=3;
			vertex_buffer_data[j+0]=cos(i*2*M_PI/n);
			vertex_buffer_data[j+1]=sin(i*2*M_PI/n);
			vertex_buffer_data[j+2]=0;
		}
		for(int i=0;i<=n;i++)
		{
			j=i*2+1;
			j*=3;
			vertex_buffer_data[j+0]=0.8*cos(i*2*M_PI/n);
			vertex_buffer_data[j+1]=0.8*sin(i*2*M_PI/n);
			vertex_buffer_data[j+2]=-0.1;
		}
		this->object[1] = create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, color, GL_FILL);
	}
	void draw(glm::mat4 VP)
	{
		Matrices.model = glm::mat4(1.0f);
		glm::mat4 translate = glm::translate (this->position);
		glm::mat4 rotate = glm::rotate ((float)(this->angle*M_PI/180.0f),V(0,0,1))*glm::rotate ((float)(M_PI/2.0f),V(1,0,0));
		Matrices.model *= (translate*rotate);
		glm::mat4 MVP = VP * Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		if(!this->redeemed)
		{
			draw3DObject(this->object[0]);
			draw3DObject(this->object[1]);
		}
	}
	bool tick(glm::vec3 player_pos)
	{
		if(this->redeemed)return false;
		glm::vec3 diff =this->position-player_pos,radius=V(-sin(this->angle*M_PI/180),cos(this->angle*M_PI/180),0),normal=V(cos(this->angle*M_PI/180),sin(this->angle*M_PI/180),0);	
		if(abs(dot(diff,radius))<1&&abs(dot(diff,normal))<0.4&&!this->redeemed)
		{this->inring=true;}
		if(this->inring&&!(dot(diff,radius)<1&&dot(diff,normal)<0.4))
		{	this->redeemed=true;printf("RING\n");return true;}
		return false;
	}

private:
	VAO *object[3];
};
#endif // SMOKE_RING_H
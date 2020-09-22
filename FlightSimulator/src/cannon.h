#include "main.h"
#include "explosion.h"

#ifndef CANNON_H
#define CANNON_H
#define dimensions 0.2

class Cannon {
public:
	Cannon() {}
	bool shoot;
	Cannon(glm::vec3 position)
	{
		this->shoot=false;
		this->position=position;
		GLfloat vertex_buffer_data[500];
		int j,n=60;
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
			vertex_buffer_data[j+0]=0.6*cos(i*2*M_PI/n);
			vertex_buffer_data[j+1]=0.6*sin(i*2*M_PI/n);
			vertex_buffer_data[j+2]=14;
		}
		for(int i=0;i<3*2*(n+1);i++)
			vertex_buffer_data[i]*=dimensions;
		this->object = create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, COLOR_DARKGRAY, GL_FILL);

		for(int i=0;i<=n;i++)
		{
			j=i*2;
			j*=3;
			vertex_buffer_data[j+0]=0.3*cos(i*2*M_PI/n);
			vertex_buffer_data[j+1]=0.3*sin(i*2*M_PI/n);
			vertex_buffer_data[j+2]=14;
		}

		for(int i=0;i<=n;i++)
		{
			j=i*2+1;
			j*=3;
			vertex_buffer_data[j+0]=0.6*cos(i*2*M_PI/n);
			vertex_buffer_data[j+1]=0.6*sin(i*2*M_PI/n);
			vertex_buffer_data[j+2]=14;
		}

		for(int i=0;i<3*2*(n+1);i++)
			vertex_buffer_data[i]*=dimensions;
		this->rim = create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, COLOR_BLACK, GL_FILL);
		this->Cannonball();
		this->shoottime=glfwGetTime();
	}
	void Cannonball()
	{
		int n=10,j;
		color_t ballcolor=COLOR_DARKGRAY;
		GLfloat vertex_buffer_data[220];

		for(int i=0;i<=n;i++){j=i*2;j*=3;	vertex_buffer_data[j+0]=0*cos(i*2*M_PI/n);		vertex_buffer_data[j+1]=0*sin(i*2*M_PI/n);		vertex_buffer_data[j+2]=1;}
		for(int i=0;i<=n;i++){j=i*2+1;j*=3;	vertex_buffer_data[j+0]=sqrt(0.5)*cos(i*2*M_PI/n);	vertex_buffer_data[j+1]=sqrt(0.5)*sin(i*2*M_PI/n);	vertex_buffer_data[j+2]=sqrt(0.5);}
		for(int i=0;i<3*2*(n+1);i++)		vertex_buffer_data[i]*=dimensions*1.5;
		this->cannonball[0]=create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, ballcolor, GL_FILL);
			
		for(int i=0;i<=n;i++){j=i*2;j*=3;	vertex_buffer_data[j+0]=sqrt(0.5)*cos(i*2*M_PI/n);		vertex_buffer_data[j+1]=sqrt(0.5)*sin(i*2*M_PI/n);		vertex_buffer_data[j+2]=sqrt(0.5);}
		for(int i=0;i<=n;i++){j=i*2+1;j*=3;	vertex_buffer_data[j+0]=cos(i*2*M_PI/n);	vertex_buffer_data[j+1]=sin(i*2*M_PI/n);	vertex_buffer_data[j+2]=0;}
		for(int i=0;i<3*2*(n+1);i++)		vertex_buffer_data[i]*=dimensions*1.5;
		this->cannonball[1]=create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, ballcolor, GL_FILL);

		for(int i=0;i<=n;i++){j=i*2;j*=3;	vertex_buffer_data[j+0]=cos(i*2*M_PI/n);		vertex_buffer_data[j+1]=sin(i*2*M_PI/n);		vertex_buffer_data[j+2]=0;}
		for(int i=0;i<=n;i++){j=i*2+1;j*=3;	vertex_buffer_data[j+0]=sqrt(0.5)*cos(i*2*M_PI/n);	vertex_buffer_data[j+1]=sqrt(0.5)*sin(i*2*M_PI/n);	vertex_buffer_data[j+2]=-sqrt(0.5);}
		for(int i=0;i<3*2*(n+1);i++)		vertex_buffer_data[i]*=dimensions*1.5;//1.5	
		this->cannonball[2]=create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, ballcolor, GL_FILL);

		for(int i=0;i<=n;i++){j=i*2;j*=3;	vertex_buffer_data[j+0]=sqrt(0.5)*cos(i*2*M_PI/n);		vertex_buffer_data[j+1]=sqrt(0.5)*sin(i*2*M_PI/n);		vertex_buffer_data[j+2]=-sqrt(0.5);}
		for(int i=0;i<=n;i++){j=i*2+1;j*=3;	vertex_buffer_data[j+0]=0*cos(i*2*M_PI/n);	vertex_buffer_data[j+1]=0*sin(i*2*M_PI/n);	vertex_buffer_data[j+2]=-1;}
		for(int i=0;i<3*2*(n+1);i++)		vertex_buffer_data[i]*=dimensions*1.5;
		this->cannonball[3]=create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, ballcolor, GL_FILL);
	}
	glm::vec3 position;
	double shoottime;
	void update(glm::vec3 newpos) {
		this->position=newpos;
	}
	float arctan(float opp,float adj)
	{
		float offset=0;
		if(opp+adj<0)offset=M_PI;
		if(abs(adj)>=abs(opp))
			return(atan(opp/adj)+offset);
		else
			return(M_PI/2-atan(adj/opp)+offset);
	}
	void draw(glm::mat4 VP,glm::vec3 player_pos) {
		Matrices.model = glm::mat4(1.0f);
		glm::mat4 translate = glm::translate (this->position);
		float theta_z,theta_x,xy;
		xy=sqrt(pow(player_pos.x,2)+pow(player_pos.y,2));
		theta_z=arctan(player_pos.x,player_pos.y)+M_PI;
		theta_x=arctan(xy,player_pos.z);
		glm::mat4 rotate=glm::rotate((float)(theta_z),V(0,0,-1))*glm::rotate((float)(theta_x),V(1,0,0));
		Matrices.model = translate*rotate;
		glm::mat4 MVP = VP * Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(this->object);
		draw3DObject(this->rim);
		// Matrices.model *= glm::translate(V(0,0,3));
	}
	glm::vec3 ballposition,ballvelocity,initpos;
	void fire(glm::vec3 cannon_pos,glm::vec3 player_pos)
	{
		return;
		if(player_pos.z==0)
			return;
		this->shoot=true;
		this->initpos=cannon_pos;
    	system("aplay -c 1 -t wav -q sound/Cannon+3.wav&");
		printf("FIRE\n");
		this->ballposition=cannon_pos;
		float scale=1;
		player_pos.x*=scale;player_pos.y*=scale;player_pos.z*=scale;
		this->ballvelocity=player_pos;
	}
	bool tick(glm::mat4 VP,glm::vec3 player_pos)
	{
		bool retval;
		if(!this->shoot)
			return false;
		float gravity = 0.001;
		Matrices.model = glm::mat4(1.0f);
		glm::mat4 MVP = VP *Matrices.model* glm::translate(this->ballposition);//*glm::translate(V(0,0,3));
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		for(int i=0;i<4;i++) draw3DObject(this->cannonball[i]);
		ballposition+=ballvelocity;
		float Offset=0.0;
		if(false and abs(this->ballposition.x-player_pos.x)<Offset&&abs(this->ballposition.y-player_pos.y)<Offset&&abs(this->ballposition.z-player_pos.z)<Offset)
		{	printf("COLLIDE\n");retval=true;}
		glm::vec3 diff=this->ballposition-this->initpos;
		if(sqrt(pow(diff.x,2)+pow(diff.y,2)+pow(diff.z,2))>200)
			this->shoot=false;
		return retval;
	}

private:
	VAO *object;
	VAO *rim;
	VAO *cannonball[4];
};
#endif // CANNON_H

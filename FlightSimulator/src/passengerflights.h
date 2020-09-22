#include "main.h"

#ifndef PAss_H
#define PAss_H
float dimension=0.7;
class Passenger {
	public:
		glm::vec3 position,velocity;
		float angle;
		Passenger(){}
		Passenger(bool dummy){
			float theta=rand()%360;
			this->angle=(float)(theta*M_PI/180)-M_PI;
			float Cos=cos((float)(theta*M_PI/180));
			float Sin=sin((float)(theta*M_PI/180));
			float alt=rand()%10+9;
			this->position=V(170*sqrt(2)*Cos,170*sqrt(2)*Sin,float(alt));
			this->velocity=V(-0.1*Cos,0.1*-Sin,0);
			this->construct();
		}
		bool collision(glm::vec3 player_pos){
			glm::vec3 diff=player_pos-this->position;
			float size=3;
			if(abs(diff.x)<1*size&&abs(diff.y)<1*size&&abs(diff.z)<0.3*size)
				return true;
			return false;
		}
		void tick()
		{
			this->position+=this->velocity;
		}
		void draw(glm::mat4 VP) {
			Matrices.model = glm::mat4(1.0f);
			glm::mat4 translate = glm::translate (this->position);
			glm::mat4 rotate = glm::rotate (this->angle,V(0,0,1));
			Matrices.model *= (translate*rotate);
			glm::mat4 MVP = VP * Matrices.model;
			glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
			draw3DObject(this->object);
	}		
	void construct() 
	{ 
		GLfloat vertex_buffer_data[1000];
		GLfloat color_buffer_data[1000];
		int n=51,n1=51;
		for(int i=0;i<n;i++)
		{
			vertex_buffer_data[0+9*i]=0;
			vertex_buffer_data[1+9*i]=sin(9*i*M_PI/n);
			vertex_buffer_data[2+9*i]=cos(9*i*M_PI/n);

			vertex_buffer_data[3+9*i]=0;
			vertex_buffer_data[4+9*i]=sin(9*(i+1)*M_PI/n);
			vertex_buffer_data[5+9*i]=cos(9*(i+1)*M_PI/n);

			vertex_buffer_data[6+9*i]=-8;
			vertex_buffer_data[7+9*i]=0;
			vertex_buffer_data[8+9*i]=1.2;
		}
		for(int i=0;i<n1;i++)
		{
			vertex_buffer_data[n*9+0+9*i]=0;
			vertex_buffer_data[n*9+1+9*i]=sin(9*i*M_PI/n1);
			vertex_buffer_data[n*9+2+9*i]=cos(9*i*M_PI/n1);

			vertex_buffer_data[n*9+3+9*i]=0;
			vertex_buffer_data[n*9+4+9*i]=sin(9*(i+1)*M_PI/n1);
			vertex_buffer_data[n*9+5+9*i]=cos(9*(i+1)*M_PI/n1);

			vertex_buffer_data[n*9+6+9*i]=3;
			vertex_buffer_data[n*9+7+9*i]=0;
			vertex_buffer_data[n*9+8+9*i]=-0.45;
		}
		//wing	
		vertex_buffer_data[9*(n1+n)+0]=0;
		vertex_buffer_data[9*(n1+n)+1]=0;
		vertex_buffer_data[9*(n1+n)+2]=0.3;

		vertex_buffer_data[9*(n1+n)+3]=-2;
		vertex_buffer_data[9*(n1+n)+4]=-8;
		vertex_buffer_data[9*(n1+n)+5]=0.3;
		
		vertex_buffer_data[9*(n1+n)+6]=-2;
		vertex_buffer_data[9*(n1+n)+7]=8;
		vertex_buffer_data[9*(n1+n)+8]=0.3;


		vertex_buffer_data[9*(n1+n+1)+0]=-8;
		vertex_buffer_data[9*(n1+n+1)+1]=0;
		vertex_buffer_data[9*(n1+n+1)+2]=1.1;

		vertex_buffer_data[9*(n1+n+1)+3]=-7;
		vertex_buffer_data[9*(n1+n+1)+4]=0;
		vertex_buffer_data[9*(n1+n+1)+5]=1.1;
		
		vertex_buffer_data[9*(n1+n+1)+6]=-8;
		vertex_buffer_data[9*(n1+n+1)+7]=0;
		vertex_buffer_data[9*(n1+n+1)+8]=2.6;


		vertex_buffer_data[9*(n1+n+2)+0]=-7.33;
		vertex_buffer_data[9*(n1+n+2)+1]=0;
		vertex_buffer_data[9*(n1+n+2)+2]=1.6;

		vertex_buffer_data[9*(n1+n+2)+3]=-8;
		vertex_buffer_data[9*(n1+n+2)+4]=2;
		vertex_buffer_data[9*(n1+n+2)+5]=1.6;
		
		vertex_buffer_data[9*(n1+n+2)+6]=-8;
		vertex_buffer_data[9*(n1+n+2)+7]=-2;
		vertex_buffer_data[9*(n1+n+2)+8]=1.6;


		vertex_buffer_data[9*(n1+n+1)+0]=-8;
		vertex_buffer_data[9*(n1+n+1)+1]=0;
		vertex_buffer_data[9*(n1+n+1)+2]=2.6;

		vertex_buffer_data[9*(n1+n+1)+0]=-8;
		vertex_buffer_data[9*(n1+n+1)+1]=0.1;
		vertex_buffer_data[9*(n1+n+1)+2]=1.1;

		vertex_buffer_data[9*(n1+n+1)+0]=-8;
		vertex_buffer_data[9*(n1+n+1)+1]=-0.1;
		vertex_buffer_data[9*(n1+n+1)+2]=1.1;

		float r=float(rand()%100)/100,g=float(rand()%100)/100,b=float(rand()%100)/100;
		for(int i=0;i<3*n;i++)
		{
			if(i%3==2)
			{
				color_buffer_data[i*3+0]=float(COLOR_BLACK.r/255.0f);
				color_buffer_data[i*3+1]=float(COLOR_BLACK.g/255.0f);;
				color_buffer_data[i*3+2]=float(COLOR_BLACK.b/255.0f);
			}
			else
			{
				color_buffer_data[i*3+0]=float(COLOR_LIGHTGRAY.r/255.0f)*r;
				color_buffer_data[i*3+1]=float(COLOR_LIGHTGRAY.g/255.0f)*g;
				color_buffer_data[i*3+2]=float(COLOR_LIGHTGRAY.b/255.0f)*b;
			}
		}
		for(int i=0;i<3*n1;i++)
		{
			if(i%3==2)
			{
				color_buffer_data[9*n+i*3+0]=float(COLOR_WHITE.r/255.0f)*r;
				color_buffer_data[9*n+i*3+1]=float(COLOR_WHITE.g/255.0f)*g;
				color_buffer_data[9*n+i*3+2]=float(COLOR_WHITE.b/255.0f)*b;
			}
			else
			{
				color_buffer_data[9*n+i*3+0]=float(COLOR_LIGHTGRAY.r/255.0f)*r;
				color_buffer_data[9*n+i*3+1]=float(COLOR_LIGHTGRAY.g/255.0f)*g;
				color_buffer_data[9*n+i*3+2]=float(COLOR_LIGHTGRAY.b/255.0f)*b;
			}		
		}

		for(int i=0;i<9;i++)
			color_buffer_data[i+9*(n1+n)]=float(COLOR_LIGHTGRAY.r/255.0f);

		for(int i=0;i<9;i++)
			color_buffer_data[i+9*(n1+n+1)]=float(COLOR_DARKGRAY.r/255.0f);

		for(int i=0;i<9;i++)
			color_buffer_data[i+9*(n1+n+2)]=float(COLOR_DARKGRAY.r/255.0f);

		for(int i=0;i<9;i++)
			color_buffer_data[i+9*(n1+n+3)]=float(COLOR_DARKGRAY.r/255.0f);

		for(int j=0;j<9*(n+n1+4);j++)
		{
			vertex_buffer_data[j]*=dimension;
		}
		this->object = create3DObject(GL_TRIANGLES, (n+n1+4)*3 ,vertex_buffer_data, color_buffer_data, GL_FILL);		
	}
	private:
		VAO *object;
};
#endif
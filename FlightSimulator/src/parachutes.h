#include "main.h"

#ifndef PAR_H
#define PAR_H
#define graviti 0.0005
class Parachute {
	public:
		float speed;
		glm::vec3 position;
		Parachute(){}
		Parachute(glm::vec3 position){
			this->position=position;
			this->speed=0;
			this->construct();
		}
		bool collision(glm::vec3 missile_pos){
			glm::vec3 diff=missile_pos-this->position;
			float size=3;
			if(abs(diff.x)<0.5*size&&abs(diff.y)<0.5*size&&abs(diff.z)<0.5*size)
				return true;
			return false;
		}
		void tick()
		{
			this->position.z+=this->speed;
			this->speed-=graviti;
		}
		void draw(glm::mat4 VP) {
			Matrices.model = glm::mat4(1.0f);
			glm::mat4 translate = glm::translate (this->position);
			Matrices.model *= translate;
			glm::mat4 MVP = VP * Matrices.model;
			glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
			for(int i=0;i<2;i++)draw3DObject(this->object[i]);
			draw3DObject(this->strings);
	}		
		void construct(){
	    GLfloat vertex_buffer_data[520];
	    color_t ballcolor=COLOR_YELLOW;int j,n=60;
	    float dimensionss=1;

		for(int i=0;i<=n;i++){j=i*2;j*=3;	vertex_buffer_data[j+0]=0*cos(i*2*M_PI/n);		vertex_buffer_data[j+1]=0*sin(i*2*M_PI/n);		vertex_buffer_data[j+2]=1;}
		for(int i=0;i<=n;i++){j=i*2+1;j*=3;	vertex_buffer_data[j+0]=sqrt(0.5)*cos(i*2*M_PI/n);	vertex_buffer_data[j+1]=sqrt(0.5)*sin(i*2*M_PI/n);	vertex_buffer_data[j+2]=sqrt(0.5);}
		for(int i=0;i<3*2*(n+1);i++)		vertex_buffer_data[i]*=dimensionss*1;
		this->object[0]=create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, ballcolor, GL_FILL);

		for(int i=0;i<=n;i++){j=i*2;j*=3;	vertex_buffer_data[j+0]=sqrt(0.5)*cos(i*2*M_PI/n);		vertex_buffer_data[j+1]=sqrt(0.5)*sin(i*2*M_PI/n);		vertex_buffer_data[j+2]=sqrt(0.5);}
		for(int i=0;i<=n;i++){j=i*2+1;j*=3;	vertex_buffer_data[j+0]=cos(i*2*M_PI/n);	vertex_buffer_data[j+1]=sin(i*2*M_PI/n);	vertex_buffer_data[j+2]=0;}
		for(int i=0;i<3*2*(n+1);i++)		vertex_buffer_data[i]*=dimensionss*1;
		this->object[1]=create3DObject(GL_TRIANGLE_STRIP, 2*(n+1), vertex_buffer_data, ballcolor, GL_FILL);

		vertex_buffer_data[0]=1;vertex_buffer_data[1]=0;vertex_buffer_data[2]=0;
		vertex_buffer_data[3]=0;vertex_buffer_data[4]=0;vertex_buffer_data[5]=-1;

		vertex_buffer_data[6]=-0.5;vertex_buffer_data[7]=sqrt(3)/2;vertex_buffer_data[8]=0;
		vertex_buffer_data[9]=0;vertex_buffer_data[10]=0;vertex_buffer_data[11]=-1;

		vertex_buffer_data[12]=-0.5;vertex_buffer_data[13]=-sqrt(3)/2;vertex_buffer_data[14]=0;
		vertex_buffer_data[15]=0;vertex_buffer_data[16]=0;vertex_buffer_data[17]=-1;

		this->strings=create3DObject(GL_LINES, 6, vertex_buffer_data, COLOR_BLACK, GL_FILL);
		}
	private:
		VAO *object[2];
		VAO *strings;
};
#endif
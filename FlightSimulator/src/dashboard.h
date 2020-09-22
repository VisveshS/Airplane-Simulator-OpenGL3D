#include "main.h"
#include "digits.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H

struct Compass
{
	VAO *circle;
	VAO *needle;
};

class Dashboard {
public:
	Dashboard() {}
	float altitude,fuel,speed,rotation,health;
	Display n1,n2,N;
	Dashboard(float altitude,float fuel,float speed,float rotation,float health)
	{
		GLfloat vertex_buffer_data[500];

		vertex_buffer_data[0]=0;vertex_buffer_data[1]=0;vertex_buffer_data[2]=0;
		vertex_buffer_data[3]=0.8;vertex_buffer_data[4]=0.4;vertex_buffer_data[5]=0;
		vertex_buffer_data[6]=0;vertex_buffer_data[7]=0.4;vertex_buffer_data[8]=0;

		vertex_buffer_data[9]=0;vertex_buffer_data[10]=0;vertex_buffer_data[11]=0;
		vertex_buffer_data[12]=0.8;vertex_buffer_data[13]=0.4;vertex_buffer_data[14]=0;
		vertex_buffer_data[15]=0.8;vertex_buffer_data[16]=0;vertex_buffer_data[17]=0;
		int n=31;
		for(int i=2;i<n+2;i++)
		{
			vertex_buffer_data[9*i+0]=0.2*cos(2*i*M_PI/n)+0.2;
			vertex_buffer_data[9*i+1]=0.2*sin(2*i*M_PI/n)+0.4;
			vertex_buffer_data[9*i+2]=0;
			
			vertex_buffer_data[9*i+3]=0.2*cos(2*(i+1)*M_PI/n)+0.2;
			vertex_buffer_data[9*i+4]=0.2*sin(2*(i+1)*M_PI/n)+0.4;
			vertex_buffer_data[9*i+5]=0;

			vertex_buffer_data[9*i+6]=0.2;
			vertex_buffer_data[9*i+7]=0.4;
			vertex_buffer_data[9*i+8]=0;   	
		}
		this->object = create3DObject(GL_TRIANGLES, (n+2)*3, vertex_buffer_data, COLOR_LIGHTGRAY, GL_FILL);
		vertex_buffer_data[0]=0;
		vertex_buffer_data[1]=0;
		vertex_buffer_data[2]=0;
		
		vertex_buffer_data[3]=-0.18;
		vertex_buffer_data[4]=0;
		vertex_buffer_data[5]=0;

		vertex_buffer_data[6]=-0.18;
		vertex_buffer_data[7]=0;
		vertex_buffer_data[8]=0;

		vertex_buffer_data[9]=-0.16;
		vertex_buffer_data[10]=0.02;
		vertex_buffer_data[11]=0;

		vertex_buffer_data[12]=-0.18;
		vertex_buffer_data[13]=0;
		vertex_buffer_data[14]=0;

		vertex_buffer_data[15]=-0.16;
		vertex_buffer_data[16]=-0.02;
		vertex_buffer_data[17]=0;
		this->needle = create3DObject(GL_LINES, 3*2 ,vertex_buffer_data,COLOR_BLACK,GL_FILL);

		vertex_buffer_data[0]=0;vertex_buffer_data[1]=0;vertex_buffer_data[2]=0;
		vertex_buffer_data[3]=0;vertex_buffer_data[4]=0.1;vertex_buffer_data[5]=0;
		vertex_buffer_data[6]=0.7;vertex_buffer_data[7]=0.1;vertex_buffer_data[8]=0;

		vertex_buffer_data[9]=0;vertex_buffer_data[10]=0;vertex_buffer_data[11]=0;
		vertex_buffer_data[12]=0.7;vertex_buffer_data[13]=0;vertex_buffer_data[14]=0;
		vertex_buffer_data[15]=0.7;vertex_buffer_data[16]=0.1;vertex_buffer_data[17]=0;
		
		this->fuel_bar = create3DObject(GL_TRIANGLES, 3*2 ,vertex_buffer_data,COLOR_RED,GL_FILL);

		vertex_buffer_data[0]=0;vertex_buffer_data[1]=0;vertex_buffer_data[2]=0;
		vertex_buffer_data[3]=0;vertex_buffer_data[4]=0.02;vertex_buffer_data[5]=0;
		vertex_buffer_data[6]=0.7;vertex_buffer_data[7]=0.02;vertex_buffer_data[8]=0;

		vertex_buffer_data[9]=0;vertex_buffer_data[10]=0;vertex_buffer_data[11]=0;
		vertex_buffer_data[12]=0.7;vertex_buffer_data[13]=0;vertex_buffer_data[14]=0;
		vertex_buffer_data[15]=0.7;vertex_buffer_data[16]=0.02;vertex_buffer_data[17]=0;

		this->health_bar = create3DObject(GL_TRIANGLES, 3*2 ,vertex_buffer_data,COLOR_MAGENTA,GL_FILL);
		for(int i=0;i<n;i++)
		{
			vertex_buffer_data[9*i+0]=0.12*cos(2*i*M_PI/n);
			vertex_buffer_data[9*i+1]=0.12*sin(2*i*M_PI/n);
			vertex_buffer_data[9*i+2]=0;
			
			vertex_buffer_data[9*i+3]=0.12*cos(2*(i+1)*M_PI/n);
			vertex_buffer_data[9*i+4]=0.12*sin(2*(i+1)*M_PI/n);
			vertex_buffer_data[9*i+5]=0;

			vertex_buffer_data[9*i+6]=0;
			vertex_buffer_data[9*i+7]=0;
			vertex_buffer_data[9*i+8]=0;   	
		}
		this->compass.circle = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, COLOR_LIGHTGRAY, GL_FILL);

		GLfloat color_buffer_data[40];

		vertex_buffer_data[0]=0;		vertex_buffer_data[1]=0.1;		vertex_buffer_data[2]=0;
		vertex_buffer_data[3]=-0.9;		vertex_buffer_data[4]=0;		vertex_buffer_data[5]=0;
		vertex_buffer_data[6]=0;		vertex_buffer_data[7]=-0.1;		vertex_buffer_data[8]=0;

		vertex_buffer_data[9]=0;		vertex_buffer_data[10]=0.1;		vertex_buffer_data[11]=0;
		vertex_buffer_data[12]=0.9;		vertex_buffer_data[13]=0;		vertex_buffer_data[14]=0;
		vertex_buffer_data[15]=0;		vertex_buffer_data[16]=-0.1;		vertex_buffer_data[17]=0;

		for(int i=0;i<3*6;i++)vertex_buffer_data[i]*=0.12;

		for(int i=0;i<9;i++){color_buffer_data[i]=(!(i%3))?1:0;}
		for(int i=9;i<18;i++){color_buffer_data[i]=0.3;}

		this->compass.needle = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color_buffer_data, GL_FILL);

		this->tick(altitude,fuel,speed,rotation,health);
		this->n1=Display(speed,V(-0.75,-0.95,-0.2));
		this->n2=Display(speed,V(-0.85,-0.95,-0.2));
		this->N=Display(speed,V(-0.95,-0.95,-0.2));
	}
	void draw() {
		this->draw_board();
		this->draw_compass();
		this->draw_needle();
		if(this->fuel>0)
			this->draw_fuel_bar();
		this->draw_health_bar();
		this->draw_speed();
	}
	void draw_board() {
		Matrices.model = glm::mat4(1.0f);
		glm::mat4 translate = glm::translate (V(-1,-1,-0.2));
		Matrices.model *= translate;
		glm::mat4 MVP = Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(this->object);
	}
	void draw_compass() {
		Matrices.model = glm::mat4(1.0f);
		glm::mat4 translate = glm::translate (V(-0.4,-0.45,-0.2));
		Matrices.model *= translate;
		glm::mat4 MVP = Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(this->compass.circle);	
		Matrices.model = glm::mat4(1.0f);
		Matrices.model *= glm::translate(V(-0.4,-0.45,-0.2));
		Matrices.model *= glm::rotate((float)(this->rotation*M_PI/180),V(0,0,-1));
		MVP = Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(this->compass.needle);
	}
	void draw_needle() {	
		Matrices.model = glm::mat4(1.0f);
		glm::mat4 translate = glm::translate (V(-0.8,-0.6,-0.2));
		glm::mat4 rotate = glm::rotate((float) ( (this->altitude/20)* M_PI), glm::vec3(0, 0, -1));
		Matrices.model *= (translate*rotate);
		glm::mat4 MVP = Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(this->needle);		
	}
	
	void draw_fuel_bar() {	
		Matrices.model = glm::mat4(1.0f);
		glm::mat4 translate = glm::translate (V(-0.95,-0.8,-0.2));
		glm::mat4 scale  	= glm::scale (V(this->fuel,1,1));
		Matrices.model *= (translate*scale);
		glm::mat4 MVP = Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(this->fuel_bar);
	}

	void draw_health_bar() {	
		Matrices.model = glm::mat4(1.0f);
		glm::mat4 translate = glm::translate (V(-0.95,-0.85,-0.20));
		glm::mat4 scale  	= glm::scale (V(this->health,1,1));
		Matrices.model *= (translate*scale);
		glm::mat4 MVP = Matrices.model;
		glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		draw3DObject(this->health_bar);
	}

	void draw_speed() {
		this->n1.draw();
		this->n2.draw();
		this->N.draw();
	}

	void tick(float altitude,float fuel,float speed,float rotation,float health)
	{
		this->altitude=altitude;
		this->fuel=fuel;
		this->health=health;
		speed*=1000;
		this->rotation=rotation;
		this->n1.update(int(speed)%10);
		this->n2.update((int(speed)/10)%10);
		this->N.update(int(speed)/100);
	}
private:
	VAO *object;
	VAO *needle;
	VAO *fuel_bar;
	VAO *health_bar;
	Compass compass;
};

#endif // DASHBOARD_H
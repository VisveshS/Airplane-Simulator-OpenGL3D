#include "camera.h"
#include "main.h"

Camera::Camera(glm::vec3 position) {
	this->mode=3;
	this->angle=0;
	this->changing=false;
	this->up=V(0,0,1);
	this->tick(position,angle,0);
}

void Camera::change() {
	this->mode=(this->mode+1)%5;
}

void Camera::tick(glm::vec3 position,float turn,float angle) {
	this->angle = turn;
	float Cos=cos(this->angle*M_PI/180.0f);
	float Sin=sin(this->angle*M_PI/180.0f);
			float Cos1=cos((float)(angle*M_PI/180));
			float Sin1=sin((float)(angle*M_PI/180));
	trackmouse=false;
	switch(this->mode)
	{
		case 0:
			this->eye = position+V(0.31*Cos,0.31*Sin,0.1);
			this->target = position+V(0.32*Cos,0.32*Sin,0.1);
			break;
		case 1://top view
			this->eye = position+V(0.001,0.001,10);
			this->target = position;
			break;
		case 2://tower view
			this->eye = V(0.001,-5,9);
			this->target = position;
			break;
		case 3://follow view
			this->eye = position+V(-1.2*Cos,-1.2*Sin,0.2);
			this->target = position;
			break;
		case 4://helicopter view
			trackmouse=true;
			this->target = position-V(0.2*((Cos*cos(((cursor_position_x-350)/4)*M_PI/180)-Sin*sin(((cursor_position_x-350)/4)*M_PI/180))),0.2*(Sin*cos(((cursor_position_x-350)/4)*M_PI/180)+Cos*sin(((cursor_position_x-350)/4)*M_PI/180)),0.2*sin(-(700-cursor_position_y)*M_PI/(180.0f*6)));
			this->eye = this->target-V(screen_zoom*((Cos*cos(((cursor_position_x-350)/4)*M_PI/180)-Sin*sin(((cursor_position_x-350)/4)*M_PI/180))),screen_zoom*(Sin*cos(((cursor_position_x-350)/4)*M_PI/180)+Cos*sin(((cursor_position_x-350)/4)*M_PI/180)),screen_zoom*sin(-(700-cursor_position_y)*M_PI/(180.0f*6)));
			break;
		default:
			break;
	};
}


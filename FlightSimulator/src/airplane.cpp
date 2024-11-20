#include "airplane.h"
#include "main.h"
#define dimension 0.07
float gravity = 0.001;
float fuel_time = 30.0f;//fly time in seconds
float Acceleration = 0.005;
float Decceleration = -0.004;

Airplane::Airplane(glm::vec3 position) {
	this->position 	= position;
	this->rotation 	= 0;
	this->barrelrollangle=0;
	this->downspeed = 0;
	this->yaw 		= -10;
	this->pitch 	= -10;
	this->roll 		= -20;
	this->Roll 		= 0;
	this->health 	= 1.0;
	this->state.turn=turn::stationary;
	this->state.ascend=ascend::stationary;
	this->releasing_missile	= false;
	this->releasing_bomb 	= false;
	this->speed 			= 0;
	this->safe=true;
	this->fuel=1.0f;
	this->using_fuel=false;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
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


	vertex_buffer_data[9*(n1+n+3)+0]=-8;
	vertex_buffer_data[9*(n1+n+3)+1]=0;
	vertex_buffer_data[9*(n1+n+3)+2]=2.6;

	vertex_buffer_data[9*(n1+n+3)+3]=-8;
	vertex_buffer_data[9*(n1+n+3)+4]=0.1;
	vertex_buffer_data[9*(n1+n+3)+5]=1.1;

	vertex_buffer_data[9*(n1+n+3)+6]=-8;
	vertex_buffer_data[9*(n1+n+3)+7]=-0.1;
	vertex_buffer_data[9*(n1+n+3)+8]=1.1;

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
			color_buffer_data[i*3+0]=float(COLOR_LIGHTGRAY.r/255.0f);
			color_buffer_data[i*3+1]=float(COLOR_LIGHTGRAY.g/255.0f);
			color_buffer_data[i*3+2]=float(COLOR_LIGHTGRAY.b/255.0f);
		}
	}
	for(int i=0;i<3*n1;i++)
	{
		if(i%3==2)
		{
			color_buffer_data[9*n+i*3+0]=float(COLOR_WHITE.r/255.0f);
			color_buffer_data[9*n+i*3+1]=float(COLOR_WHITE.g/255.0f);;
			color_buffer_data[9*n+i*3+2]=float(COLOR_WHITE.b/255.0f);
		}
		else
		{
			color_buffer_data[9*n+i*3+0]=float(COLOR_LIGHTGRAY.r/255.0f);
			color_buffer_data[9*n+i*3+1]=float(COLOR_LIGHTGRAY.g/255.0f);
			color_buffer_data[9*n+i*3+2]=float(COLOR_LIGHTGRAY.b/255.0f);
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
	this->crash = create3DObject(GL_TRIANGLES, (n+n1+4)*3 ,vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Airplane::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	float Cos=cos(this->rotation*M_PI/180.0f);
	float Sin=sin(this->rotation*M_PI/180.0f);

	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	if(this->state.turn == turn::stationary&&this->state.ascend == ascend::stationary)
		rotate*=glm::rotate((float)(this->Roll*M_PI/180),V(1,0,0));
	if(this->state.turn == turn::right_turn)
		rotate *= glm::rotate((float)(this->yaw*M_PI/180.0f),V(0,0,1));
	if(this->state.turn == turn::left_turn)
		rotate *= glm::rotate((float)(-this->yaw*M_PI/180.0f),V(0,0,1));
	if(this->state.ascend == ascend::ascend)
		rotate *= glm::rotate((float)(this->pitch*M_PI/180.0f),V(0,1,0));
	if(this->state.turn == turn::right_turn)
		rotate *= glm::rotate((float)(-(this->roll+this->Roll)*M_PI/180.0f),V(1,0,0));
	if(this->state.turn == turn::left_turn)
		rotate *= glm::rotate((float)((this->roll+this->Roll)*M_PI/180.0f),V(1,0,0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
	if(!this->safe)
		draw3DObject(this->crash);
}

void Airplane::acceleration(bool x) {
	if(x&&this->fuel>=0)
	{
		this->speed+=Acceleration;
		if(this->speed>0.5)this->speed=0.5;
	}
	else 
	{
		this->speed+=Decceleration;
		if(this->speed<0)this->speed=0;
	}
	float Cos=cos(this->rotation*M_PI/180.0f);
	float Sin=sin(this->rotation*M_PI/180.0f);
	this->position+=V(this->speed*Cos,this->speed*Sin,0);
}

void Airplane::Input(char charecter_pressed)
{
	float displace=2;
	switch(charecter_pressed)
	{
		case 'f':
			if(this->fuel>0)
				break;
		case 'u':
			if(this->fuel>0)
			{
				this->position+=V(0,0,0.1);
				this->downspeed=0;
			}
			break;
		case 'l':
            if(this->fuel>0)
            {
            	this->rotation += displace;
            }
			break;
		case 'r':
            if(this->fuel>0)
            {
            	this->rotation -= displace;
            }
			break;
		default:
			break;
	};
	if(this->fuel<=0)
		this->fall();

	if(charecter_pressed=='u'||charecter_pressed=='f'||charecter_pressed=='l'||charecter_pressed=='r')
	{
		if(!this->using_fuel)
		{
			this->using_fuel=true;
			this->lastpress=glfwGetTime();
		}
		if(glfwGetTime()-this->lastpress>fuel_time)
			this->fuel=0;
	}
	else
	{
		if(this->using_fuel)
		{
			this->using_fuel=false;
			this->fuel-=(glfwGetTime()-this->lastpress)/fuel_time;
			this->lastpress=glfwGetTime();
		}
	}
	if(this->rotation>360)
		this->rotation-=360;
	if(this->rotation<0)
		this->rotation+=360;
	if(this->position.z>20.0f)
		this->position.z=20.0f;
}

void Airplane::fall() {
	this->downspeed+=gravity;
	this->position.z-=this->downspeed;
	if(this->position.z<0.0f)
	{
		this->downspeed=0;
		this->position.z=0;
	}
}

void Airplane::tick(int place) {
	this->missile();
	this->bomb();
	for(std::vector <Explosion>::iterator it=this->explosions.begin();it!=this->explosions.end();++it)
		(*it).tick();
	enum location {AIR,WATER,RUNWAY,VOLCANO};
	if(this->safe&&(place==VOLCANO||place==WATER)){this->crashTime=glfwGetTime();this->safe=false;}
	else if((!this->safe)&&(place==RUNWAY||place==AIR)){;this->safe=true;}
	if(place==WATER)this->health-=std::max(double(0),double((glfwGetTime()-this->crashTime)/400));
	if(place==VOLCANO)this->health-=std::max(double(0),double((glfwGetTime()-this->crashTime)/133));
	this->health=std::min(1.0f,this->health);
	if(this->health<=0)
		exit(0);
}

//shooting

void Airplane::missile() {
	if(!this->releasing_missile&&click_status==click::MISSILE)
	{
		Missile temp;
		temp = Missile(this->position,this->rotation);
		this->missiles.push_back(temp);
		this->releasing_missile=true;
		// printf("MISSILE\n");
	}
	if(click_status == click::NOTHING)
		this->releasing_missile=false;
}

void Airplane::bomb() {
	if(!this->releasing_bomb&&click_status==click::BOMB)
	{
		Bomb temp;
		temp = Bomb(this->position,this->rotation);
		this->bombs.push_back(temp);
		this->releasing_bomb=true;
	}
	if(click_status == click::NOTHING)
		this->releasing_bomb=false;
}

void Airplane::barrelroll(Camera *camera) {
	float Cos=cos(this->rotation*M_PI/180.0f);
	float Sin=sin(this->rotation*M_PI/180.0f);
	float Cos1=cos(++(this->barrelrollangle)*M_PI/180.0f);
	float Sin1=sin(this->barrelrollangle*M_PI/180.0f);
	this->Roll++;
	(*camera).up=V(Sin1*-Sin,Sin1*-Cos,Cos1);
}

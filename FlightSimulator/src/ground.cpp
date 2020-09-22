#include "ground.h"
#include "main.h"

#define dimension 170
#define N 100

#define island_radius 2
#define island_height 0.2
#define no_of_islands 30

#define mountain_radius 3
#define mountain_height 9
#define no_of_mountains 12

#define no_of_runways 15
#define no_of_fuel_points 10

Ground::Ground(bool dummy) {
	srand(time(0));
	static const GLfloat vertex_buffer_data[] = {
		-dimension,-dimension,-0.1,
		-dimension,dimension,-0.1,
		dimension,-dimension,-0.1,
		dimension,dimension,-0.1,
	};
	this->where_in=AIR;
	this->runway_no=0;
	for(int i=0;i<no_of_fuel_points;i++)this->fuel_left[i]=1.0f;
	this->consuming_fuel=false;	
	float posx,posy;
	GLfloat vertex_buffer_data_1[N];
	GLfloat vertex_buffer_data_2[N];

	//islands
	for(int j=0;j<no_of_islands;j++)
	{
		redo:
			posx=rand()%(2*(dimension-10))-(dimension-10);
			posy=rand()%(2*(dimension-10))-(dimension-10);
			posx+=rand()%10/10;
			posy+=rand()%10/10;
		if(posx<=2&&posx>=-2&&posy>=-2&&posy<=2)
			goto redo;
		this->islands_locations[j]=V(posx,posy,0);
		vertex_buffer_data_1[0]=posx;
		vertex_buffer_data_1[1]=posy;
		vertex_buffer_data_1[2]=island_height;
		int n=31,i;
		for(i=0;i<=n;i++)
		{
			vertex_buffer_data_1[(i+1)*3+0]=posx+island_radius*cos(2*i*M_PI/(n));
			vertex_buffer_data_1[(i+1)*3+1]=posy+island_radius*sin(2*i*M_PI/(n));
			vertex_buffer_data_1[(i+1)*3+2]=0;
		}
		this->island[j] = create3DObject(GL_TRIANGLE_FAN, n+2, vertex_buffer_data_1, COLOR_GREEN, GL_FILL);
	}
	//mountains
	for(int j=0;j<no_of_mountains;j++)
	{
		redo1:
			posx=rand()%(2*(dimension-10))-(dimension-10);
			posy=rand()%(2*(dimension-10))-(dimension-10);
			posx+=rand()%10/10;
			posy+=rand()%10/10;
		if(posx<=1&&posx>=-1&&posy>=-1&&posy<=1)
			goto redo1;
		this->mountains_locations[j]=V(posx,posy,0);
		vertex_buffer_data_1[0]=posx;
		vertex_buffer_data_1[1]=posy;
		vertex_buffer_data_1[2]=mountain_height;

		vertex_buffer_data_2[0]=posx;
		vertex_buffer_data_2[1]=posy;
		vertex_buffer_data_2[2]=mountain_height+0.01;

		int n=31,i;
		for(i=0;i<=n;i++)
		{
			vertex_buffer_data_1[(i+1)*3+0]=posx+mountain_radius*cos(2*i*M_PI/(n));
			vertex_buffer_data_1[(i+1)*3+1]=posy+mountain_radius*sin(2*i*M_PI/(n));
			vertex_buffer_data_1[(i+1)*3+2]=0;
	
			vertex_buffer_data_2[(i+1)*3+0]=posx+mountain_radius*cos(2*i*M_PI/(n))*0.3;
			vertex_buffer_data_2[(i+1)*3+1]=posy+mountain_radius*sin(2*i*M_PI/(n))*0.3;
			vertex_buffer_data_2[(i+1)*3+2]=mountain_height*0.7;
		}
		this->mountains[j] = create3DObject(GL_TRIANGLE_FAN, n+2, vertex_buffer_data_1, COLOR_SIENNA, GL_FILL);
		this->lava[j]	   = create3DObject(GL_TRIANGLE_FAN, n+2, vertex_buffer_data_2, COLOR_ORANGE, GL_FILL);
	}
	float angle;
	for(int j=0;j<no_of_runways;j++)
	{
		redo2:
			posx=rand()%(2*(dimension-10))-(dimension-10);
			posy=rand()%(2*(dimension-10))-(dimension-10);
			posx+=rand()%10/10;
			posy+=rand()%10/10;
		if(posx<=1&&posx>=-1&&posy>=-1&&posy<=1)
			goto redo2;

		angle=(j==0)?0:rand()%360;
		if(!j)posx=0;
		if(!j)posy=0;

		this->runways_location[j].coordinates=V(posx,posy,0);
		this->runways_location[j].angle=angle;

		vertex_buffer_data_1[3]=float(-1.12*cos((angle+26.56)*M_PI/(180.0)))+posx;
		vertex_buffer_data_1[4]=float(-1.12*sin((angle+26.56)*M_PI/(180.0)))+posy;
		vertex_buffer_data_1[5]=0;
		
		vertex_buffer_data_1[0]=float(-1.12*cos((angle-26.56)*M_PI/(180.0)))+posx;
		vertex_buffer_data_1[1]=float(-1.12*sin((angle-26.56)*M_PI/(180.0)))+posy;
		vertex_buffer_data_1[2]=0;

		vertex_buffer_data_1[6]=float(8.016*cos((angle+3.5763)*M_PI/(180.0)))+posx;
		vertex_buffer_data_1[7]=float(8.016*sin((angle+3.5763)*M_PI/(180.0)))+posy;
		vertex_buffer_data_1[8]=0;
		
		vertex_buffer_data_1[9]=float(8.016*cos((angle-3.5763)*M_PI/(180.0)))+posx;
		vertex_buffer_data_1[10]=float(8.016*sin((angle-3.5763)*M_PI/(180.0)))+posy;
		vertex_buffer_data_1[11]=0;

		this->runways[j] = create3DObject(GL_TRIANGLE_STRIP, 4, vertex_buffer_data_1, COLOR_BLACK, GL_FILL);
	}
	GLfloat vertex_buffer_data_3[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };
    //smoke rings
    color_t palette[5]={COLOR_ORANGE,COLOR_MAGENTA,COLOR_GREEN,COLOR_WHITE,COLOR_LIGHTGRAY};
    for(int i=0;i<10;i++)
    {
		posx=rand()%(2*(dimension-10))-(dimension-10);
		posy=rand()%(2*(dimension-10))-(dimension-10);
		float posz=rand()%5+5;
		posx+=rand()%10/10;
		posy+=rand()%10/10;
    	this->smokeRing[i] = SmokeRing(V(posx,posy,posz),rand()%180,palette[int(rand()%5)]);
    }
    int rel_pos;
    for(int j=0;j<no_of_fuel_points;j++)
    {
		rel_pos = rand()%10-1;
		fuel_locations[j]=rel_pos;
	    for(int i=0;i<12*3*3;i++)
	    {
			switch(i%3)
			{
				case 0:
					vertex_buffer_data_1[i]=vertex_buffer_data_3[i]*0.1*0.5;
					vertex_buffer_data_1[i]+=this->runways_location[j+no_of_runways-no_of_fuel_points].coordinates.x+cos(this->runways_location[j+no_of_runways-no_of_fuel_points].angle*M_PI/180.0f)*(rel_pos);
					break;
				case 1:
					vertex_buffer_data_1[i]=vertex_buffer_data_3[i]*0.1*0.5;
					vertex_buffer_data_1[i]+=this->runways_location[j+no_of_runways-no_of_fuel_points].coordinates.y+sin(this->runways_location[j+no_of_runways-no_of_fuel_points].angle*M_PI/180.0f)*(rel_pos);
					break;
				case 2:
					vertex_buffer_data_1[i]=vertex_buffer_data_3[i]*0.1*1.25;
					break;
			}
	    }
	    this->fuel_point[j] = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data_1, COLOR_ORANGE, GL_FILL);
	}   
	this->ocean = create3DObject(GL_TRIANGLE_STRIP, 4, vertex_buffer_data, COLOR_BLUE, GL_FILL);
}
void Ground::ringcheck()
{
}
void Ground::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->ocean);
	for(int j=0;j<no_of_islands;j++)
	{
		draw3DObject(this->island[j]);
	}
	for(int j=0;j<no_of_mountains;j++)
	{
		draw3DObject(this->mountains[j]);
		draw3DObject(this->lava[j]);
	}
	for(int j=0;j<no_of_runways;j++)
		draw3DObject(this->runways[j]);
	for(int j=0;j<no_of_fuel_points;j++)
		if(this->fuel_left[j]>=0)
			this->draw_fuel(VP,j);
	for(int j=0;j<10;j++)
		this->smokeRing[j].draw(VP);
	}
void Ground::draw_fuel(glm::mat4 VP,int index)	{
	Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (V(0,0,0.125));
    glm::mat4 scale = glm::scale (V(1,1,this->fuel_left[index]));
	Matrices.model *= (scale*translate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->fuel_point[index]);
}

float Ground::consume_fuel(int tank_no,float player_fuel)
{
	if(!this->consuming_fuel)
	{
		this->consuming_fuel=true;
		float givefuel=(this->fuel_left[tank_no]>=(1-player_fuel)/1)?(1-player_fuel)/1:this->fuel_left[tank_no];
		this->fuel_left[tank_no]-=(1-player_fuel)/1;if(this->fuel_left[tank_no]<0)this->fuel_left[tank_no]=0;
		return givefuel;
	}
	return 0;
}

float Ground::where(glm::vec3 position,float player_fuel) {
	glm::vec3 temp,rot;
	int state=this->where_in;
	float Cos;
	float Sin;
	int place=-1;
	int tempno=-1;
	if(position.z>0)
		this->where_in=AIR;
	if(position.z==0)
		for(int j=0;j<no_of_runways;j++)
		{
			if(this->runways_location[j].coordinates.x<position.x+9.2&&this->runways_location[j].coordinates.x>position.x-9.2)
				if(this->runways_location[j].coordinates.y<position.y+9.2&&this->runways_location[j].coordinates.y>position.y-9.2)
				{
					Cos=cos(this->runways_location[j].angle*M_PI/180.0);
					Sin=sin(this->runways_location[j].angle*M_PI/180.0);
					temp=V(position.x-this->runways_location[j].coordinates.x,position.y-this->runways_location[j].coordinates.y,0);
					rot=V(temp.x*Cos+temp.y*Sin,temp.x*-Sin+temp.y*Cos,0);
					if((rot.x<8&&rot.x>-1)&&(rot.y>-0.5&&rot.y<0.5))
						place=RUNWAY;
				}
			tempno=(tempno==-1&&place==RUNWAY)?j:tempno;	
		}
	this->runway_no=(tempno==-1)?this->runway_no:tempno;	
	if(place==RUNWAY)
		this->where_in=RUNWAY;
	if(place == -1 && position.z==0)
		this->where_in=WATER;
	float dist;place=-1;
	if(position.z<9)
		for(int j=0;j<no_of_mountains;j++)
		{
			if(position.x-this->mountains_locations[j].x>-12||position.x-this->mountains_locations[j].x<12)
				if(position.y-this->mountains_locations[j].y>-12||position.y-this->mountains_locations[j].y<12)
				{
					dist=(position.x-this->mountains_locations[j].x)*(position.x-this->mountains_locations[j].x);
					dist+=(position.y-this->mountains_locations[j].y)*(position.y-this->mountains_locations[j].y);
					dist=sqrt(dist);
					if(dist<4-position.z/3)
						place=VOLCANO;
				}
		}
	if(place==VOLCANO)
		this->where_in=VOLCANO;
	if(this->where_in==RUNWAY&&this->runway_no>=(no_of_runways-no_of_fuel_points))
	{
		float Cos=cos(this->runways_location[this->runway_no].angle*M_PI/180.0f)*(this->fuel_locations[this->runway_no]);
		float Sin=sin(this->runways_location[this->runway_no].angle*M_PI/180.0f)*(this->fuel_locations[this->runway_no]);
		glm::vec3 dist=V(this->runways_location[this->runway_no].coordinates.x+cos(this->runways_location[this->runway_no].angle*M_PI/180.0f)*(this->fuel_locations[this->runway_no-(no_of_runways-no_of_fuel_points)]),this->runways_location[this->runway_no].coordinates.y+sin(this->runways_location[this->runway_no].angle*M_PI/180.0f)*(this->fuel_locations[this->runway_no-(no_of_runways-no_of_fuel_points)]),0)-position;
		if(dist.x*dist.x+dist.y*dist.y>=0.045)
			this->consuming_fuel=false;
		else	
			return(this->consume_fuel(this->runway_no-(no_of_runways-no_of_fuel_points),player_fuel));
	}
	return 0;
}

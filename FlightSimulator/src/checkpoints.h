#include "main.h"
#include "ground.h"
#include "airplane.h"
#include "parachutes.h"
#include "passengerflights.h"

#define no_of_islands 30

#define sx2_size 3

#ifndef CHECKPOINT_H
#define CHECKPOINT_H


class Checkpoint {
public:
	Checkpoint() {}
	Checkpoint(Ground* ground,Airplane *airplane);
	void missile_attack_enemy();
	void bomb_attack_enemy();
	glm::vec3 player_position;
	int current_checkpoint;
	Ground *ground;
	Airplane *airplane;
	std::vector<Parachute> parachutes;
	Cannon cannon[no_of_islands];
	void draw(glm::mat4 VP);
	void tick();
private:
	VAO *shinyRedArrow;
};

Checkpoint::Checkpoint(Ground* ground,Airplane* airplane) {
	this->ground = ground;
	this->airplane = airplane;
	this->current_checkpoint = 0;
	color_t color={225, 10, 10};
	GLfloat vertex_buffer_data[] = {
	1*sx2_size,1*sx2_size,0,
	-1*sx2_size,1*sx2_size,0,
	0*sx2_size,2*sx2_size,0,

	0.5*sx2_size,0*sx2_size,0,
	0.5*sx2_size,1*sx2_size,0,
	-0.5*sx2_size,0*sx2_size,0,

	-0.5*sx2_size,0*sx2_size,0,
	0.5*sx2_size,1*sx2_size,0,
	-0.5*sx2_size,1*sx2_size,0,
   };
	this->shinyRedArrow = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, color, GL_FILL);	
	for(int i=0;i<no_of_islands;i++)
		this->cannon[i] = Cannon(this->ground->islands_locations[i]);
}

void Checkpoint::missile_attack_enemy() {
	float range=1.77;
	bool hit=false;
	glm::vec3 gap=V(0,0,0);
	for(std::vector <Missile>::iterator it=(*this->airplane).missiles.begin();it!=(*this->airplane).missiles.end();++it)
	{
		gap.x = (*it).position.x-(*ground).islands_locations[this->current_checkpoint].x;
		gap.y = (*it).position.y-(*ground).islands_locations[this->current_checkpoint].y;
		gap.z = (*it).position.z-(*ground).islands_locations[this->current_checkpoint].z;
		if((gap.x<=range)&&(gap.y<=range)&&(gap.x>=-range)&&(gap.y>=-range)&&(gap.z<=0))
		{
			printf("Checkpoint %d achieved!\n",this->current_checkpoint+1);
			hit=true;
		}
		if((*it).position.z<=0)
		{
			Explosion temp;
			temp = Explosion(V((*it).position.x,(*it).position.y,0),COLOR_YELLOW);
			this->airplane->explosions.push_back(temp);
			this->airplane->missiles.erase(it--);
		}
	}
	if(hit)
	{
		this->current_checkpoint++;
	}
}

void Checkpoint::bomb_attack_enemy() {
	float range=1.77;
	bool hit=false;
	glm::vec3 gap=V(0,0,0);
	for(std::vector <Bomb>::iterator it=(*this->airplane).bombs.begin();it!=(*this->airplane).bombs.end();++it)
	{
		gap.x = (*it).position.x-(*ground).islands_locations[this->current_checkpoint].x;
		gap.y = (*it).position.y-(*ground).islands_locations[this->current_checkpoint].y;
		gap.z = (*it).position.z-(*ground).islands_locations[this->current_checkpoint].z;
		if((gap.x<=range)&&(gap.y<=range)&&(gap.x>=-range)&&(gap.y>=-range)&&(gap.z<=0))
		{
			printf("Checkpoint %d achieved!\n",this->current_checkpoint+1);
			hit=true;
		}
		if((*it).position.z<=0)
		{
			Explosion temp;
			temp = Explosion(V((*it).position.x,(*it).position.y,0),COLOR_YELLOW);
			this->airplane->explosions.push_back(temp);
			this->airplane->bombs.erase(it--);
		}
	}
	if(hit)
		this->current_checkpoint++;
}

void Checkpoint::tick() {
	this->bomb_attack_enemy();
	this->missile_attack_enemy();
	for(int i=0;i<10;i++)
	{
		if(this->ground->smokeRing[i].tick(this->airplane->position))
			this->airplane->health+=0.1;
	}
	if(int(rand()%20)==11)
	{
		int posx,posy,dimension=170;
		posx=rand()%(2*(dimension-10))-(dimension-10);
		posy=rand()%(2*(dimension-10))-(dimension-10);		
		this->parachutes.push_back(Parachute(V(float(posx),float(posy),40)));
	}
	for(std::vector<Parachute>::iterator it=this->parachutes.begin();it!=parachutes.end();it++)
	{
		(*it).tick();
		if((*it).position.z<0)
			this->parachutes.erase(it--);
		for(std::vector <Missile>::iterator it2=(*this->airplane).missiles.begin();it2!=(*this->airplane).missiles.end();++it2)
			if((*it).collision((*it2).position))
			{this->parachutes.erase(it--);
				printf("PARACHUTE\n");
				this->airplane->health+=0.2;
			}
	}
}

void Checkpoint::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate ((*this->ground).islands_locations[this->current_checkpoint]+V(0,0,10));
	glm::mat4 rotate = glm::rotate ((float)(-M_PI/2),V(1,0,0));
	rotate = rotate * glm::rotate ((float)((90-(*airplane).rotation)*M_PI/180),V(0,1,0));
	Matrices.model *= (translate*rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->shinyRedArrow);
	Matrices.model = glm::mat4(1.0f);
	MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glm::vec3 dist;float len;
	for(int i=this->current_checkpoint;i<no_of_islands;i++)
	{
		dist = this->airplane->position-this->ground->islands_locations[i];
		len=sqrt(dist.x*dist.x+dist.y*dist.y+dist.z*dist.z);
		dist.x/=len;dist.y/=len;dist.z/=len;
		this->cannon[i].draw(VP,dist);
		if(i==this->current_checkpoint and rand()%200==0)
			this->cannon[i].fire(this->ground->islands_locations[i],dist);
		if(i==this->current_checkpoint)
			if(this->cannon[i].tick(VP,this->airplane->position)==true)
			{
				this->airplane->explosions.push_back(Explosion(this->airplane->position,COLOR_BLACK));
				// this->airplane->health-=0.1;
			}
	}
	for(std::vector<Parachute>::iterator it=this->parachutes.begin();it!=parachutes.end();it++)
		(*it).draw(VP);
}

#endif // CHECKPOINT_H

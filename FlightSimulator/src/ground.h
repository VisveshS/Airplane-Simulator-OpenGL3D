#include "main.h"
#include "cannon.h"
#include "smoke_ring.h"

#ifndef GROUND_H
#define GROUND_H

struct Runway_location{glm::vec3 coordinates;float angle;};
enum location {AIR,WATER,RUNWAY,VOLCANO};

class Ground {
public:
	Ground(){}
	Ground(bool dummy);
	void draw(glm::mat4 VP);
	void draw_fuel(glm::mat4 VP,int index);
	float consume_fuel(int tank_no,float player_fuel);
	float where(glm::vec3 position,float fuel);
	void ringcheck();
	int where_in;
	bool consuming_fuel;
	SmokeRing smokeRing[10];
	int runway_no;
	glm::vec3 islands_locations[100];
	glm::vec3 mountains_locations[40];
	int fuel_locations[40];
	float fuel_left[10];
	Cannon cannons[100];
	Runway_location runways_location[30];
private:
	VAO *ocean;
	VAO *island[100];
	VAO *mountains[40];
	VAO *lava[40];
	VAO *runways[30];
	VAO *fuel_point[10];
};

#endif // GROUND_H

#include "main.h"
#include "camera.h"
#include "missile.h"
#include "bomb.h"
#include "explosion.h"

#ifndef AIRPLANE_H
#define AIRPLANE_H

namespace turn{enum state{stationary,right_turn,left_turn};}
namespace ascend{enum state{stationary,ascend};}
enum click {NOTHING,MISSILE,BOMB};

class Airplane {
public:
	Airplane() {}
	Airplane(glm::vec3 position);
	glm::vec3 position;
	float speed;
	float fuel;
	float health;
	float barrelrollangle,Roll;
	bool using_fuel;
	double crashTime;
	double lastpress;
	struct State{int turn;int ascend;}state;
	float rotation,yaw,pitch,roll;
	float downspeed;
	void draw(glm::mat4 VP);
	void reset();
	void fall();
	void acceleration(bool x);
	void tick(int place);
	void Input(char charecter_pressed);
	bool releasing_missile,releasing_bomb;
	void missile();
	void barrelroll(Camera *camera);
	void bomb();
	std::vector <Missile> missiles;
	std::vector <Bomb> bombs;
	std::vector <Explosion> explosions;
	bool safe;
private:
	VAO *object;
	VAO *crash;
};

#endif // AIRPLANE_H

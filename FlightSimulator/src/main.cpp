#include "main.h"
#include "timer.h"
#include "airplane.h"
#include "camera.h"
#include "ground.h"
#include "dashboard.h"
#include "checkpoints.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Airplane airplane;
Camera camera;
Ground ground;
Dashboard dashboard;
Checkpoint checkpoint;

int width  = 650;
int height = 650;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
bool trackmouse;
int cursor_position_x=width/2,cursor_position_y=height/2;
int click_status;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
	// clear the color and depth in the frame buffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use the loaded shader program
	// Don't change unless you know what you are doing
	glUseProgram (programID);

	// Eye - Location of camera. Don't change unless you are sure!!
	glm::vec3 eye =camera.eye;
	// Target - Where is the camera looking at.  Don't change unless you are sure!!
	glm::vec3 target =camera.target;
	// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
	// glm::vec3 up =camera.up;
	glm::vec3 up =V(0, 0, 1);

	// Compute Camera matrix (view)
	Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
	// Don't change unless you are sure!!
	// Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

	// Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
	// Don't change unless you are sure!!
	glm::mat4 VP = Matrices.projection * Matrices.view;

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	// Don't change unless you are sure!!
	glm::mat4 MVP;  // MVP = Projection * View * Model

	// Scene render
	airplane.draw(VP);
	ground.draw(VP);
	for(vector <Missile>::iterator it=airplane.missiles.begin();it!=airplane.missiles.end();++it)
		(*it).draw(VP);
	for(vector <Bomb>::iterator it=airplane.bombs.begin();it!=airplane.bombs.end();++it)
		(*it).draw(VP);
	for(std::vector <Explosion>::iterator it=airplane.explosions.begin();it!=airplane.explosions.end();++it)
	{
		(*it).draw(VP);
		if((*it).explosion_instant+0.1<glfwGetTime())
			airplane.explosions.erase(it--);
	}
	dashboard.draw();
	checkpoint.draw(VP);
}

void update(char charecter_pressed)
{
	airplane.Input(charecter_pressed);
	draw();
}

void tick_input(GLFWwindow *window) {
	int front  = glfwGetKey(window, GLFW_KEY_UP);
	int up  = glfwGetKey(window, GLFW_KEY_SPACE);
	int left  = glfwGetKey(window, GLFW_KEY_LEFT);
	int right  = glfwGetKey(window, GLFW_KEY_RIGHT);
	int changeview = glfwGetKey(window, GLFW_KEY_C);
	if(glfwGetKey(window, GLFW_KEY_B))
	{
		airplane.barrelroll(&camera);
		printf("barrelroll\n");
	}
	if(up==GLFW_RELEASE)
		airplane.fall();
	update('\0');
	if (front) {
		update('f');
		airplane.state.turn=turn::stationary;
		airplane.state.ascend=ascend::stationary;
	}
	if (up) {
		update('u');
		airplane.state.ascend=ascend::ascend;
	}
	if (left) {
		update('l');
		airplane.state.turn=turn::left_turn;
	}
	if (right) {
		update('r');
		airplane.state.turn=turn::right_turn;
	}
	if (changeview&&!camera.changing) {
		camera.change();
		camera.changing=true;
	}
	if (changeview == GLFW_RELEASE) {
		camera.changing=false;
	}
	if(!front&&!right&&!left) {
		airplane.state.turn=turn::stationary;
	}
	if(!front&&!up) {
		airplane.state.ascend=ascend::stationary;
	}
	airplane.acceleration(front);
	camera.tick(airplane.position,airplane.rotation,airplane.Roll);
}

void tick_elements() {
	for(vector <Missile>::iterator it=airplane.missiles.begin();it!=airplane.missiles.end();++it)
		(*it).tick();
	for(vector <Bomb>::iterator it=airplane.bombs.begin();it!=airplane.bombs.end();++it)
		(*it).tick();
	airplane.tick(ground.where_in);
	airplane.fuel+=(ground.where(airplane.position,airplane.fuel));
	dashboard.tick(airplane.position.z,airplane.fuel,airplane.speed,airplane.rotation,airplane.health);
	checkpoint.tick();
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
	/* Objects should be created before any other gl function and shaders */
	// Create the models

	airplane    = Airplane(V(0,0,0));
	camera      = Camera(airplane.position);
	ground 		= Ground(true);
	dashboard  	= Dashboard(0.0f,airplane.fuel,airplane.speed,airplane.rotation,airplane.health);
	checkpoint 	= Checkpoint(&ground,&airplane);
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


	reshapeWindow (window, width, height);

	// Background color of the scene
	glClearColor (COLOR_LIGHTBLUE.r / 255.0, COLOR_LIGHTBLUE.g / 255.0, COLOR_LIGHTBLUE.b / 255.0, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

	cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
	cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
	cout << "VERSION: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
	srand(time(0));

	window = initGLFW(width, height);

	initGL (window, width, height);

	/* Draw in loop */
	while (!glfwWindowShouldClose(window)) {
		// Process timers

		if (t60.processTick()) {
			// 60 fps
			// OpenGL Draw commands
			draw();
			// Swap Frame Buffer in double buffering
			glfwSwapBuffers(window);

			tick_elements();
			tick_input(window);
		}

		// Poll for Keyboard and mouse events
		glfwPollEvents();
	}

	quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
	return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
		   (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
	float top    = screen_center_y + 4 / screen_zoom;
	float bottom = screen_center_y - 4 / screen_zoom;
	float left   = screen_center_x - 4 / screen_zoom;
	float right  = screen_center_x + 4 / screen_zoom;
	Matrices.projection = glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f);
}

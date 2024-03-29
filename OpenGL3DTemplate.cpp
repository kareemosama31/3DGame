#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <ctime>
#include <string>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif



class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 3.0f, float eyeY = 3.0f, float eyeZ = 3.0f, float centerX = 2.0f, float centerY = 0.0f, float centerZ = 2.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}

	void setFrontView() {
		eye = Vector3f(1.0f, 1.0f, 2.0f);
		center = Vector3f(1.0f, 1.0f, 0.0f);
		up = Vector3f(0.0f, 1.0f, 0.0f);


		// Rotate the view to the left
		float angle = 90.0f; // Adjust the angle as needed
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(angle)) + right * sin(DEG2RAD(angle));
		up = view.cross(right);
		center = eye + view;
	}


	void setTopView() {
		eye = Vector3f(1.0f, 3.0f, 1.0f);
		center = Vector3f(1.0f, 0.0f, 1.0f);
		up = Vector3f(0.0f, 0.0f, -1.0f);
	}

	void setSideView() {
		eye = Vector3f(1.0f, 1.0f, 2.0f);
		center = Vector3f(1.0f, 1.0f, 0.0f);
		up = Vector3f(0.0f, 1.0f, 0.0f);

		// Rotate the view to the left
		float angle = 30.0f; // Adjust the angle as needed
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(angle)) + right * sin(DEG2RAD(angle));
		up = view.cross(right);
		center = eye + view;
	}
};


class Player {
public:
	Vector3f position;
	Vector3f direction;  // Direction of the player

	Player(float x = 2.0f, float y = 0.0f, float z = 2.0f) : position(x, y, z), direction(1.0f, 0.0f, 0.0f) {}



			void draw() {
				// Draw head

				glPushMatrix();
				glColor3f(1.0, 0.0, 0.0); // Red color
				glTranslatef(position.x + 0.5, position.y + 0.95, position.z + 0.5); // Center of the ground
				glutSolidSphere(0.1, 20, 20);
				glPopMatrix();



				// Body (Cube)
				glPushMatrix();
				glColor3f(0.0, 1.0, 0.0); // Green color
				glTranslatef(position.x + 0.5, position.y + 0.75, position.z + 0.5); // Center of the ground
				glutSolidCube(0.2);
				glPopMatrix();


				// Right Arm (Cube)
				glPushMatrix();
				glColor3f(0.0, 0.0, 1.0); // Blue color
				glTranslatef(position.x + 0.65, position.y + 0.7, position.z + 0.5); // Center of the ground
				glRotatef(45.0, 0.0, 0.0, 1.0);
				glutSolidCube(0.1);
				glPopMatrix();



				// Left Arm (Cube)
				glPushMatrix();
				glColor3f(0.0, 0.0, 1.0); // Blue color
				glTranslatef(position.x + 0.35, position.y + 0.7, position.z + 0.5); // Center of the ground
				glRotatef(-45.0, 0.0, 0.0, 1.0);
				glutSolidCube(0.1);
				glPopMatrix();



				// Right Leg (Cube)
				glPushMatrix();
				glColor3f(0.0, 0.0, 1.0); // Blue color
				glTranslatef(position.x + 0.57, position.y + 0.6, position.z + 0.5); // Center of the ground
				glutSolidCube(0.1);
				glPopMatrix();


				// Left Leg (Cube)
				glPushMatrix();
				glColor3f(0.0, 0.0, 1.0); // Blue color
				glTranslatef(position.x + 0.43, position.y + 0.6, position.z + 0.5); // Center of the ground
				glutSolidCube(0.1);
				glPopMatrix();

			}

			void moveX(float d) {
				position.x += d;
			}

			void moveY(float d) {
				position.y += d;
			}

			void moveZ(float d) {
				position.z += d;
			}
	};



Player player;
Camera camera;
float WALL_MIN_X = -0.2f; //0.3
float WALL_MAX_X = 6.6f; //7.2
float WALL_MIN_Y = -0.6f; //-0.25
float WALL_MAX_Y = 3.0f; //3.0
float WALL_MIN_Z = 0.1f; //0.1
float WALL_MAX_Z = 4.4f; //4.8
bool goal = false;
int timeLimitSeconds = 60;  // Set the time limit in seconds
time_t startTime;
bool timeDone = false;
const int colorChangeInterval = 2; // Change color every 5 seconds
int elapsedTime = 0;
bool working = false;
float carouselAngle = 0.0f;
float ferrisWheelAngle = 0.0f;
float foliageOffset = 0.0f; // Global variable to control foliage movement
float coneOffset = 0.0f; // Global variable to control cone movement
float windStrength = 0.05f; // Strength of the wind effect
float seesawAngle = 0.0f;




void timer(int value) {
	time_t currentTime = time(nullptr);
	elapsedTime = static_cast<int>(currentTime - startTime);

	// Check if the time limit is reached
	if (elapsedTime >= timeLimitSeconds) {
		std::string resultMessage = "Time's up! You ";

		// Check the goal to determine the result
		if (goal) {
			std::cout << "You win!" << std::endl;
			resultMessage += "win!";
		}
		else {
			std::cout << "You lose!" << std::endl;
			resultMessage += "lose!";
		}
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glColor3f(0.0, 1.0, 0.0);  // Set text color to white
		glRasterPos2f(-0.5, 0);   // Set the position for the text

		// Display the result message character by character
		for (const char& c : resultMessage) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
		}
		timeDone = true;
	}
	else {
		glutTimerFunc(1000, timer, 0);  // Call the timer function after 1000 milliseconds (1 second)
	}

	glutPostRedisplay();  // Request a redraw to update the displayed message
}

void initialize() {
	// Other initialization code goes here
	startTime = time(nullptr);  // Record the start time
	glutTimerFunc(1000, timer, 0);  // Start the timer
}



void drawPlayer() {
	player.draw();
}


void drawCylinder(float radius, float height, int sides) {
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= sides; ++i) {
		float theta = i * 2.0f * M_PI / sides;
		float x = radius * cos(theta);
		float y = radius * sin(theta);

		glVertex3f(x, y, 0.0f);
		glVertex3f(x, y, height);
	}
	glEnd();
}

void drawWheelSupport(float radius, float height, int sides) {
	glPushMatrix();
	drawCylinder(radius, height, sides);
	glPopMatrix();
}
void drawFerrisWheel() {
	int sides = 35;
	float wheelRadius = 1.3f;
	float cabinRadius = 0.4f;
	float cabinHeight = 0.6f;
	float supportHeight = 3.0f;
	float sphereRadius = 0.1f; // Adjust the sphere radius as needed

	glPushMatrix();
	glTranslated(0.3, 0, -1.0);

	// Draw Ferris wheel support structure
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslated(-1.0, 1.0, 1.4);
	glRotated(90, 1, 0, 0);
	drawWheelSupport(0.1f, supportHeight, sides);
	glPopMatrix();

	// Draw lines from top of the cylinder to the bottom
	glPushMatrix();
	for (int i = 0; i <= sides; ++i) {
		float theta = i * 2.0f * M_PI / sides;
		float x = wheelRadius * cos(theta);
		float y = wheelRadius * sin(theta);

		if (i % 2 == 0) {
			glColor3f(0.6f, 0.8f, 1.0f);
		}
		else {
			glColor3f(1.0f, 1.0f, 1.0f);
		}

		glBegin(GL_LINES);
		// Draw line
		glVertex3f(-1.0f + x, 1.4f + y, supportHeight - 1.35);
		glVertex3f(-1.0f, 1.0f, supportHeight - 1.35);
		glEnd();
		// Draw sphere at the end of the line
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f); // Adjust sphere color as needed
		glTranslatef(-1.0f + x, 1.4f + y, supportHeight - 1.35);
		glRotatef(ferrisWheelAngle, 0.0, 0.0, 1.0);
		glutSolidSphere(sphereRadius, 5, 5); // Adjust sphere details as needed
		glPopMatrix();
	}
	glPopMatrix();

	glPopMatrix();
}




void drawWall(double thickness) {


	// Draw the first cube

	glPushMatrix();
	if (elapsedTime % 2 == 0) {
		glColor3f(0.0f, 0.6f, 0.6f);
	}
	else {
		glColor3f(0.1f, 0.9f, 1.0f);
	}
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	if (elapsedTime % 2 == 0) {
		glColor3f(0.1f, 0.9f, 1.0f);
	}
	else {
		glColor3f(0.0f, 0.6f, 0.6f);
	}
	glTranslated(1.0, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	/*glRotated(45, 0, 0, 0);*/
	glutSolidCube(1);
	glPopMatrix();


}

float bendAngle = 20.0f;
void drawSeesaw() {
	glPushMatrix();
	glTranslated(0.2, 0, 0);

	// Draw the main beam (cylinder) in a cute pink color
	glColor3f(1.0f, 0.5f, 0.8f);
	glPushMatrix();
	glTranslatef(0.0f, -1.6f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	drawCylinder(0.1, 0.4, 50);
	glPopMatrix();

	// Draw the seesaw plank (cuboid) in a cheerful yellow color
	glColor3f(1.0f, 1.0f, 0.4f);
	glPushMatrix();
	glTranslatef(0.0f, -1.6f, 0.0f);
	
	glRotatef(bendAngle, 0.0f, 0.0f, 1.0f);
	glScalef(2.0, 0.2, 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	// Draw the left support (cuboid) in a lovely lavender color
	glColor3f(0.6f, 1.0f, 0.6f);
	glPushMatrix();
	glTranslatef(-0.6f, -1.4f - 0.5f * sin(seesawAngle), 0.0f); // Move the left seat up and down using sine function
	glScalef(0.1, 1.0, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();

	// Draw the right support (cuboid) in a mint green color
	glColor3f(0.6f, 1.0f, 0.6f);
	glPushMatrix();
	glTranslatef(0.6f, -1.4f + 0.5f * sin(seesawAngle), 0.0f); // Move the right seat up and down using sine function
	glScalef(0.1, 1.0, 0.1);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	// Draw the left handle (cylinder) in a soft blue color
	glColor3f(0.6f, 0.8f, 1.0f);
	glPushMatrix();
	glTranslatef(-0.6f, -1.0f - 0.5f * sin(seesawAngle), -0.25f); // Move the left seat up and down using sine function
	glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
	drawCylinder(0.05, 0.5, 50);
	glPopMatrix();

	// Draw the right handle (cylinder) in a gentle orange color
	glColor3f(1.0f, 0.8f, 0.6f);
	glPushMatrix();
	glTranslatef(0.6f, -1.0f + 0.5f * sin(seesawAngle), -0.25f); // Move the right seat up and down using sine function
	glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
	drawCylinder(0.05, 0.5, 50);
	glPopMatrix();

	glPopMatrix();
}


void drawCylinder1(float radius, float height, int sides) {
	glBegin(GL_QUADS);
	for (int i = 0; i < sides; ++i) {
		float theta = i * 2.0f * M_PI / sides;
		float x = radius * cos(theta);
		float y = radius * sin(theta);

		float nextTheta = (i + 1) * 2.0f * M_PI / sides;
		float nextX = radius * cos(nextTheta);
		float nextY = radius * sin(nextTheta);

		// Draw the side of the cylinder
		glVertex3f(x, y, 0.0f);
		glVertex3f(nextX, nextY, 0.0f);
		glVertex3f(nextX, nextY, height);
		glVertex3f(x, y, height);
	}
	glEnd();

	// Draw the top and bottom circles
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, 0.0f);  // Center of the top circle
	for (int i = 0; i <= sides; ++i) {
		float theta = i * 2.0f * M_PI / sides;
		float x = radius * cos(theta);
		float y = radius * sin(theta);
		glVertex3f(x, y, 0.0f);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0f, 0.0f, height);  // Center of the bottom circle
	for (int i = 0; i <= sides; ++i) {
		float theta = i * 2.0f * M_PI / sides;
		float x = radius * cos(theta);
		float y = radius * sin(theta);
		glVertex3f(x, y, height);
	}
	glEnd();
}

void drawCarousel() {
	int sides = 4;
	float wheelRadius = 0.9f;
	float cabinRadius = 0.15f;
	float cabinHeight = 0.4f;
	float supportHeight = 3.0f;

	glPushMatrix();
	glTranslated(2.0, 4.0, 4.0);

	// Draw Carousel support structure
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslated(-1.0, 0.0, 1.7);
	drawWheelSupport(0.1f, supportHeight * 0.75, sides);
	glPopMatrix();

	// Draw Carousel wheel
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslated(-1.0, -3.855, 0);
	glRotated(90, 1, 0, 0);
	drawCylinder1(wheelRadius, 0.1f, sides);
	glPopMatrix();

	glPushMatrix();

	// Draw Carousel wheel
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();

	glTranslated(-1.0, -1.65, 0);
	glRotated(90, 1, 0, 0);
	glRotatef(carouselAngle, 0.0, 0.0, 1.0);
	drawCylinder1(wheelRadius, 0.1f, sides);
	glPopMatrix();

	// Draw lines from the top of the cylinder to some point below
	glPushMatrix();
	glRotated(90, 1, 0, 0);
	glTranslated(0, 1.65, 3.2);
	glBegin(GL_LINES);
	for (int i = 0; i <= 4; ++i) {
		float theta = i * 2.0f * M_PI / 4;
		float x = wheelRadius * cos(theta);
		float y = wheelRadius * sin(theta);

		glVertex3f(-1.0 + x, -1.65 + y, 0.0);  // Top of the cylinder
		glVertex3f(-1.0 + x, -1.65 + y, -1.5); // Point below the cylinder
	}


	glEnd();
	//glColor3f(1.0f, 0.5f, 0.5f);
	for (int i = 0; i < 4; ++i) {
		glPushMatrix();
		glTranslated(-1.0, -1.6, -1.7);
		float theta = i * 2.0f * M_PI / 4;
		float x = wheelRadius * cos(theta);
		float y = wheelRadius * sin(theta);
		glTranslatef(x, y, supportHeight - 1.55);
		glColor3f((i % 2 == 0) ? 0.0f : 1.0f, (i % 2 == 0) ? 1.0f : 0.5f, 0.0f);
		glRotatef(carouselAngle, 0.0, 0.0, 1.0);
		drawCylinder1(cabinRadius, cabinHeight, sides);
		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();


	glPopMatrix();
}

class Bench {
public:
	float length;
	float width;
	float height;

	Bench(float benchLength = 0.8f, float benchWidth = 0.2f, float benchHeight = 0.2f) {
		length = benchLength;
		width = benchWidth;
		height = benchHeight;
	}

	void draw() {
		// Draw seat
		glPushMatrix();
		glColor3f(0.5, 0.2, 0.0); // Brown color for the seat

		// Adjust the position along the y-axis to touch the ground
		glTranslatef(0.0, -0.3, -1.4);

		glScaled(length, height, width);
		glutSolidCube(1.0);
		glPopMatrix();

		// Draw legs
		float legDistance = length * 0.4; // Adjust the distance of the legs from the corners
		float legHeight = height * 0.8;   // Adjust the height of the legs

		// Front left leg
		glPushMatrix();
		glColor3f(0.5, 0.2, 0.0); // Brown color for the legs

		// Adjust the position along the y-axis to touch the ground
		glTranslatef(-legDistance, -0.4, -1.3);

		glScaled(width, legHeight, width);
		glutSolidCube(1.0);
		glPopMatrix();


// Front right leg
glPushMatrix();
glColor3f(0.5, 0.2, 0.0);

// Adjust the position along the y-axis to touch the ground
glTranslatef(legDistance, -0.4, -1.5);

glScaled(width, legHeight, width);
glutSolidCube(1.0);
glPopMatrix();

// Back left leg
glPushMatrix();
glColor3f(0.5, 0.2, 0.0);

// Adjust the position along the y-axis to touch the ground
glTranslatef(-legDistance, -0.4, -1.5);

glScaled(width, legHeight, width);
glutSolidCube(1.0);
glPopMatrix();

// Back right leg
glPushMatrix();
glColor3f(0.5, 0.2, 0.0);

// Adjust the position along the y-axis to touch the ground
glTranslatef(legDistance, -0.4, -1.3);

glScaled(width, legHeight, width);
glutSolidCube(1.0);
glPopMatrix();
	}
};

Bench bench;






void setupLights() {
	// Material properties
	GLfloat ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Increased ambient intensity
	GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Increased diffuse intensity
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat shininess[] = { 100.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	// Light properties
	GLfloat lightIntensity[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Increased intensity
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightIntensity);

	// Enable lighting and light 0
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);  // Enable normalization of normals for proper lighting
}


void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1200 / 750, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void drawBench() {
	bench.draw();


}
float gateBYNOT = 0.0f;

void drawGate() {
	// Draw left pillar (cuboid)
	glColor3f(0.0f, 0.0f, 1.0f); // Adjust color as needed
	glPushMatrix();
	glTranslatef(-2.0f, gateBYNOT, 0.0f);
	glScalef(0.2, 2.0, 0.2); // Adjust dimensions as needed
	glutSolidCube(1.0);
	glPopMatrix();

	// Draw right pillar (cuboid)
	glColor3f(0.0f, 0.0f, 1.0f); // Adjust color as needed
	glPushMatrix();
	glTranslatef(2.0f, gateBYNOT, 0.0f);
	glScalef(0.2, 2.0, 0.2); // Adjust dimensions as needed
	glutSolidCube(1.0);
	glPopMatrix();

	// Draw horizontal bar (cuboid)
	glColor3f(0.0f, 0.0f, 1.0f); // Adjust color as needed
	glPushMatrix();
	glTranslatef(0.0f, gateBYNOT+1.8f, 0.0f);
	glScalef(2.0, 0.2, 0.2); // Adjust dimensions as needed
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawTree() {
	// Draw trunk
	glColor3f(0.5f, 0.35f, 0.05f); // Brown color for the trunk
	glPushMatrix();
	glTranslatef(3.0f, 0.0f, 3.0f); // Position the tree trunk
	glScalef(0.2f, 1.5f, 0.2f); // Adjust size of the trunk
	glutSolidCube(1.0);
	glPopMatrix();

	// Draw foliage (sphere)
	glColor3f(0.0f, 0.5f, 0.0f); // Green color for the foliage
	glPushMatrix();
	glTranslatef(3.0f, 1.5f, 3.0f); // Position the foliage closer to the top of the trunk
	glutSolidSphere(1.0, 50, 50); // Use a sphere for the foliage
	glPopMatrix();

	// Draw additional primitive (cone)
	glColor3f(0.0f, 0.5f, 0.0f); // Green color for the additional primitive (cone)
	glPushMatrix();
	glTranslatef(3.0f, 2.5f, 3.0f); // Adjust the position to touch the foliage
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Orient the cone properly
	glutSolidCone(0.8, 1.5, 50, 50); // Use a cone for the additional primitive
	glPopMatrix();

	// Simulate foliage movement (back-and-forth motion)
	float foliageMovement = sin(foliageOffset);
	glPushMatrix();
	glTranslatef(0.0f, foliageMovement * 0.1f, 0.0f); // Adjust the amplitude and direction of movement
	glTranslatef(3.0f, 1.5f, 3.0f); // Position the foliage closer to the top of the trunk
	glutSolidSphere(1.0, 50, 50); // Use a sphere for the foliage
	glPopMatrix();

	// Simulate cone movement (back-and-forth motion)
	float coneMovement = cos(coneOffset);
	glPushMatrix();
	glTranslatef(0.0f, coneMovement * 0.1f, 0.0f); // Adjust the amplitude and direction of movement
	glTranslatef(3.0f, 2.5f, 3.0f); // Adjust the position to touch the foliage
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Orient the cone properly
	glutSolidCone(0.8, 1.5, 50, 50); // Use a cone for the additional primitive
	glPopMatrix();
}


void animateTimer(int value) {
	// Update rotation angles
	carouselAngle += 2.0f;  // Adjust the rotation speed as needed
	ferrisWheelAngle += 1.0f;  // Adjust the rotation speed as needed


	// Ensure angles stay within a reasonable range
	if (carouselAngle >= 360.0f) {
		carouselAngle -= 360.0f;
	}

	if (ferrisWheelAngle >= 360.0f) {
		ferrisWheelAngle -= 360.0f;
	}

	// Redisplay the scene
	glutPostRedisplay();

	// Continue the animation if working is true
	if (working) {
		glutTimerFunc(16, animateTimer, 0);  // 60 frames per second (1000ms / 60fps)
	}
}

void animate() {
	if (!working) {
		working = true;
		glutTimerFunc(0, animateTimer, 0);  // Start the animation
	}
}

void stopAnimate() {
	working = false;
}




float rotateBench = 90.0f;
void Display() {
	


	if (!timeDone) {
		setupCamera();
		setupLights();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (working) {
			foliageOffset += windStrength;
			coneOffset += windStrength;
			seesawAngle += 0.1f;
			rotateBench += 2.0f;
			
			bendAngle += 1.0f; // Adjust the rotation speed as needed
			if (bendAngle > 20.0f || bendAngle < -20.0f) {
				bendAngle = -bendAngle; // Reverse the rotation direction when reaching the limits
			}

		}
		gateBYNOT += 0.1f;
		if (gateBYNOT > 6.0f)
			gateBYNOT = 0;
		/*glPushMatrix();
		glTranslated(0.4, 0.4, 0.6);
		glRotated(45, 0, 0, 1);
		glScaled(0.08, 0.08, 0.08);
		drawJack();
		glPopMatrix();


		glPushMatrix();
		glTranslated(0.6, 0.38, 0.5);
		glRotated(30, 0, 1, 0);
		glutSolidTeapot(0.08);
		glPopMatrix();


		glPushMatrix();
		glTranslated(0.25, 0.42, 0.35);
		glutSolidSphere(0.1, 15, 15);
		glPopMatrix();


		glPushMatrix();
		glTranslated(0.4, 0.0, 0.4);
		drawTable(0.6, 0.02, 0.02, 0.3);
		glPopMatrix();*/

		drawPlayer();  // Draw the player
		
		
		glPushMatrix();
		glTranslatef(2.0f, 0.5f, 2.0f);
		glRotated(rotateBench, 0, 1,0);
		drawBench();
		glPopMatrix();
		
		glPushMatrix();
		glTranslated(3.0, 0.0, 0.0);
		drawFerrisWheel();
		glPopMatrix();

		glPushMatrix();
		glTranslated(1.0, 0.0, 0.0);
		drawTree();
		glPopMatrix();
		if (!goal) {
			glPushMatrix();
			glTranslated(6.5, 0.0, 2.5);
			glRotated(90, 0, 1, 0);
			drawGate();
			glPopMatrix();
		}

		glPushMatrix();
		drawCarousel();
		glPopMatrix();

		glPushMatrix();
	
		glPopMatrix();

		glPushMatrix();
		glTranslated(5, 2.0, 0.5);
		drawSeesaw();
		glPopMatrix();

		glPushMatrix();
		glScaled(5.0, 1.0, 5.0);
		drawWall(0.02);
		glPopMatrix();

		glPushMatrix();
		glScaled(1.0, 3.0, 5.0);
		glRotated(90, 0, 0, 1.0);
		drawWall(0.02);
		glPopMatrix();


		glPushMatrix();
		glScaled(5.0, 3.0, 1.0);
		glRotated(-90, 1.0, 0.0, 0.0);
		drawWall(0.02);
		glPopMatrix();


		glPushMatrix();
		glScaled(5.0, 3.0, 1.0);
		glTranslated(0.0, 0.0, 5.0);
		glRotated(-90, 1.0, 0.0, 0.0);
		drawWall(0.02);
		glPopMatrix();
	}
	else {
		glClear(GL_COLOR_BUFFER_BIT);
		std::string resultMessage = "Time's up! You ";

		// Check the goal to determine the result
		if (goal) {
			std::cout << "You win!" << std::endl;
			glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
			resultMessage += "win!";
		}
		else {
			std::cout << "You lose!" << std::endl;
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			resultMessage += "lose!";
		}

		glColor3d(1.0, 0.0, 0.0);  // Set text color to white
		glRasterPos2f(0, 0);   // Set the position for the text

		// Display the result message character by character
		for (const char& c : resultMessage) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
		}
	}


	glFlush();
}


void Keyboard(unsigned char key, int x, int y) {
	float d = 0.05;
	float newX = 0;
	float newY = 0;
	float newZ = 0;
	float myX;
	float myY;
	float myZ;

	switch (key) {
	case 't': //top
		camera.setTopView();
		break;
	case 's': //side
		camera.setSideView();
		break;
	case 'f': //front
		camera.setFrontView();
		break;
	case 'u':
		camera.moveY(d);
		break;
	case 'd':
		camera.moveY(-d);
		break;
	case 'r':
		camera.moveX(d);
		break;
	case 'l':
		camera.moveX(-d);
		break;
	case 'c':
		camera.moveZ(d);
		break;
	case 'b':
		camera.moveZ(-d);
		break;
	case 'x':
		// Calculate the new position
		newX = player.position.x + d;
		myZ = player.position.z;

		// Check if the new position is within the boundaries
		if (newX >= WALL_MIN_X && newX <= WALL_MAX_X) {
			player.moveX(d);
		}
		if (newX >= 6 && myZ >= 0 && myZ <= 4) {
			goal = true;
		}

		break;
	case 'w':
		// Calculate the new position
		newX = player.position.x - d;
		myZ = player.position.z;

		// Check if the new position is within the boundaries
		if (newX >= WALL_MIN_X && newX <= WALL_MAX_X) {
			player.moveX(-d);
		}

		if (newX >= 6 && myZ >= 0 && myZ <= 4) {
			goal = true;
		}
		break;
	case 'y':
		// Calculate the new position
		newY = player.position.y + d;

		// Check if the new position is within the boundaries
		if (newY >= WALL_MIN_Y && newY <= WALL_MAX_Y) {
			player.moveY(d);
		}

		break;
	case 'a':
		// Calculate the new position
		newY = player.position.y - d;

		// Check if the new position is within the boundaries
		if (newY >= WALL_MIN_Y && newY <= WALL_MAX_Y) {
			player.moveY(-d);
		}
		break;
	case 'z':
		// Calculate the new position
		newZ = player.position.z + d;
		myX = player.position.x;
		// Check if the new position is within the boundaries
		if (newZ >= WALL_MIN_Z && newZ <= WALL_MAX_Z) {
			player.moveZ(d);
		}

		if (myX >= 6 && newZ >= 0 && newZ <= 4) {
			goal = true;
		}
		break;
	case 'p':
		// Calculate the new position
		newZ = player.position.z - d;
		myX = player.position.x;
		// Check if the new position is within the boundaries
		if (newZ >= WALL_MIN_Z && newZ <= WALL_MAX_Z) {
			player.moveZ(-d);
		}

		if (myX >= 6 && newZ >= 0 && newZ <= 4) {
			goal = true;
		}
		break;
	case 'o':
		if (working) {
			stopAnimate();

		}
		else {
			animate();

		}
		break;
	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}
	setupCamera();

	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 2.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(1200, 750);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Amusement Park");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	initialize();

	glutMainLoop();
}
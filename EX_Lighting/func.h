#pragma once
#define ARRAY_MAX 10000000
#include "GL/freeglut.h"
	
struct Position
{
	float x;
	float y;
	float z;
};


void disp();
void view1(int, int, int, int);
void view2(int, int, int, int);
void view3(int, int, int, int);
void mainMotion();
void idle(void);
void reshape(int, int);
void readPoints();
void InitialProc();
void makeTest(float, float, float);
void make2Test(float, float, float);
void make3Test(float, float, float, GLuint);
void make3Test(float, float, float);
void makeRengaTile(float, float, float, GLuint);
void makeGround(float, float, float, GLuint);
void makeWeapon(float , float , float);
void makeBall(float, float, float,float);

void makeBack(float, float, float);
void keyDown(unsigned char, int, int);
void keyUp(unsigned char, int, int);
void passiveMotion(int , int );
GLuint loadTexture(const char*);

extern Position myPosition;
extern Position lookingPosition;

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <vector>

#include "stb_image.h"

#include "func.h"

#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "gl/freeglut_std.h"

#define PI 3.14159265
#define WINDOW_WIDTH 1980
#define WINDOW_HEIGHT 1080
#define WARP_WIDTH 900
#define WARP_HEIGHT 500
#define movingSpeed 0.032

const char* imagePath = "renga.png";
const char* imagePath1 = "tuti.jpg";
const char* skyFront = "flower.png";
const char* skyRight = "HDR skyRight.jpg";
const char* skyLeft = "HDR skyLeft.jpg";
const char* skyTop = "HDR skyTop.jpg";
const char* skyBot = "HDR skyBot.jpg";
const char* skyBack = "HDR skyBack.jpg";

GLuint textureID;
GLuint textureID1;
GLuint texSkyFront;
GLuint texSkyRight;
GLuint texSkyLeft;
GLuint texSkyTop;
GLuint texSkyBot;
GLuint texSkyBack;

bool pressW = false;
bool pressS = false;
bool pressA = false;
bool pressD = false;
bool pressSPACE = false;
bool pressSHIFT_L = false;
bool pressCTRL_L = false;

double movingStraight;
double movingRight;
double movingUp;
double myAngle;

float angle = 0.0;


Position myPosition;
Position lookingPosition;

void keyDown(unsigned char key, int x, int y)
{
	if (key == 0x1b)
		exit(0);
	if (key == 'w' || key == 'W')
	{
		pressW = true;
	}
	if (key == 's' || key == 'S')
	{
		pressS = true;
	}
	if (key == 'a' || key == 'A')
	{
		pressA = true;
	}
	if (key == 'd' || key == 'D')
	{
		pressD = true;
	}
	if (key == 32)
	{
		pressSPACE = true;
	}
}
void keyUp(unsigned char key, int x, int y) 
{
	if (key == 'w' || key == 'W')
	{
		pressW = false;
	}
	if (key == 's' || key == 'S')
	{
		pressS = false;
	}
	if (key == 'a' || key == 'A')
	{
		pressA = false;
	}
	if (key == 'd' || key == 'D')
	{
		pressD = false;
	}
	if (key == 32)
	{
		pressSPACE = false;
	}
}
void speDown(int key,int x, int y)
{
	if (key == GLUT_KEY_CTRL_L)
	{
		pressCTRL_L = true;
	}
	if (key == GLUT_KEY_SHIFT_L)
	{
		pressSHIFT_L = true;
	}
}
void speUp(int key, int x, int y)
{
	if (key == GLUT_KEY_CTRL_L)
	{
		pressCTRL_L = false;
	}
	if (key == GLUT_KEY_SHIFT_L)
	{
		pressSHIFT_L = false;
	}
}
void clicking(int x, int y)
{
	glutWarpPointer(WARP_WIDTH, WARP_HEIGHT);
	lookingPosition.x -= (x - 900) / 100.0;//dx
	lookingPosition.z -= (y - 500) / 140.0;//dy
	if (lookingPosition.z * 20.0 >= 89.0)
	{
		lookingPosition.z = 4.4;
	}
	else if (lookingPosition.z * 20.0 <= -89.0)
	{
		lookingPosition.z = -4.4;
	}

}
void passiveMotion(int x, int y)
{
	glutWarpPointer(WARP_WIDTH, WARP_HEIGHT);
	lookingPosition.x -= (x - 900) / 100.0;//dx
	lookingPosition.z -= (y - 500) / 140.0;//dy
	if (lookingPosition.z * 20.0  >= 89.0)
	{
		lookingPosition.z = 4.4;
	}
	else if (lookingPosition.z * 20.0  <= -89.0)
	{
		lookingPosition.z = -4.4;
	}
}
void InitialProc()
{
	readPoints();
	glutWarpPointer(WARP_WIDTH, WARP_HEIGHT);
	myPosition.x = 0.0;
	myPosition.y = 0.0;	
	myPosition.z = 1.5;

	lookingPosition.x = 0.0;
	lookingPosition.y = 0;	
	lookingPosition.z = 0;

	textureID = loadTexture(imagePath);
	textureID1 = loadTexture(imagePath1);
	texSkyFront = loadTexture(skyFront);
	texSkyBack = loadTexture(skyBack);
	texSkyBot = loadTexture(skyBot);
	texSkyLeft = loadTexture(skyLeft);
	texSkyRight = loadTexture(skyRight);
	texSkyTop = loadTexture(skyTop);

	//照明の設定
	float lightposMat[] = { 0 , 4, 4, 0 };
	float diffuse[] = { 0.5,0.5,0.5,0.5 };
	float specular[] = { 0.3,0.3,0.3,0.3 };
	float ambient[] = { 0.2,0.2,0.2,0.5 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightposMat);  // 光源の位置
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	//材質の設定
	//float diffuseMat[] = { 1,1,1,1 };
	//float specularMat[] = { 1,1,1,1 };
	//float ambientMat[] = { 1,1,1,1 };
}
void motionController()
{
	movingStraight = 0;
	movingRight = 0;
	if (pressW == true)
	{
		if (pressSHIFT_L == true)
		{
			movingStraight = movingSpeed * 2.0;
		}
		else
		{
			movingStraight = movingSpeed;
		}
	}
	if (pressS == true)
	{
		movingStraight = -movingSpeed;
	}
	if (pressA == true)
	{
		movingRight = -movingSpeed;
	}
	if (pressD == true)
	{
		movingRight = movingSpeed;
	}
	if (pressSPACE == true)
	{
		movingUp += movingSpeed;
	}
	if (pressCTRL_L == true)
	{
		movingUp -= movingSpeed;
	}
	myAngle = lookingPosition.x * 20.0;//向いている角度
	double radian = myAngle / 180.0 * PI;
	myPosition.x -= sin(radian) * movingStraight;
	myPosition.y += cos(radian) * movingStraight;
	myPosition.x += cos(radian) * movingRight;
	myPosition.y -= -sin(radian) * movingRight;

}
void disp()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   /* 画面を消去 */
	glMatrixMode(GL_MODELVIEW);
	angle += 0.03;
	float lightposMat[] = { 0 ,  4, 4, 0 };
	float diffuse[] = { 0.5,0.5,0.5,0.5 };
	float specular[] = { 0.3,0.3,0.3,0.3 };
	float ambient[] = { 0.2,0.2,0.2,0.5 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightposMat);  // 光源の位置
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// テクスチャの読み込みとバインド
	glEnable(GL_DEPTH_TEST);	//奥行きを追加
	glPushMatrix();
	view1(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);

	//glPushMatrix();
	//view2(0, 0, 640, 400);
	//glPopMatrix();

	//glPushMatrix();
	//view3(1400, 700, 520, 280);
	//glPopMatrix();

	glutSwapBuffers();	//or glFlush()
}
void idle(void)
{
	//glutPostRedisplay();
}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);					// 射影行列を操作する
	glLoadIdentity();						// 行列を初期化
	gluPerspective(80.0, (double)width / height, 0.1, 150);
	glMatrixMode(GL_MODELVIEW);
}
void view1(int x,int y,int w,int h)
{
	glViewport(x, y, w, h);
	motionController();
	unsigned int angleZ = sin(lookingPosition.z * 20.0 / 180.0 * PI);
	gluLookAt(myPosition.x ,myPosition.y , 0.5+ movingUp,
		myPosition.x - (sin(lookingPosition.x * 20.0 / 180.0 * PI)* (1.0 - angleZ)) , myPosition.y + (cos(lookingPosition.x * 20.0 / 180.0 * PI)* (1.0 - angleZ)), 0.5 + (sin(lookingPosition.z * 20.0 / 180.0 * PI)* 2.0) + movingUp,
		0, 0, 1);
	float lightposMat[] = { 0,4,4,0 };
	float diffuse[] = { 0.1,0.1,0.1,1 };
	float specular[] = { 0.3,0.3,0.3,0.3 };
	float ambient[] = { 0.2,0.2,0.2,0.5 };
	float diffuseMat[] = { 0.9,0.9,0.9,1 };
	float specularMat[] = { 0.5,0.5,0.5,1 };
	float ambientMat[] = { 0.24725,0.1995,0.0745,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightposMat);  // 光源の位置
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	makeRengaTile(1, 1, 1, textureID);

	makeGround(1, 1, 1, textureID1);

	makeBack(47.0 / 255.0, 110.0 / 255.0, 247.0 / 255.0);


	glPushMatrix();
	glPushAttrib(GL_LIGHTING_BIT);
	glTranslatef( myPosition.x,  myPosition.y, movingUp);
	glRotatef(myAngle, 0, 0, 1);
	glRotatef(lookingPosition.z, 1, 0, 0);
	glEnable(GL_LIGHTING);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat);
	//glMaterialfv(GL_FRONT, GL_SPECULAR,specularMat);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMat);
	glMaterialfv(GL_BACK_LEFT, GL_DIFFUSE, diffuseMat);
	glMaterialfv(GL_BACK_LEFT, GL_SPECULAR, specularMat);
	glMaterialfv(GL_BACK_LEFT, GL_AMBIENT, ambientMat);
	glMaterialf(GL_BACK_LEFT, GL_SHININESS, 10);

	makeWeapon(0.5, 0.5, 0.5);

	glDisable(GL_LIGHTING);
	glPopAttrib();
	glPopMatrix();
	
	glPushAttrib(GL_LIGHTING_BIT);
	glEnable(GL_LIGHTING);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMat);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMat);
	glMaterialf(GL_FRONT, GL_SHININESS, 10);

	makeBall(0.5, 0.5, 0.5,1.0);
	glDisable(GL_LIGHTING);
	glPopAttrib();

	//mainMotion();
	//makeTest(0, 0.5, 0.5 );
}
void view2(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
	gluLookAt(10, -5, 5, 0, 0, 0, 0, 1, 0);
	glRotatef(angle, 1, 1, 0);
	mainMotion();
}
void view3(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
	gluLookAt(0, 2, 2, 0, 0, 0, 0, 1, 0);
	glRotatef(angle, 1, 1, 0);
}
void mainMotion()
{
	glPointSize(4);
	glColor3f(0.4, 0.4, 0.4);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glEnable(GL_TEXTURE_2D);
	// テクスチャの有効化

	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);
	glTexCoord2d(0.0, 3);
	glVertex3f(5, 5, -5);
	glTexCoord2d(3, 3);
	glVertex3f(5, -5, -5);
	glTexCoord2d(3, 0.0);
	glVertex3f(-5, -5, -5);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(-5, 5, -5); //面1(下)
	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texSkyLeft);
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);
	glTexCoord2d(3, 0);
	glVertex3f(-5, 5, -5);
	glTexCoord2d(0, 0);
	glVertex3f(-5, -5, -5);
	glTexCoord2d(0, 3);
	glVertex3f(-5, -5, 5);
	glTexCoord2d(3, 3);
	glVertex3f(-5, 5, 5); //面2(左)
	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texSkyBot);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);

	glTexCoord2d(0.0, 3);
	glVertex3f(-5, 5, 5);
	glTexCoord2d(3, 3);
	glVertex3f(-5, -5, 5);
	glTexCoord2d(3, 0.0);
	glVertex3f(5, -5, 5);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(5, 5, 5); //面3(上)
	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texSkyRight);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);

	glTexCoord2d(0.0, 3);
	glVertex3f(5, 5, 5);
	glTexCoord2d(3, 3);
	glVertex3f(5, -5, 5);
	glTexCoord2d(3, 0.0);
	glVertex3f(5, -5, -5);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(5, 5, -5); //面4(右)
	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texSkyFront);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);

	glTexCoord2d(0.0, 3);
	glVertex3f(5, 5, 5);
	glTexCoord2d(3, 3);
	glVertex3f(-5, 5, 5);
	glTexCoord2d(3, 0.0);
	glVertex3f(-5, 5, -5);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(5, 5, -5); //面5(正面)
	glEnd();

	//glBindTexture(GL_TEXTURE_2D, texSkyBack);
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);

	glTexCoord2d(0.0, 3);
	glVertex3f(5, -5, 5);
	glTexCoord2d(3, 3);
	glVertex3f(-5, -5, 5);
	glTexCoord2d(3, 0.0);
	glVertex3f(-5, -5, -5);
	glTexCoord2d(0.0, 0.0);
	glVertex3f(5, -5, -5); //面6(後ろ)
	glEnd();


	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
void timerCallback(int x)
{
	glutPostRedisplay();
	glutTimerFunc(0.1, timerCallback, 0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("LightingTest");
	glutWarpPointer(WARP_WIDTH, WARP_HEIGHT);
	glutSetCursor(GLUT_CURSOR_NONE);
	InitialProc();
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(speDown);
	glutSpecialUpFunc(speUp);
	glutPassiveMotionFunc(passiveMotion);
	glutMotionFunc(clicking);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutIdleFunc(idle);
	glutTimerFunc(0.1, timerCallback, 0);
	glutReshapeFunc(reshape);
	glutDisplayFunc(disp);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);//色を有効化
	glEnable(GL_COLOR_MATERIAL_FACE);
	//glEnable(GL_DEPTH_TEST);	//奥行きを追加
	//glEnable(GL_LIGHTING);		//ライティングON
	glEnable(GL_LIGHT0);

	glutMainLoop();

	glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL_FACE);
	glDisable(GL_COLOR_MATERIAL);

	return 0;
}
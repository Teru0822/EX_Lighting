#include <stdio.h>
#include <stdlib.h>
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "gl/freeglut_std.h"
#include <string>
#include <math.h>
#include "func.h"

double angle = 0;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(1020, 780);
	glutCreateWindow("Ace combat");
	readPoints();
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutDisplayFunc(disp);
	glEnable(GL_COLOR_MATERIAL);//色を有効化
	glEnable(GL_DEPTH_TEST);	//奥行きを追加
	glEnable(GL_LIGHTING);		//ライティングON
	glEnable(GL_LIGHT0);

	glutMainLoop();

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);

	return 0;
}

void disp()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   /* 画面を消去 */
	glMatrixMode(GL_MODELVIEW);  /* 幾何（描画位置など設定する）モード */
	glLoadIdentity();  /* 幾何を初期化する */
	//glShadeModel(GL_SMOOTH);
	GLfloat lightpos[] = { 0 , 200.0 , 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);  // 光源の位置

	glEnableClientState(GL_VERTEX_ARRAY);//vertex_array使いたいなら入れる
	//光源は回転できない
	//ビューが重なった時の描画するしないは視点からそのオブジェクトまでの距離に依存している
	angle += 0.01;

	glPushMatrix();
	view1(0, 0, 1020, 780);
	glPopMatrix();

	glPushMatrix();
	glScalef(10, 10, 1);
	view3(0, 0, 1100, 350);
	glPopMatrix();

	glPushMatrix();
	view2(0, 0, 560, 400);
	glPopMatrix();





	glutSwapBuffers();	//or glFlush()


}
void idle(void)
{
	glutPostRedisplay();
}
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);					// 射影行列を操作する
	glLoadIdentity();						// 行列を初期化
	gluPerspective(60.0, (double)width / height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}
void view1(int x,int y,int w,int h)
{
	glViewport(x, y, w, h);
	gluLookAt(2, 5, -5, 0, 0, 0, 0, 1, 0);
	glRotatef(angle, 0, 1, 1);
	mainMotion();

}
void view2(int x, int y, int w, int h)
{

	glViewport(x, y, w, h);
	gluLookAt(2, -5, 5, 0, 0, 0, 0, 1, 0);
	glRotatef(angle, 1, 1, 0);
	mainMotion();

}
void view3(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
	gluLookAt(0, 20, 0.1, 0, 0, 0, 0, 1, 0);
	stateOBJ();

}
void mainMotion()
{

	glPointSize(4);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5); //面1(手前)
	glEnd();

	glPointSize(4);
	glColor3f(0.5, 0.5, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5); //面2(左)
	glEnd();

	glPointSize(4);
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5); //面3(奥)
	glEnd();

	glPointSize(4);
	glColor3f(0, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5); //面4(右)
	glEnd();

}
void stateOBJ()
{
	makeState(1,1,1);
}
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
	glEnable(GL_COLOR_MATERIAL);//�F��L����
	glEnable(GL_DEPTH_TEST);	//���s����ǉ�
	glEnable(GL_LIGHTING);		//���C�e�B���OON
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   /* ��ʂ����� */
	glMatrixMode(GL_MODELVIEW);  /* �􉽁i�`��ʒu�Ȃǐݒ肷��j���[�h */
	glLoadIdentity();  /* �􉽂����������� */
	//glShadeModel(GL_SMOOTH);
	GLfloat lightpos[] = { 0 , 200.0 , 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);  // �����̈ʒu

	glEnableClientState(GL_VERTEX_ARRAY);//vertex_array�g�������Ȃ�����
	//�����͉�]�ł��Ȃ�
	//�r���[���d�Ȃ������̕`�悷�邵�Ȃ��͎��_���炻�̃I�u�W�F�N�g�܂ł̋����Ɉˑ����Ă���
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
	glMatrixMode(GL_PROJECTION);					// �ˉe�s��𑀍삷��
	glLoadIdentity();						// �s���������
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
	glVertex3f(-0.5, 0.5, -0.5); //��1(��O)
	glEnd();

	glPointSize(4);
	glColor3f(0.5, 0.5, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5); //��2(��)
	glEnd();

	glPointSize(4);
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5); //��3(��)
	glEnd();

	glPointSize(4);
	glColor3f(0, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5); //��4(�E)
	glEnd();

}
void stateOBJ()
{
	makeState(1,1,1);
}
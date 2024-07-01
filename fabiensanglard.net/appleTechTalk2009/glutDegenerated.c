#include "GLUT/glut.h"
#include <stdio.h>

typedef float vec3_t[3];

enum VERTICE_NAMES { A,B,C,D,E,F,G,H} ;



vec3_t vertices[] = {	{-50, 50,-5},	//A
						{-50,-50,-5},	//B
						{-25, 50,-5},	//C
						{-25,-50,-5},	//D
						{ 25, 50,-5},	//E
						{ 25,-50,-5},	//F
						{ 50, 50,-5},	//G
						{ 50,-50,-5}	//H
};

//unsigned char indices[] = {A,B,C,D,E,F,G,H} ; 
unsigned char degenerated_indices[] = {A,B,C,D,D,E,E,F,G,H} ; 

void drawObjects(void)
{
	glClearColor(0,0,0,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glColor4f(1, 1, 1, 1);
	
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	
	//glDrawElements(GL_TRIANGLE_STRIP, 8, GL_UNSIGNED_BYTE, indices);
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_BYTE, degenerated_indices);
}

void renderScene(void) 
{
	drawObjects();
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	
	if (key == 27) 
		exit(0);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Degenerated GL_TRIANGLE_STRIP");
	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	
	
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	
	glutKeyboardFunc(processNormalKeys);
	
	glutMainLoop();
}

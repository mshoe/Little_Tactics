#include<iostream>
#include <gl/freeglut.h>
#include "CGameEngine.h"
#include "GameBoard.h"
#include "Math.h"
#include "Stats.h"
#include "Queue.h"
#include "PlayerGame.h"
#include "Renderer.h"

/*
Little Tactics
A game by Michael Xu
v0.1, June 2016
RULES: 
1.	Each piece has a base 2 movement range, 2 hit points, and 1 attack
2.	X goes first, turns alternate
3.	Each turn, the player selects a piece and performs an attack, a move, both, or none if none are available (impossible in this game however).
	You cannot skip a turn if there are available moves to be made.
4.	If a piece has a friendly ally piece adjacent to it, it's attack is increased to 2, allowing it to 1-hit any unit
5.	If a piece has 2 or more friendly ally pieces in a chain, it's attack is increased to 2, and it's movement is increased to 3.
	However, when this piece is damaged, all of it's adjacent allys are damaged too.
6.	Attacking a piece bumps it in the direction of the attack, displacing it by 1 tile. This affects lines of units as well, and can be used to
	indirectly bump your own pieces (without damaging them). However, if there is a wall blocking the end of the line of units, no displacement 
	will occur.
6.	Win by elimating all of the opposing players pieces

Technical Accomplishments and Game Features:
1.	Pathfinding movement range.
2.	Damaging a chain of units.
3.	Bumping a line of units.
*/

CGameEngine *gameEngine = new CGameEngine;
PlayerGame *playState = new PlayerGame;

//GameBoard *board = new GameBoard(8, 8, 1);
//PlayerGame *game = new PlayerGame(board);

GLboolean polySmooth = GL_TRUE;

void init(void) {
	GLfloat values[2];

	//Light
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 0.9f, 0.9f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 0.9f, 0.9f, 1.0f };
	GLfloat light_position[] = { 50000.f, 1.f, 1000.0f, 50.0f };

	//Material
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 1.0f };
	/*	select clearing (background) color */
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	//game->getRenderer()->initDisplayLists();
}

void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_UP) {

		}
		break;
	default:
		break;
	}
}

void KeyBoard(unsigned char key, int x, int y) {
	gameEngine->KeyBoard(key, x, y);
}

void reShape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		glOrtho(-6.5f, 6.5f, -6.5f * (GLfloat)h / (GLfloat)w,
			6.5f * (GLfloat)h / (GLfloat)w, -9.0f, 10.0f);
	}
	else {
		glOrtho(-6.5f, 6.5f, -6.5f * (GLfloat)w / (GLfloat)h,
			6.5f * (GLfloat)w / (GLfloat)h, -9.0f, 10.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(4.5f, 2.5f, 1.f, 3.5f, 3.5f, 0.0f, 0.f, 0.f, 1.f);
	//OVERLAY WILL BE AT (3.f, 3.f, 0.f)
}

void Draw() {
	gameEngine->Draw();
	/*game->getRenderer()->renderGame();*/
}

void IdleUpdate() {
	gameEngine->IdleUpdate();
	/*game->winner = game->checkWinner();
	glutPostRedisplay();*/
}

int main(int argc, char** argv)
{
	/*
	Declare initial window size, position, and display mode
	(single buffer and RGBA). Open window with "Little Tactics"
	in its title bar. Call initialization routines.
	Register callback function to display graphics.
	Enter main loop and process events
	*/
	std::cout << "Little Tactics" << std::endl << "A game by Michael Xu" << std::endl;

	gameEngine->ChangeState(playState);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(750, 750);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Little Tactics");
	init();
	glutMouseFunc(mouse);
	glutKeyboardFunc(KeyBoard);
	glutReshapeFunc(reShape);
	glutDisplayFunc(Draw);
	glutIdleFunc(IdleUpdate);
	glutMainLoop();

	return 0;
}
#include "Renderer.h"

Renderer::Renderer() {
	game = nullptr;
	rotation = 0.f;
	initDisplayLists();
}

Renderer::Renderer(PlayerGame * game) {
	this->game = game;
	this->ui = game->getUI();
	rotation = 0.f;
	initDisplayLists();
}

void Renderer::render(const Tile * tile)
{
	//Voxel
	Vector3<float> *color = tile->color;
	glColor3f(color->x, color->y, color->z);
	GLfloat mat_diffuse[] = { color->x, color->y, color->z, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	int i, j;
	for (i = 0; i < 6; i++) {
		glBegin(GL_POLYGON);
		for (j = 0; j < 4; j++) {
			glVertex3f(tile->vertices[4 * i + j]->x, tile->vertices[4 * i + j]->y, tile->vertices[4 * i + j]->z);
		}
		glEnd();
	}
}

void Renderer::render(const Piece * piece)
{
	Vector3<float> *color = piece->color;
	glColor3f(color->x, color->y, color->z);

	GLfloat mat_diffuse[] = { color->x, color->y, color->z, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	int i, j;
	for (i = 0; i < 6; i++) {
		glBegin(GL_POLYGON);
		for (j = 0; j < 4; j++) {
			glVertex3f(piece->vertices[4 * i + j]->x, piece->vertices[4 * i + j]->y, piece->vertices[4 * i + j]->z);
		}
		glEnd();
	}

	glColor3f(1.f, 0.f, 0.f);//black
	float x = piece->coordinates->x;
	float y = piece->coordinates->y;
	float z = piece->coordinates->z;
	float size = piece->size;
	float tileSize = piece->tileSize;
	//rendering eyes
	if (piece->facing == NORTH) {
		glBegin(GL_POLYGON);
		glVertex3f(x - size / 2 - size / 64, y + size / 4, z + tileSize / 2 + size / 4);
		glVertex3f(x - size / 2 - size / 64, y + size / 4 - size / 8, z + tileSize / 2 + size / 4);
		glVertex3f(x - size / 2 - size / 64, y + size / 4 - size / 8, z + tileSize / 2 + size / 2 + size / 16);
		glVertex3f(x - size / 2 - size / 64, y + size / 4, z + tileSize / 2 + size / 2 + size / 16);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x - size / 2 - size / 64, y - size / 4, z + tileSize / 2 + size / 4);
		glVertex3f(x - size / 2 - size / 64, y - size / 4 + size / 8, z + tileSize / 2 + size / 4);
		glVertex3f(x - size / 2 - size / 64, y - size / 4 + size / 8, z + tileSize / 2 + size / 2 + size / 16);
		glVertex3f(x - size / 2 - size / 64, y - size / 4, z + tileSize / 2 + size / 2 + size / 16);
		glEnd();
	}
	else if (piece->facing == EAST) {
		glBegin(GL_POLYGON);
		glVertex3f(x + size / 4, y + size / 2 + size / 64, z + tileSize / 2 + size / 4);
		glVertex3f(x + size / 4 - size / 8, y + size / 2 + size / 64, z + tileSize / 2 + size / 4);
		glVertex3f(x + size / 4 - size / 8, y + size / 2 + size / 64, z + tileSize / 2 + size / 2 + size / 16);
		glVertex3f(x + size / 4, y + size / 2 + size / 64, z + tileSize / 2 + size / 2 + size / 16);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x - size / 4, y + size / 2 + size / 64, z + tileSize / 2 + size / 4);
		glVertex3f(x - size / 4 + size / 8, y + size / 2 + size / 64, z + tileSize / 2 + size / 4);
		glVertex3f(x - size / 4 + size / 8, y + size / 2 + size / 64, z + tileSize / 2 + size / 2 + size / 16);
		glVertex3f(x - size / 4, y + size / 2 + size / 64, z + tileSize / 2 + size / 2 + size / 16);
		glEnd();
	}
	else if (piece->facing == SOUTH) {
		glBegin(GL_POLYGON);
		glVertex3f(x + size / 2 + size / 64, y + size / 4, z + tileSize / 2 + size / 4);
		glVertex3f(x + size / 2 + size / 64, y + size / 4 - size / 8, z + tileSize / 2 + size / 4);
		glVertex3f(x + size / 2 + size / 64, y + size / 4 - size / 8, z + tileSize / 2 + size / 2 + size / 16);
		glVertex3f(x + size / 2 + size / 64, y + size / 4, z + tileSize / 2 + size / 2 + size / 16);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x + size / 2 + size / 64, y - size / 4, z + tileSize / 2 + size / 4);
		glVertex3f(x + size / 2 + size / 64, y - size / 4 + size / 8, z + tileSize / 2 + size / 4);
		glVertex3f(x + size / 2 + size / 64, y - size / 4 + size / 8, z + tileSize / 2 + size / 2 + size / 16);
		glVertex3f(x + size / 2 + size / 64, y - size / 4, z + tileSize / 2 + size / 2 + size / 16);
		glEnd();
	}
	else if (piece->facing == WEST) {
		glBegin(GL_POLYGON);
		glVertex3f(x + size / 4, y - size / 2 - size / 64, z + tileSize / 2 + size / 4);
		glVertex3f(x + size / 4 - size / 8, y - size / 2 - size / 64, z + tileSize / 2 + size / 4);
		glVertex3f(x + size / 4 - size / 8, y - size / 2 - size / 64, z + tileSize / 2 + size / 2 + size / 16);
		glVertex3f(x + size / 4, y - size / 2 - size / 64, z + tileSize / 2 + size / 2 + size / 16);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x - size / 4, y - size / 2 - size / 64, z + tileSize / 2 + size / 4);
		glVertex3f(x - size / 4 + size / 8, y - size / 2 - size / 64, z + tileSize / 2 + size / 4);
		glVertex3f(x - size / 4 + size / 8, y - size / 2 - size / 64, z + tileSize / 2 + size / 2 + size / 16);
		glVertex3f(x - size / 4, y - size / 2 - size / 64, z + tileSize / 2 + size / 2 + size / 16);
		glEnd();
	}
}

void Renderer::renderMovementTiles(const Tile * tile)
{
	int x = tile->coordinates->x;
	int y = tile->coordinates->y;
	int z = tile->coordinates->z;
	glColor3f(0.74902f, 0.847059f, 0.847059f);

	GLfloat mat_specular[] = { 0.74902f, 0.847059f, 0.847059f, 1.0f };//light blue
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glBegin(GL_POLYGON);
	glVertex3f((x + 0.4f), (y + 0.4f), z + 0.4f);
	glVertex3f((x - 0.4f), (y + 0.4f), z + 0.4f);
	glVertex3f((x - 0.4f), (y - 0.4f), z + 0.4f);
	glVertex3f((x + 0.4f), (y - 0.4f), z + 0.4f);
	glEnd();
}

void Renderer::renderAttackTiles(const Piece * piece)
{
	int x = piece->coordinates->x;
	int y = piece->coordinates->y;
	int z = piece->coordinates->z;
	glColor3f(1.0f, 0.0f, 0.0f);//red

	GLfloat mat_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	glBegin(GL_POLYGON);
	glVertex3f((x + 0.4f), (y + 0.4f), z + 0.4f);
	glVertex3f((x - 0.4f), (y + 0.4f), z + 0.4f);
	glVertex3f((x - 0.4f), (y - 0.4f), z + 0.4f);
	glVertex3f((x + 0.4f), (y - 0.4f), z + 0.4f);
	glEnd();
}

void Renderer::renderSelector() {
	if (game->selector == nullptr)
		return;
	int x = game->selector->x;
	int y = game->selector->y;
	int z = game->selector->z;
	glColor3f(0.0f, 1.0f, 1.0f);

	GLfloat mat_specular[] = { 0.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

	glBegin(GL_POLYGON);
	glVertex3f((x + 0.4f), (y + 0.4f), z + 0.42f);
	glVertex3f((x - 0.4f), (y + 0.4f), z + 0.42f);
	glVertex3f((x - 0.4f), (y - 0.4f), z + 0.42f);
	glVertex3f((x + 0.4f), (y - 0.4f), z + 0.42f);
	glEnd();
}

void Renderer::renderSelectedPiece()
{
	if (game->currentPiece != nullptr) {
		int x = game->currentPiece->coordinates->x;
		int y = game->currentPiece->coordinates->y;
		int z = game->currentPiece->coordinates->z;
		glColor3f(1.f, 1.f, 0.f);

		glBegin(GL_POLYGON);
		glVertex3f((x + 0.41f), (y + 0.41f), z + 0.43f);
		glVertex3f((x - 0.41f), (y + 0.41f), z + 0.43f);
		glVertex3f((x - 0.41f), (y - 0.41f), z + 0.43f);
		glVertex3f((x + 0.41f), (y - 0.41f), z + 0.43f);
		glEnd();
	}
}

void Renderer::renderLaser(Vector3<float> *p1Coords, Piece *piece2, int direction, int ATK)
{
	float tileSize = 0.75f;
	float x1 = p1Coords->x;
	float y1 = p1Coords->y;
	float z1 = p1Coords->z + tileSize / 2;

	float x2 = piece2->coordinates->x;
	float y2 = piece2->coordinates->y;
	float z2 = piece2->coordinates->z + tileSize / 2;

	float size = 0.15f * ATK;
	if (ATK == 1) {
		glColor3f(0.f, 0.5f, 1.f);
	}
	else {
		glColor3f(1.f, 1.f, 0.f);
	}

	switch (direction) {
	case SOUTH:
	case NORTH:
		glBegin(GL_POLYGON);
		glVertex3f(x1, y1 + size / 2, z1);
		glVertex3f(x1, y1 - size / 2, z1);
		glVertex3f(x1, y1 - size / 2, z1 + size / 2);
		glVertex3f(x1, y1 + size / 2, z1 + size / 2);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x1, y1 + size / 2, z1);
		glVertex3f(x1, y1 + size / 2, z1 + size / 2);
		glVertex3f(x2, y2 + size / 2, z2 + size / 2);
		glVertex3f(x2, y2 + size / 2, z2);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x1, y1 + size / 2, z1 + size / 2);
		glVertex3f(x1, y1 - size / 2, z1 + size / 2);
		glVertex3f(x2, y2 - size / 2, z2 + size / 2);
		glVertex3f(x2, y2 + size / 2, z2 + size / 2);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x1, y1 - size / 2, z1);
		glVertex3f(x1, y1 - size / 2, z1 + size / 2);
		glVertex3f(x2, y2 - size / 2, z2 + size / 2);
		glVertex3f(x2, y2 - size / 2, z2);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x1, y1 + size / 2, z1);
		glVertex3f(x1, y1 - size / 2, z1);
		glVertex3f(x2, y2 - size / 2, z2);
		glVertex3f(x2, y2 + size / 2, z2);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x2, y2 + size / 2, z2);
		glVertex3f(x2, y2 - size / 2, z2);
		glVertex3f(x2, y2 - size / 2, z2 + size / 2);
		glVertex3f(x2, y2 + size / 2, z2 + size / 2);
		glEnd();
		break;
	case EAST:
	case WEST:
		glBegin(GL_POLYGON);
		glVertex3f(x1 + size / 2, y1, z1);
		glVertex3f(x1 - size / 2, y1, z1);
		glVertex3f(x1 - size / 2, y1, z1 + size / 2);
		glVertex3f(x1 + size / 2, y1, z1 + size / 2);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x1 + size / 2, y1, z1);
		glVertex3f(x1 + size / 2, y1, z1 + size / 2);
		glVertex3f(x2 + size / 2, y2, z2 + size / 2);
		glVertex3f(x2 + size / 2, y2, z2);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x1 + size / 2, y1, z1 + size / 2);
		glVertex3f(x1 - size / 2, y1, z1 + size / 2);
		glVertex3f(x2 - size / 2, y2, z2 + size / 2);
		glVertex3f(x2 + size / 2, y2, z2 + size / 2);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x1 - size / 2, y1, z1);
		glVertex3f(x1 - size / 2, y1, z1 + size / 2);
		glVertex3f(x2 - size / 2, y2, z2 + size / 2);
		glVertex3f(x2 - size / 2, y2, z2);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x1 + size / 2, y1, z1);
		glVertex3f(x1 - size / 2, y1, z1);
		glVertex3f(x2 - size / 2, y2, z2);
		glVertex3f(x2 + size / 2, y2, z2);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(x2 + size / 2, y2, z2);
		glVertex3f(x2 - size / 2, y2, z2);
		glVertex3f(x2 - size / 2, y2, z2 + size / 2);
		glVertex3f(x2 + size / 2, y2, z2 + size / 2);
		glEnd();
		break;
	default:
		break;
	}
}

void Renderer::initDisplayLists()
{
	wordMove = glGenLists(8);
	
	glNewList(8, GL_COMPILE); 
		Vector3<float> *test = new Vector3<float>(0.f, 0.f, 0.f);
		Vector3<float> *testColor = new Vector3<float>(1.f, 1.f, 1.f);
		renderWordMove(test, testColor, 0.5f);
		delete test;
		delete testColor;
	glEndList();
	

	glShadeModel(GL_FLAT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Renderer::renderTurnNum(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	Vector3<float> *copy = new Vector3<float>(coordinates->x, coordinates->y, coordinates->z);
	glColor3f(color->x, color->y, color->z);

	int turn = ui->turn;

	int hundreds = turn / 100;
	int tens = (turn - hundreds * 100) / 10;
	int ones = (turn - hundreds * 100 - tens * 10);

	renderInt(copy, color, size, hundreds);

	copy->translateVector(0.f, 1.f, 0.f);

	renderInt(copy, color, size, tens);

	copy->translateVector(0.f, 1.f, 0.f);

	renderInt(copy, color, size, ones);

	delete copy;
}

void Renderer::renderInt(Vector3<float> *coordinates, Vector3<float> *color, float size, int num) {
	switch (num) {
	case 0:
		render0(coordinates, color, size);
		break;
	case 1:
		render1(coordinates, color, size);
		break;
	case 2:
		render2(coordinates, color, size);
		break;
	case 3:
		render3(coordinates, color, size);
		break;
	case 4:
		render4(coordinates, color, size);
		break;
	case 5:
		render5(coordinates, color, size);
		break;
	case 6:
		render6(coordinates, color, size);
		break;
	case 7:
		render7(coordinates, color, size);
		break;
	case 8:
		render8(coordinates, color, size);
		break;
	case 9:
		render9(coordinates, color, size);
		break;
	default:
		break;
	}
}

void Renderer::renderActionSelector(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glEnd();
}

void Renderer::renderWordMove(Vector3<float>* coordinates, Vector3<float> *color, float size)
{
	Vector3<float> *copy = new Vector3<float>(coordinates->x, coordinates->y, coordinates->z);

	renderM(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderO(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderV(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderE(copy, color, size);

	delete copy;
}

void Renderer::renderWordAttack(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	Vector3<float> *copy = new Vector3<float>(coordinates->x, coordinates->y, coordinates->z);
	renderA(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderT(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderT(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderA(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderC(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderK(copy, color, size);

	delete copy;
}

void Renderer::renderWordWait(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	Vector3<float> *copy = new Vector3<float>(coordinates->x, coordinates->y, coordinates->z);
	renderW(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderA(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderI(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderT(copy, color, size);
	delete copy;
}

void Renderer::renderWordTurn(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	Vector3<float> *copy = new Vector3<float>(coordinates->x, coordinates->y, coordinates->z);
	renderT(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderU(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderR(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderN(copy, color, size);
	delete copy;
}

void Renderer::renderWordGame(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	Vector3<float> *copy = new Vector3<float>(coordinates->x, coordinates->y, coordinates->z);
	renderG(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderA(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderM(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderE(copy, color, size);
	delete copy;
}

void Renderer::renderWordAuto(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	Vector3<float> *copy = new Vector3<float>(coordinates->x, coordinates->y, coordinates->z);
	renderA(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderU(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderT(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderO(copy, color, size);
	delete copy;
}

void Renderer::renderWordRestart(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	Vector3<float> *copy = new Vector3<float>(coordinates->x, coordinates->y, coordinates->z);
	renderR(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderE(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderS(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderT(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderA(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderR(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderT(copy, color, size);
	delete copy;
}

void Renderer::renderWordExit(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	Vector3<float> *copy = new Vector3<float>(coordinates->x, coordinates->y, coordinates->z);
	renderE(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderX(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderI(copy, color, size);
	copy->translateVector(0.f, size * 2, 0.f);
	renderT(copy, color, size);
	delete copy;
}

void Renderer::renderA(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size/2, y + size / 4, z - size / 2);
	glVertex3f(x + size/2, y + size / 2, z - size / 2);
	glVertex3f(x + size/2, y + size / 2, z + size / 2);
	glVertex3f(x + size/2, y + size / 4, z + size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size/2, y + size / 4, z + size / 2);
	glVertex3f(x + size/2, y - size / 4, z + size / 2);
	glVertex3f(x + size/2, y - size / 4, z + size / 4);
	glVertex3f(x + size/2, y + size / 4, z + size / 4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size/2, y + size / 4, z);
	glVertex3f(x + size/2, y - size / 4, z);
	glVertex3f(x + size/2, y - size / 4, z - size / 4);
	glVertex3f(x + size/2, y + size / 4, z - size / 4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size/2, y - size / 4, z - size / 2);
	glVertex3f(x + size/2, y - size / 2, z - size / 2);
	glVertex3f(x + size/2, y - size / 2, z + size / 2);
	glVertex3f(x + size/2, y - size / 4, z + size / 2);
	glEnd();
}

void Renderer::renderC(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z - size / 4);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4);
	glVertex3f(x + size / 2, y - size / 4, z + size / 4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4);
	glEnd();
}

void Renderer::renderE(Vector3<float>* coordinates, Vector3<float> *color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	//4 rectangles

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 4, z - size / 2);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2 - size / 5);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2 - size / 5);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / (5 * 2));
	glVertex3f(x + size / 2, y + size / 4, z + size / (5 * 2));
	glVertex3f(x + size / 2, y + size / 4, z - size / (5 * 2));
	glVertex3f(x + size / 2, y - size / 2, z - size / (5 * 2));
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2 + size / 5);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2 + size / 5);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glEnd();
}

void Renderer::renderG(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 4, z - size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4 - size / 16);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z);
	glVertex3f(x + size / 2, y + size / 2, z);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 4, z - size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z - size / 8);
	glVertex3f(x + size / 2, y - size / 16, z - size / 8);
	glVertex3f(x + size / 2, y - size / 16, z);
	glVertex3f(x + size / 2, y + size / 2, z);
	glEnd();
}

void Renderer::renderK(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y, z);
	glVertex3f(x + size / 2, y - size / 4 - size / 16, z);
	glVertex3f(x + size / 2, y + size / 4 - size / 16, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y, z);
	glVertex3f(x + size / 2, y - size / 4 - size / 16, z);
	glVertex3f(x + size / 2, y + size / 4 - size / 16, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glEnd();
}

void Renderer::renderI(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 8, z - size / 4);
	glVertex3f(x + size / 2, y - size / 8, z - size / 4);
	glVertex3f(x + size / 2, y - size / 8, z + size / 4);
	glVertex3f(x + size / 2, y + size / 8, z + size / 4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glEnd();
}

void Renderer::renderM(Vector3<float>* coordinates, Vector3<float> *color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	//Gotta do a polgyon with no > 180 degree inside angles

	//just four 4-sided polygons, 2 of them are rectangles, 4 of them are parallelograms

	glBegin(GL_POLYGON);
	glVertex3f(x + size/2, y + size/2, z + size/2);
	glVertex3f(x + size/2, y + size/2, z - size/2);
	glVertex3f(x + size/2, y + size/4, z - size/2);
	glVertex3f(x + size/2, y + size/4, z + size/2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size/2, y + size/4, z + size/4);
	glVertex3f(x + size/2, y + size/4, z + size/2);
	glVertex3f(x + size/2, y, z + size/4);
	glVertex3f(x + size/2, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size/2, y, z);
	glVertex3f(x + size/2, y, z + size/4);
	glVertex3f(x + size/2, y - size/4, z + size/2);
	glVertex3f(x + size/2, y - size/4, z + size/4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size/2, y - size/4, z + size/2);
	glVertex3f(x + size/2, y - size/4, z - size/2);
	glVertex3f(x + size/2, y - size/2, z - size/2);
	glVertex3f(x + size/2, y - size/2, z + size/2);
	glEnd();
}

void Renderer::renderN(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glVertex3f(x + size / 2, y - size / 4, z - size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z + size / 8);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z - size / 8);
	glVertex3f(x + size / 2, y + size / 4, z - size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z - size / 2);
	glEnd();
}

void Renderer::renderO(Vector3<float>* coordinates, Vector3<float> *color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	//4 rectangles

	glBegin(GL_POLYGON);
	glVertex3f(x + size/2, y + size/2, z - size/2);
	glVertex3f(x + size/2, y + size/2, z + size/2);
	glVertex3f(x + size/2, y + size/4, z + size/2);
	glVertex3f(x + size/2, y + size/4, z - size/2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size/2, y + size/2, z + size/2);
	glVertex3f(x + size/2, y - size/2, z + size/2);
	glVertex3f(x + size/2, y - size/2, z + size/4);
	glVertex3f(x + size/2, y + size/2, z + size/4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size/2, y - size/2, z + size/2);
	glVertex3f(x + size/2, y - size/2, z - size/2);
	glVertex3f(x + size/2, y - size/4, z - size/2);
	glVertex3f(x + size/2, y - size/4, z + size/2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size/2, y - size/2, z - size/4);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glEnd();
}

void Renderer::renderQ(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	//4 rectangles

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z - size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 4, z - size / 2);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z - size / 4);
	glVertex3f(x + size / 2, y, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2 - size / 4);
	glVertex3f(x + size / 2, y + size / 2 + size / 4, z - size / 2);
	glEnd();
}

void Renderer::renderR(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y - size / 4, z + size / 4 + size / 8);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z);
	glVertex3f(x + size / 2, y + size / 2, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z);
	glVertex3f(x + size / 2, y + size / 2, z);
	glVertex3f(x + size / 2, y + size / 2, z + size / 8);
	glVertex3f(x + size / 2, y - size / 4, z + size / 8);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y, z);
	glVertex3f(x + size / 2, y - size / 4 - size / 16, z);
	glVertex3f(x + size / 2, y + size / 4 - size / 16, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glEnd();
}

void Renderer::renderS(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	render5(coordinates, color, size);
}

void Renderer::renderT(Vector3<float>* coordinates, Vector3<float> *color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 8, z - size / 2);
	glVertex3f(x + size / 2, y - size / 8, z - size / 2);
	glVertex3f(x + size / 2, y - size / 8, z + size / 4);
	glVertex3f(x + size / 2, y + size / 8, z + size / 4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glEnd();
}

void Renderer::renderU(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z - size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 4, z - size / 2);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glEnd();
	
}

void Renderer::renderV(Vector3<float>* coordinates, Vector3<float> *color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glVertex3f(x + size / 2, y, z);
	glVertex3f(x + size / 2, y, z - size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z + size / 2);
	glVertex3f(x + size / 2, y, z);
	glVertex3f(x + size / 2, y, z - size / 2);
	glEnd();
}

void Renderer::renderW(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 4, z - size / 2);
	glVertex3f(x + size / 2, y + size / 4, z + size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z - size / 4);
	glVertex3f(x + size / 2, y + size / 4, z - size / 2);
	glVertex3f(x + size / 2, y, z - size / 4);
	glVertex3f(x + size / 2, y, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y, z);
	glVertex3f(x + size / 2, y, z - size / 4);
	glVertex3f(x + size / 2, y - size / 4, z - size / 2);
	glVertex3f(x + size / 2, y - size / 4, z - size / 4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glVertex3f(x + size / 2, y - size / 4, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glEnd();

}

void Renderer::renderX(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	//2 rectangles
	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4);
	glVertex3f(x + size / 2, y + size / 4, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4);
	glVertex3f(x + size / 2, y - size / 4, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4);
	glEnd();
}

void Renderer::render0(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	//4 rectangles

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z - size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 8);
	glEnd();

	//diagonal to signify it is a zero and not an O
	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y - size / 4 - size / 8, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 4 + size / 8, z - size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 4, z - size / 2);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glEnd();
}

void Renderer::render1(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glVertex3f(x + size / 2, y - size / 4, z - size / 2);
	glEnd();
}

void Renderer::render2(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 16);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y + size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 4, z + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 2, z - size / 16);
	glVertex3f(x + size / 2, y - size / 2, z - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y - size / 2, z - size / 16);
	glVertex3f(x + size / 2, y - size / 4, z - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 16);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4 - size / 16);
	glEnd();
}

void Renderer::render3(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 16);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y + size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 4, z + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 2, z - size / 16);
	glVertex3f(x + size / 2, y - size / 2, z - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 16);
	glVertex3f(x + size / 2, y + size / 4, z - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 16);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4 - size / 16);
	glEnd();
}

void Renderer::render4(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y - size / 4, z + size / 2);
	glVertex3f(x + size / 2, y - size / 4, z);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z - size / 16);
	glVertex3f(x + size / 2, y - size / 2, z + size / 8);
	glVertex3f(x + size / 2, y + size / 2, z + size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z - size / 2);
	glEnd();
}

void Renderer::render5(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 16);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y - size / 2, z + size / 16);
	glVertex3f(x + size / 2, y - size / 4, z + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 2, z - size / 16);
	glVertex3f(x + size / 2, y - size / 2, z - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 16);
	glVertex3f(x + size / 2, y + size / 4, z - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 16);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4 - size / 16);
	glEnd();
}

void Renderer::render6(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 16);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y - size / 2, z + size / 16);
	glVertex3f(x + size / 2, y - size / 4, z + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 2, z - size / 16);
	glVertex3f(x + size / 2, y - size / 2, z - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 16);
	glVertex3f(x + size / 2, y + size / 4, z - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 16);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4 - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y - size / 2, z - size / 16);
	glVertex3f(x + size / 2, y - size / 4, z - size / 16);
	glEnd();
}

void Renderer::render7(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 16);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z + size / 2);
	glVertex3f(x + size / 2, y + size / 4, z - size / 2);
	glEnd();
}

void Renderer::render8(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 16);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y - size / 2, z + size / 16);
	glVertex3f(x + size / 2, y - size / 4, z + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 2, z - size / 16);
	glVertex3f(x + size / 2, y - size / 2, z - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y + size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 4, z + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 16);
	glVertex3f(x + size / 2, y + size / 4, z - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 2);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 16);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4 - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y - size / 2, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y - size / 2, z - size / 16);
	glVertex3f(x + size / 2, y - size / 4, z - size / 16);
	glEnd();
}

void Renderer::render9(Vector3<float>* coordinates, Vector3<float>* color, float size)
{
	float x = coordinates->x;
	float y = coordinates->y;
	float z = coordinates->z;
	glColor3f(color->x, color->y, color->z);

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 2);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 16);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 4, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y - size / 2, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y - size / 2, z + size / 16);
	glVertex3f(x + size / 2, y - size / 4, z + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y - size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 2, z - size / 16);
	glVertex3f(x + size / 2, y - size / 2, z - size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y + size / 2, z + size / 4 + size / 8);
	glVertex3f(x + size / 2, y + size / 2, z + size / 16);
	glVertex3f(x + size / 2, y + size / 4, z + size / 16);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(x + size / 2, y + size / 4, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 4 - size / 8);
	glVertex3f(x + size / 2, y + size / 2, z - size / 16);
	glVertex3f(x + size / 2, y + size / 4, z - size / 16);
	glEnd();
}

void Renderer::setAnim(Animation * anim)
{
	this->anim = anim;
}

void Renderer::renderGame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPushMatrix();

	//ROTATION OF BOARD

		renderBoard(game->getBoard(), game->currentMovementList, game->currentAttackList);
		renderPieces(game->playerPieceList);
		renderPieces(game->cpuPieceList);
		renderLasers();

	renderUI();

	glFlush();
	//glPopMatrix();
	glutSwapBuffers();
}

void Renderer::renderBoard(GameBoard *board, List<Node> *movList, List<Node> *atkList)
{
	GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_shininess[] = { 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	Tile *tile;
	Piece *piece;
	int i, j, k;
	for (k = 0; k < board->HEIGHT; k++) {
		for (i = 0; i < board->ROWS; i++) {
			for (j = 0; j < board->COLS; j++) {
				Vector3<float> *coordinates = new Vector3<float>(i, j, k);

				//First: display the tiles
				tile = board->getTile(coordinates);
				render(tile);

				//If MovList: display the possible movements
				if (movList != nullptr) {
					if (movList->search(tile) && !tile->coordinates->compareVector(game->selector))
						renderMovementTiles(tile);
				}

				//Second: display the pieces
				piece = tile->getPiece();
				if (piece != nullptr) {
					//render(piece);

					//If AtkList: display the possible targets
					if (atkList != nullptr) {
						if (atkList->search(piece))
							renderAttackTiles(piece);
					}
				}
				delete coordinates;
			}
		}
	}
}

void Renderer::renderUI()
{
	if (game->selectorState == SELECTOR_ACTIVE)
		renderSelector();

	renderSelectedPiece();

	//SELECTING AN ACTION
	Vector3<float> *test = new Vector3<float>(9.5f, -1.f, 1.f);
	Vector3<float> *testColor = new Vector3<float>(1.f, 1.f, 1.f);
	float size = 0.5f;

	//RIGHT MENU

	//MOVE
	if (ui->firstAction == MOVE || ui->secondAction == MOVE || game->winner != -1) {
		testColor->changeVector(0.3f, 0.3f, 0.3f);
	}
	renderWordMove(test, testColor, size);
	//

	testColor->changeVector(1.f, 1.f, 1.f);
	test->translateVector(1.f, -1.f, 0.f);

	//ATTACK
	if (ui->firstAction == ATTACK || ui->secondAction == ATTACK || game->winner != -1) {
		testColor->changeVector(0.3f, 0.3f, 0.3f);
	}
	renderWordAttack(test, testColor, size);
	//

	testColor->changeVector(1.f, 1.f, 1.f);
	test->translateVector(1.f, -1.f, 0.f);

	//WAIT
	if (ui->firstAction == 0 || game->winner != -1) {
		testColor->changeVector(0.3f, 0.3f, 0.3f);
	}
	renderWordWait(test, testColor, size);
	//

	testColor->changeVector(1.f, 1.f, 1.f);
	test->translateVector(-1.f, 1.f, 0.f);

	//LEFT MENU
	size = 0.5f;
	glRotatef(-90, 0.f, 0.f, 1.f);
	test->changeVector(2.f, 4.5f, 0.5f);

	//AUTO
	renderWordAuto(test, testColor, size);
	//
	
	//RESTART
	test->translateVector(1.f, -2.f, 0.f);
	renderWordRestart(test, testColor, size);
	//

	//EXIT
	test->translateVector(1.f, 4.f, 0.f);
	renderWordExit(test, testColor, size);
	//

	glRotatef(90, 0.f, 0.f, 1.f);

	testColor->changeVector(1.f, 1.f, 1.f);
	test->changeVector(9.5f, -1.5f, 0.f);
	//ACTION SELECTOR

	if (ui->leftRightSelection == RIGHT) {
		if (ui->actionSelection == MOVE) {
			test->translateVector(-1.f, 0.5f, 0.f);
			if (ui->currentAction == MOVE) {
				size = 0.75f;
				testColor->changeVector(1.f, 1.f, 0.f);
			}
		}
		else if (ui->actionSelection == ATTACK) {
			test->translateVector(0.f, -0.5f, 0.f);
			if (ui->currentAction == ATTACK) {
				size = 0.75f;
				testColor->changeVector(1.f, 1.f, 0.f);
			}
		}
		else if (ui->actionSelection == WAIT) {
			test->translateVector(1.f, -1.5f, 0.f);
		}
		renderActionSelector(test, testColor, size);
	}
	else if (ui->leftRightSelection == LEFT) {
		glRotatef(-90, 0.f, 0.f, 1.f);
		test->changeVector(2.f, 8.5f, 0.5f);
		if (ui->actionSelection == AUTO) {
			if (ui->currentAction == AUTO) {
				size = 0.75f;
				testColor->changeVector(1.f, 1.f, 0.f);
			}
		}
		else if (ui->actionSelection == RESTART) {
			test->translateVector(0.5f, 0.5f, -0.5f);
			if (ui->currentAction == RESTART) {
				size = 0.75f;
				testColor->changeVector(1.f, 1.f, 1.f);
			}
		}
		else if (ui->actionSelection == EXIT) {
			test->translateVector(1.f, 1.f, -1.f);
			if (ui->currentAction == EXIT) {
				size = 0.75f;
				testColor->changeVector(1.f, 1.f, 0.f);
			}
		}
		renderActionSelector(test, testColor, size);
		glRotatef(90, 0.f, 0.f, 1.f);
	}
	
	//Render Turn and #
	size = 0.5f;
	test->changeVector(-1.f, 1.f, 1.f);
	testColor->changeVector(1.f, 1.f, 1.f);
	renderWordTurn(test, testColor, size);
	test->translateVector(0.f, 4.5f, 0.f);
	renderTurnNum(test, testColor, size);
	test->translateVector(0.f, 0.f, 1.f);
	if (game->winner != -1)
		renderWordGame(test, testColor, size);

	delete test;
	delete testColor;
	//glCallList(1);
}

void Renderer::renderPieces(List<Node> *pieceList)
{
	Node *temp = pieceList->start;
	while (temp != nullptr) {
		render(temp->piece);
		temp = temp->next;
	}
}

void Renderer::renderLasers()
{
	if (!anim->isAttackQueueEmpty()) {
		renderLaser(anim->attackQueue->front->p1Coords,
			anim->attackQueue->front->piece2,
			game->getDirection(anim->attackQueue->front->p1Coords, anim->attackQueue->front->piece2->coordinates),
			anim->attackQueue->front->ATK);
	}
}

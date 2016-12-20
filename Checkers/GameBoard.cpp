#include<iostream>
#include "GameBoard.h"
#include "Math.h"

GameBoard::GameBoard() {
	ROWS = 8; COLS = 8; HEIGHT = 1;
	/*adjMat = new adjMatrix();*/
	initBoard(8, 8, 1);
	linkTiles(8, 8, 1);
}

GameBoard::GameBoard(int rows, int cols, int height) {
	ROWS = rows; COLS = cols; HEIGHT = height;
	initBoard(rows, cols, height);
	linkTiles(rows, cols, height);
}

Tile *GameBoard::getTile(Vector3<float> *coordinates) {
	//height first to organize the layers
	return board[(int)coordinates->z][(int)coordinates->x][(int)coordinates->y];
}

Tile ****GameBoard::getBoard() {
	return board;
}

void GameBoard::initBoard(int rows, int cols, int height) {
	//Standard solid rectangular prism
	//This will be the most basic board type

	int i, j, k;
	//height first, because organization of layers will be by height
	board = new Tile***[height];
	for (i = 0; i < height; i++) {
		board[i] = new Tile **[rows];
		for (j = 0; j < rows; j++) {
			board[i][j] = new Tile *[cols];
		}
	}
	for (k = 0; k < height; k++) {
		for (i = 0; i < rows; i++) {
			for (j = 0; j < cols; j++) {
				//Make the tile
				if (i % 2 != j % 2)
					board[k][i][j] = new Tile((float)i, (float)j, (float)k, 0.91f, 0.76f, 0.65f);//light wood
				else
					board[k][i][j] = new Tile((float)i, (float)j, (float)k, 0.65f, 0.50f, 0.39f);//medium wood

				//Make the piece if there is supposed to be one
				//Checkerboard pattern
				Piece *newPiece;
				if (Math::isEven(i) != Math::isEven(j) && i < ROWS / 3 && j != 1 && j != 6) {
					newPiece = new Piece(79, 2, 1, 1, 2, 1, 0, 1.0f, 1.0f, 1.0f);//white
					board[k][i][j]->changePiece(newPiece);//O
				}
				else if (Math::isEven(i) != Math::isEven(j) && i > ROWS - ROWS / 3 - 1 && j != 1 && j != 6) {
					newPiece = new Piece(88, 2, 1, 1, 2, 1, 1, 0.25f, 0.25f, 0.25f);//dark grey
					board[k][i][j]->changePiece(newPiece);//X
				}
				//else if (i == 7) {
				//	newPiece = new Piece(88, 2, 1, 1, 2, 1, 1, 0.25f, 0.25f, 0.25f);//dark grey
				//	board[k][i][j]->changePiece(newPiece);//X
				//}
			}
		}
	}
}

//void GameBoard::printBoard() {
//	int i, j, k;
//	Piece *piece;
//	char pieceChar;
//	std::cout << "  ";
//	for (k = 0; k < COLS; k++) {
//		std::cout << "  " << k << " ";
//	}
//	std::cout << std::endl;
//	for (i = 0; i < ROWS; i++) {
//		std::cout << "  ";
//		for (k = 0; k < COLS; k++) {
//			std::cout << " ---";
//		}
//		std::cout << std::endl;
//		std::cout << i << " |";
//		for (j = 0; j < COLS; j++) {
//			piece = board[i][j]->getPiece();
//			if (piece == nullptr)
//				pieceChar = 32;
//			else
//				pieceChar = piece->getChar();
//			std::cout << " " << pieceChar << " |";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << "  ";
//	for (k = 0; k < COLS; k++) {
//		std::cout << " ---";
//	}
//	std::cout << std::endl;
//}
//
//void GameBoard::printBoard(List *movList) {
//	int i, j, k;
//	Piece *piece;
//	char pieceChar;
//	std::cout << "  ";
//	for (k = 0; k < COLS; k++) {
//		std::cout << "  " << k << " ";
//	}
//	std::cout << std::endl;
//	for (i = 0; i < ROWS; i++) {
//		std::cout << "  ";
//		for (k = 0; k < COLS; k++) {
//			std::cout << " ---";
//		}
//		std::cout << std::endl;
//		std::cout << i << " |";
//		for (j = 0; j < COLS; j++) {
//			piece = board[i][j]->getPiece();
//			Vector3 *coordinates = new Vector3(i, j);
//			if (movList->search(coordinates)) {
//				pieceChar = 42;
//			}
//			else if (piece == nullptr)
//				pieceChar = 32;
//			else
//				pieceChar = piece->getChar();
//			std::cout << " " << pieceChar << " |";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << "  ";
//	for (k = 0; k < COLS; k++) {
//		std::cout << " ---";
//	}
//	std::cout << std::endl;
//}
//
//void GameBoard::printBoard(List *atkList, int z) {
//	int i, j, k;
//	Piece *piece;
//	char pieceChar;
//	std::cout << "  ";
//	for (k = 0; k < COLS; k++) {
//		std::cout << "  " << k << " ";
//	}
//	std::cout << std::endl;
//	for (i = 0; i < ROWS; i++) {
//		std::cout << "  ";
//		for (k = 0; k < COLS; k++) {
//			std::cout << " ---";
//		}
//		std::cout << std::endl;
//		std::cout << i << " |";
//		for (j = 0; j < COLS; j++) {
//			piece = board[i][j]->getPiece();
//			Vector3 *coordinates = new Vector3(i, j);
//			if (atkList->search(coordinates)) {
//				pieceChar = 65;
//			}
//			else if (piece == nullptr)
//				pieceChar = 32;
//			else
//				pieceChar = piece->getChar();
//			std::cout << " " << pieceChar << " |";
//			delete coordinates;
//		}
//		std::cout << std::endl;
//	}
//	std::cout << "  ";
//	for (k = 0; k < COLS; k++) {
//		std::cout << " ---";
//	}
//	std::cout << std::endl;
//}

void GameBoard::linkTiles(int rows, int cols, int height) {
	int i, j, k;
	Tile *tile;
	for (k = 0; k < height; k++) {
		for (i = 0; i < rows; i++) {
			for (j = 0; j < cols; j++) {
				Vector3<float> *coordinates1 = new Vector3<float>(i, j, k);
				Vector3<float> *coordinates2 = new Vector3<float>;
				tile = getTile(coordinates1);
				//NORTH
				if (i != 0) {
					coordinates2->changeVector(i - 1, j, k);
					tile->linkTileNorth(getTile(coordinates2));
				}
				//SOUTH
				if (i != rows - 1) {
					coordinates2->changeVector(i + 1, j, k);
					tile->linkTileSouth(getTile(coordinates2));
				}
				//WEST
				if (j != 0) {
					coordinates2->changeVector(i, j - 1, k);
					tile->linkTileWest(getTile(coordinates2));
				}
				//EAST
				if (j != cols - 1) {
					coordinates2->changeVector(i, j + 1, k);
					tile->linkTileEast(getTile(coordinates2));
				}
				//UP
				if (k != height - 1) {
					coordinates2->changeVector(i, j, k + 1);
					tile->linkTileUp(getTile(coordinates2));
				}
				//DOWN
				if (k != 0) {
					coordinates2->changeVector(i, j, k - 1);
					tile->linkTileDown(getTile(coordinates2));
				}
				delete coordinates1;
				delete coordinates2;
			}
		}
	}
}

void GameBoard::updateAdjMatrix() {
	//use getTile
}

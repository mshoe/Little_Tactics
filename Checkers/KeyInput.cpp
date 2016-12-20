#include "KeyInput.h"

KeyInput::KeyInput()
{
	game = nullptr;
	keyBoardActive = true;
}

KeyInput::KeyInput(PlayerGame *game)
{
	this->game = game;
	this->ui = game->getUI();
	this->renderer = game->getRenderer();
	keyBoardActive = true;
}

KeyInput::~KeyInput()
{
}

void KeyInput::KeyBoard(unsigned char key, int x, int y, CGameEngine *gameEngine) {
	bool skipEnd = false;
	switch (key) {
	case ' ':
		//If the player is allowed to make actions right now
		if (keyBoardActive) {
			//If the right menu is active
			if (ui->leftRightSelection == RIGHT) {
				//SPACEBAR - Select a piece
				if (ui->actionSelection == WAIT && ui->firstAction != 0 && game->winner == -1) {
					ui->secondAction = WAIT;
					game->nextTurn();
				}
				else if (ui->currentAction != WAIT && game->winner == -1) {
					if (ui->currentAction == 0) {
						if (ui->actionSelection != WAIT) {
							if (ui->firstAction != ui->actionSelection && ui->secondAction != ui->actionSelection) {
								ui->currentAction = ui->actionSelection;
							}
						}
					}
					else if (ui->currentAction == MOVE) {
						if (game->currentTile != nullptr) {
							if (game->pieceState == PIECE_ACTIVE) {
								if (game->currentMovementList != nullptr) {
									if (game->currentMovementList->search(game->currentTile)) {
										//movePiece(currentPiece, currentTile);
										anim->movementQueue->insQueue(anim->aStar(game->currentPiece, game->currentTile));
										if (ui->firstAction != 0) {
											ui->secondAction = MOVE;
											ui->currentAction = WAIT;
										}
										else {
											ui->firstAction = MOVE;
											ui->currentAction = 0;
										}
									}
								}
								game->currentPiece = nullptr;
								game->updatePieceState();
								game->updateStats();
								game->updateCurrentMovementList();
							}
							else {
								if (game->correctTurn(game->currentTile->getPiece()))
									game->currentPiece = game->currentTile->getPiece();
								game->updatePieceState();
								game->updateStats();
								game->updateCurrentMovementList();
							}
						}
					}
					else if (ui->currentAction == ATTACK) {
						if (game->currentTile != nullptr) {
							if (game->pieceState == PIECE_ACTIVE) {
								if (game->currentAttackList != nullptr) {
									if (game->currentAttackList->search(game->currentTile)) {
										Piece *bumpedPiece = game->currentTile->getPiece();
										game->bump(game->currentPiece, bumpedPiece);
										if (anim->isMovementQueueEmpty()) {
											game->attackPieceChainQ(game->currentPiece, bumpedPiece);
										}
										else {
											game->piece1 = game->currentPiece;
											game->piece2 = bumpedPiece;
										}
										if (ui->firstAction != 0) {
											ui->secondAction = ATTACK;
											ui->currentAction = WAIT;
										}
										else {
											ui->firstAction = ATTACK;
											ui->currentAction = 0;
										}
									}
								}
								game->currentPiece = nullptr;
								game->updatePieceState();
								game->updateStats();
								game->updateCurrentAttackList();
							}
							else {
								if (game->correctTurn(game->currentTile->getPiece()))
									game->currentPiece = game->currentTile->getPiece();
								game->updatePieceState();
								game->updateStats();
								game->updateCurrentAttackList();
							}
						}
					}
				}
			}
			else if (ui->leftRightSelection == LEFT) {
				if (ui->actionSelection == AUTO) {

				}
				else if (ui->actionSelection == RESTART) {
					game->restart();
					skipEnd = true;
				}
				else if (ui->actionSelection == EXIT) {

				}
				
			}
		}
		break;
	case 'b':
		if (ui->currentAction != 0 && ui->currentAction != WAIT) {
			if (game->currentPiece == nullptr)
				ui->currentAction = 0;
			game->currentPiece = nullptr;
			game->updatePieceState();
			game->updateStats();
			game->updateCurrentMovementList();
			game->updateCurrentAttackList();
		}
		break;
	case 'a':
		glTranslatef(3.5f, 3.5f, 0.f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(-3.5f, -3.5f, 0.0f);
		/*renderer->rotation += 90.f;
		if (renderer->rotation == 270.f) {
			renderer->rotation = -90.f;
		}*/
		break;
	case 'd':
		glTranslatef(3.5f, 3.5f, 0.f);
		glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(-3.5f, -3.5f, 0.0f);
		/*renderer->rotation -= 90.f;
		if (renderer->rotation == -270.f) {
			renderer->rotation = 90.f;
		}*/
		break;
	case 'w':
		glTranslatef(4.0f, 4.0f, 0.0f);
		glRotatef(-45.0f, 1.0f, 1.0f, 0.0f);
		glTranslatef(-4.0f, -4.0f, 0.0f);
		break;
	case 's':
		glTranslatef(4.0f, 4.0f, 0.0f);
		glRotatef(45.0f, 1.0f, 1.0f, 0.0f);
		glTranslatef(-4.0f, -4.0f, 0.0f);
		break;
	case 'j':
		if (ui->currentAction == 0 || ui->currentAction == WAIT) {
			ui->leftRightSelection -= 1;
			if (ui->leftRightSelection < 1) {
				ui->leftRightSelection = 2;
			}
		}
		if (ui->currentAction != 0 && ui->currentAction != WAIT) {
			if (game->selectorState == SELECTOR_INACTIVE)
				game->selectorState = SELECTOR_ACTIVE;
			else if (game->selector->y > 0) {
				game->selector->translateVector(0, -1, 0);
			}
		}
		break;
	case 'l':
		if (ui->currentAction == 0 || ui->currentAction == WAIT) {
			ui->leftRightSelection += 1;
			if (ui->leftRightSelection > 2) {
				ui->leftRightSelection = 1;
			}
		}
		if (ui->currentAction != 0 && ui->currentAction != WAIT) {
			if (game->selectorState == SELECTOR_INACTIVE)
				game->selectorState = SELECTOR_ACTIVE;
			else if (game->selector->y < game->getBoard()->COLS - 1) {
				game->selector->translateVector(0, 1, 0);
			}
		}
		break;
	case 'i':
		if (ui->currentAction == 0 || ui->currentAction == WAIT) {
			ui->actionSelection -= 1;
			if (ui->actionSelection < 1) {
				ui->actionSelection = 3;
			}
		}
		else {
			if (game->selectorState == SELECTOR_INACTIVE)
				game->selectorState = SELECTOR_ACTIVE;
			else if (game->selector->x > 0) {
				game->selector->translateVector(-1, 0, 0);
			}
		}
		break;
	case 'k':
		if (ui->currentAction == 0 || ui->currentAction == WAIT) {
			ui->actionSelection += 1;
			if (ui->actionSelection > 3) {
				ui->actionSelection = 1;
			}
		}
		else {
			if (game->selectorState == SELECTOR_INACTIVE)
				game->selectorState = SELECTOR_ACTIVE;
			else if (game->selector->x < game->getBoard()->ROWS - 1) {
				game->selector->translateVector(1, 0, 0);
			}
		}
		break;
	default:
		break;
	}
	if (!skipEnd) {
		game->updateCurrentTile();
	}
}

void KeyInput::setAnim(Animation * anim)
{
	this->anim = anim;
}

#include <iostream>
#include <fstream>
#include "engine.h"
#include "../player/humanPlayer.h"
#include "../player/compPlayer.h"

engine::engine() :
	isBlackOnMove(false),
	hasBlackWon(false),
	hasWhiteWon(false),
	boardFlipped(false),
	autoBoardFlip(true) {
  players[0] = new humanPlayer;
  players[1] = new humanPlayer;
  analyzer = new moveAnalyzer;
  movePerformer.chessBoard = &chessBoard;
}

engine::engine(const engine &engineToCpyFrom) {
  *this = engineToCpyFrom;
}

engine::~engine() {
  delete players[0];
  delete players[1];
  delete analyzer;
  chessBoard.deletePiecesVector(chessBoard.piecesVector);
}

engine &engine::operator=(const engine &engineToCpyFrom) {
  if (this != &engineToCpyFrom) {
	players[0] = engineToCpyFrom.players[0]->clone();
	players[1] = engineToCpyFrom.players[1]->clone();
	chessBoard = engineToCpyFrom.chessBoard;
	movePerformer = engineToCpyFrom.movePerformer;
	analyzer = analyzer->clone();
	isBlackOnMove = engineToCpyFrom.isBlackOnMove;
	hasBlackWon = engineToCpyFrom.hasBlackWon;
	hasWhiteWon = engineToCpyFrom.hasWhiteWon;
	boardFlipped = engineToCpyFrom.boardFlipped;
	autoBoardFlip = engineToCpyFrom.autoBoardFlip;
  }
  return *this;
}

void engine::setAnalyzer(const vector2 &pieceToMoveCoords) {
  delete analyzer;
  analyzer = new moveAnalyzer;
  analyzer->chessBoard = &chessBoard;
  analyzer->moves = &moves;
  analyzer->movedPieceCoords = pieceToMoveCoords;
}

player *engine::returnPlayerOnMove() {
  if (players[0]->onMove) {
	return players[0];
  } else {
	return players[1];
  }
}

void engine::readInitFile(const std::string &fileName) {
  std::fstream initFile(fileName, std::ios::in);
  std::string placeHolder;
  if (initFile.good()) {
	for (unsigned short i = 0; i < chessBoard.piecesVector.size(); i++) {
	  for (unsigned short j = 0; j < chessBoard.getPiecesVector()[i].size(); j++) {
		initFile >> placeHolder;
		chessBoard.initAPiece(placeHolder, vector2(placeHolder[1] - '0', placeHolder[2] - '0'));
	  }
	}
  } else {
//        throw std::runtime_error ("File access error.");    //TODO finish exceptoin throwing
  }
}

/*
* Checks if passed piece is payer on move piece 
*/
bool engine::isPiecePlayerOnMove(const vector2 &pieceCoords) {
  return chessBoard.piecesVector[pieceCoords.x][pieceCoords.y]->getIsBlack() == returnPlayerOnMove()->isBlack;
}

void engine::initiateHotSeat() {
  delete players[0];
  delete players[1];

  players[0] = new humanPlayer();
  players[1] = new humanPlayer();

  players[0]->isBlack = false;
  players[1]->isBlack = true;

  players[0]->onMove = true;
  players[1]->onMove = false;
}

void engine::initiateAgainstComp() {
  delete players[0];
  delete players[1];

  players[0] = new humanPlayer();
  players[1] = new compPlayer();
}

void engine::swapPlayerOnMove() {
  std::swap(players[0]->onMove, players[1]->onMove);
}

void engine::executeAMove() {
  vector2 destination;
  getAMove(destination);
  if (checkDestination(destination)) {
	decreaseOpponentPoints(destination);
	movePerformer.executeAMove(analyzer->movedPieceCoords, destination);
	pushMoveBack(destination);
	if (analyzer->isKingChecked(!returnPlayerOnMove()->isBlack)) {
	  chessBoard.setCheck(!returnPlayerOnMove()->isBlack, true);
	} else {
	  chessBoard.setCheck(!returnPlayerOnMove()->isBlack, false);
	}
	swapPlayerOnMove();
  } else {
	return;
  }
}

/*
 * Pass isPlayerBlack of on move player.
 */
void engine::decreaseOpponentPoints(const vector2 &destFieldCoords) {
  if (chessBoard.getPieceByCoords(destFieldCoords)->getIsAlive()) {
	if (players[0]->isBlack == chessBoard.getPieceByCoords(destFieldCoords)->getIsBlack()) {
	  players[0]->points -= chessBoard.getPieceByCoords(destFieldCoords)->getPoints();
	} else {
	  players[1]->points -= chessBoard.getPieceByCoords(destFieldCoords)->getPoints();
	}
  }
}

void engine::toggleBool(bool &boolToToggle) {
  boolToToggle = !boolToToggle;
}

void engine::setPlayersPoints() {
  players[0]->points = chessBoard.sumPlayerPiecesPoints(players[0]->isBlack);
  players[1]->points = chessBoard.sumPlayerPiecesPoints(players[1]->isBlack);
}

void engine::runGame() {
  chooseMode();
  setPlayersPoints();
}

void engine::pushMoveBack(const vector2 &destinationCoords) {
  std::array<vector2, 2> move;
  move[0] = analyzer->movedPieceCoords;
  move[1] = destinationCoords;
  moves.push_back(move);
}

void engine::checkForGameEnd() {
//	if (chessBoard.getKing(returnPlayerOnMove()->isBlack)->getCheck()) {
  if (analyzer->checkForMate(returnPlayerOnMove()->isBlack)) {
	if (returnPlayerOnMove()->isBlack) {
	  whiteHasWon();
	} else {
	  blackHasWon();
	}
  } else if (analyzer->checkForDraw(returnPlayerOnMove()->isBlack)) {
	draw();
  }
//	}
}

void engine::whiteHasWon() {
  if (!players[0]->isBlack) {
	players[0]->setWinState(1);
	players[1]->setWinState(-1);
  } else {
	players[1]->setWinState(1);
	players[0]->setWinState(-1);
  }
}

void engine::blackHasWon() {
  if (players[0]->isBlack) {
	players[0]->setWinState(1);
	players[1]->setWinState(-1);
  } else {
	players[1]->setWinState(1);
	players[0]->setWinState(-1);
  }
}

void engine::draw() {
  players[0]->setWinState(0.5);
  players[1]->setWinState(0.5);
}

float engine::evalState(const player &playerToEval) {
  if (playerToEval.isBlack) {

  }
  playerToEval.hasPlayerWon();
  return 0.0;
}

void engine::get_all_legal_moves_for_player(v2vec2d &legalMoves, const bool &isBlack) {
  for (unsigned int idx0 = 0; idx0 < chessBoard.height; idx0++) {
	for (const piece *pieceToCheck: chessBoard.piecesVector[idx0]) {
	  if (pieceToCheck->getIsBlack() == isBlack && pieceToCheck->getIsAlive()) {
		std::array<vector2, 2> singleLegalMove;
		singleLegalMove[0] = pieceToCheck->getPosition();
		setAnalyzer(pieceToCheck->getPosition());
		analyzer->countAllLegalMovesForPiece();
		for (const vector2 &pieceDest: analyzer->legalDestForPiece) {
		  singleLegalMove[1] = pieceDest;
		  legalMoves.push_back(singleLegalMove);
		}
	  }
	}
  }
}

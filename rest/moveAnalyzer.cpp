#include <algorithm>
#include "../pieces/pawn.h"
#include "moveAnalyzer.h"
#include "moveHandler.h"

moveAnalyzer::moveAnalyzer() = default;

moveAnalyzer::moveAnalyzer(const moveAnalyzer &analyerToCopyFrom) {
  *this = analyerToCopyFrom;
}

moveAnalyzer &moveAnalyzer::operator=(const moveAnalyzer &analyzerToCopyFrom) {
  if (this != &analyzerToCopyFrom) {
	movedPieceCoords = analyzerToCopyFrom.movedPieceCoords;
	chessBoard = analyzerToCopyFrom.chessBoard;
	moves = analyzerToCopyFrom.moves;
	legalDestForPiece = analyzerToCopyFrom.legalDestForPiece;
	//infoToPass = analyzerToCopyFrom.infoToPass;
  }
  return *this;
}

void moveAnalyzer::setChessBoard(const board &boardToBeSetFrom) {
  *chessBoard = boardToBeSetFrom;
}

moveAnalyzer *moveAnalyzer::clone() {
  return new moveAnalyzer(*this);
}

bool moveAnalyzer::isDestinationLegal(const vector2 &destinationFieldCoords) {
  return std::find(legalDestForPiece.begin(), legalDestForPiece.end(), destinationFieldCoords) !=
	  legalDestForPiece.end();
}

void moveAnalyzer::countAllLegalMovesForPiece() {
  for (unsigned short i = 0; i < chessBoard->piecesVector.size(); i++) {
	for (unsigned short j = 0; j < chessBoard->piecesVector[i].size(); j++) {
	  if (evaluateTheMove(movedPieceCoords, vector2(i, j))) {
		legalDestForPiece.push_back(vector2(i, j));
	  }
	}
  }
}

/*Returns true if move legal*/
bool moveAnalyzer::checkForLegalMove(const vector2 &pieceToCheckForCoords, const vector2 &destinationFieldCoords) {
  piece *destinationField = chessBoard->getPieceByCoords(destinationFieldCoords)->copy();
  destinationField->position = destinationFieldCoords;
  piece *pieceToCheckFor = chessBoard->getPieceByCoords(pieceToCheckForCoords)->copy();
  vector2 displacement(
	  destinationFieldCoords.x - pieceToCheckForCoords.x,
	  destinationFieldCoords.y - pieceToCheckForCoords.y);
  piece::infoForPiece infoToPass;

  infoToPass.destinationField = destinationField->copy();
  if (!moves->empty()) {
	infoToPass.lastMove = moves->back();
  }
  infoToPass.piecesVector = chessBoard->getPiecesVector();
  infoToPass.displacement = displacement;
  if (pieceToCheckFor->checkForLegalMove(infoToPass)) {
	if (pieceToCheckFor->getPerformsEnPassant()) {
	  chessBoard->getPieceByCoords(pieceToCheckForCoords)->setPerformsEnPassant(true);
	}
	delete pieceToCheckFor;
	delete destinationField;
	return true;
  } else {
	delete pieceToCheckFor;
	delete destinationField;
	return false;
  }
}

bool moveAnalyzer::evaluateTheMove(const vector2 &pieceToCheckForCoords, const vector2 &destinationFieldCoords) {
  if (checkForLegalMove(pieceToCheckForCoords, destinationFieldCoords)) {
	//if (!isPieceKing(destinationFieldCoords)) {	//TODO remove from here and add to checkForObstacles
	if (!checkForObstacles(pieceToCheckForCoords, destinationFieldCoords)) {
	  if (!isKingCheckedAfterMove(destinationFieldCoords,
								  chessBoard->getPieceByCoords(pieceToCheckForCoords)->getIsBlack())) {

		return true;
	  }
	}
	//}
  }
  return false;
}

bool moveAnalyzer::isPieceKing(const vector2 &pieceCoords) {
  if (chessBoard->getPiecesVector()[pieceCoords.x][pieceCoords.y]->id == 'k') {
	return true;
  } else {
	return false;
  }
}

/*If king checked returns true*/
bool moveAnalyzer::isKingChecked(const bool &isKingBlack) {
  const pvec2d piecesVec = chessBoard->getPiecesVector();
  vector2 kingCoords = chessBoard->getCoordsOfKing(isKingBlack);
  for (unsigned short i = 0; i < piecesVec.size(); i++) {
	for (unsigned short j = 0; j < piecesVec[i].size(); j++) {
	  if (piecesVec[i][j]->getIsBlack() != isKingBlack &&
		  piecesVec[i][j]->isAlive) {
		if (!checkForObstacles(vector2(i, j), kingCoords)) {
		  if (checkForLegalMove(vector2(i, j), kingCoords)) {
			return true;
		  }
		}
	  }
	}
  }
  return false;
}

bool moveAnalyzer::isKingCheckedAfterMove(const vector2 &destinationFieldCoords, const bool &isKingBlack) {
  //piece* placeHolder = chessBoard->piecesVector[destinationFieldCoords.x][destinationFieldCoords.y]->copy();
  moveAnalyzer tempAnalyzer;
  moveHandler tempHandler;
  bool kingChecked;
  board tempBoard(chessBoard->copyPiecesVector());
  tempAnalyzer.chessBoard = &tempBoard;
  tempAnalyzer.moves = moves;
  tempAnalyzer.movedPieceCoords = destinationFieldCoords;
  tempHandler.setChessBoard(*tempAnalyzer.chessBoard);

  tempHandler.executeAMove(movedPieceCoords, destinationFieldCoords);

  if (tempAnalyzer.isKingChecked(isKingBlack)) {
	kingChecked = true;
  } else {
	kingChecked = false;
  }
  /*chessBoard->piecesVector[destinationFieldCoords.x][destinationFieldCoords.y] = placeHolder->copy();*/
  /*delete placeHolder;*/
  tempAnalyzer.chessBoard->deletePiecesVector(tempAnalyzer.chessBoard->piecesVector);
  return kingChecked;
}

void moveAnalyzer::adjustIndexX(short &indexX, const vector2 &pieceToCheckForCoords, const vector2 &displacement) {
  if (displacement.x > 0) {
	indexX = pieceToCheckForCoords.x;
  } else {
	indexX = -pieceToCheckForCoords.x;
  }
}

void moveAnalyzer::adjustIndexY(short &indexY, const vector2 &pieceToCheckForCoords, const vector2 &displacement) {
  if (displacement.y > 0) {
	indexY = pieceToCheckForCoords.y;
  } else {
	indexY = -pieceToCheckForCoords.y;
  }
}

/*
*
* Checks for any obstacle (piece) on moved piece's way.
* (analyzes fields between moved piece's starting position and destinaton field.)
* Returns true if obstacle found.
*/
bool moveAnalyzer::checkForObstacles(const vector2 &pieceToCheckForCoords, const vector2 &destinationFieldCoords) {
  vector2 displacement(
	  destinationFieldCoords.x - pieceToCheckForCoords.x,
	  destinationFieldCoords.y - pieceToCheckForCoords.y);

  short displacementLen, indexX, indexY = 0;

  piece *destinationField = chessBoard->getPieceByCoords(destinationFieldCoords)->copy();
  piece *pieceToCheckFor = chessBoard->getPieceByCoords(pieceToCheckForCoords)->copy();

  /*
  * Same color of destination field piece as pieceToCheckFor color considered as obstacle
  */
  if (destinationField->isAlive) {
	if (checkForSameColor(
		*pieceToCheckFor,
		*destinationField)) {
	  delete pieceToCheckFor;
	  delete destinationField;
	  return true;
	}
  }
  delete pieceToCheckFor;
  delete destinationField;

  if (chessBoard->getPieceByCoords(pieceToCheckForCoords)->id != 'n') {
	/*
	* If piece moves down the board (from white perspective) - starting positon is negated
	* to enable checking indexes lower than starting position.
	*/
	adjustIndexX(indexX, pieceToCheckForCoords, displacement);
	adjustIndexY(indexY, pieceToCheckForCoords, displacement);
	/*
	evaluateTheMove
	*/
	if (displacement.y == 0) {
	  for (unsigned short i = 1; i < abs(displacement.x); i++) {
		/*
		* When indexX is negative value, ading to it will decrease abs value and allow checking
		* board way down.
		*/
		if (chessBoard->getPiecesVector()[abs(indexX + i)][pieceToCheckForCoords.y]->getIsAlive()) {
		  return true;
		}
	  }
	} else {
	  /*
	  * pieceToCheckFor moves verticaly.
	  */
	  if (displacement.x == 0) {
		for (unsigned short i = 1; i < abs(displacement.y); i++) {
		  if (chessBoard->getPiecesVector()[pieceToCheckForCoords.x][abs(indexY + i)]->getIsAlive()) {
			return true;
		  }
		}
	  }
		/*
		* pieceToCheckFor moves diagonally.
		*/
	  else {
		for (unsigned short i = 1; i < abs(displacement.y); i++) {
		  if (chessBoard->getPiecesVector()[abs(indexX + i)][abs(indexY + i)]->getIsAlive()) {
			return true;
		  }
		}
	  }
	}
  }
  return false;
}

bool moveAnalyzer::checkForSameColor(const piece &pieceToCheckFor, const piece &destinationField) {
  if (pieceToCheckFor.getIsBlack() == destinationField.getIsBlack()) {
	return true;
  } else {
	return false;
  }
}

bool moveAnalyzer::hasPlayerAnyMove(const bool &isPlayerBlack) {
  moveAnalyzer tempAnalyzer(*this);
  for (unsigned short i = 0; i < chessBoard->piecesVector.size(); i++) {
	for (unsigned short j = 0; j < chessBoard->piecesVector[i].size(); j++) {
	  if (chessBoard->getPieceByCoords(vector2(i, j))->isBlack == isPlayerBlack) {
		tempAnalyzer.movedPieceCoords = vector2(i, j);
		tempAnalyzer.legalDestForPiece.clear();
		tempAnalyzer.countAllLegalMovesForPiece();
		if (!tempAnalyzer.legalDestForPiece.empty()) {
		  return true;
		} else {
		  continue;
		}
	  } else {
		continue;
	  }
	}
  }
  return false;
}

bool moveAnalyzer::checkForMate(const bool &isPlayerBlack) {
  if (chessBoard->getPieceByCoords(chessBoard->getCoordsOfKing(isPlayerBlack))->isChecked()) {
	return !hasPlayerAnyMove(isPlayerBlack);
  } else {
	return false;
  }
}

bool moveAnalyzer::checkForDraw(const bool &isPlayerBlack) {
  if (chessBoard->countPieces() == 2) {
	return true;
  } else {
	if (!chessBoard->getPieceByCoords(chessBoard->getCoordsOfKing(isPlayerBlack))->isChecked()) {
	  return !hasPlayerAnyMove(isPlayerBlack);
	} else {
	  return false;
	}
  }
}
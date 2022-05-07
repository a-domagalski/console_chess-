#include "moveHandler.h"
#include "../pieces/pawn.h"

moveHandler::moveHandler(const piece &destinationToBeSetFrom, const piece &pieceToBeSetFrom) {
  //TODO assignment operator for both classes
}

void moveHandler::setChessBoard(board &boardToCopyFrom) {
  chessBoard = &boardToCopyFrom;
}

void moveHandler::executeAMove(const vector2 &pieceToMoveCoords, const vector2 &destinationCoords) {
  vector2 displacement(
	  destinationCoords.x - pieceToMoveCoords.x,
	  destinationCoords.y - pieceToMoveCoords.y
  );

  if (chessBoard->piecesVector[pieceToMoveCoords.x][pieceToMoveCoords.y]->id == 'p' &&
	  chessBoard->piecesVector[pieceToMoveCoords.x][pieceToMoveCoords.y]->getPerformsEnPassant()) {
	performEnPassant(pieceToMoveCoords, destinationCoords);
  } else if (chessBoard->piecesVector[pieceToMoveCoords.x][pieceToMoveCoords.y]->id == 'k' &&
	  chessBoard->piecesVector[pieceToMoveCoords.x][pieceToMoveCoords.y]->getDoCastle() &&
	  abs(displacement.y) > 1 && displacement.x == 0) {
	performCastle(pieceToMoveCoords, destinationCoords);
  } else {
	moveAPiece(pieceToMoveCoords, destinationCoords);
  }
  /*Calling for destination coords because piece have just been moved
   * - it's no longer on pieceToMoveCoords.*/
  resetPiecesFlags(destinationCoords);
}

void moveHandler::moveAPiece(const vector2 &pieceToMoveCoords, const vector2 &destinationCoords) {

  delete chessBoard->piecesVector[destinationCoords.x][destinationCoords.y];
  chessBoard->piecesVector[destinationCoords.x][destinationCoords.y] =
	  chessBoard->piecesVector[pieceToMoveCoords.x][pieceToMoveCoords.y]->copy();
  deleteAPiece(pieceToMoveCoords);
  chessBoard->piecesVector[destinationCoords.x][destinationCoords.y]->position = destinationCoords;
}

void moveHandler::resetPiecesFlags(const vector2 &pieceToMoveCoords) {
  chessBoard->getKing(chessBoard->piecesVector[pieceToMoveCoords.x][pieceToMoveCoords.y]->isBlack)->setDoCastle(
	  false);
  chessBoard->piecesVector[pieceToMoveCoords.x][pieceToMoveCoords.y]->setPerformsEnPassant(false);
  chessBoard->piecesVector[pieceToMoveCoords.x][pieceToMoveCoords.y]->piece_never_moved = false;
}

void moveHandler::performCastle(const vector2 &pieceToMoveCoords, const vector2 &destinationCoords) {
  if (chessBoard->piecesVector[pieceToMoveCoords.x][pieceToMoveCoords.y]->isBlack) {
	if (destinationCoords.y == 6) {
	  moveAPiece(pieceToMoveCoords, destinationCoords);
	  moveAPiece(vector2(7, 7), vector2(7, 5));
	} else {
	  moveAPiece(pieceToMoveCoords, destinationCoords);
	  moveAPiece(vector2(7, 0), vector2(7, 3));
	}
  } else {
	if (destinationCoords.y == 6) {
	  moveAPiece(pieceToMoveCoords, destinationCoords);
	  moveAPiece(vector2(0, 7), vector2(0, 5));
	} else {
	  moveAPiece(pieceToMoveCoords, destinationCoords);
	  moveAPiece(vector2(0, 0), vector2(0, 3));
	}
  }
}

void moveHandler::takeCastleBack(const vector2 &kingCoords) {
  if (chessBoard->piecesVector[kingCoords.x][kingCoords.y]->isBlack) {
	if (kingCoords.y == 6) {
	  moveAPiece(vector2(7, 6), vector2(7, 4));
	  moveAPiece(vector2(7, 5), vector2(7, 7));
	} else {
	  moveAPiece(vector2(7, 2), vector2(7, 4));
	  moveAPiece(vector2(7, 3), vector2(7, 0));
	}
  } else {
	if (kingCoords.y == 6) {
	  moveAPiece(vector2(0, 6), vector2(0, 4));
	  moveAPiece(vector2(0, 5), vector2(0, 7));
	} else {
	  moveAPiece(vector2(0, 2), vector2(0, 4));
	  moveAPiece(vector2(0, 3), vector2(0, 0));
	}
  }

}

void moveHandler::performEnPassant(const vector2 &pieceToMoveCoords, const vector2 &destinationCoords) {
  vector2 displacement(
	  destinationCoords.x - pieceToMoveCoords.x,
	  destinationCoords.y - pieceToMoveCoords.y);
  moveAPiece(pieceToMoveCoords, destinationCoords);
  deleteAPiece(vector2(pieceToMoveCoords.x, pieceToMoveCoords.y + displacement.y));
}

void moveHandler::deleteAPiece(const vector2 &pieceToDelCoords) {
  delete chessBoard->piecesVector[pieceToDelCoords.x][pieceToDelCoords.y];
  chessBoard->piecesVector[pieceToDelCoords.x][pieceToDelCoords.y] = new pawn;
}
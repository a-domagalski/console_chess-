#include "pawn.h"

pawn::pawn() : piece() {
  id = 'p';
  points = 10;
  performsEnPassant = false;
}

pawn::pawn(const pawn &pieceToCopyFrom) {
  *this = pieceToCopyFrom;
}

pawn &pawn::operator=(const pawn &pieceToCopyFrom) {
  if (this != &pieceToCopyFrom) {
	piece::operator=(pieceToCopyFrom);
	performsEnPassant = pieceToCopyFrom.performsEnPassant;
  } else {
	return *this;
  }
}

pawn *pawn::copy() {
  return new pawn(*this);
}

bool pawn::getPerformsEnPassant() {
  return performsEnPassant;
}

void pawn::setPerformsEnPassant(const bool &stateToSetFrom) {
  performsEnPassant = stateToSetFrom;
}

void pawn::setFirstMove(const bool &firstMoveToSetFrom) {
  piece_never_moved = firstMoveToSetFrom;
}

/*Returns true if move legal*/
bool pawn::checkForLegalMove(const infoForPiece &passedInfo) {
  if (passedInfo.destinationField->getIsAlive()) {
	return checkIfTakes(passedInfo.displacement, *passedInfo.destinationField);
  } else {
	if (checkIfTakes(passedInfo.displacement, *passedInfo.destinationField)) {
	  return enPassant(passedInfo);
	}
	if (isBlack) {
	  return basicCheckForBlack(passedInfo.displacement);
	} else {
	  return basicCheckForWhite(passedInfo.displacement);
	}
  }
}

bool pawn::checkIfTakes(const vector2 &displacement, const piece &destinationField) const {
  short PieceXDirection = 0;
  if (isBlack) {
	PieceXDirection = -1;
  } else {
	PieceXDirection = 1;
  }
  if (displacement.x == PieceXDirection && abs(displacement.y) == 1) {
	return true;
  } else {
	return false;
  }
}

/*
* If takes (so if taking conditions are met (checkIfCanTake returns true)), check if en passant
*/
bool pawn::enPassant(const infoForPiece &passedInfo) {
  /*
  * Checking for white.
  */
  if (position.x == 4 && !isBlack) {
	if (!passedInfo.lastMove.empty() &&
		passedInfo.lastMove[0].x == 6 && passedInfo.lastMove[1].x == 4) {
	  if (passedInfo.destinationField->getPosition().y == passedInfo.lastMove[1].y) {
		if (passedInfo.piecesVector[4][passedInfo.lastMove[0].y]->getID() == 'p') {
		  performsEnPassant = true;
		  return true;
		}
	  }
	}
  }
  /*
  * Checking for black.
  */
  if (position.x == 3 && isBlack) {

	if (!passedInfo.lastMove.empty() &&
		passedInfo.lastMove[0].x == 1 && passedInfo.lastMove[1].x == 3) {
	  if (passedInfo.destinationField->getPosition().y == passedInfo.lastMove[0].y) {
		if (passedInfo.piecesVector[3][passedInfo.lastMove[0].y]->getID() == 'p') {
		  performsEnPassant = true;
		  return true;
		}
	  }
	}
  }
  return false;
}

bool pawn::basicCheckForBlack(const vector2 &displacement) const {
  if (!piece_never_moved) {
	if (displacement.x < -1) {
	  return false;
	} else if (displacement.x == -1 && displacement.y == 0) {
	  return true;
	}
  } else {
	if ((displacement.y == 0 && displacement.x == -1) || (displacement.y == 0 && displacement.x == -2)) {
	  return true;
	}
  }
  return false;
}

bool pawn::basicCheckForWhite(const vector2 &displacement) const {
  if (!piece_never_moved) {
	if (displacement.x > 1) {
	  return false;
	} else if (displacement.x == 1 && displacement.y == 0) {
	  return true;
	}
  } else {
	if ((displacement.y == 0 && displacement.x == 1) || (displacement.y == 0 && displacement.x == 2)) {
	  return true;
	}
  }
  return false;
}

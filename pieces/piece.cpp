#include "piece.h"

piece::piece() :
	isAlive(false),
	isBlack(false),
	piece_never_moved(true),    //TODO Remember to toggle piece_never_moved after performing first move
	id('?'),
	position(vector2(0, 0)),
	points(0.1) {}

piece::piece(const piece &pieceToBeCopiedFrom) {
  *this = pieceToBeCopiedFrom;
}

piece &piece::operator=(const piece &pieceToBeCopiedFrom) {
  if (this != &pieceToBeCopiedFrom) {
	isAlive = pieceToBeCopiedFrom.isAlive;
	isBlack = pieceToBeCopiedFrom.isBlack;
	piece_never_moved = pieceToBeCopiedFrom.piece_never_moved;
	id = pieceToBeCopiedFrom.id;
	position = pieceToBeCopiedFrom.position;
	points = pieceToBeCopiedFrom.points;
  }
  return *this;
}

bool operator==(const piece &pieceToCheckForL, const piece &pieceToCheckForR) {
  if (pieceToCheckForL.position == pieceToCheckForR.position) {
	return true;
  } else {
	return false;
  }
}

bool piece::getIsAlive() const {
  return isAlive;
}

bool piece::getIsBlack() const {
  return isBlack;
}

vector2 piece::getPosition() const {
  return position;
}

char piece::getID() const {
  return id;
}

int piece::getPoints() {
  return points;
}

bool piece::isFirstMoveMade() const {
  return !piece_never_moved;
}

void piece::setPosition(const vector2 &positionToSet) {
  position = positionToSet;
}



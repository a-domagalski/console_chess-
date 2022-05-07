#ifndef MOVEANALYZER_H
#define MOVEANALYZER_H

#include "board.h"

typedef std::vector<std::array<vector2, 2>> v2vec2d;

class moveAnalyzer {
 protected:
  vector2 movedPieceCoords;
  board *chessBoard;
  const v2vec2d *moves;
  std::vector<vector2> legalDestForPiece;
  //przeniesienie infoToPass do jednej metody stad cos zmienia?

  void adjustIndexX(short &, const vector2 &, const vector2 &);
  void adjustIndexY(short &, const vector2 &, const vector2 &);
  void moveAPiece(const vector2 &, const vector2 &);

 public:

  moveAnalyzer();
  moveAnalyzer(const moveAnalyzer &);
  moveAnalyzer &operator=(const moveAnalyzer &);
  moveAnalyzer *clone();

  void setChessBoard(const board &);
  bool evaluateTheMove(const vector2 &, const vector2 &);
  bool checkForObstacles(const vector2 &, const vector2 &);
  bool checkForSameColor(const piece &, const piece &);
  bool isPieceKing(const vector2 &);
  bool isKingCheckedAfterMove(const vector2 &, const bool &);
  bool isKingChecked(const bool &);
  bool checkForLegalMove(const vector2 &, const vector2 &);
  void countAllLegalMovesForPiece();
  bool isDestinationLegal(const vector2 &);
  bool hasPlayerAnyMove(const bool &);
  bool checkForMate(const bool &);
  bool checkForDraw(const bool &);

  friend class engine;
  friend class consoleChess;
};

#endif
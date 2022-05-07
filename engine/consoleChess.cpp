#include <iostream>
#include <random>
#include <functional>
#include "consoleChess.h"

consoleChess::consoleChess() : engine() {}

consoleChess::consoleChess(const consoleChess &engineToCpyFrom) {
  *this = engineToCpyFrom;
}

consoleChess &consoleChess::operator=(const consoleChess &engineToCpyFrom) {
  if (this != &engineToCpyFrom) {
	engine::operator=(engineToCpyFrom);
  }
  return *this;
}

consoleChess *consoleChess::clone() {
  return new consoleChess(*this);
}

std::string consoleChess::getInput() {
  std::string placeHolder;
  getline(std::cin, placeHolder);
  interpreteInput(placeHolder);
  return placeHolder;
}

void consoleChess::interpreteInput(std::string &inputToInterperte) {
  if (inputToInterperte == "exit") {
	std::exit(NULL);
  }
  if (inputToInterperte == "resign") {
	//TODO if(white.onMove || black.onMove) then do all of this below (if game started)
	if (returnPlayerOnMove()->isBlack) {
	  displayText("Black resigns.\n");
	  whiteHasWon();
	  std::exit(NULL);
	} else {
	  displayText("White resigns.\n");
	  blackHasWon();
	  std::exit(NULL);
	}
  }
  if (inputToInterperte == "flip board") {
	toggleBool(boardFlipped);
  }
  if (inputToInterperte == "auto flip on") {
	autoBoardFlip = true;
  }
  if (inputToInterperte == "auto flip off") {
	autoBoardFlip = false;
  }
}

void consoleChess::chessToCompNotation(std::string &stringToConvert) {
  if (std::isdigit(stringToConvert[0]) || !std::isdigit(stringToConvert[1])) {
	return;
  }
  stringToConvert[0] = std::toupper(stringToConvert[0]);
  stringToConvert[0] -= 17;

  decreaseCharDigitBy1(stringToConvert[1]);
  std::swap(stringToConvert[0], stringToConvert[1]);
  return;
}

void consoleChess::compTochessNotation(std::string &stringToConvert) {
  for (unsigned int i = 0; i < stringToConvert.size() - 1; i += 2) {
	std::swap(stringToConvert[i], stringToConvert[i + 1]);
	stringToConvert[i] += 17;
	stringToConvert[i + 1] += 1;
  }

  return;
}

void consoleChess::decreaseCharDigitBy1(char &charToModify) {
  if (isdigit(charToModify)) {
	charToModify -= 1;
  } else {
	return;
  }
}

void consoleChess::displayText(const std::string &textToDisplay) {
  std::cout << textToDisplay;
}

void consoleChess::chooseMode() {
  displayText("1. Hot Seat\n2. Against Computer (disabled)\n");

  std::string placeHolder = getInput();
  if (!isNumber(placeHolder)) {
	displayText("Choose correct mode\n");
	chooseMode();
	return;
  }
  switch (std::stoi(placeHolder)) {
	case 1:initiateHotSeat();
	  break;
	case 2:
	  //initiateAgainstComp();
	  displayText("Choose another mode\n");
	  chooseMode();
	  break;
	default:displayText("Choose correct mode\n");
	  chooseMode();
	  break;
  }
}

bool consoleChess::isNumber(const std::string &stringToCheck) {
  std::string::const_iterator iter = stringToCheck.begin();
  while (iter != stringToCheck.end() && std::isdigit(*iter)) {
	++iter;
  }
  return !stringToCheck.empty() && iter == stringToCheck.end();
}

/* https://stackoverflow.com/questions/43329352/generating-random-boolean/43329456 */
bool randomBool() {
  static auto randBool = std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
  return randBool();
}

/*When against Computer*/
void consoleChess::chooseColor() {
  displayText("1. Play as white\n2. Play as black\n3.Random\n");

  std::string placeHolder = getInput();
  if (!isNumber(placeHolder)) {
	displayText("Choose correct option\n");
	chooseColor();
	return;
  }

  switch (std::stoi(placeHolder)) {
	case 1:players[0]->isBlack = false;
	  players[1]->isBlack = true;
	  break;
	case 2:players[0]->isBlack = true;
	  players[1]->isBlack = false;
	  break;
	case 3:players[0]->isBlack = randomBool();
	  players[1]->isBlack = !players[0]->isBlack;
	  break;
	default:displayText("Choose correct option\n");
	  chooseColor();
	  break;
  }
}

std::string consoleChess::getPieceChar(const piece *pieceToDisp) {
  std::string pieceChar = "";
  if (pieceToDisp->getIsBlack()) {
	pieceChar += 'B';
  } else {
	pieceChar += 'W';
  }
  switch (pieceToDisp->getID()) {
	case 'p':pieceChar += 'p';
	  break;
	case 'n':pieceChar += 'n';
	  break;
	case 'b':pieceChar += 'b';
	  break;
	case 'q':pieceChar += 'q';
	  break;
	case 'k':pieceChar += 'k';
	  break;
	case 'r':pieceChar += 'r';
	  break;
	default:pieceChar = "- ";
	  break;
  }
  return pieceChar;
}

void consoleChess::displayBoardForWhite() {
  std::string pieceChar;
  std::cout << "\n";
  for (short i = chessBoard.getPiecesVector().size() - 1; i >= 0; i--) {
	for (unsigned short j = 0; j < chessBoard.getPiecesVector()[i].size(); j++) {
	  pieceChar = "";
	  pieceChar += getPieceChar(chessBoard.getPiecesVector()[i][j]);
	  if (!chessBoard.getPiecesVector()[i][j]->getIsAlive()) {
		pieceChar = "--";
	  }
	  std::cout << pieceChar << " ";
	}
	std::cout << i + 1 << " " << std::endl;
  }
  for (unsigned short i = 0; i < chessBoard.getPiecesVector().size(); i++) {
	std::cout << (char)('a' + i) << "  ";
  }
  std::cout << "\n\n";

}

//TODO opis szachownicy jest na odwrot w stosunku do figur 
void consoleChess::displayBoardForBlack() {
  std::string pieceChar;
  std::cout << "\n";

  for (unsigned short i = 0; i < chessBoard.getPiecesVector().size(); i++) {
	for (short j = chessBoard.getPiecesVector()[i].size() - 1; j >= 0; j--) {
	  pieceChar = "";
	  pieceChar += getPieceChar(chessBoard.getPiecesVector()[i][j]);
	  if (!chessBoard.getPiecesVector()[i][j]->getIsAlive()) {
		pieceChar = "--";
	  }
	  std::cout << pieceChar << " ";
	}
	std::cout << 1 + i << " " << std::endl;
  }
  for (unsigned short i = 0; i < chessBoard.getPiecesVector().size(); i++) {
	std::cout << (char)('h' - i) << "  ";
  }
  std::cout << "\n\n";
}

void consoleChess::setCursorPosition(const COORD &cursorPos) {
  HANDLE OutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(OutHandle, cursorPos);
}

COORD consoleChess::getCurrentCusrorCords() {

  HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO infoStorage;
  GetConsoleScreenBufferInfo(outHandle, &infoStorage);

  return infoStorage.dwCursorPosition;
}

void consoleChess::displayBoard(const COORD &cursorPos) {
  //setCursorPosition(cursorPos);
  if (autoBoardFlip == true) {
	if (returnPlayerOnMove()->isBlack) {
	  boardFlipped = true;
	} else {
	  boardFlipped = false;
	}
  } else {
	if (!boardFlipped) {
	  displayBoardForWhite();
	} else {
	  displayBoardForBlack();
	}
  }
  displayBoardForWhite();
}

bool consoleChess::strToVec2(const std::string strToConvert, vector2 &convertedCoords) {
  if (strToConvert.size() == 2) {
	if (isNumber(strToConvert)) {
	  convertedCoords = vector2(strToConvert[0] - '0', strToConvert[1] - '0');
	  return true;
	}
  }
  convertedCoords = vector2(111, 111);
  return false;
}

bool consoleChess::getCoords(vector2 &coordsToPass) {
  std::string placeHolder = getInput();
  chessToCompNotation(placeHolder);
  interpreteInput(placeHolder);
  if (strToVec2(placeHolder, coordsToPass)) {
	return true;
  } else {
	displayText("Invalid coords\n");
	return false;
  }
}

//TODO split it to multiple methods
bool consoleChess::getAMove(vector2 &coords) {
  displayText("Pick a piece by writing coords eg. 'e4'\n");
  if (!getCoords(coords)) {
	getAMove(coords);
  } else if (!isPiecePlayerOnMove(coords)) {
	displayText("Invalid color piece picked.\n");
	getAMove(coords);
  }
  while (chessBoard.piecesVector[coords.x][coords.y]->getIsAlive() &&
	  isPiecePlayerOnMove(coords)) {
	setAnalyzer(coords);
	displayText("Picked piece: ");
	std::cout << getPieceChar(chessBoard.piecesVector[coords.x][coords.y]) << "\n";
	displayLegalMovesForPiece();
	v2vec2d temp;
			  << chessBoard.getPieceByCoords(coords)->getPerformsEnPassant() << "\n";
	displayText("Pass destination field coords or pick other piece.\n");

	while (!getCoords(coords) &&
		players[0]->hasWon == 0 &&
		players[1]->hasWon == 0);
  }
  return true;
}

bool consoleChess::checkDestination(const vector2 &destinationFieldCoords) {

  if (analyzer->isDestinationLegal(destinationFieldCoords)) {
	return true;
  } else {
	displayText("Illegal move\n");
  }
  return false;
}

void consoleChess::dispLegalPlayerMoves(const v2vec2d &legalMoves) {
  std::string placeHolder;
  placeHolder.resize(4);
  for (const std::array<vector2, 2> &singleMove: legalMoves) {
	placeHolder[0] = singleMove[0].x + 48;
	placeHolder[1] = singleMove[0].y + 48;

	placeHolder[2] = singleMove[1].x + 48;
	placeHolder[3] = singleMove[1].y + 48;

	compTochessNotation(placeHolder);
	std::cout << placeHolder << "\n";
  }
}

void consoleChess::displayLegalMovesForPiece() {
  analyzer->countAllLegalMovesForPiece();
  std::cout << "Moves legal for picked piece: ";
  std::string placeHolder;
  placeHolder.resize(2);
  for (unsigned short i = 0; i < analyzer->legalDestForPiece.size(); i++) {
	placeHolder[0] = analyzer->legalDestForPiece[i].x + 48;
	placeHolder[1] = analyzer->legalDestForPiece[i].y + 48;
	compTochessNotation(placeHolder);
	std::cout << placeHolder << ";";
  }
  std::cout << std::endl;
}

bool consoleChess::checkForCorrectMoveInput(const std::string &inputToEvaluate) {
  if (inputToEvaluate.size() != 4) {
	return false;
  } else {
	int placeHolder = 0;
	for (unsigned short i = 0; i < 4; i++) {
	  if (std::isdigit(inputToEvaluate[i])) {
		if (std::stoi(inputToEvaluate) - '0' > 8 || std::stoi(inputToEvaluate) - '0' < 0) {
		  return false;
		} else {
		  return true;
		}
	  } else {
		return false;
	  }
	}
  }
}

void consoleChess::blackHasWon() {
  displayText("Black has won.\n");
  engine::blackHasWon();
}

void consoleChess::whiteHasWon() {
  displayText("White has won.\n");
  engine::whiteHasWon();
}

void consoleChess::draw() {
  engine::draw();
  displayText("Draw");
}

void consoleChess::displayPlayerPoints() {
  if (returnPlayerOnMove()->isBlack) {
	std::cout << "Blacks points: ";
  } else {
	std::cout << "Whites points: ";
  }
  std::cout << returnPlayerOnMove()->points << std::endl;
}

void consoleChess::runGame() {
  engine::runGame();
  COORD cursorPos{0, 0};
  while (!(hasBlackWon || hasWhiteWon)) {
	displayBoard(cursorPos);
	executeAMove();
	displayPlayerPoints();
	checkForGameEnd();
  }
}



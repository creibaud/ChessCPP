#ifndef PIECES_H
#define PIECES_H

#include "../pieces/pawn/pawn.h"
#include "../pieces/rook/rook.h"
#include "../pieces/knight/knight.h"
#include "../pieces/bishop/bishop.h"
#include "../pieces/queen/queen.h"
#include "../pieces/king/king.h"

#define WHITE_PAWN Pawn(sf::Color::White);
#define BLACK_PAWN Pawn(sf::Color::Black);

#define WHITE_ROOK Rook(sf::Color::White);
#define BLACK_ROOK Rook(sf::Color::Black);

#define WHITE_KNIGHT Knight(sf::Color::White);
#define BLACK_KNIGHT Knight(sf::Color::Black);

#define WHITE_BISHOP Bishop(sf::Color::White);
#define BLACK_BISHOP Bishop(sf::Color::Black);

#define WHITE_QUEEN Queen(sf::Color::White);
#define BLACK_QUEEN Queen(sf::Color::Black);

#define WHITE_KING King(sf::Color::White);
#define BLACK_KING King(sf::Color::Black);

#endif // PIECES_H
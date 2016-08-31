#include "ChessPiece.h"

ChessPiece::ChessPiece() {
    this->setPiece(piece::Pawn);    
}

void ChessPiece::setPiece(piece p){
    
    this->name = p;
    
    switch(this->name){
    
        case piece::Pawn:
            this->height = 39.2f;
        break;
        
        case piece::Knight:
            this->height = 50.3f;
        break;
    
        case piece::Bishop:
            this->height = 48.f;
        break;
        
        case piece::Rook:
            this->height = 45.f;
        break;
        
        case piece::Queen:
            this->height = 48.f;
        break;
        
        case piece::King:
            this->height = 47.f;
        break;
        
        case piece::None:
            this->height = 0.f;
        break;
    }
    
}

piece ChessPiece::getPiece(){
    return this->name;
}

float ChessPiece::getHeight(){
    return this->height;
}

void ChessPiece::setCoord(float x , float y){
    this->coord_piece.x = x;
    this->coord_piece.y = y;
}

float ChessPiece::getCoordX(){ 
    return this->coord_piece.x;
}

float ChessPiece::getCoordY(){ 
    return this->coord_piece.y;
}

ChessPiece::ChessPiece(const ChessPiece& orig) {
}

ChessPiece::~ChessPiece() {
}


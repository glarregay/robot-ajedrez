#ifndef CHESSPIECE_H
#define CHESSPIECE_H

enum class piece{Pawn,Knight,Bishop,Rook,Queen,King,None};

typedef struct coorden {
    float x;
    float y;
} CoordPiece;

class ChessPiece {   
public:
    ChessPiece();
    void setPiece(piece p);
    void setCoord(float x ,float y);
    piece getPiece();
    float getCoordX();
    float getCoordY();
    float getHeight();
    ChessPiece(const ChessPiece& orig);
    virtual ~ChessPiece();
private:
    piece name;
    float height;
    CoordPiece coord_piece;
};

#endif /* CHESSPIECE_H */


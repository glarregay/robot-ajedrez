#ifndef ABBCHESS_H
#define ABBCHESS_H

#include "ChessPiece.h"
#include "IRC5-Client-Linux/Controller.h"
#include "IRC5-Client-Linux/Commands.h"
#include "IRC5-Client-Linux/RapidData/Pos.h"
#include "IRC5-Client-Linux/RapidData/Num.h"

enum class MovementType{Normal,Attack,ShortCastling,LongCastling,None};
enum class MateType{White,Black,None};

typedef struct chessmove{
    
    MovementType move_type;
    ChessPiece piece_origin;
    ChessPiece piece_destiny;
    MateType mate_type;
    
}ChessMove;


class ABBchess {
public:
    ABBchess(string ip_controller ,int port_controller);
    void motionCapture();
    void motionCalibration();
    void updateChessMove(ChessMove* chess_move);
    void connectABBchess();
    void disconnectABBchess();
    void playMove();
    void waitButton();
    void waitButtonNonBlocking();
    int buttonPressed();
    virtual ~ABBchess();
private:

    Pos* pos_p0;
    Pos* pos_p1;
    Num* offset_height;
    Controller* ctrl;
    Commands* abb_cmd;
    string routine;
    
};

#endif /* ABBCHESS_H */


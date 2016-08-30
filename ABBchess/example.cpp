/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Fede
 *
 * Created on 29 de agosto de 2016, 17:41
 */

#include <cstdlib>
#include "ABBchess/IRC5-Client-Linux/Commands.h"
#include "ABBchess/IRC5-Client-Linux/Controller.h"
#include "ABBchess/ABBchess.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    ABBchess abb_chess("192.168.1.103",8001);
   
    ChessMove* cm=new ChessMove();

    cm->move_type = MovementType::Attack;
    cm->piece_origin.setPiece(piece::Knight);
    cm->piece_origin.setCoord(0.,200.);
    cm->piece_destiny.setPiece(piece::Pawn);
    cm->piece_destiny.setCoord(0.,300.);
    
    abb_chess.connectABBchess();
    
    abb_chess.updateChessMove(cm);
    
    abb_chess.disconnectABBchess();
    
    return 0;
}


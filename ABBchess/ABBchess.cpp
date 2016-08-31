#include "ABBchess.h"

ABBchess::ABBchess(string ip_controller ,int port_controller){
    
    this->ctrl = new Controller(ip_controller,port_controller);
    this->abb_cmd = new Commands();
    this->pos_p0 = new Pos("pos_p0");
    this->pos_p1 = new Pos("pos_p1");
    this->offset_height = new Num("offset_height");

}

void ABBchess::connectABBchess(){
    
    this->ctrl->connectController();
}

void ABBchess::disconnectABBchess(){
    this->ctrl->disconnectController();
}

void ABBchess::motionCapture(){

    ctrl->sendCommand(abb_cmd->executeRutine("HomeCamera"),true);
    ctrl->sendCommand(abb_cmd->executeRutine("OpenGripper"),true);
    
}

void ABBchess::motionCalibration(){

    ctrl->sendCommand(abb_cmd->executeRutine("HomeCamera"),true);
    
}

void ABBchess::updateChessMove(ChessMove* chess_move){
   
    
    switch(chess_move->move_type){
        
        case MovementType::Normal:
            this->routine="NormalMove";
            pos_p1->setZ(-(chess_move->piece_origin.getHeight()));
        break;
           
        case MovementType::Attack:
            this->routine="AttackMove";
            pos_p1->setZ(-(chess_move->piece_destiny.getHeight()));
        break;
        
        case MovementType::ShortCastling:
            this->routine="ShortCastlingMove";
            chess_move->piece_destiny.setPiece(piece::Rook); 
            pos_p1->setZ(-(chess_move->piece_destiny.getHeight()));
        break;
        
        case MovementType::LongCastling:
            this->routine="LongCastlingMove";
            chess_move->piece_destiny.setPiece(piece::Rook); 
            pos_p1->setZ(-(chess_move->piece_destiny.getHeight()));
        break;
        
        case MovementType::None:
        break;
        
    }
   
    
    if(chess_move->piece_origin.getPiece()==piece::Knight)//Comparar si la pieza origen es un caballo
        offset_height->setNum(110.f);
    else
        offset_height->setNum(chess_move->piece_origin.getHeight());
   
    
    /*----------Actualizar variables-------------------*/
    
    pos_p0->setX(chess_move->piece_origin.getCoordX());
    pos_p0->setY(chess_move->piece_origin.getCoordY());
    pos_p0->setZ(-(chess_move->piece_origin.getHeight()));
    
    pos_p1->setX(chess_move->piece_destiny.getCoordX());
    pos_p1->setY(chess_move->piece_destiny.getCoordY());
    
    /*----------Enviar variables al controlador-----------*/
    
    ctrl->sendCommand(abb_cmd->writeData(pos_p0),true);
    ctrl->sendCommand(abb_cmd->writeData(pos_p1),true);
    ctrl->sendCommand(abb_cmd->writeData(offset_height),true);
    
    
}

void ABBchess::playMove(){
    
    ctrl->sendCommand(abb_cmd->executeRutine("UpdateTargets"),true);
    ctrl->sendCommand(abb_cmd->executeRutine(this->routine),true);
    ctrl->sendCommand(abb_cmd->executeRutine("HumanWait"),true);  
}

void ABBchess::waitButton() {
    ctrl->sendCommand(abb_cmd->executeRutine("ButtonWait"),true); 
}

int ABBchess::buttonPressed(){
    
    string state_button = ctrl->sendCommand(abb_cmd->stateButton(),true);
    
    if(state_button.compare("pressed")){
        return 1;
    }
    else if(state_button.compare("notpressed")){
        return 0;
    }else{
        return -1;
    }
    
}

void ABBchess::waitButtonNonBlocking() {
    ctrl->sendCommand(abb_cmd->executeRutine("ButtonWait"),false); 
}

int ABBchess::buttonPressed() {
    string resp = ctrl->readResponse();
    
    if(resp.size() > 0) 
        return 1;
    else
        return 0;
}

ABBchess::~ABBchess(){
}


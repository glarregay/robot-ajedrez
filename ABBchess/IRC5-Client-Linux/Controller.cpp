#include "Controller.h"

using namespace std;

Controller::Controller(string ip_server,int port) {
  

   sockfd = socket(AF_INET,SOCK_STREAM,0);
  
   bzero((char *)&serverABB_addr, sizeof(serverABB_addr));  
   this->port = port;
   serverABB_addr.sin_family = AF_INET;
   serverABB_addr.sin_port = htons(port);
   serverABB_addr.sin_addr.s_addr = inet_addr(ip_server.c_str());

}

void Controller::connectController(){
    if (connect(sockfd,(struct sockaddr *) &serverABB_addr,sizeof(serverABB_addr)) < 0) 
        perror("ERROR al conectar!!");
}

void Controller::disconnectController(){
    close(sockfd);
}



string Controller::sendCommand(string command,bool wait_command){
   
  stringstream sread;
  sread.clear();
  
  command.push_back('\n');
    
  *buffer_send=(char*)command.c_str();
  
  do{
    bytes_read=recv(sockfd,buffer_recv,255,MSG_DONTWAIT);
    sread << buffer_recv ;
  } while(bytes_read != -1);
  
  bytes_read = 0;
  sread.clear();
  
  send(sockfd,*buffer_send,command.length(), 0);
  
  if(wait_command==true){
    bytes_read=recv(sockfd,buffer_recv,255,0);
    sread << buffer_recv ;
  }
  
  return sread.str();
} 

string Controller::readResponse() {
    
    stringstream sread;
    sread.clear();
    
    bytes_read=recv(sockfd,buffer_recv,255,MSG_DONTWAIT);
    sread << buffer_recv ;
    
    if(bytes_read == -1) {
        return "";
    }
    
    return sread.str();
    
}


Controller::Controller(const Controller& orig) {

}

Controller::~Controller(){
}





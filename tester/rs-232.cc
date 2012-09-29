/******************************
//      class rs_232.cc
//
//implemention of RS-232 class
//
//    Yuan Chao
//
// ver. 0.2   2000/08/16
// ver. 0.1   1999/05/27
******************************/

#include <iostream.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <poll.h>
#include "rs-232.h"

int time_out;

RS_232::RS_232( int port, int speed, int check, int data, int stop ){
  Port = port;
  Speed = speed;
  Check = check;
  Data = data;
  Stop = stop;

}

RS_232::RS_232(){
  Port = 2;
  Speed = 9600;
  Check = 0;
  Data = 8;
  Stop = 1;

}

int RS_232::Init(){
  char port_name[16]="/dev/ttyS1";
  struct termios term;

  if (Port!=2)
    port_name[9] += Port-2;

  if((fd = open( port_name, O_RDWR | O_NONBLOCK)) < 0 ){
    cout << "Error open COM" << Port << "!\n";
    return(-1);
  }

  if(isatty(fd)==0){
    cout << "Error: ttyS" << Port-1 << " is not a tty\n";
    return(-1);
  }

  if(tcgetattr(fd, &term)<0){
    cout << "tcgetattr error\n";
    return(-1);
  }

  if(Data == 8 && Check == 0){
    term.c_cflag=CS8;
  }else{
    term.c_cflag=CS7|PARENB;
  }

  term.c_cflag|=CREAD|HUPCL|CRTSCTS;    //CRTSXOFF
  term.c_iflag=IXON|IXOFF|IGNBRK|ISTRIP|IGNPAR;

  term.c_oflag=0;
  term.c_lflag=0;

  term.c_cc[VMIN]=1;
  term.c_cc[VTIME]=0;

  if(Speed == 9600){
    cfsetispeed(&term,B9600);
    cfsetospeed(&term,B9600);
  }else{
    cfsetispeed(&term,B19200);
    cfsetospeed(&term,B19200);
  }

  if(tcsetattr(fd, TCSANOW, &term)<0){
    cout << "tcsetattr error\n";
    return(-1);
  }

  return(0);

}

int RS_232::Read( char *str ){
  char in_char, tmp[80]="";
  char len=0,in_len=0;
  int test=0;
  struct pollfd fds;

  fds.fd=fd;
  fds.events=POLLIN;

  tcflush( fd, TCOFLUSH );

  delay(1);
//  poll(NULL,0,200);

  if(poll(&fds,1,500) < 0)		//wait for first char...
	cout << "Polling error...\n";

  while( time_out!=1 && in_len!=-1 ){

    if(fds.revents & POLLHUP){
      cout << "Already hang up...\n";
      break;
    }

    if((fds.revents & POLLIN) && (in_len = read(fd, &in_char, 1)) > 0){
      tmp[len]= in_char;
      len++;
    }

    test=poll(&fds,1,10);
    if( test == 0){		//wait for next char...
      break;
    }else if( test < 0 ){
      cout << "Polling error...\n";
    }
  }
//len=read(fd,tmp,15);
  undelay();

  tmp[len]='\0';

//cout << tmp << endl;		//for debugging

  tcflush( fd, TCIOFLUSH );

  strcpy(str,tmp);
  return len;
 
}

int RS_232::Write( char *str, int len){
  int test=0;

  tcflush( fd, TCIOFLUSH );
  test=write(fd, str, len);
  tcdrain( fd );
  
  return ( test );
}

int RS_232::Write( char *str){
  int test=0;

  tcflush( fd, TCIOFLUSH );
  test=write(fd, str, strlen(str));
  tcdrain( fd );
 
  return ( test );
}

void RS_232::delay( int sec ){
  signal( SIGALRM, handler );
  time_out = 0;
  alarm(sec);

}

void RS_232::handler(int sig){
  time_out = 1;

  return;
}

void RS_232::undelay(){
  //signal( SIGALRM, old );
  time_out = 0;
  alarm(0);
}










/**********************
//  tester --- to the center of a pad
//
//  Controller Program for
//  Scanning table PC3 contol box
//
//	by Yuan Chao
//             2002/03
//  ver 0.1
***********************/

#include <stdio.h>
#include <unistd.h>
#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <poll.h>
#include "rs-232.h"
#include "tester.h"
#include "ugpib.h"


int main(int argc, char *argv[]){

  //Init COM1 port for PC3
  com=RS_232(1,9600,0,8,1);
  com.Init();

  vel(1,200);
  vel(3,500);

  //Init IEEE488 for LCR
  if ( (dmm=ibdev(0,17,0,10,1,0))<0 )
    cout << "GPIB Init error!";

  ibclr(dmm);
  ibwrt(dmm, (void *)"*RST;*CLS",9);
  sleep(1);
  ibwrt(dmm, (void *)"DISP:LINE 'NTUHEP Flex ROBOT'",29);
  sleep(1);
  ibwrt(dmm, (void *)"FUNC:IMP RX",11);
  sleep(1);
  ibwrt(dmm, (void *)"TRIG:SOUR BUS",13);
  sleep(1);
  ibwrt(dmm, (void *)"INIT:CONT ON",12);
  sleep(1);

  read_lcr();
  if(m_lcr_r>100.)
    to_pad();

  pad_last=m_y;

  while(true){
    to_gap();
    to_pad();

    pad_curr=fabs(m_y-pad_last);
    if( pad_last > 0.02 )
      cout<<"\tDefect found!! Distance from last pad is "<<pad_curr<<" cm.\n";
    pad_last=m_y;
  }

  return(0);

}

double read_lcr(){

  poll(NULL,0,500);
  ibtrg(dmm);
  poll(NULL,0,500);
  ibrd(dmm, ibtmp, 50);
  sscanf(ibtmp, "%le,%le", &m_lcr_r, &m_lcr_x);

  return(m_lcr_r);

}

void vel(int axis, int dist){

  sprintf(tmp_str,"V%d %d\r", axis, dist);
  com.Write(tmp_str);

}

void move(int axis, float dist){

  sprintf(tmp_str,"M%d %+07.3f\r", axis, dist);
  com.Write(tmp_str);

}

void step(){
  move(3,-0.1);
  wait_pc3();
  move(1,+0.005);
  wait_pc3();
  move(3,+0.1);
  wait_pc3();
}

int ready(){
  com.Write("Q\r");
  com.Read(tmp_str);
  if(tmp_str[24]=='W')
    return(0);
  else
    return(-1);

}

void wait_pc3(){

  do{
    com.Write("Q\r");
    com.Read(tmp_str);
    sscanf(tmp_str+24,"%c", &all_stat);
    //    poll(NULL,0,500);
  }while(all_stat=='R');

}

void show_add(){
  com.Write("Q\r");
  com.Read(tmp_str);

  sscanf(tmp_str,"%e", &m_x);
  sscanf(tmp_str+8,"%e", &m_y);
  sscanf(tmp_str+16,"%e", &m_z);

  printf("\nX:%+7.3f Y:%+7.3f Z:%+7.3f ", m_x, m_y ,m_z);
}

void show(){

  do{
    com.Write("Q\r");
    com.Read(tmp_str);

    sscanf(tmp_str,"%le", &m_x);
    sscanf(tmp_str+8,"%le", &m_y);
    sscanf(tmp_str+16,"%le", &m_z);

    sscanf(tmp_str+24,"%c", &all_stat);

    printf("\rX:%+7.3f Y:%+7.3f Z:%+7.3f ", m_x, m_y ,m_z);
  }while(all_stat!='W');

}

void to_gap(){
  int dmm;
  char ibtmp[255];

  for(int i=1; i<=500 && m_lcr_r<100.; i++){
    move(3,-0.5);
    wait_pc3();
    move(2,+0.003);
    wait_pc3();
    move(3,+0.5);
    wait_pc3();

    poll(NULL,0,500);
    ibtrg(dmm);
    poll(NULL,0,500);
    ibrd(dmm, ibtmp, 50);
    show_add();

    sscanf(ibtmp, "%le,%le", &m_lcr_r, &m_lcr_x);
    printf("\t R= %f \t, x= %f", m_lcr_r, m_lcr_x);
  }
}

void to_pad(){
  int dmm;
  char ibtmp[255];
  
  for(int i=1; i<=500 && m_lcr_r>100.; i++){
    move(3,-0.5);
    wait_pc3();
    move(2,+0.003);
    wait_pc3();
    move(3,+0.5);
    wait_pc3();

    poll(NULL,0,500);
    ibtrg(dmm);
    poll(NULL,0,500);
    ibrd(dmm, ibtmp, 50);
    show_add();

    sscanf(ibtmp, "%le,%le", &m_lcr_r, &m_lcr_x);
    printf("\t R= %f \t, x= %f", m_lcr_r, m_lcr_x);
  }
}


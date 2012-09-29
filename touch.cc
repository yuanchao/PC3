/**********************
//  touch --- plan finder
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
#include "pc3.h"
#include "ugpib.h"


int main(int argc, char *argv[]){
  int dmm;
  char ibtmp[255];
  FILE *fd;

  //Init COM1 port for PC3

  com=RS_232(1,9600,0,8,1);
  com.Init();

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

  for(int i=1; i<=10; i++){
    move(3,+0.05);
    poll(NULL,0,200);
    wait_pc3();
    ibtrg(dmm);
    ibrd(dmm, ibtmp, 50);
    show_add();

    sscanf(ibtmp, "%le,%le", &m_lcr_r, &m_lcr_x); 
    printf("\t R= %f \t, x= %f\n", m_lcr_r, m_lcr_x);

    if(m_lcr_r<10.){
      move(3,+0.05);
      cout << "Plan found!\n";
      return(0);
    }
  }

  cout <<  "Can't find plan!\n";
  return(-1);

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

  printf("\rX:%+7.3f Y:%+7.3f Z:%+7.3f ", m_x, m_y ,m_z);
}

void show(){

//  float m_x, m_y, m_z;

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

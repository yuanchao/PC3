/**********************
//   stable
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

#define MAXFLOAT  3.40282347e+38F

int main(int argc, char *argv[]){
  int dmm, bad_count=0;
  double m_begin=0;
  char ibtmp[255];
  FILE *fd;

  //Init COM1 port for PC3

  com=RS_232(1,9600,0,8,1);
  com.Init();

  vel(1,200);
  vel(3,500);

  if(argc>1){
    if( !(fd=fopen(argv[1], "a"))){
       cout << "Output file " << argv[1] << " open error!\n";
       exit(-1);
    }
  }else{
    if( !(fd=fopen("stable.txt", "a"))){
       cout << "Output file output.txt open error!\n";
       exit(-1);
    }
  }  

//  fflush(fd);

  //Init IEEE488 for LCR

  if ( (dmm=ibdev(0,17,0,10,1,0))<0 )
    cout << "GPIB Init error!";

  ibclr(dmm);
  ibwrt(dmm, (void *)"*RST;*CLS",9);
  poll(NULL,0,500);
  ibwrt(dmm, (void *)"DISP:LINE 'NTUHEP Flex ROBOT'",29);
  poll(NULL,0,500);
  ibwrt(dmm, (void *)"FUNC:IMP RX",11);
  poll(NULL,0,500);
  ibwrt(dmm, (void *)"TRIG:SOUR BUS",13);
  poll(NULL,0,500);
  ibwrt(dmm, (void *)"INIT:CONT ON",12);
  poll(NULL,0,500);

  //show();
  m_begin=m_y;

  fprintf(fd, "No. \tOffset \tR \tx= \n");

  for(int i=1; i<=600; i++){
    measure(dmm);

    printf("\n%03d \t R= %6.2f \t, x= %6.2f", i, fabs(m_lcr_r), m_lcr_x);
    cout.flush();

    fprintf(fd, "%03d \t%f \t %f", i, m_lcr_r, m_lcr_x);
    fflush(fd);

    vel(3,500);
    wait_pc3();
    move(3,-0.1);
    wait_pc3();
                                                                                
    move(2,+0.146);
                                                                                
    wait_pc3();
    vel(3,100);
    wait_pc3();
    move(3,+0.1);
    wait_pc3();

    measure(dmm);
                                                                                
    printf("\t R= %6.2f \t, x= %6.2f", fabs(m_lcr_r), m_lcr_x);
    cout.flush();
                                                                                
    fprintf(fd, " \t%f \t %f\n", m_lcr_r, m_lcr_x);
    fflush(fd);
                                                                                
    vel(3,500);
    wait_pc3();
    move(3,-0.1);
    wait_pc3();
                                                                                
    move(2,-0.146);
                                                                                
    wait_pc3();
    vel(3,100);
    wait_pc3();
    move(3,+0.1);
    wait_pc3();

  }

  return(0);

}

void measure(int dev){
  double t_lcr_r=0., t_lcr_x=0.;
  char ibtmp[255];

  m_lcr_r=MAXFLOAT, m_lcr_x=MAXFLOAT;

  for(int j=0; j<3; j++){
    poll(NULL,0,500);
    ibtrg(dev);
    poll(NULL,0,200);
    ibrd(dev, ibtmp, 50);
    sscanf(ibtmp, "%le,%le", &t_lcr_r, &t_lcr_x);

    cout << ".";
    cout.flush();
    if(fabs(t_lcr_r)<fabs(m_lcr_r)){
      m_lcr_r=t_lcr_r;
      m_lcr_x=t_lcr_x;
    }
  }
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
  //distance between 2 pads is 146um while min-step for PC3 is 10um.
  //for every 5 steps: 2 go 140um, 3 go 150um.
  static int counter=0;

  vel(3,500);
  wait_pc3();
  move(3,-0.1);
  wait_pc3();

  move(2,+0.146);

  wait_pc3();
  vel(3,100);
  wait_pc3();
  move(3,+0.1);
  wait_pc3();
}

void step_back(){
  wait_pc3();
  vel(3,500);
  wait_pc3();
  move(3,-0.1);
  wait_pc3();
//  move(2,-0.10);
//  wait_pc3();
//  move(2,0.07);  //go back 30um
  move(2,+0.02);  //go forward 20um
  wait_pc3();
  vel(3,100);
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
  char stat1, stat2, stat3;
  do{
    com.Write("Q\r");
    poll(NULL,0,100);
    com.Read(tmp_str);
  }while(tmp_str[24]!='W');
//    sscanf(tmp_str+24,"%c\r%c\r%c\r%c", &all_stat, &stat1, &stat2, &stat3);
//  }while(stat1!='W'||stat2!='W'||stat3!='W');

}

void show_add(){
  com.Write("Q\r");
  com.Read(tmp_str);

  sscanf(tmp_str,"%le", &m_x);
  sscanf(tmp_str+8,"%le", &m_y);
  sscanf(tmp_str+16,"%le", &m_z);

  cout << "\nX: " << m_x << "\tY: " << m_y << "\tZ: " << m_z;
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

    printf("\nX:%+7.3f Y:%+7.3f Z:%+7.3f ", m_x, m_y ,m_z);
    cout.flush();
  }while(all_stat!='W');

}

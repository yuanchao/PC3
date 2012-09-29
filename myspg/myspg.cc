/**********************
//   myspg
//
//  command sender for
//  EFC smart pulsing module
//
//	by Yuan Chao
//             2000/08
//  ver 0.1
***********************/

#include <stdio.h>
#include <unistd.h>
#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include "rs-232.h"


int main(int argc, char *argv[]){
  char tmp_str[16];
  int i,m_adam=0,counter=0;

  RS_232 com1(1,9600,0,8,1);

  if(argc<2){
    cout << "No command...\n";
    return (-1);
  }

  //init spg
  sprintf(tmp_str,"WATS%c%c",0,6);     //stop all timer
  com1.Write(tmp_str,6);

  sprintf(tmp_str,"WAFS%c%c",0,6);     //stop all FP
  com1.Write(tmp_str,6);

  
  sprintf(tmp_str,"W0FH%c%c",0x80,6);  //FP, high
  com1.Write(tmp_str,6);

  sprintf(tmp_str,"W0FL%c%c",0x00,6);  //FP, low
  com1.Write(tmp_str,6);

  sprintf(tmp_str,"W0PH%c%c",0x80,6);  //PP, high
  com1.Write(tmp_str,6);

  sprintf(tmp_str,"W0PL%c%c",0x04,6);  //PP, low
  com1.Write(tmp_str,6);

  sprintf(tmp_str,"W0LH%c%c",0x80,6);  //PP, high
  com1.Write(tmp_str,6);

  sprintf(tmp_str,"W0LL%c%c",0x08,6);  //PP, low
  com1.Write(tmp_str,6);


  //sending commands
  if(strcmp(argv[1],"tp")==0){

    //turn on forward tp

    //set internal timer
    sprintf(tmp_str,"W0TB%c%c",0x01,6);
    com1.Write(tmp_str,6);
    
    sprintf(tmp_str,"W0TH%c%c",0x02,6);
    com1.Write(tmp_str,6);

    sprintf(tmp_str,"W0TL%c%c",0x11,6);
    com1.Write(tmp_str,6);

    //PP output ~0.5V
    sprintf(tmp_str,"W0PA%c%c",0x0e,6);
    com1.Write(tmp_str,6);
    
    //PP preload 6 chann/clock, start from chann 1
    sprintf(tmp_str,"W0PP%c%c",0x3f,6);
    com1.Write(tmp_str,6);

    //PP shift 1 chann
    sprintf(tmp_str,"W0PB%c%c",0x01,6);
    com1.Write(tmp_str,6);

    //PP & timer start
    sprintf(tmp_str,"W0PS%c%c",0xc0,6);  //internal timer
    com1.Write(tmp_str,6);

    sprintf(tmp_str,"W0TS%c%c",0x80,6);  //start timer
    com1.Write(tmp_str,6);

    //turn on backward tp

    //set internal timer
    sprintf(tmp_str,"W1TB%c%c",0x01,6);
    com1.Write(tmp_str,6);
    
    sprintf(tmp_str,"W1TH%c%c",0x02,6);
    com1.Write(tmp_str,6);

    sprintf(tmp_str,"W1TL%c%c",0x11,6);
    com1.Write(tmp_str,6);

    //PP output ~0.5V
    sprintf(tmp_str,"W1PA%c%c",0x0e,6);
    com1.Write(tmp_str,6);
    
    //PP preload 6 chann/clock, start from chann 1
    sprintf(tmp_str,"W1PP%c%c",0x3f,6);
    com1.Write(tmp_str,6);

    //PP shift 1 chann
    sprintf(tmp_str,"W1PB%c%c",0x01,6);
    com1.Write(tmp_str,6);

    //PP & timer start
    sprintf(tmp_str,"W1PS%c%c",0xc0,6);  //internal timer
    com1.Write(tmp_str,6);

    sprintf(tmp_str,"W1TS%c%c",0x80,6);  //start timer
    com1.Write(tmp_str,6);


  }else if(strcmp(argv[1],"led")==0){
    //turn on forward led

    //set internal timer
    sprintf(tmp_str,"W0TB%c%c",0x01,6);
    com1.Write(tmp_str,6);
    
    sprintf(tmp_str,"W0TH%c%c",0x02,6);
    com1.Write(tmp_str,6);

    sprintf(tmp_str,"W0TL%c%c",0x11,6);
    com1.Write(tmp_str,6);

    //LP output ~4.0V
    sprintf(tmp_str,"W0LA%c%c",0x6d,6);
    com1.Write(tmp_str,6);
    
    //LP preload 6 chann/clock, start from chann 1
    sprintf(tmp_str,"W0LP%c%c",0x3f,6);
    com1.Write(tmp_str,6);

    //LP shift 1 chann
    sprintf(tmp_str,"W0LB%c%c",0x01,6);
    com1.Write(tmp_str,6);

    //LP & timer start
    sprintf(tmp_str,"W0LS%c%c",0xc0,6);  //internal timer
    com1.Write(tmp_str,6);

    sprintf(tmp_str,"W0TS%c%c",0x80,6);  //start timer
    com1.Write(tmp_str,6);

    //turn on backward led

    //set internal timer
    sprintf(tmp_str,"W1TB%c%c",0x01,6);
    com1.Write(tmp_str,6);
    
    sprintf(tmp_str,"W1TH%c%c",0x02,6);
    com1.Write(tmp_str,6);

    sprintf(tmp_str,"W1TL%c%c",0x11,6);
    com1.Write(tmp_str,6);

    //LP output ~4.0V
    sprintf(tmp_str,"W1FA%c%c",0x6d,6);
    com1.Write(tmp_str,6);
    
    //LP preload 6 chann/clock, start from chann 1
    sprintf(tmp_str,"W1FP%c%c",0x3f,6);
    com1.Write(tmp_str,6);

    //LP shift 1 chann
    sprintf(tmp_str,"W1FB%c%c",0x01,6);
    com1.Write(tmp_str,6);

    //LP & timer start
    sprintf(tmp_str,"W1FS%c%c",0xc0,6);  //internal timer
    com1.Write(tmp_str,6);

    sprintf(tmp_str,"W1TS%c%c",0x80,6);  //start timer
    com1.Write(tmp_str,6);

  }else if(strcmp(argv[1],"fib")==0){
    //turn on forward fib

    //set internal timer
    sprintf(tmp_str,"W0TB%c%c",0x01,6);
    com1.Write(tmp_str,6);
    
    sprintf(tmp_str,"W0TH%c%c",0x02,6);
    com1.Write(tmp_str,6);

    sprintf(tmp_str,"W0TL%c%c",0x11,6);
    com1.Write(tmp_str,6);

    //FP output ~4.0V
    sprintf(tmp_str,"W0FA%c%c",0x6d,6);
    com1.Write(tmp_str,6);
    
    //FP preload 6 chann/clock, start from chann 1
    sprintf(tmp_str,"W0FP%c%c",0x3f,6);
    com1.Write(tmp_str,6);

    //FP shift 1 chann
    sprintf(tmp_str,"W0FB%c%c",0x01,6);
    com1.Write(tmp_str,6);

    //FP & timer start
    sprintf(tmp_str,"W0FS%c%c",0xc0,6);  //internal timer
    com1.Write(tmp_str,6);

    sprintf(tmp_str,"W0TS%c%c",0x80,6);  //start timer
    com1.Write(tmp_str,6);

    //turn on backward fib

    //set internal timer
    sprintf(tmp_str,"W1TB%c%c",0x01,6);
    com1.Write(tmp_str,6);
    
    sprintf(tmp_str,"W1TH%c%c",0x02,6);
    com1.Write(tmp_str,6);

    sprintf(tmp_str,"W1TL%c%c",0x11,6);
    com1.Write(tmp_str,6);

    //FP output ~4.0V
    sprintf(tmp_str,"W1FA%c%c",0x6d,6);
    com1.Write(tmp_str,6);
    
    //FP preload 6 chann/clock, start from chann 1
    sprintf(tmp_str,"W1FP%c%c",0x3f,6);
    com1.Write(tmp_str,6);

    //FP shift 1 chann
    sprintf(tmp_str,"W1FB%c%c",0x01,6);
    com1.Write(tmp_str,6);

    //FP & timer start
    sprintf(tmp_str,"W1FS%c%c",0xc0,6);  //internal timer
    com1.Write(tmp_str,6);

    sprintf(tmp_str,"W1TS%c%c",0x80,6);  //start timer
    com1.Write(tmp_str,6);

  }else{
    cout << "Command Error... Stop all...\n";
  }
 
  //    sleep(1);
  return(0);

}


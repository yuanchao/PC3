/**********************
//  tester
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

char tmp_str[80];
char status[30];
char all_stat, temp;
double m_x, m_y, m_z;
double m_lcr_r, m_lcr_x;
int i,m_adam=0,counter=0;
RS_232 com;

int dmm;
double pad_begin=0, pad_end=0, pad_last=0, m_gap=0, pad_curr=0;
char ibtmp[255];
FILE *fd;

double read_lcr();

void vel(int axis, int dist);
void move(int axis, float dist);
void step();
void wait_pc3();

int ready();

void show_add();
void show();

void to_pad();
void to_gap();

/**********************
//   myspg
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

int stp_axis;
float stp_dist;

int cmp_axis;
float cmp_dist;
float cmp_accum;

float m_x1=0.,m_y1=0.;
float m_x2=0.,m_y2=0.;

void measure(int dev);

void vel(int axis, int dist);
void move(int axis, float dist);

void step();
void step(int axis, float dist);
void step(int axis, float dist, int c_axis, float c_dist);
void step_back();
void step_back(int axis, float dist);

void wait_pc3();
void wait_pc3_long();
int ready();

void show_add();
void show();

#include "graphics.h"
#include<bits/stdc++.h>
using namespace std;
#define MAXN 501
const COLORS clist[5]={LIGHTGRAY,MAGENTA,BLUE,GREEN,RED};
const int face_opt[5][2]={{},{0,1},{1,1},{0,-1},{1,-1}};
const int accum[2][10]={{0,1,1,1,1,1,2,3,3,3},{0,0,1,2,-1,-2,0,0,1,-1}};
const int mv_x[5]={0,1,0,-1,0},mv_y[5]={0,0,1,0,-1};
const int My_table_X=100,My_table_Y=100;
const int Eny_table_X=600,Eny_table_Y=100;
int target_x=1,target_y=1,target_face=1;
int now_table_X=My_table_X,now_table_Y=My_table_Y;
int plane_num;
int mapt[11][11];
inline int react_to_keyb(){
    int t=getch();
    for(;!t;t=getch())
    printf("%d\n",t);
    if(t==293) return 3;
    if(t==295) return 1;
    if(t==294) return 4;
    if(t==296) return 2;
    if(t==44||t==46) return t;
    if(t==13) return 13;
    if(t==27) exit(0);
    return 0;
}
inline void undraw_target(){
    setfillcolor(clist[mapt[target_x][target_y]]);
    bar(now_table_X+(target_x-1)*30,now_table_Y+(target_y-1)*30,
    now_table_X+(target_x-1)*30+26,now_table_Y+(target_y-1)*30+26);
    return;
}
inline void draw_bar(int x,int y,COLORS C){
    setfillcolor(C);
    bar(now_table_X+(x-1)*30,now_table_Y+(y-1)*30,now_table_X+(x-1)*30+26,now_table_Y+(y-1)*30+26);
}
inline void draw_target(){
    setcolor(LIGHTCYAN);
    int middle_x=now_table_X+(target_x-1)*30+13,middle_y=now_table_Y+(target_y-1)*30+13;
    circle(middle_x,middle_y,7);
    line(middle_x,middle_y-10,middle_x,middle_y-3);
    line(middle_x,middle_y+10,middle_x,middle_y+3);
    line(middle_x-10,middle_y,middle_x-3,middle_y);
    line(middle_x+10,middle_y,middle_x+3,middle_y);
    return;
}
#include"placeownplane.h"
int main(){
    initgraph(900, 675);
    int start_x=100,start_y=100;
    setfillcolor(LIGHTGRAY);
    for(int i=1;i<=10;i++,start_y+=30,start_x=100)
        for(int j=1;j<=10;j++) bar(start_x,start_y,start_x+26,start_y+26),start_x+=30;

    start_x=500; start_y=100;
    for(int i=1;i<=10;i++,start_y+=30,start_x=500)
        for(int j=1;j<=10;j++) bar(start_x,start_y,start_x+26,start_y+26),start_x+=30;
    put_plane();
    return 0;
}

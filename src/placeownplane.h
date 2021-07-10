#include "graphics.h"
#include<bits/stdc++.h>
using namespace std;
struct plane{
    int face,x,y,C,number;
}plane_list[MAXN];

inline bool check_legal(int num){
    int face=plane_list[num].face;
    for(int k=1;k<=9;k++){
        int x_set=plane_list[num].x+accum[face_opt[face][0]][k]*face_opt[face][1],
            y_set=plane_list[num].y+accum[face_opt[face][0]^1][k]*face_opt[face][1];
        if(!(x_set>0&&x_set<=10&&y_set>0&&y_set<=10)) return 0;
        if(mapt[x_set][y_set]) return 0;
    }
    return 1;
}
inline void unshow_plane(int num){
    int face=plane_list[num].face;
    draw_bar(plane_list[num].x,plane_list[num].y,clist[mapt[plane_list[num].x][plane_list[num].y]]);
    for(int k=1;k<=9;k++){
        int x_set=plane_list[num].x+accum[face_opt[face][0]][k]*face_opt[face][1],
            y_set=plane_list[num].y+accum[face_opt[face][0]^1][k]*face_opt[face][1];
        if(!(x_set>0&&x_set<=10&&y_set>0&&y_set<=10)) continue;
        if(mapt[x_set][y_set]) continue;
        draw_bar(x_set,y_set,LIGHTGRAY);
    }
    return;
}
inline void show_plane(int num){
    int face=plane_list[num].face;
    if(mapt[plane_list[num].x][plane_list[num].y]==0)
        draw_bar(plane_list[num].x,plane_list[num].y,clist[plane_list[num].C]);
    for(int k=1;k<=9;k++){
        int x_set=plane_list[num].x+accum[face_opt[face][0]][k]*face_opt[face][1],
            y_set=plane_list[num].y+accum[face_opt[face][0]^1][k]*face_opt[face][1];
        if(!(x_set>0&&x_set<=10&&y_set>0&&y_set<=10)) continue;
        if(mapt[x_set][y_set]) continue;
        draw_bar(x_set,y_set,clist[plane_list[num].C]);
        //printf("%d ",k);
    }
    //printf("\n");
    return;
}
inline void upd_plane_status(int num){
    if(check_legal(plane_num)) plane_list[plane_num].C=plane_num;
    else plane_list[plane_num].C=4;
    return;
}
inline void create_plane(){
    plane_list[++plane_num].x=target_x; plane_list[plane_num].y=target_y;
    plane_list[plane_num].face=target_face;
    plane_list[plane_num].number=plane_num;
    upd_plane_status(plane_num);
    show_plane(plane_num);
    return;
}
inline void rotate(int val,int num){
    unshow_plane(num); target_face+=val;
    plane_list[num].face+=val;
    if(plane_list[num].face==5) plane_list[num].face=1;
    if(plane_list[num].face==0) plane_list[num].face=4;
    upd_plane_status(num);
    show_plane(num);
}
inline bool confirm_plane_put(int num){
    int face=plane_list[num].face;
    if(plane_list[num].C==4) return 0;
    mapt[plane_list[num].x][plane_list[num].y]=num;
    for(int k=1;k<=9;k++){
        int x_set=plane_list[num].x+accum[face_opt[face][0]][k]*face_opt[face][1],
            y_set=plane_list[num].y+accum[face_opt[face][0]^1][k]*face_opt[face][1];
        mapt[x_set][y_set]=num;
    }
    target_face++;
    if(target_face==5) target_face=1;
    return 1;
}
inline int put_plane(){
    target_x=target_y=target_face=1;
    for(int i=1;i<=3;i++){
        create_plane();
        draw_target();
        for(;;){
            int p=react_to_keyb();
            if(p==44||p==46){
                rotate(45-p,plane_num); draw_target(); continue;
            }
            if(p==13){
                if(confirm_plane_put(plane_num)) break;
                else continue;
            }
            int nx=target_x+mv_x[p],ny=target_y+mv_y[p];
            if(!(nx>0&&nx<=10&&ny>0&&ny<=10)) continue;
            undraw_target(); unshow_plane(plane_num);
            target_x+=mv_x[p]; target_y+=mv_y[p];
            plane_list[plane_num].x=target_x; plane_list[plane_num].y=target_y;
            //printf("%d\n",plane_list[plane_num].C);
            //printf("%d %d\n",plane_list[plane_num].C,plane_list[plane_num].face);
            upd_plane_status(plane_num);
            show_plane(plane_num);
            draw_target();
        }
    }
}

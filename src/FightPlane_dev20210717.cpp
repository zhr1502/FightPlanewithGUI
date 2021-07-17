#include<bits/stdc++.h>
#include<windows.h>
#include"include/GL/glut.h"
#include"include/GL/freeglut.h"
using namespace std;
const int face_opt[5][2]={{},{0,1},{1,1},{0,-1},{1,-1}};
const int accum[2][10]={{0,1,1,1,1,1,2,3,3,3},{0,0,1,2,-1,-2,0,0,1,-1}};
const int mv_x[5]={0,1,0,-1,0},mv_y[5]={0,0,1,0,-1};
const int matrix_siz=10;
const float ordinary_siz=0.087,selected_siz=0.095,table_siz=0.1;
float R=0.5,G=0.5,B=0.5;
const float color_define[6][3]={{0.5,0.5,0.5},{0,0,1},{0,1,0},{0.525,0.145,0.803},{0.7,0,0},{0,0,0}};
/*
0 gray
1 blue
2 green
3 purple
4 dark_red
5 black
*/
struct plane{
    int face,x,y,C,number;
}plane_list[5];
int plane_num;
int stage_now;
/*
0 init windows
1 place own plane
2 waiting for other placing plane
3 choose place to attack
4 waiting for others attack
5 game finished
*/
int viwprt_siz=500;
int planemap[matrix_siz+1][matrix_siz+1];
bool is_target[matrix_siz+1][matrix_siz+1];
int target_x=1,target_y=1,target_face=1;
#include"include/placeownplane.h"
inline void drawbar(const float *c,float a,float b,float siz){
    glColor3fv(c);
    glBegin(GL_POLYGON);
    glVertex2f(a-siz,b-siz);
    glVertex2f(a+siz,b-siz);
    glVertex2f(a+siz,b+siz);
    glVertex2f(a-siz,b+siz);
    glEnd(); return;
}
void Placeplane_displayinit(){
    memset(planemap,0,sizeof(planemap));
    for(int i=1;i<plane_num;i++) upd_plane_status(i),show_plane_inmap(i);
    plane_list[plane_num].x=target_x; plane_list[plane_num].y=target_y;
    plane_list[plane_num].face=target_face;
    upd_plane_status(plane_num); show_plane_inmap(plane_num);
    return;
}
void display(void){
    Placeplane_displayinit();
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=1;i<=matrix_siz;i++)
        for(int j=1;j<=matrix_siz;j++){
                float core_X=(-1+table_siz+2*(j-1)*table_siz),core_Y=(1-table_siz-2*(i-1)*table_siz);
                if(stage_now>=3)
                drawbar(color_define[planemap[i][j]],core_X,core_Y,(i==target_x&&j==target_y)?selected_siz:ordinary_siz);
                else
                drawbar(color_define[planemap[i][j]],core_X,core_Y,ordinary_siz);
            }
    glFlush();
    glutSwapBuffers();
    return;
}
void keyboarddetecter(unsigned char c,int x,int y){
    if(stage_now==1){
        if(c=='\n'||c=='\r') 
            if(confirm_plane_put(plane_num)){
                if(plane_num<3) create_plane();
                else stage_now++,exit(EXIT_SUCCESS);
            }
        if(c=='='){
            rotate(1,plane_num);
        }
        if(c=='-'){
            rotate(-1,plane_num);
        }
        glutPostRedisplay(); return;
    }
    return;
}
void specialkey(int key,int x,int y){
    if(key==GLUT_KEY_UP){
        if(target_x-1) target_x--;
    }
    if(key==GLUT_KEY_DOWN){
        if(target_x+1<=10) target_x++;
    }
    if(key==GLUT_KEY_LEFT){
        if(target_y-1) target_y--;
    }
    if(key==GLUT_KEY_RIGHT){
        if(target_y+1<=10) target_y++;
    }
    glutPostRedisplay();
    return;
}
void changeSize(int w,int h){
	viwprt_siz=min(w,h);
    // glClear(GL_COLOR_BUFFER_BIT); memset(preplanemap,1,sizeof(preplanemap));
    // memset(pretarget,0,sizeof(pretarget));
    glViewport(0, h-viwprt_siz, viwprt_siz, viwprt_siz);
	return;
}
void Mymouse(int button,int state,int x,int y){
    swap(x,y);
    float winx=x*1.0/viwprt_siz,winy=y*1.0/viwprt_siz;
    if(button==GLUT_MIDDLE_BUTTON) exit(EXIT_SUCCESS);
    if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
        int table_pos_x=1,table_pos_y=1;
        //printf("%d %d %.2f %.2f %.2f\n",x,y,winx,winy,siz);
        for(;winx>table_siz;winx-=table_siz,table_pos_x++) if(table_pos_x>10) break;
        for(;winy>table_siz;winy-=table_siz,table_pos_y++) if(table_pos_y>10) break;
        printf("%d %d %.2f %.2f\n",table_pos_x,table_pos_y,winx,winy);
        if(table_pos_x<=10&&table_pos_y<=10){
            if(winx<=(table_siz+ordinary_siz)/2&&winx>=(table_siz-ordinary_siz)/2&&
               winy<=(table_siz+ordinary_siz)/2&&winy>=(table_siz-ordinary_siz)/2)
               target_x=table_pos_x,target_y=table_pos_y;
        }
    }
    return;
}
void MouseWheel(int button,int dir,int x,int y){
    if(dir>0) rotate(1,plane_num);
    if(dir<0) rotate(-1,plane_num);
    glutPostRedisplay();
    return;
}
int main(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(300,300);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow(argv[1]);
    glutDisplayFunc(&display);
    glutReshapeFunc(&changeSize);
    glutMouseFunc(&Mymouse);
    glutSpecialFunc(&specialkey);
    glutKeyboardFunc(&keyboarddetecter);
    glutMouseWheelFunc(MouseWheel);
    stage_now=1;
    create_plane();
    glutMainLoop();
    return 0;
}
#include<bits/stdc++.h>
#ifdef WIN32
    #include<windows.h>
#endif
#include<GL/glut.h>
#include<GL/freeglut.h>
#include"FPplane.hpp"
#include<utility>
using namespace std;
const int screen_h=450,screen_w=774,table_a=300;
float R=0.5,G=0.5,B=0.5;
//const float color_define[6][3]={{0.5,0.5,0.5},{0,0,1},{0,1,0},{0.525,0.145,0.803},{0.7,0,0},{0,0,0}};
/*
0 gray
1 blue
2 green
3 purple
4 dark_red
5 black
*/
extern int stage_now,plane_num;
int EdgeU,EdgeL;
/*
0 init windows
1 place own plane
2 waiting for other placing plane
3 choose place to attack
4 waiting for others attack
5 game finished
*/

#include"FPUI.hpp"
button Button[10];
const float screen_ratio=screen_h*1.0/screen_w;
int viwprt_siz=300,windowid,Buttonum;
float viwprt_zoom=1;
extern int target_x,target_y,target_face;
void drawbar(const float *c,float a,float b,float siz){
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
void display_table(int num){
	float Midline=(float)(1+MapH)/2;
    for(int i=1;i<=MapH;i++)
        for(int j=1;j<=MapW;j++){
            float core_X=(num*2-3)*(MiddleSiz/2)+j*TableSiz+(num-2)*TableSiz*MapW-TableSiz/2,
                  core_Y=(Midline-i)*TableSiz;
            if(stage_now>=3)
            	drawbar(color_define[planemap[i][j]],core_X,core_Y,(i==target_x&&j==target_y)?SelectedSiz/2:OrdinarySiz/2);
            else
            	drawbar(color_define[planemap[i][j]],core_X,core_Y,OrdinarySiz/2);
        }
    return;
}
pair<float,float> TransformToOrtho(int x,int y){
	return make_pair((x-EdgeL)/(screen_w*viwprt_zoom)*WidthSizeinAxis,(y-EdgeU)/(screen_h*viwprt_zoom)*HeightSizeinAxis);
}
void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
	if(stage_now==0){
		for(int i=1;i<=Buttonum;i++)
			Button[i].display();
		printf("%d button displayed\n",Buttonum);

	}
    if(stage_now==1){
        Placeplane_displayinit();
        display_table(1); display_table(2);
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
				else stage_now++;
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
        if(target_x+1<=MapW) target_x++;
    }
    if(key==GLUT_KEY_LEFT){
        if(target_y-1) target_y--;
    }
    if(key==GLUT_KEY_RIGHT){
        if(target_y+1<=MapH) target_y++;
    }
    glutPostRedisplay();
    return;
}
void changeSize(int w,int h){
	viwprt_zoom=min(w*1.0/screen_w,h*1.0/screen_h);
    if(w*1.0/screen_w<h*1.0/screen_h) viwprt_siz=w*screen_ratio;
    else viwprt_siz=h;
    glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float scale=(float)w*screen_h/screen_w/h;
	if(w/WidthSizeinAxis>=h/HeightSizeinAxis)
		gluOrtho2D(LeftEdgeAxis*scale,RightEdgeAxis*scale,BottomAxis,TopAxis),
		viwprt_zoom=(float)h/screen_h,
		EdgeL=int((w-screen_w*viwprt_zoom)/2),EdgeU=0;
	else
		gluOrtho2D(LeftEdgeAxis,RightEdgeAxis,BottomAxis/scale,TopAxis/scale),
		viwprt_zoom=(float)w/screen_w,
		EdgeU=int((h-screen_h*viwprt_zoom)/2),EdgeL=0;	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	return;
}
void Mymouse(int button,int state,int x,int y){
    if(button==GLUT_MIDDLE_BUTTON) exit(EXIT_SUCCESS);
    if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
		if(stage_now==0){
			for(int i=1;i<=Buttonum;i++) Button[i].Onpressed(x,y);
		}
		pair<float,float> Pos=TransformToOrtho(x,y);
		float MouseMapX=Pos.first-EdgeSiz,MouseMapY=Pos.second-TopBarSiz;
        int table_pos_x=int(MouseMapX/TableSiz),table_pos_y=int(MouseMapY/TableSiz);
		if(table_pos_x*TableSiz<MouseMapX) table_pos_x++;
		if(table_pos_y*TableSiz<MouseMapY) table_pos_y++;
		if(MouseMapX>=0&&MouseMapY>=0&&table_pos_x<=MapW&&table_pos_y<=MapH)
			target_x=table_pos_y,target_y=table_pos_x;
    }
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_UP){
		if(stage_now==0)
			for(int i=1;i<=Buttonum;i++)
				if(Button[i].is_pressed)
					Button[i].Dispressed();
	}
    #ifdef linux
        if(button==3&&state==GLUT_DOWN){
            rotate(1,plane_num);
        }
        if(button==4&&state==GLUT_DOWN){
            rotate(-1,plane_num);
        }
    #endif
    glutPostRedisplay();
    return;
}
#ifdef WIN32
    void MouseWheel(int button,int dir,int x,int y){
        if(dir>0) rotate(1,plane_num);
        if(dir<0) rotate(-1,plane_num);
        glutPostRedisplay();
        return;
    }
#endif
void mouseMove(int x,int y){
	bool flag=0;
	for(int i=1;i<=Buttonum;i++) flag|=Button[i].Onpitch(x,y);
	if(flag) glutPostRedisplay();
	return;
}
void init(int argc,char **argv){
    glutInit(&argc,argv);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(screen_w,screen_h);
    glutInitDisplayMode(GLUT_DOUBLE);
    windowid=glutCreateWindow(argv[1]);
    glutDisplayFunc(&display);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(LeftEdgeAxis,RightEdgeAxis,BottomAxis,TopAxis);
    glutReshapeFunc(&changeSize);
    glutMouseFunc(&Mymouse);
    glutSpecialFunc(&specialkey);
    glutKeyboardFunc(&keyboarddetecter);
	glutPassiveMotionFunc(mouseMove);
    #ifdef WIN32
        glutMouseWheelFunc(MouseWheel);
    #endif
}
void DestroyWindow(){
	glutDestroyWindow(windowid);
	return;
}


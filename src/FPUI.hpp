#include"parameter.hpp"
#include<GL/glut.h>
#include<GL/freeglut.h>
void drawbar(const float*,float,float,float);
void Placeplane_displayinit();
void display_table(int);
void display(void);
void keyboarddetecter(unsigned char,int,int);
void specialkey(int,int,int);
void changeSize(int,int);
void Mymouse(int,int,int,int);
void init(int,char**);
void DestroyWindow();
pair<float,float> TransformToOrtho(int,int);
const float color_define[6][3]={{0.5,0.5,0.5},{0,0,1},{0,1,0},{0.525,0.145,0.803},{0.7,0,0},{0,0,0}};
struct button{
	float endpointx,endpointy;
	float Bwidth,Bheight;
	int color;
	bool is_pressed;
	bool is_pitched;
	void create_button(float ex,float ey,float W,float H,int c){
		endpointx=ex; endpointy=ey;
		Bwidth=W; Bheight=H;
		color=c;
		return;
	}
	void display(){
		float R=color_define[color][0],G=color_define[color][1],B=color_define[color][2];
		float blacken=1,scale=1;
		if(is_pressed) blacken=0.9;
		glColor3f(R*blacken,G*blacken,B*blacken);
		glPushMatrix();
		glTranslatef(endpointx+Bwidth/2,endpointy+Bheight/2,0);
		if(is_pitched)	scale=1.02;
		else scale=1;
    	glBegin(GL_POLYGON);
		glVertex2f(-Bwidth/2*scale,-Bheight/2*scale);
		glVertex2f(Bwidth/2*scale,-Bheight/2*scale);
		glVertex2f(Bwidth/2*scale,Bheight/2*scale);
		glVertex2f(-Bwidth/2*scale,Bheight/2*scale);
		glEnd();
		glPopMatrix();
		return;
	}
	void Dispressed(){
		is_pressed=0;
		return;
	}
	bool Onpressed(int x,int y){
		bool pre=is_pressed;
		pair<float,float> Pos=TransformToOrtho(x,y);
		float Posx=Pos.first+LeftEdgeAxis,Posy=TopAxis-Pos.second;
		if(Posx>=endpointx&&Posx<=endpointx+Bwidth&&
		   Posy>=endpointy&&Posy<=endpointy+Bheight)
			is_pressed=1;
		else is_pressed=0;
		//printf("Button press Detector:%d\n",is_pressed);
		return pre!=is_pressed;
	}
	bool Onpitch(int x,int y){
		bool pre=is_pitched;
		pair<float,float> Pos=TransformToOrtho(x,y);
		float Posx=Pos.first+LeftEdgeAxis,Posy=TopAxis-Pos.second;
		if(Posx>=endpointx&&Posx<=endpointx+Bwidth&&
		   Posy>=endpointy&&Posy<=endpointy+Bheight)
			is_pitched=1;
		else is_pitched=0;
		//printf("Button Pitch Detector:%.2f %.2f %d\n",Posx,Posy,is_pitched);
		return pre!=is_pitched;

	}
};
struct anchored_button{
	int endpointix,endpointiy;
	int Bwidthi,Bheighti;
	float endpointx,endpointy;
	float Bwidth,Bheight;
	int color;
	bool is_pressed;
	bool is_pitched;
	void create_button(int ex,int ey,int W,int H,int c){
		endpointix=ex; endpointiy=ey;
		Bwidthi=W; Bheighti=H;
		upd_button();
		color=c;
		return;
	}
	void upd_button(){
		return;
	}
	void display(){
		float R=color_define[color][0],G=color_define[color][1],B=color_define[color][2];
		float blacken=1,scale=1;
		if(is_pressed) blacken=0.9;
		glColor3f(R*blacken,G*blacken,B*blacken);
		glPushMatrix();
		glTranslatef(endpointx+Bwidth/2,endpointy+Bheight/2,0);
		if(is_pitched)	scale=1.02;
		else scale=1;
    	glBegin(GL_POLYGON);
		glVertex2f(-Bwidth/2*scale,-Bheight/2*scale);
		glVertex2f(Bwidth/2*scale,-Bheight/2*scale);
		glVertex2f(Bwidth/2*scale,Bheight/2*scale);
		glVertex2f(-Bwidth/2*scale,Bheight/2*scale);
		glEnd();
		glPopMatrix();
		return;
	}
	void Dispressed(){
		is_pressed=0;
		return;
	}
	bool Onpressed(int x,int y){
		bool pre=is_pressed;
		pair<float,float> Pos=TransformToOrtho(x,y);
		float Posx=Pos.first+LeftEdgeAxis,Posy=TopAxis-Pos.second;
		if(Posx>=endpointx&&Posx<=endpointx+Bwidth&&
		   Posy>=endpointy&&Posy<=endpointy+Bheight)
			is_pressed=1;
		else is_pressed=0;
		//printf("Button press Detector:%d\n",is_pressed);
		return pre!=is_pressed;
	}
	bool Onpitch(int x,int y){
		bool pre=is_pitched;
		pair<float,float> Pos=TransformToOrtho(x,y);
		float Posx=Pos.first+LeftEdgeAxis,Posy=TopAxis-Pos.second;
		if(Posx>=endpointx&&Posx<=endpointx+Bwidth&&
		   Posy>=endpointy&&Posy<=endpointy+Bheight)
			is_pitched=1;
		else is_pitched=0;
		//printf("Button Pitch Detector:%.2f %.2f %d\n",Posx,Posy,is_pitched);
		return pre!=is_pitched;

	}
};

extern button Button[10];
extern int Buttonum;

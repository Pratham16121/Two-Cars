#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
//**************All the function which are working properly*****************
void Instruction();
void SetObj(int);
void Roads();
void car(int,int,int);
void Square(int,int,int);
void Border();
void WelcomePage();
void Circles(int,int,int);
void setvalues();
void Motion(int);
void ShiftCars(char);
//**************************Global variables********************************
int midx,midy,speed; 
int Cary;
int Lane1,Lane2,Lane3,Lane4;
int BlueCarX,RedCarX; // These are my two cars varibale
int BlueObjX,RedObjX,RedObjY=30,BlueObjY=30,BlueObjShape,RedObjShape;
int Out=0,Score=0;
//***********Now the game***************************************************
void Exit()
{
	cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t   "<<Score;
	Border();
	outtextxy(midx-50,midy-12,"Score is ");
}
void SpeedChanger(){
	if(Score>=0&&Score<=3)
		speed=7;
	else if(Score>=4&&Score<=8)
		speed=6;
	else if(Score>=9&&Score<=14)
		speed=5;
	else if(Score>=14&&Score<=18)
		speed=4;
	else if(Score>=19&&Score<=25)
		speed=3;
	else if(Score>=26)
		speed=2;
}
void GameFrame()
{
	Roads();
	car(BlueCarX,Cary,1);
	car(RedCarX,Cary,4);
	randomize();
	SetObj(1);
	SetObj(4);
	char ch;
	P:while(!kbhit()){
		Motion(1);
		Motion(4);
		delay(speed);
		if(Out)
		{
			goto Q;
		}
	}
	ch=getch();
	ShiftCars(ch);
	goto P;
	Q:cleardevice();
	Exit();
}
void main()
{
	int gd=DETECT, gm;
	initgraph(&gd,&gm," ");
	setvalues();
	Border();
	WelcomePage();
	cleardevice();
	Border();
	GameFrame();
	getch();
	getch();
}
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
void ShiftCars(char ch)
{
	if(ch=='s'){
		car(BlueCarX,Cary,0);
		BlueCarX=(BlueCarX==Lane1)?Lane2:Lane1;
		car(BlueCarX,Cary,1);
	}
	else if (ch=='k'){
		car(RedCarX,Cary,0);
		RedCarX=(RedCarX==Lane3)?Lane4:Lane3;
		car(RedCarX,Cary,4);
	}
}
void Motion(int color)
{
	int shape, x, y;
	int CarX;
	if(color ==1){
		shape = BlueObjShape;
		x = BlueObjX;
		y = BlueObjY;
		BlueObjY++;
		CarX=BlueCarX;
	}
	else{
		shape = RedObjShape;
		x = RedObjX;
		y = RedObjY;
		RedObjY++;
		CarX=RedCarX;
	}

	if(y<=2*midy-93){
		if(shape == 0){
			Circles(x,y,0);
			y++;
			Circles(x,y,color);
		}
		else{
			Square(x,y,0);
			y++;
			Square(x,y,color);
		}
	}
	else{
		if(CarX==x){
			if(shape==1){
				Out = 1;
			}
		}
		else{
			if(shape == 0){
				Out = 1;
			}
		}
		if(!Out){
			if(shape == 0){
				Score++;
				Circles(x,y,0);
				SpeedChanger();
			}
			else{
				Square(x,y,0);
			}
			SetObj(color);
			car(CarX,Cary,color);
		}
	}


	/*if(color==1){
		if(BlueObjY<=2*midx-93){
			if(BlueObjShape==0){
				Circles(BlueObjX,BlueObjY,0);
				BlueObjY++;
				Circles(BlueObjX,BlueObjY,1);
			}
			else{
				Square(BlueObjX,BlueObjY,0);
				BlueObjY++;
				Square(BlueObjX,BlueObjY,1);
			}
		}
	}
	else{
		if(RedObjY<=2*midx-93){
			if(RedObjShape==0){
				Circles(RedObjX,RedObjY,0);
				RedObjY++;
				Circles(RedObjX,RedObjY,1);
			}
			else{
				Square(RedObjX,RedObjY,0);
				RedObjY++;
				Square(RedObjX,RedObjY,1);
			}
		}
	}*/
}
void SetObj(int color)
{
	int lane=random(2);
	int shape=random(2);
	int x;

	if(color==1)
	{
		BlueObjShape = shape;

		if(lane == 0){
			x = Lane1;
		}
		else{
			x = Lane2;
		}
		BlueObjX = x;
		BlueObjY = 30;
	}
	else{
		RedObjShape = shape;

		if(lane == 0){
			x = Lane3;
		}
		else{
			x = Lane4;
		}
		RedObjX = x;
		RedObjY = 30;
	}

	if(shape == 0){
		Circles(x,30,color);
	}
	else{
		Square(x,30,color);
	}
}

void setvalues()
{
	midx=getmaxx()/2;
	midy=getmaxy()/2;
	Cary=getmaxy()-60;
	Lane1=midx-150;
	Lane2=midx-50;
	Lane3=midx+50;
	Lane4=midx+150;
	BlueCarX=Lane1;
	RedCarX=Lane4;
	speed=8;
}
void Circles(int x,int y,int color)
{
	setcolor(color);
	circle(x,y,8);
	setcolor(WHITE);
}
void Square(int x,int y,int color)
{
	setcolor(color);
	int Polygon[]={x-8,y-8,x+8,y-8,x+8,y+8,x-8,y+8,x-8,y-8};
	drawpoly(5,Polygon);
	setcolor(WHITE);
}
void car(int x,int y,int color)
{
	int Polygon[]={x-5,y+10,x+5,y+10,x+5,y-10,x-5,y-10,x-5,y+10};
	setcolor(color);
	drawpoly(5,Polygon);
	Polygon[2]=x+10;
	Polygon[3]=y-18;
	Polygon[0]=x-10;
	Polygon[1]=y-18;
	Polygon[8]=Polygon[0];
	Polygon[9]=Polygon[1];
	drawpoly(5,Polygon);
	Polygon[4]=x+5;
	Polygon[5]=y+10;
	Polygon[6]=x-5;
	Polygon[7]=y+10;
	Polygon[2]=x+9;
	Polygon[3]=y+15;
	Polygon[0]=x-9;
	Polygon[1]=y+15;
	Polygon[8]=Polygon[0];
	Polygon[9]=Polygon[1];
	drawpoly(5,Polygon);
	int Body[]={x-5,y-25,x+5,y-25,x+12,y-18,x+12,y+17,x-12,y+17,x-12,y-18,x-5,y-25};
	drawpoly(7,Body);
	setcolor(WHITE);
}
void Instruction()
{
	outtextxy(midx-47,midy-145,"INSTRUCTIONS");
	line(midx-51,midy-135,midx+51,midy-135);
	int Polygon[]={midx-150,midy-150,midx+150,midy-150,midx+150,midy+150,midx-150,midy+150,midx-150,midy-150};
	drawpoly(5,Polygon);
	setlinestyle(2,0,0);
	line(midx,midy-130,midx,midy+145);
	outtextxy(midx-142,midy-120,"Press S to change");
	outtextxy(midx-140,midy-100,"    the lane");
	outtextxy(midx+8,midy-120,"Press K to change");
	outtextxy(midx+10,midy-100,"    the lane");
	setlinestyle(1,0,0);
	setcolor(BLUE);
	line(midx-75,midy-75,midx-75,midy+145);
	setcolor(RED);
	line(midx+75,midy-75,midx+75,midy+145);
	setcolor(WHITE);
	setlinestyle(0,0,0);
	line(midx-95,midy+113,midx-50,midy+113);
	outtextxy(midx-53,midy+110,">");
	outtextxy(midx+50,midy+110,"<");
	line(midx+50,midy+113,midx+95,midy+113);
	car(midx-112,midy+112,1);
	Square(midx-112,midy,1);
	car(midx+112,midy+112,4);
	Circles(midx+37,midy,4);
	setcolor(WHITE);
	outtextxy(midx-130,midy+157,"-> You have to dodge the squares");
	outtextxy(midx-155,midy+170,"-> You have to collect ALL the Circless");
	outtextxy(midx-240,midy+183,"-> Your score will be equal to the number of Circless collected");
	outtextxy(midx-115,midy+205,"Press ENTER to start the game");
}
void Border()
{
	int maxx=getmaxx(),maxy=getmaxy();
	line(0,0,0,maxy);
	line(0,0,maxx,0);
	line(0,maxy,maxx,maxy);
	line(maxx,maxy,maxx,0);
	line(3,3,3,maxy-3);
	line(3,3,maxx-3,3);
	line(3,maxy-3,maxx-3,maxy-3);
	line(maxx-3,maxy-3,maxx-3,3);
	line(6,6,6,maxy-6);
	line(6,6,maxx-6,6);
	line(6,maxy-6,maxx-6,maxy-6);
	line(maxx-6,maxy-6,maxx-6,6);
}
void WelcomePage()
{
	outtextxy(getmaxx()/2 - 75,50,"Welcome to the game");
	line(getmaxx()/2 - 95,65,getmaxx()/2 + 95,65);
	Instruction();
	getch();
}
void Roads()
{
	int maxy=getmaxy();
	int Poly[]={midx-200,20,midx+200,20,midx+200,maxy-20,midx-200,maxy-20,midx-200,20};
	drawpoly(5,Poly);
	setlinestyle(2,0,0);
	line(midx,22,midx,maxy-22);
	setlinestyle(1,0,0);
	setcolor(BLUE);
	line(midx-100,25,midx-100,maxy-25);
	setlinestyle(1,0,0);
	setcolor(RED);
	line(midx+100,25,midx+100,maxy-25);
	setlinestyle(0,0,0);
	setcolor(WHITE);
}

#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<winbgim.h>
#include<time.h>
#include<iostream>
#include<ctime>
#include<vector>


void menu();

void encabezadoguardar();
char *ingresar(int x, int y);
FILE *datalogf;
int a=0,i=0,t=0,x=0,xx=0,yy=0,bandera1=0,bandera2=0,bandera3=0,salir=0,len;
char enviado[300],mensaje[300],recibido[10],hora[100],valormap[100],valortps[100],num[20];
HANDLE h;
DCB dcb;
DWORD dwEventMask,n;


int main(){
	
initwindow(500,200);
datalogf=fopen("datalog.csv","at+");
encabezadoguardar();
while(1){


menu();


	}

	return 0;
}

void menu(){







outtextxy(80,25,"Boost control datalog");


outtextxy(80,120,"TPS %: ");
outtextxy(250,120, valortps);
outtextxy(80,220,"MAP: ");
outtextxy(250,220, valormap);


	outtextxy(400,100,"Ingresar presion:  "); 
	



}





#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<winbgim.h>
#include<time.h>
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<winbgim.h>
#include<time.h>
#include<iostream>


void Puerto();
void Data();
void Guardar();
void Menu();
void Mouse();
void Time();
void Salir();


int a=0,i=0,t=0,x=0,xx=0,yy=0;
FILE *fichero;
char enviado[300],mensaje[300],recibido[10],MY_TIME[50],ultimo[300];
HANDLE h;
DCB dcb;
DWORD dwEventMask,n;

int main(){
	initwindow(500,200);
	fichero=fopen("Datalogger.csv","at+");
    Puerto();
    while(1){
        while(kbhit()){
           	gets(enviado);
            strcat(enviado,"|");
            t=strlen(enviado);
            for(i=0;i<=t;i++){
                WriteFile(h, &enviado[i], 1, &n, NULL);
            }                 
        }
        Data();
	}
	return 0;
}

void Puerto(){
	
	h=CreateFile("COM3",GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
    if(h==INVALID_HANDLE_VALUE){ /*ocurrio un error al intentar abrir el puerto*/
    }

       /* obtenemos la configuracion actual */
    if(! GetCommState(h, &dcb)){/* error: no se puede obtener la configuracion */
    }
        
    /* Configuramos el puerto */
    dcb.BaudRate = CBR_9600; //9600 Baud
    dcb.ByteSize = 8; //8 data bits
    dcb.Parity = NOPARITY; //no parity
    dcb.StopBits = ONESTOPBIT; //1 stop
        
    COMMTIMEOUTS timeouts; //Comando para establecer la espera al leer el puerto
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutMultiplier = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 50;
    timeouts.WriteTotalTimeoutConstant = 10;
    SetCommTimeouts(h, &timeouts);  /* Establecemos la nueva configuracion */
        
    if(!SetCommState(h, &dcb)){
        /* Error al configurar el puerto */
    }
 
    /* Para que WaitCommEvent espere el evento RXCHAR */
    SetCommMask(h, EV_RXCHAR);
        
}

void Data(){
	ReadFile(h, &recibido, 1 , &n, NULL);
	Menu();
	Mouse();
	Time(); 
    if(recibido[0]!=0){
        if(recibido[0]=='|'){
            Guardar();
            recibido[0]=0;
            ultimo[0]=0;
            strcat(ultimo,mensaje);
            x=strlen(mensaje);
            for(a=0;a<=x;a++){
                mensaje[a]=0;
            }
        }
        else{
            strcat(mensaje,recibido);
        }
    }
}

void Guardar(){
	Sleep(1000);
	fprintf(fichero,mensaje);
	fprintf(fichero,",");
	fprintf(fichero,MY_TIME);
	fprintf(fichero,"\n");
}

void Menu(){
	cleardevice();
	setcolor(4);
	settextstyle(4,0,2);
	outtextxy(15,5,"Datalogger");
	rectangle(120,75,270,110);
	rectangle(295,75,445,110);
	rectangle(20,130,95,160);
	setcolor(8);
	outtextxy(25,40, "Ultimo Dato: ");
	outtextxy(25,80, "Led: ");
	setcolor(15);
	outtextxy(225,40,ultimo);
	outtextxy(125,80,"Encender");
	outtextxy(300,80,"Apagar");
	outtextxy(25,135,"Salir");
	outtextxy(150,135,MY_TIME);
}

void Mouse(){
	getmouseclick(WM_LBUTTONDOWN, xx, yy);
	if(xx>120 && xx<270 && yy>75 && yy<110){
		strcat(enviado,"led_1|");
        t=strlen(enviado);
        for(i=0;i<=t;i++){
            WriteFile(h, &enviado[i], 1, &n, NULL);
        }
	}
	if(xx>295 && xx<445 && yy>75 && yy<110){
		strcat(enviado,"led_0|");
        t=strlen(enviado);
        for(i=0;i<=t;i++){
            WriteFile(h, &enviado[i], 1, &n, NULL);
        }
	}
	if(xx>20 && xx<95 && yy>130 && yy<160){
		Salir();
	}
	xx=0;
	yy=0;
	enviado[0]='\0';
}

void Time(){
	time_t t;
    struct tm *tmp;
    time(&t); 
    tmp = localtime(&t); 
    strftime(MY_TIME, sizeof(MY_TIME), "%x,%X", tmp);
}

void Salir(){
	closegraph();
	fclose(fichero);
}



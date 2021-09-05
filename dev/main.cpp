#include<windows.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<winbgim.h>
#include<time.h>
#include<iostream>
#include <ctime>
#include <vector>
char tecla;
int h=0,x=0,xx=0,yy=0,malone=1,post=0,fat=0,fat1=0,fat2=0,salir=0,nn=1,y=0,t,i,a,len,larg=-100,count=0,led=0,b=0,b1=0,b2=0,b3=0,b4=0,b5=0,dl=0,res2,z=150,estado=0,COMnum=0;
float res;
char enviado[300],mensaje[300],recibido[50],hora[100],valortps[100],valormap[100],encendido[100],valorpfinal[200],valorpbase[200],num[300],histeresis[100],histeresis2[100];
char COM[5]="COM0";
int ancho=700,alto=400;
void menu();
void mouse();
void puerto();
void recibir();
void hora2();
FILE *datalogf;
void guardar();
void encabezadoguardar();
void limpiar();
void salirr();
HANDLE p;
DCB dcb;
DWORD dwEventMask,n;




int main(){

	initwindow(ancho,alto);
	datalogf=fopen("datalog.csv","at+");
encabezadoguardar();
setbkcolor(0);
setcolor(15);
puerto();
if(estado==1){
	
menu();
}
else
{
	puerto();
}
}

void mouse()
{
 if(310<yy&&yy<350&&0<=xx&&xx<=700)
 {  

  	 	 
    malone=0;
    fat=0;
    fat2=0;
 	h=215;
 	z=-40;
 larg=-150;
 	post=post+1;
 	if(post==2)
 	{    post=0;
 		 salirr();
	 }
 }
  if(270<yy&&yy<330&&250<=xx&&xx<=310)  
 {

 	malone=0;
 	post=0;
 	h=185;
 	fat=fat+1;
 	z=140;
 	 larg=-50;
 	fat2=0;
 	dl=1;

 	if(fat==2)
 	{
 		fat=0;
 		x=0;
	}
 }	
 

  if(270<yy&&yy<330&&321<=xx&&xx<=400) 
 {

 	malone=0;
 	post=0;
 	h=185;
 	z=230;
 	 larg=40;
 	fat2=fat2+1;
 	fat=0,fat1=0;
 	dl=0;
 	if(fat2==2)
 	{
 		fat2=0;
 		x=0;
	}
 }	
	
 
	

	
}

void puerto(){

       while(estado!=1)
       {
           p=CreateFile(COM,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	   
	   if(p==INVALID_HANDLE_VALUE)
       { /*ocurrio un error al intentar abrir el puerto*/
       
       settextstyle(10,0,5);
       
        rectangle(40,95,ancho-35,alto-50);

      outtextxy(35,30,"BOOST CONTROL");
 
      settextstyle(10,0,2);
      
       outtextxy(100,110,"ERROR EN EL PUERTO.. ");
       outtextxy(100,140,"REINTENTANDO... ");
       
       COMnum++;
      COM[3]=49+COMnum;

      if(COMnum>=15)
      	{
      		outtextxy(100,190,"ERROR, NO HAY DISPOSITIVO CONECTADO ");
           getch();
           exit(0);
       }
       estado=0;
   }
                 	else
         	{
               estado=1;
            }
       
   }


       /* obtenemos la configuracion actual */
       if(! GetCommState(p, &dcb))
       {/* error: no se puede obtener la configuracion */
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
        SetCommTimeouts(p, &timeouts);  /* Establecemos la nueva configuracion */
        
        if(!SetCommState(p, &dcb))
        {
        /* Error al configurar el puerto */
        }
 
         /* Para que WaitCommEvent espere el evento RXCHAR */
        SetCommMask(p, EV_RXCHAR);  

}


void recibir(){
	ReadFile(p, &recibido, 1 , &n, NULL);    
            if(recibido[0]!=0){
                if(recibido[0]=='@'){             
                  strcat(valormap,mensaje);
                  strcat(valormap," BAR     ");
                  b=1;
                   recibido[0]=0;
                    len=strlen(mensaje);
                    for(a=0;a<=len;a++){
                        mensaje[a]=0;
                    }
                }
                    if(recibido[0]=='/'){               
                  strcat(valorpfinal,mensaje);
                  strcat(valorpfinal," BAR    ");
                   b1=1;
                   recibido[0]=0;
                    len=strlen(mensaje);
                    for(a=0;a<=len;a++){
                        mensaje[a]=0;
                    }
                }
                if(recibido[0]=='%'){               
                  strcat(valortps,mensaje);
                  strcat(valortps," %    ");
                     b4=1;
                   recibido[0]=0;
                    len=strlen(mensaje);
                    for(a=0;a<=len;a++){
                        mensaje[a]=0;
                    }
                }

                if(recibido[0]=='|'){               
                  strcat(encendido,mensaje);
                  strcat(encendido,"     ");
                     b2=1;
                   recibido[0]=0;
                    len=strlen(mensaje);
                    for(a=0;a<=len;a++){
                        mensaje[a]=0;
                    }
                }
                else{
                    strcat(mensaje,recibido);

	                
                }

            }
}

void guardar(){
	if (dl==1){

            if(b==1 && b1==1 && b2==1 && b4==1){
		


              fprintf(datalogf,valormap);
	           fprintf(datalogf,";");
	           	         fprintf(datalogf,valorpfinal);

	           fprintf(datalogf,";");
	           	        fprintf(datalogf,valortps);

	           fprintf(datalogf,";");
	           
	           	           fprintf(datalogf,encendido);

	           fprintf(datalogf,";");
	          fprintf(datalogf,hora);
	           fprintf(datalogf,"\n");
                b3=1;
                b=0;
                b1=0;
                b2=0;
                b4=0;
            	}
	}	          
}

void limpiar(){


			   if(b3==1 || dl==0)    {
			  


                    len=strlen(valormap);
                    for(a=0;a<=len;a++){
                        valormap[a]=0;
                    }
                   
                    len=strlen(valortps);
                    for(a=0;a<=len;a++){
                        valortps[a]=0;
                        
                    }
                    len=strlen(encendido);
                    for(a=0;a<=len;a++){
                        encendido[a]=0;

                        
                   }
                   len=strlen(valorpfinal);
                    for(a=0;a<=len;a++){
                        valorpfinal[a]=0;

                        
                   }

 
b3=0;

}
}
void encabezadoguardar(){


		    fprintf(datalogf,"PRES WG");
	          fprintf(datalogf,";");
	          fprintf(datalogf,"V.P.EXTRA");
	          fprintf(datalogf,";");
	         fprintf(datalogf,"TPS");
	          fprintf(datalogf,";");
	          fprintf(datalogf,"ON/OFF");
	          fprintf(datalogf,";");
	          	fprintf(datalogf,"HORA");
	          fprintf(datalogf,"\n");

}
void hora2(){

    

time_t tiempo = time(0);

struct tm * tlocal = localtime(&tiempo);
strftime(hora,128,"%H:%M:%S",tlocal);

outtextxy(550,65,hora);


 

}
void menu()
{


do{
	h=0,malone=1;

do
{
if(nn==1)
{cleardevice();
 nn=0;}
 
 recibir();
  hora2();


 settextstyle(10,0,5);

 rectangle(100+z,100+h,350+larg,130+h);

rectangle(40,95,ancho-35,alto-50);

 outtextxy(35,30,"BOOST CONTROL");
 
 settextstyle(10,0,2);

 outtextxy(100,110,"Presion de turbo: ");

outtextxy(400,110,valormap);

 outtextxy(100,140,"Tps: ");

 
 outtextxy(400,140,valortps);
 
 
  outtextxy(100,200,"ESTADO DEL CONTROLADOR: ");
 
 outtextxy(480,200,encendido);


 
outtextxy(100,170,"Presion extra: ");
outtextxy(400,170, valorpfinal);

 outtextxy(100,290,"DATALOG");
  outtextxy(250,290,"ON   /   OFF");

 outtextxy(100,320,"Salir");


   guardar();
   
limpiar();

if(kbhit())
{
 tecla=getch(); 
 nn=1;	
}
if(ismouseclick(WM_LBUTTONDOWN))
{
	getmouseclick(WM_LBUTTONDOWN,xx,yy);
    clearmouseclick(WM_LBUTTONDOWN);
    nn=1;
}
else
{
	xx=0;
	yy=0;
}

  mouse();
 
 tecla=0;
}
while(x==0);
x=0;




}while(salir==0);

}


void salirr(){
    fclose(datalogf);
	closegraph();

}










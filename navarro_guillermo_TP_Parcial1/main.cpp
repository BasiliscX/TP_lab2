#include<iostream>
#include<cstring>
#include<ctime>
using namespace std;
#include"ventanimation.h"
#include"JugadoresFunciones.h"
#include"DeportesFunciones.h"
#include"MenuConfiguracion.h"
#include"reportes.h"

int main(){
    int x,y, eleccion;
    bool menu=true;
    while(menu){
ConsoleSize(80,40);
ConsoleTitle("TORNEO DE DEPORTES");
        system("cls");
        BoxAnimation(3,ConsoleColumns()-1,ConsoleRows()-1,2);
        x=(ConsoleColumns()/4)-5;
        y=ConsoleRows()/2;
        PosXY(x,y);
        BoxAnimation(2,(ConsoleColumns()/2)+10,(y-10),2);
        x=(ConsoleColumns()/4);
        y=(ConsoleRows()/2)+2;
        PosXY(x,y++);
        TextAnimation("1) MENU JUGADORES");
        PosXY(x,y++);
        TextAnimation("2) MENU DEPORTES");
        PosXY(x,y++);
        TextAnimation("3) REPORTES");
        PosXY(x,y++);
        TextAnimation("4) CONFIGURACION");
        PosXY(x,y++);
        TextAnimation("0) FIN DEL PROGRAMA");
        PosXY(x+=4,y+1);
        TextAnimation("SELECCIONE UNA DE LAS OPCIONES: ");
        cin>>eleccion;

        switch(eleccion){
            case 1 : MenuJugadores(); break;
            case 2 : MenuDeportes(); break;
            case 3 : Reportes(); break;
            case 4 : MenuConfiguracion(); break;
            default: menu=false; break;
        }
    }
PosXY(PosX(),PosY()+8);
return 0;
}

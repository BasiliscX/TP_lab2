#ifndef MENUCONFIGURACION_H_INCLUDED
#define MENUCONFIGURACION_H_INCLUDED

void MenuConfiguracion();
bool copiarJugadores();bool copiarDeportes();
bool RestaurarJugadores();
bool RestaurarDeportes();
bool DatosInicio();

void MenuConfiguracion(){
    int x,y, eleccion;
    bool menu=true;

    while(menu){
        system("cls");
        ConsoleTitle("MENU CONFIGUACION");
        BoxAnimation(3,ConsoleColumns(),ConsoleRows()-1,2);
        x=(ConsoleColumns()/4)-5;
        y=ConsoleRows()/2;
        PosXY(x,y);
        BoxAnimation(2,(ConsoleColumns()/2)+14,(y-10),2);
        x=(ConsoleColumns()/4);
        y=(ConsoleRows()/2)+2;
        PosXY(x,y++);
        TextAnimation("1) COPIA DE SEGURIDAD DEL ARCHIVO DE JUGADORES");
        PosXY(x,y++);
        TextAnimation("2) COPIA DE SEGURIDAD DEL ARCHIVO DE DEPORTES");
        PosXY(x,y++);
        TextAnimation("3) RESTAURAR EL ARCHIVO DE JUGADORES");
        PosXY(x,y++);
        TextAnimation("4) RESTAURAR EL ARCHIVO DE DEPORTES");
        PosXY(x,y++);
        TextAnimation("5) ESTABLECER DATOS DE INICIO");
        PosXY(x,y++);
        TextAnimation("0) VOLVER AL MENU PRINCIPAL");
        PosXY(x+=4,y++);
        TextAnimation("Eleccion: ");
        cin>>eleccion;

        switch(eleccion){
            case 1 : copiarJugadores(); break;
            case 2 : copiarDeportes(); break;
            case 3 : RestaurarJugadores(); break;
            case 4 : RestaurarDeportes(); break;
            case 5 : DatosInicio(); break;
            default: menu=false; break;
        }
    }
}
bool copiarJugadores(){
    JugadoresArchivo archivo[2]{"Jugadores.dat","Jugadores.bkp"};
    system("cls");
ConsoleTitle("GUARDAR DATOS DE JUGADORES");
int x=30;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("COPIA DE SEGURIDAD");
    x=4;
PosXY(x,y+6);
    int eleccion;
    bool soloActivos=true;
TextAnimation("Desea copiar tambien los elementos inactivos? (1:Si, 0:No): ");
    cin>>eleccion;
    if(eleccion==1){ soloActivos=false; }
    y=PosY();
PosXY(x,y);
    archivo[0].ListarJugador(soloActivos);
    x=PosX()+4;
    y=PosY()+2;
PosXY(x,y);
TextAnimation("Desea hacer una copia de seguridad? (1:Si, 0:No): ");
    cin>>eleccion;
    if(eleccion!=1){ return false; }
    int cant=archivo[0].ContarJugadores();
    Jugadores jugador;
    if(soloActivos){
        archivo[1].BorrarDatos();
        for(int i=0;i<=cant;i++){
            jugador=archivo[0].getRegistro(i+1);
            if(jugador.getEstado()){
                archivo[1].AgregarJugador(jugador);
            }
        }
    }
    else{
        system("copy Jugadores.dat Jugadores.bkp");
    }
    cout<<"\n\t\tCopia exitosa!\n";
    Pausa();
    return true;
}
bool copiarDeportes(){
    DeportesArchivo archivo[2]{"deportes.dat","deportes.bkp"};
    system("cls");
ConsoleTitle("GUARDAR DATOS DE DEPORTES");
int x=30;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("COPIA DE SEGURIDAD");
    x=4;
PosXY(x,y+6);
    int eleccion;
    bool soloActivos=true;
TextAnimation("Desea copiar tambien los elementos inactivos? (1:Si, 0:No): ");
    cin>>eleccion;
    if(eleccion==1){ soloActivos=false; }
    y=PosY();
PosXY(x,y);
    archivo[0].ListarDeporte(soloActivos);
    x=PosX()+4;
    y=PosY()+2;
PosXY(x,y);
TextAnimation("Desea hacer una copia de seguridad? (1:Si, 0:No): ");
    cin>>eleccion;
    if(eleccion!=1){ return false; }
    int cant=archivo[0].ContarDeportes();
    Deportes deporte;
    if(soloActivos){
        archivo[1].BorrarDatos();
        for(int i=0;i<=cant;i++){
            deporte=archivo[0].getRegistro(i+1);
            if(deporte.getEstado()){
                archivo[1].AgregarDeporte(deporte);
            }
        }
    }
    else{
        system("copy deportes.dat deportes.bkp");
    }
    cout<<"\n\t\tCopia exitosa!\n";
    Pausa();
    return true;
}
bool RestaurarJugadores(){
    JugadoresArchivo archivo[2]{"Jugadores.dat","Jugadores.bkp"};
    system("cls");
ConsoleTitle("RESTAURAR DATOS DE JUGADORES");
int x=20;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("COPIA DE SEGURIDAD (Jugadores.bkp)");
    x=4;
PosXY(x,y+6);
    int eleccion;
    bool soloActivos=true;
TextAnimation("Desea restaurar tambien los elementos inactivos si los hay? (1:Si, 0:No): ");
    cin>>eleccion;
    if(eleccion==1){ soloActivos=false; }
    y=PosY();
PosXY(x,y);
    archivo[1].ListarJugador(soloActivos);
    x=PosX()+4;
    y=PosY()+2;
PosXY(x,y);
TextAnimation("Desea restaurar los elementos? (1:Si, 0:No): ");
    cin>>eleccion;
    if(eleccion!=1){ return false; }
    int cant=archivo[1].ContarJugadores();
    Jugadores jugador;
    if(soloActivos){
        archivo[0].BorrarDatos();
        for(int i=0;i<=cant;i++){
            jugador=archivo[1].getRegistro(i+1);
            if(jugador.getEstado()){
                archivo[0].AgregarJugador(jugador);
            }
        }
    }
    else{
        system("copy Jugadores.bkp Jugadores.dat");
    }
    cout<<"\n\t\tCopia exitosa!\n";
    Pausa();
    return true;
}
bool RestaurarDeportes(){
    DeportesArchivo archivo[2]{"deportes.dat","deportes.bkp"};
    system("cls");
ConsoleTitle("RESTAURAR DATOS DE DEPORTES");
int x=30;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("COPIA DE SEGURIDAD (deportes.bkp)");
    x=4;
PosXY(x,y+6);
    int eleccion;
    bool soloActivos=true;
TextAnimation("Desea restaurar tambien los elementos inactivos si los hay? (1:Si, 0:No): ");
    cin>>eleccion;
    if(eleccion==1){ soloActivos=false; }
    y=PosY();
PosXY(x,y);
    archivo[1].ListarDeporte(soloActivos);
    x=PosX()+4;
    y=PosY()+2;
PosXY(x,y);
TextAnimation("Desea restaurar los elementos? (1:Si, 0:No): ");
    cin>>eleccion;
    if(eleccion!=1){ return false; }
    int cant=archivo[1].ContarDeportes();
    Deportes deporte;
    if(soloActivos){
        archivo[0].BorrarDatos();
        for(int i=0;i<=cant;i++){
            deporte=archivo[1].getRegistro(i+1);
            if(deporte.getEstado()){
                archivo[0].AgregarDeporte(deporte);
            }
        }
    }
    else{
        system("copy deportes.bkp deportes.dat");
    }
    cout<<"\n\t\tCopia exitosa!\n";
    Pausa();
    return true;
}
bool DatosInicio(){
    system("cls");
ConsoleTitle("ESTABLECER DATOS DE INICIO");
int x=10;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("DATOS DE \"deportesInicio.dat\" - \"JugadoresInicio.dat\"");
    x=4;
PosXY(x,y+6);
    int eleccion;
TextAnimation("Desea establecer los datos por defecto? (1:Si, 0:No): ");
    cin>>eleccion;
    if(eleccion!=1){ return false; }
    system("copy deportesInicio.dat deportes.dat");
    system("copy JugadoresInicio.dat Jugadores.dat");
    cout<<"\n\t\tCopia exitosa!\n";
    Pausa();
    return true;
}
#endif // MENUCONFIGURACION_H_INCLUDED

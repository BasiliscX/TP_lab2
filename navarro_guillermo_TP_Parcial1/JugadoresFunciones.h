#ifndef JUGADORESFUNCIONES_H_INCLUDED
#define JUGADORESFUNCIONES_H_INCLUDED
#include"Fecha.h"
#include"Jugadores.h"
#include"Deportes.h"

//Herramientas:
void animacionMenu(const char*);
void AnimacionesTituloCartel(const char*);
void Pausa();
//Funciones Menu:
void MenuJugadores();
bool AgregarJugador();
bool ListarJugadorDNI();
void ListarJugadores();
bool ModificarFechaInscripcion();
bool EliminarRegistroJugador();

void MenuJugadores(){
    int x,y, eleccion;
    bool menu=true;

    while(menu){
        system("cls");
        ConsoleTitle("MENU JUGADORES");
        BoxAnimation(3,ConsoleColumns()-1,ConsoleRows()-1,2);
        x=(ConsoleColumns()/4)-5;
        y=ConsoleRows()/2;
        PosXY(x,y);
        BoxAnimation(2,(ConsoleColumns()/2)+10,(y-10),2);
        x=(ConsoleColumns()/4);
        y=(ConsoleRows()/2)+2;
        PosXY(x,y++);
        TextAnimation("1) AGREGAR JUGADOR");
        PosXY(x,y++);
        TextAnimation("2) LISTAR JUGADOR POR DNI");
        PosXY(x,y++);
        TextAnimation("3) LISTAR TODOS LOS JUGADORES");
        PosXY(x,y++);
        TextAnimation("4) MODIFICAR FECHA DE INSCRIPCION");
        PosXY(x,y++);
        TextAnimation("5) ELIMINAR REGISTRO DE JUGADOR");
        PosXY(x,y++);
        TextAnimation("0) VOLVER AL MENU PRINCIPAL");
        PosXY(x+=4,y++);
        TextAnimation("Eleccion: ");
        cin>>eleccion;

        switch(eleccion){
            case 1 : AgregarJugador(); break;
            case 2 : ListarJugadorDNI(); break;
            case 3 : ListarJugadores(); break;
            case 4 : ModificarFechaInscripcion(); break;
            case 5 : EliminarRegistroJugador(); break;
            default: menu=false; break;
        }
    }
}

/************** Herramientas **************/
void animacionMenu(const char*titulo){
    system("cls");
    ConsoleTitle(titulo);
    BoxAnimation(3,ConsoleColumns()-1,ConsoleRows()-1,2);
    int x=10;
    int y=10;
    PosXY(x,y);
}
void AnimacionesTituloCartel(const char*titulo){
    int t=strlen(titulo);
BoxAnimation(2,(t+3),2,5);
t+=2;
int x=(PosX()-t);
int y=(PosY()-1);
PosXY(x,y);
TextAnimation(titulo);
}
void Pausa(){
    PosXY(PosX()+4,PosY()+1);
    system("pause");
}

/************** Funciones Menu **************/
bool AgregarJugador(){
    int dni;
animacionMenu("AGREGAR JUGADOR");
    Jugadores jugador;
    JugadoresArchivo archivo("Jugadores.dat");
    DeportesArchivo archivoD("deportes.dat");
    int x=PosX();
    int y=PosY()-3;
    PosXY(x,y);
    cout<<"\n\tDNI: ";
    cin>>dni;
    if(archivo.getJugadorDNI(dni)>=0){
        cout<<"\n\tDNI EXISTENTE\n";
        Pausa();
        return false;
    }
    int vD[10]={0};
    for(int i=0;i<10;i++){
        vD[i]=archivoD.getNumeroID(i);
    }
    if(!jugador.Cargar(dni,vD,10)){ return false; }
    int eleccion;
    cout<<"\n\t\tLos datos ingresados son correctos? (1:Si, 0:No): ";
    cin>>eleccion;
    if(eleccion!=1){ return false; }
animacionMenu("AGREGAR JUGADOR");
    if(archivo.AgregarJugador(jugador)){
        cout<<"\n\tAGREGADO EXITOSAMENTE!\n";
    }
    else{
        cout<<"\n\tHUBO UN PROBLEMA DE ARCHIVO\n";
        Pausa();
        return false;
    }
    jugador.Mostrar();
    Pausa();
    return true;
}
bool ListarJugadorDNI(){
    animacionMenu("LISTAR JUGADOR POR DNI");
int x=30;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("Jugador por DNI");
PosXY(x,y+3);
    JugadoresArchivo archivo("Jugadores.dat");
    int dni;
    cout<<"\n\tDNI: ";
    cin>>dni;
    int pos=archivo.getJugadorDNI(dni);
    if(pos==-1){
        cout<<"\n\tERROR DE ARCHIVO\n";
        Pausa();
        return false;
    }
    if(pos==-2){
        cout<<"\n\tDNI INCORRECTO\n";
        Pausa();
        return false;
    }
    Jugadores jugador=archivo.getRegistro(pos+1);
    if(!jugador.getEstado()){
        cout<<"\n\t\tESTADO INACTIVO!\n";
        Pausa();
        return false;
    }
    jugador.Mostrar();
    Pausa();
    return true;
}
void ListarJugadores(){
    JugadoresArchivo archivo("Jugadores.dat");
    system("cls");
ConsoleTitle("LISTA DE JUGADORES");
int x=30;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("JUGADORES");
PosXY(x,y+3);
    archivo.ListarJugador();
    Pausa();
}
bool ModificarFechaInscripcion(){
    JugadoresArchivo archivo("Jugadores.dat");
    Jugadores jugador;
    int cant=archivo.ContarJugadores();
    system("cls");
ConsoleTitle("MODIFICAR FECHA DE INSCRIPCION");
int x=30;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("INDICE DE JUGADORES");
PosXY(x,y+3);
    for(int i=0;i<cant;i++){
        jugador=archivo.getRegistro(i+1);
        if(jugador.getEstado()){
            cout<<"\n\tDNI: "<<jugador.getDNI();
            cout<<"\n\tNombre: "<<jugador.getNombre();
            cout<<"\n\tApellido: "<<jugador.getApellido();
            cout<<"\n\tFecha de inscripcion";
            jugador.MostrarFechaInscripcion();
            cout<<endl;
        }
    }
    int dni;
    bool ingreso=true;
    while(ingreso){
        cout<<"\n\tIngrese el DNI de jugador a modificar (0 para salir): ";
        cin>>dni;
        if(dni==0){ return true; }
        if(dni<1 || archivo.getJugadorDNI(dni)<0){
            cout<<"\n\t\tDNI INCORRECTO, INTENTE NUEVAMENTE:\n";
        }
        else{ ingreso=false; }
    }
    int pos=archivo.getJugadorDNI(dni)+1;
    jugador=archivo.getRegistro(pos);
    if(!jugador.getEstado()){
        cout<<"\n\t\tESTADO INACTIVO!\n";
        Pausa();
        return false;
    }
    cout<<"\n\tDNI: "<<jugador.getDNI();
    cout<<"\n\tNombre: "<<jugador.getNombre();
    cout<<"\n\tApellido: "<<jugador.getApellido();
    cout<<"\n\tFecha de inscripcion";
    jugador.MostrarFechaInscripcion();
    int eleccion;
    cout<<"\n\t\tEl registro es correcto? (1-Si, 0-No): ";
    cin>>eleccion;
    ((eleccion==1)?ingreso=true:ingreso=false);
    if(ingreso){
        cout<<"\n\t\tNueva fecha de inscripcion\n";
        jugador.CargarFechaInscripcion();
        if(archivo.ModificarJugador(pos,jugador)){
            cout<<"\n\t\tModificacion exitosa!\n";
            jugador.Mostrar();
            Pausa();
        }
        else{
            cout<<"\n\t\tERROR DE ARCHIVO\n";
            Pausa();
        }
    }
    else{ return false; }
    return true;
}
bool EliminarRegistroJugador(){
    JugadoresArchivo archivo("Jugadores.dat");
    Jugadores jugador;
    int cant=archivo.ContarJugadores();
    system("cls");
ConsoleTitle("ELIMINAR REGISTRO DE UN JUGADOR");
int x=30;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("INDICE DE JUGADORES ACTIVOS");
PosXY(x,y+3);
    for(int i=0;i<cant;i++){
        jugador=archivo.getRegistro(i+1);
        if(jugador.getEstado()){
            jugador.Mostrar();
            cout<<endl;
        }
    }
    int dni;
    bool ingreso=true;
    while(ingreso){
        cout<<"\n\tIngrese el numero de DNI a inactivar (0 para salir): ";
        cin>>dni;
        if(dni==0){ return true; }
        if(dni<1 || archivo.getJugadorDNI(dni)<0){
            cout<<"\n\t\tNUMERO INCORRECTO, INTENTE NUEVAMENTE:\n";
        }
        else{ ingreso=false; }
    }
    int pos=archivo.getJugadorDNI(dni)+1;
    jugador=archivo.getRegistro(pos);
    if(!jugador.getEstado()){
        cout<<"\n\t\tACTUALMENTE INACTIVO!\n";
        Pausa();
        return false;
    }
    jugador.Mostrar();
    cout<<"\n\tESTADO: "<<((jugador.getEstado())?"Activo":"Inactivo")<<endl;
    if(!jugador.getEstado()){
        cout<<"\n\t\tSalir\n";
        Pausa();
    }
    int eleccion;
    cout<<"\n\t\tEl registro es correcto? (1-Si, 0-No): ";
    cin>>eleccion;
    ((eleccion==1)?ingreso=true:ingreso=false);
    if(ingreso){
        jugador.setEstado(false);
        if(archivo.ModificarJugador(pos,jugador)){
            cout<<"\n\t\tModificacion exitosa!\n";
            jugador.Mostrar();
            cout<<"\n\tESTADO: "<<((jugador.getEstado())?"Activo":"Inactivo")<<endl;
            Pausa();
        }
        else{
            cout<<"\n\t\tERROR DE ARCHIVO\n";
            Pausa();
            return false;
        }
    }
    else{ return false; }
    return true;
}


#endif // JUGADORESFUNCIONES_H_INCLUDED

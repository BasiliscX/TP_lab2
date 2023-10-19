#ifndef DEPORTESFUNCIONES_H_INCLUDED
#define DEPORTESFUNCIONES_H_INCLUDED

void MenuDeportes();
bool AgregarDeporte();
bool ListarDeporteID();
void ListarDeportes();
bool ModificarAnioOrigen();
bool EliminarRegistroDeportes();

void MenuDeportes(){
    int x,y, eleccion;
    bool menu=true;

    while(menu){
        system("cls");
        ConsoleTitle("MENU DEPORTES");
        BoxAnimation(3,ConsoleColumns()-1,ConsoleRows()-1,2);
        x=(ConsoleColumns()/4)-5;
        y=ConsoleRows()/2;
        PosXY(x,y);
        BoxAnimation(2,(ConsoleColumns()/2)+10,(y-10),2);
        x=(ConsoleColumns()/4);
        y=(ConsoleRows()/2)+2;
        PosXY(x,y++);
        TextAnimation("1) AGREGAR DEPORTE");
        PosXY(x,y++);
        TextAnimation("2) LISTAR DEPORTE POR ID");
        PosXY(x,y++);
        TextAnimation("3) LISTAR TODO");
        PosXY(x,y++);
        TextAnimation("4) MODIFICAR AÑO DE ORIGEN");
        PosXY(x,y++);
        TextAnimation("5) ELIMINAR REGISTRO");
        PosXY(x,y++);
        TextAnimation("0) VOLVER AL MENU PRINCIPAL");
        PosXY(x+=4,y++);
        TextAnimation("Eleccion: ");
        cin>>eleccion;

        switch(eleccion){
            case 1 : AgregarDeporte(); break;
            case 2 : ListarDeporteID(); break;
            case 3 : ListarDeportes(); break;
            case 4 : ModificarAnioOrigen(); break;
            case 5 : EliminarRegistroDeportes(); break;
            default: menu=false; break;
        }
    }
}
/************** Funciones Menu **************/
bool AgregarDeporte(){
animacionMenu("AGREGAR DEPORTE");
    Deportes deporte;
    DeportesArchivo archivo("deportes.dat");
    int x=PosX();
    int y=PosY()-3;
    PosXY(x,y);
    if(!deporte.Cargar()){ return false; }
    int eleccion;
    cout<<"\n\t\tLos datos ingresados son correctos? (1:Si, 0:No): ";
    cin>>eleccion;
    if(eleccion!=1){
        return false;
    }
animacionMenu("AGREGAR DEPORTE");
    if(archivo.AgregarDeporte(deporte)){
        cout<<"\n\tAGREGADO EXITOSAMENTE!\n";
    }
    else{
        cout<<"\n\tHUBO UN PROBLEMA DE ARCHIVO\n";
        Pausa();
        return false;
    }
    deporte.Mostrar();
    Pausa();
    return true;
}
bool ListarDeporteID(){
    animacionMenu("LISTAR DEPORTE POR ID");
int x=30;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("Deporte por ID");
PosXY(x,y+3);
    DeportesArchivo archivo("deportes.dat");
    int id;
    cout<<"\n\tID: ";
    cin>>id;
    int indice=archivo.getDeporteID(id);
    if(indice==-1){
        cout<<"\n\tERROR DE ARCHIVO\n";
        Pausa();
        return false;
    }
    if(indice==-2){
        cout<<"\n\tID INCORRECTO\n";
        Pausa();
        return false;
    }
    Deportes deporte=archivo.getRegistro(indice+1);//Indice=posicion-1
    if(!deporte.getEstado()){
        cout<<"\n\t\tESTADO INACTIVO!\n";
        Pausa();
        return false;
    }
    deporte.Mostrar();
    Pausa();
    return true;
}
void ListarDeportes(){
    DeportesArchivo archivo("deportes.dat");
    system("cls");
ConsoleTitle("LISTA DE DEPORTES");
int x=30;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("DEPORTES");
PosXY(x,y+3);
    archivo.ListarDeporte();
    Pausa();
}
bool ModificarAnioOrigen(){
    system("cls");
    DeportesArchivo archivo("deportes.dat");
    int cant=archivo.ContarDeportes();
ConsoleTitle("MODIFICAR ANIO DE ORIGEN");
int x=30;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("INDICE DE DEPORTES");
PosXY(x,y+3);
    for(int i=0;i<=cant;i++){
        Deportes deporte=archivo.getRegistro(i+1);
        if(deporte.getEstado()){
            cout<<"\n ID "<<deporte.getIdDeporte();
            cout<<"\n\tNombre: "<<deporte.getNombre();
            cout<<"\n\tAnio de origen: "<<deporte.getAnioOrigen();
            cout<<endl;
        }
    }
    int id;
    bool ingreso=true;
    while(ingreso){
        cout<<"\n\tIngrese el numero de ID a modificar (0 para salir): ";
        cin>>id;
        if(id==0){ return true; }
        if(id<1 || id>(cant)){
            cout<<"\n\t\tID INCORRECTO, INTENTE NUEVAMENTE:\n";
        }
        else{ ingreso=false; }
    }
    int indice=archivo.getDeporteID(id);
    Deportes deporte=archivo.getRegistro(indice+1);
    if(!deporte.getEstado()){
        cout<<"\n\t\tESTADO INACTIVO!\n";
        Pausa();
        return false;
    }
    cout<<"\n\tID: "<<deporte.getIdDeporte();
    cout<<"\n\tNombre: "<<deporte.getNombre();
    cout<<"\n\tAnio de origen: "<<deporte.getAnioOrigen();
    int eleccion;
    cout<<"\n\t\tEl registro es correcto? (1-Si, 0-No): ";
    cin>>eleccion;
    ((eleccion==1)?ingreso=true:ingreso=false);
    if(ingreso){
        int anio;
        cout<<"\n\tNuevo anio de origen: ";
        cin>>anio;
        deporte.setAnioOrigen(anio);
        if(deporte.getAnioOrigen()==-1){
            cout<<"\n\t\tANIO INVALIDO!\n";
            Pausa();
            return false;
        }
        if(archivo.ModificarDeportes(indice+1,deporte)){
            cout<<"\n\t\tModificacion exitosa!\n";
            deporte.Mostrar();
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
bool EliminarRegistroDeportes(){
    DeportesArchivo archivo("deportes.dat");
    system("cls");
ConsoleTitle("ELIMINAR REGISTRO DE UN DEPORTE");
int x=25;
int y=2;
PosXY(x,y);
    AnimacionesTituloCartel("INDICE DE DEPORTES ACTIVOS");
PosXY(x,y+3);
    if(!archivo.ListarDeporte()){
        cout<<"\n\t\tERROR DE ARCHIVO\n";
        Pausa();
        return false;
    }
    int id;
    int cant=archivo.ContarDeportes();
    bool ingreso=true;
    while(ingreso){
        cout<<"\n\tIngrese el numero de ID a modificar (0 para salir): ";
        cin>>id;
        if(id==0){ return true; }
        if(id<1 || id>(cant+1)){
            cout<<"\n\t\tID INCORRECTO, INTENTE NUEVAMENTE:\n";
        }
        else{ ingreso=false; }
    }
    int indice=archivo.getDeporteID(id);
    Deportes deporte=archivo.getRegistro(indice+1);
    if(!deporte.getEstado()){
        cout<<"\n\t\tESTADO ACTUALMENTE INACTIVO!\n";
        Pausa();
        return false;
    }
    deporte.Mostrar();
    cout<<"\n\tESTADO: "<<((deporte.getEstado())?"Activo":"Inactivo")<<endl;
    if(!deporte.getEstado()){
        cout<<"\n\t\tSalir\n";
        Pausa();
    }
    int eleccion;
    cout<<"\n\t\tEl registro es correcto? (1-Si, 0-No): ";
    cin>>eleccion;
    ((eleccion==1)?ingreso=true:ingreso=false);
    if(ingreso){
        deporte.setEstado(false);
        if(archivo.ModificarDeportes(indice+1,deporte)){
            cout<<"\n\t\tModificacion exitosa!\n";
            deporte.Mostrar();
            cout<<"\n\tESTADO: "<<((deporte.getEstado())?"Activo":"Inactivo")<<endl;
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


#endif // DEPORTESFUNCIONES_H_INCLUDED

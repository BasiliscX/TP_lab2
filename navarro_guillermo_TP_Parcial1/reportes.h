#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED

/**
Generar un archivo con los docentes
que participan de deportes pertenecientes al tipo de deporte 5.
Cada registro del archivo nuevo debe tener el siguiente formato:

DNI, nombre, apellido y fecha de inscripción
*/
class Docentes{
private:
    int DNI;
    char Nombre[30];
    char Apellido[30];
    Fecha fechaInscripcion;
public:
    Docentes(int dni=9999999,const char*n="nombre",const char*ap="apellido",int d=1,int m=1,int a=2020){
        setDNI(dni);
        setNombre(n);
        setApellido(ap);
        fechaInscripcion.setDia(d);
        fechaInscripcion.setMes(m);
        fechaInscripcion.setAnio(a);
    }
    void setDNI(int d){ DNI=d; }
    void setNombre(const char*n){ strcpy(Nombre,n); }
    void setApellido(const char*a){ strcpy(Apellido,a); }
    void setFechaInscripcion(int d, int m, int a){
        fechaInscripcion.setDia(d);
        fechaInscripcion.setMes(m);
        fechaInscripcion.setAnio(a);
    }
    int getDNI(){ return DNI; }
    const char*getNombre(){ return Nombre; }
    const char*getApellido(){ return Apellido; }
};
class DocentesArchivo{
private:
    char nombre[30];
public:
    DocentesArchivo(const char*n){ strcpy(nombre,n); }
bool AgregarDocente(Docentes reg,const char*modo="ab"){
    FILE*p=fopen(nombre,modo);
    if(p==NULL){ return false; }
    fwrite(&reg,sizeof(Docentes),1,p);
    fclose(p);
    return true;
}
};
/**
Informar el/los deporte/s
con menos de 15 de jugadores inscriptos ESTE AÑO

EQUIPO
6=1 2023
8=1 2023
*/

bool Reportes(){
    system("cls");
    cout<<"\n\t\tDEPORTES CON MENOS DE 15 INSCRIPTOS\n";
    time_t t=time(nullptr);
    tm*f=localtime(&t);
    int aAct=f->tm_year+1900;
    Deportes deporte;
    Jugadores jugador;
    DeportesArchivo archivo("deportes.dat");
    JugadoresArchivo archivoJ("Jugadores.dat");
    int cant=archivoJ.ContarJugadores();
    int vD[10]={0};
    for(int i=0;i<cant;i++){
        jugador=archivoJ.getRegistro(i+1);
        if(jugador.getAnioInscripcion()==aAct){
            for(int j=0;j<10;j++){
                if(jugador.getdeporte()==j+1){//deportes e/1~10
                    vD[j]++;
                }
            }
        }
    }
    bool menosDeQuince=true;
    cout<<"\n\tLOS DEPORTES SON: ";
    for(int i=0;i<10;i++){
        if(vD[i]>=15){ menosDeQuince=false; }
    }
    if(menosDeQuince){
        for(int i=0;i<10;i++){
            if(vD[i]!=0){
                cout<<"\n\t\tNumero: "<<i+1;
            }
        }
    }

    int cont=0;
    Docentes docente;
    DocentesArchivo archivoD("docentesDeporte5.dat");
    int cantidad=archivoJ.ContarJugadores();
    for(int i=0;i<cantidad;i++){
        jugador=archivoJ.getRegistro(i+1);
        if(jugador.getClaustro()==1){
            if(jugador.getdeporte()==5){
                docente.setDNI(jugador.getDNI());
                docente.setNombre(jugador.getNombre());
                docente.setApellido(jugador.getApellido());
                int d=jugador.getDiaInscripcion();
                int m=jugador.getMesInscripcion();
                int a=jugador.getAnioInscripcion();
                docente.setFechaInscripcion(d,m,a);
                archivoD.AgregarDocente(docente);
                cont++;
            }
        }
    }
    cout<<"\n\n\t\tSE AGREGARON "<<cont<<" DOCENTES AL ARCHIVO CON DEPORTE NUMERO 5.\n";
    Pausa();
    return true;
}


#endif // REPORTES_H_INCLUDED

#ifndef JUGADORES_H_INCLUDED
#define JUGADORES_H_INCLUDED

class Jugadores{
private:
    int DNI;
    char Nombre[30];
    char Apellido[30];
    char Email[30];
    char Telefono[30];
    int Claustro;
    int Deporte;
    int NumeroEquipo;
    Fecha FechaInscripcion;
    float Matricula;
    bool Estado;
public:
    Jugadores(int, const char*, const char*, const char*, const char*,
              int, int, int, int, int, int, float, bool);
    bool Cargar(int,int*,int);
    void Mostrar();
    void CargarFechaInscripcion();
    void MostrarFechaInscripcion();
    void setDNI(int d){ DNI=d; }
    void setNombre(const char*n){ strcpy(Nombre,n); }
    void setApellido(const char*a){ strcpy(Apellido,a); }
    void setEmail(const char*e){ strcpy(Email,e); }
    void setTelefono(const char*t){ strcpy(Telefono,t); }
    void setClaustro(int c){
        if(c>0 && c<5){ Claustro=c; }
        else{ Claustro=1; }
    }
    void setDeporte(int d){
        if(d>0 && d<11){ Deporte=d; }
        else{ Deporte=-1; }
    }
    void setNumeroEquipo(int n){ NumeroEquipo=n; }
    void setDiaInscripcion(int d){ FechaInscripcion.setDia(d); }
    void setMesInscripcion(int m){ FechaInscripcion.setMes(m); }
    void setAnioInscripcion(int a){ FechaInscripcion.setAnio(a); }
    void setMatricula(float m){
        if(m>=0){ Matricula=m; }
        else{ Matricula=0; }
    }
    void setEstado(bool e){ Estado=e; }
    int getDNI(){ return DNI; }
    const char*getNombre(){ return Nombre; }
    const char*getApellido(){ return Apellido; }
    const char*getEmail(){ return Email; }
    const char*getTelefono(){ return Telefono; }
    int getClaustro(){ return Claustro; }
    int getdeporte(){ return Deporte; }
    int getNumeroEquipo(){ return NumeroEquipo; }
    int getDiaInscripcion(){ return FechaInscripcion.getDia(); }
    int getMesInscripcion(){ return FechaInscripcion.getMes(); }
    int getAnioInscripcion(){ return FechaInscripcion.getAnio(); }
    float getMatricula(){ return Matricula; }
    bool getEstado(){ return Estado; }
};
Jugadores::Jugadores(int DNI=0, const char*Nombre="-", const char*Apellido="-", const char*Email="-", const char*Telefono="-", int Claustro=1, int Deporte=1, int NumeroEquipo=1, int dia=1, int mes=1, int anio=2023, float Matricula=0, bool Estado=false){
    setDNI(DNI);
    setNombre(Nombre);
    setApellido(Apellido);
    setEmail(Email);
    setTelefono(Telefono);
    setClaustro(Claustro);
    setDeporte(Deporte);
    setNumeroEquipo(NumeroEquipo);
    FechaInscripcion.setDia(dia);
    FechaInscripcion.setMes(mes);
    FechaInscripcion.setAnio(anio);
    setMatricula(Matricula);
    setEstado(Estado);
}
bool Jugadores::Cargar(int dni=-1, int vD[]={0},int t=10){
    int cl,de,ne, esInt;
    bool es=false;
    char no[30],ap[30],em[30],te[30];
    float ma;
    if(dni==-1){
        cout<<"\n\tDNI: ";
        cin>>dni;
    }
    cout<<"\n\tNombre: ";
    cin>>no;
    cout<<"\n\tApellido: ";
    cin>>ap;
    cout<<"\n\tEmail: ";
    cin>>em;
    cout<<"\n\tTelefono: ";
    cin>>te;
    cout<<"\n\tClaustro (1: docente; 2 alumno; no docente; 4 graduado): ";
    cin>>cl;
    if(cl<1 || cl>4){
        cout<<"\n\t\tCLAUSTRO INCORRECTO, INTENTAR NUEVAMENTE.\n";
        system("pause");
        return false;
    }
    cout<<"\n\tDeporte (numero entre 1 y 10)";
    cout<<"\n\t - disponibles: ";
    for(int i=0;i<t;i++){ if(vD[i]>0) cout<<"| "<<vD[i]<<" "; }
    cout<<"|\n\t\tEleccion: ";
    cin>>de;
    if(de<1 || de>10){
        cout<<"\n\t\tDEPORTE INCORRECTO, INTENTAR NUEVAMENTE.\n";
        system("pause");
        return false;
    }
    bool activo=false;
    for(int i=0;i<t;i++){
        if(de==vD[i]){
            setDeporte(de);
            activo=true;
        }
    }
    if(!activo){
        cout<<"\n\t\tDEPORTE INACTIVO, INTENTAR NUEVAMENTE.\n";
        system("pause");
        return false;
    }
    cout<<"\n\tNumero de equipo: ";
    cin>>ne;
    cout<<"\n\tFecha de inscripcion";
    FechaInscripcion.Cargar();
    cout<<"\n\tMatricula: ";
    cin>>ma;
    cout<<"\n\tEstado (0:Inactivo, 1:Activo): ";
    cin>>esInt;
    if(esInt>0){ es=true; }

    setDNI(dni);
    setNombre(no);
    setApellido(ap);
    setEmail(em);
    setTelefono(te);
    setClaustro(cl);
    setNumeroEquipo(ne);
    setMatricula(ma);
    setEstado(es);
    return true;
}
void Jugadores::Mostrar(){
    cout<<"\n\tDNI: "<<getDNI();
    cout<<"\n\tNombre: "<<getNombre();
    cout<<"\n\tApellido: "<<getApellido();
    cout<<"\n\tEmail: "<<getEmail();
    cout<<"\n\tTelefono: "<<getTelefono();
    cout<<"\n\tClaustro (1: docente; 2 alumno; 3 no docente; 4 graduado): "<<getClaustro();
    cout<<"\n\tDeporte (numero entre 1 y 10): "<<getdeporte();
    cout<<"\n\tNumero de equipo: "<<getNumeroEquipo();
    cout<<"\n\tFecha de inscripcion";
    FechaInscripcion.Mostrar();
    cout<<"\n\tMatricula: "<<getMatricula();
}
void Jugadores::CargarFechaInscripcion(){
    FechaInscripcion.Cargar();
}
void Jugadores::MostrarFechaInscripcion(){
    cout<<"\n\tDia: "<<getDiaInscripcion();
    cout<<"\n\tMes: "<<getMesInscripcion();
    cout<<"\n\tAnio: "<<getAnioInscripcion();
}
/****************** ARCHIVO ******************/
class JugadoresArchivo{
private:
    char nombre[30];
public:
    JugadoresArchivo(const char*n){ strcpy(nombre,n); }
    bool BorrarDatos();
    bool AgregarJugador(Jugadores,const char*);
    bool ListarJugador(bool);
    int getJugadorDNI(int);
    Jugadores getRegistro(int);
    int ContarJugadores(bool);
    bool ModificarJugador(int,Jugadores);
};
bool JugadoresArchivo::AgregarJugador(Jugadores reg,const char*modo="ab"){
    FILE*p=fopen(nombre,modo);
    if(p==NULL){ return false; }
    fwrite(&reg,sizeof(Jugadores),1,p);
    fclose(p);
    return true;
}
bool JugadoresArchivo::BorrarDatos(){
    FILE*p=fopen(nombre,"wb");
    if(p==NULL){ return false; }
    fclose(p);
    return true;
}
bool JugadoresArchivo::ListarJugador(bool soloActivos=true){
    Jugadores reg;
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return false; }
    while(fread(&reg,sizeof(Jugadores),1,p)){
        if(soloActivos){
            if(reg.getEstado()){
                reg.Mostrar();
                cout<<endl;
            }
        }
        else{
            reg.Mostrar();
            cout<<"\n\tESTADO: "<<((reg.getEstado())?"Activo":"Inactivo")<<endl;
            cout<<endl;
        }
    }
    fclose(p);
    return true;
}
int JugadoresArchivo::getJugadorDNI(int dni){
    int cont=0;
    Jugadores reg;
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return -1; }
    while(fread(&reg,sizeof(Jugadores),1,p)){
        if(reg.getDNI()==dni){
            fclose(p);
            return cont;
        }
        cont++;
    }
    fclose(p);
    return -2;
}
Jugadores JugadoresArchivo::getRegistro(int pos){
    Jugadores reg;
    pos--;
    reg.setDNI(-1);
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return reg; }
    fseek(p,sizeof(Jugadores)*pos,0);
    fread(&reg,sizeof(Jugadores),1,p);
    fclose(p);
    return reg;
}
int JugadoresArchivo::ContarJugadores(bool soloActivos=true){
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return -1; }
    if(soloActivos){
        Jugadores reg;
        int cont=0;
        while(fread(&reg,sizeof(Jugadores),1,p)){
            if(reg.getEstado()){ cont++; }
        }
        fclose(p);
        return cont;
    }
    fseek(p,0,2);//ultima posicion
    int cantBytes=ftell(p);//tamaño desde 0 a posicion
    fclose(p);
    return cantBytes/sizeof(Jugadores);
}
bool JugadoresArchivo::ModificarJugador(int pos,Jugadores reg){
    FILE*p=fopen(nombre,"rb+");
    if(p==NULL){ return false; }
    pos--;
    fseek(p,sizeof(Jugadores)*pos,0);
    fwrite(&reg,sizeof(Jugadores),1,p);
    fclose(p);
    return true;
}

#endif // JUGADORES_H_INCLUDED

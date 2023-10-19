#ifndef DEPORTES_H_INCLUDED
#define DEPORTES_H_INCLUDED

class Deportes{
private:
    static int contador;
    time_t t=time(nullptr);
    int idDeporte;
    char nombre[30];
    int tipoDeporte;
    int anioOrigen;
    bool estado;
public:
    Deportes(const char*,int,int,bool);
    bool Cargar();
    void Mostrar();
    void setNombre(const char*n){ strcpy(nombre,n); }
    void setTipoDeporte(int td){
        if(td>=1 && td<=21){ tipoDeporte=td; }
        else{ tipoDeporte=-1; }
    }
    void setAnioOrigen(int a){
        tm*f=localtime(&t);
        int aAct=f->tm_year+1900;
        if(a>=1800 && a<=aAct){ anioOrigen=a; }
        else{ anioOrigen=-1; }
    }
    void setEstado(bool e){ estado=e; }
    int getIdDeporte(){ return idDeporte; }
    const char*getNombre(){ return nombre; }
    int getTipoDeporte(){ return tipoDeporte; }
    int getAnioOrigen(){ return anioOrigen; }
    bool getEstado(){ return estado; }
};
int Deportes::contador=0;
Deportes::Deportes(const char*n="deporte",int td=1,int a=1800,bool e=false){
    setNombre(n);
    setTipoDeporte(td);
    setAnioOrigen(a);
    setEstado(e);
}
bool Deportes::Cargar(){
    char n[30];
    int td,a,est;
    bool e=false;
    cout<<"\n\tNombre: ";
    cin>>n;
    cout<<"\n\tTipo de deporte (1~21): ";
    cin>>td;
    setTipoDeporte(td);
    if(tipoDeporte==-1){
        cout<<"\n\t\tDATO INCORRECTO, INTENTAR NUEVAMENTE.\n";
        system("pause");
        return false;
    }
    cout<<"\n\tAnio de origen: ";
    cin>>a;
    setAnioOrigen(a);
    if(anioOrigen==-1){
        cout<<"\n\t\tDATO INCORRECTO, INTENTAR NUEVAMENTE.\n";
        system("pause");
        return false;
    }
    cout<<"\n\tEstado (1: Activo - 0: Inactivo): ";
    cin>>est;
    if(est==1){ e=true; }
    setNombre(n);
    setEstado(e);
    contador++;
    idDeporte=contador;
    return true;
}
void Deportes::Mostrar(){
    cout<<"\n\tId Deporte: "<<getIdDeporte();
    cout<<"\n\tNombre: "<<getNombre();
    cout<<"\n\tTipo de deporte: "<<getTipoDeporte();
    cout<<"\n\tAnio de origen: "<<getAnioOrigen();
}
/****************** ARCHIVO ******************/
class DeportesArchivo{
private:
    char nombre[30];
public:
    DeportesArchivo(const char*n){ strcpy(nombre,n); }
    bool AgregarDeporte(Deportes,const char*);
    bool BorrarDatos();
    bool ListarDeporte(bool);
    int getDeporteID(int);
    Deportes getRegistro(int);
    int ContarDeportes(bool);
    bool ModificarDeportes(int,Deportes);
    int getNumeroID(int);
};
bool DeportesArchivo::AgregarDeporte(Deportes reg,const char*modo="ab"){
    FILE*p=fopen(nombre,modo);
    if(p==NULL){ return false; }
    fwrite(&reg,sizeof(Deportes),1,p);
    fclose(p);
    return true;
}
bool DeportesArchivo::BorrarDatos(){
    FILE*p=fopen(nombre,"wb");
    if(p==NULL){ return false; }
    fclose(p);
    return true;
}
bool DeportesArchivo::ListarDeporte(bool soloActivos=true){
    Deportes reg;
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return false; }
    while(fread(&reg,sizeof(Deportes),1,p)){
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
int DeportesArchivo::getDeporteID(int id){
    int cont=0;
    Deportes reg;
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return -1; }
    while(fread(&reg,sizeof(Deportes),1,p)){
        if(reg.getIdDeporte()==id){
            fclose(p);
            return cont;
        }
        cont++;
    }
    fclose(p);
    return -2;
}
Deportes DeportesArchivo::getRegistro(int pos){
    Deportes reg;
    pos--;//indice
    reg.setEstado(false);
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return reg; }
    fseek(p,sizeof(Deportes)*pos,0);
    fread(&reg,sizeof(Deportes),1,p);
    fclose(p);
    return reg;
}
int DeportesArchivo::ContarDeportes(bool soloActivos=true){
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return -1; }
        if(soloActivos){
        Deportes reg;
        int cont=0;
        while(fread(&reg,sizeof(Deportes),1,p)){
            if(reg.getEstado()){ cont++; }
        }
        fclose(p);
        return cont;
    }
    fseek(p,0,2);//ultima posicion
    int cantBytes=ftell(p);//tamaño desde 0 a posicion
    return cantBytes/sizeof(Deportes);
}
bool DeportesArchivo::ModificarDeportes(int pos,Deportes reg){
    FILE*p=fopen(nombre,"rb+");
    if(p==NULL){ return false; }
    pos--;//indice
    fseek(p,sizeof(Deportes)*pos,0);
    fwrite(&reg,sizeof(Deportes),1,p);
    fclose(p);
    return true;
}
int DeportesArchivo::getNumeroID(int indice){
    Deportes reg;
    FILE*p=fopen(nombre,"rb");
    if(p==NULL){ return -1; }
    fseek(p,sizeof(Deportes)*indice,0);
    fread(&reg,sizeof(Deportes),1,p);
    fclose(p);
    int id=0;
    if(reg.getEstado()){ id=reg.getIdDeporte(); }
    return id;
}
#endif // DEPORTES_H_INCLUDED

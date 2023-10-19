#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include<iostream>
#include<ctime>

class Fecha{
private:
    int _dia;
    int _mes;
    int _anio;
public:
    Fecha(int,int,int);
    void Cargar();
    void Mostrar();
    void setDia(int d){
        if(d>0 && d<32) { _dia=d; }
        else { _dia=-1; }
    }
    void setMes(int m){
        if(m>0 && m<13) { _mes=m; }
        else { _mes=-1; }
    }
    void setAnio(int a){
        if(a>1799 && a<9999) { _anio=a; }
        else { _anio=-1; }
    }
    int getDia() { return _dia; }
    int getMes() { return _mes; }
    int getAnio(){ return _anio; }
};

Fecha::Fecha(int d=1, int m=1, int a=1900){
    Fecha::setDia(d);
    Fecha::setMes(m);
    Fecha::setAnio(a);
}
void Fecha::Cargar(){
    time_t t=time(nullptr);
    tm*f=localtime(&t);
    int d,m,a;
    int dAct=f->tm_mday;
    int mAct=f->tm_mon+1;
    int aAct=f->tm_year+1900;
    bool cargar=true;
    while(cargar){
        std::cout<<"\n\tFecha actual:"<<dAct<<"/"<<mAct<<"/"<<aAct<<"\n";
        std::cout<<"\n\tDia: ";
        std::cin>>d;
        std::cout<<"\n\tMes: ";
        std::cin>>m;
        std::cout<<"\n\tAnio: ";
        std::cin>>a;

        if(a>=2000){
            if(a<aAct || (a==aAct && m<mAct) || (a==aAct && m==mAct && d<=dAct)){
                Fecha::setDia(d);
                Fecha::setMes(m);
                Fecha::setAnio(a);
                cargar=false;
            }
        }
        else{
            system("cls");
            std::cout<<"\n\t\tVALORES INCORRECTOS!\n";
        }
    }
}
void Fecha::Mostrar(){
    std::cout<<"\n\tDia: ";
    std::cout<<Fecha::getDia();
    std::cout<<"\n\tMes: ";
    std::cout<<Fecha::getMes();
    std::cout<<"\n\tAnio: ";
    std::cout<<Fecha::getAnio();
}

#endif // FECHA_H_INCLUDED

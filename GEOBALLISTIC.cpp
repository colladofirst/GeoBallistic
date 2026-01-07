/****-El modelo no representa sistemas balísticos reales ni aplicaciones prácticas-****/
/*
Proyecto: Distancia geodésica y modelo de proyectil idealizado
Descripción:
-Calcula distancias geodésicas entre 2 puntos de la Tierra usando la fórmula de Haversine
-Usa una idealización del modelo clásico para estimar velocidades, fuerzas y energias
-Únicamenente propositos educacionales y teoricos


Notes:
-Modelo físico ALTAMENTE simplificado
-No resistencia del aire, guiado o simulación balística real

*/

#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

#define M_PI 3.14159265358979323846

//Convierte grados a radianes
double GradtoRad(double grados)
{
    double rad=grados*M_PI/180.0;
    return rad;
}
//Calcula la distancia geodésica entre 2 puntos de la tierra usando Haversine
double Haversine(double lat1,double lon1,double lat2,double lon2)
{
    lat1=GradtoRad(lat1); lat2=GradtoRad(lat2);
    lon2=GradtoRad(lon2); lon1=GradtoRad(lon1);
    const double R=6371e3;
    double dLat=lat2-lat1;
    double dLon=lon2-lon1;

    double a=pow(sin(dLat/2),2) + cos(lat1)*cos(lat2)*pow(sin(dLon/2),2);
    return 2*R*asin(sqrt(a));
}
//Verifica que el formato de las coordenadas(x,y) es correcto
bool LectorCoords (double &lat, double &lon)
{
    char p1,p2,coma;
    cin>>p1>>lat>>coma>>lon>>p2;
    if( p1=='('&& p2== ')' && coma==',')
    {
        return true;
    }
    else{
        return false;
    }
}
struct velocidad2D {
 double vx,vy,v;
};
typedef struct velocidad2D Vel2D;
//Calcula la velocidad inicial asumiendo un movimiento ideal
Vel2D DescVelocidad (double t, double lat1, double lat2, double lon1, double lon2,double alpha)
{
    double dist=Haversine(lat1,lon1,lat2,lon2);
    Vel2D Velocidad;
    Velocidad.vx=dist/t;
    alpha=GradtoRad(alpha);
    Velocidad.v=Velocidad.vx/cos(alpha);
    Velocidad.vy=Velocidad.v*sin(alpha);
    return Velocidad;
}
//Clasifica la velocidad para diferentes marcos físicos (clásico, relativista, imposible)
int vPosible (Vel2D vf)
{
    int flag;
    if(vf.v>=3e8)
    {
        flag=0;
        return flag;
    }
    else if (vf.v>3e7&&vf.v<3e8)
    {
        flag=1;
        return flag;
    }
    else
    {
        flag=2;
        return flag;
    }
}
struct Fuerza2D {
 double F,Fx,Fy;
 };
 typedef struct Fuerza2D F2D;
 //Calcula la fuerza necesaria de lanzamiento asumiendo a=cte
F2D Farranque(double t, double m,Vel2D dv)
{
    F2D F0;
    F0.Fx=m*dv.vx/t;
    F0.Fy=m*dv.vy/t;
    F0.F=sqrt((F0.Fx*F0.Fx+F0.Fy*F0.Fy));
    return F0;
}
//Calcula la Em necesaria para el mov ideal
double Etotal (double m, double v, double h)
{
    double Ec=1.0/2*m*v*v;
    double Ep= m*9.81*h;
    return Ep+Ec;
}
int main ()
{
    //Input de coordenadas + verificación de formato con función
    double LatUser1, LatUser2, LonUser1, LonUser2, DistUser;
    cout << "Introduzca las coordenadas del punto partida(formato= (x1,y1) ): ";
    bool Lectura1=LectorCoords(LatUser1,LonUser1);
    while (Lectura1==false)
    {
        cout << "Coordenadas mal formateadas, introduzca de nuevo\n";
        Lectura1=LectorCoords(LatUser1,LonUser1);
    }
    cout << "Introduzca las coordenadas del punto de llegada (formato= (x2,y2) ): ";
    bool Lectura2=LectorCoords(LatUser2,LonUser2);
    while (Lectura2==false)
    {
        cout << "Coordenadas mal formateadas, introduzca de nuevo\n";
            Lectura2=LectorCoords(LatUser2,LonUser2);
    }
    DistUser=Haversine(LatUser1,LonUser1,LatUser2,LonUser2);
    cout <<"\n\nLa distancia entre P1 y P2 es = "<<DistUser<<"m | "<<DistUser/1000<<"km\n";
    //Input de tiempo y angulo + calculo de velocidades
    double t,alpha;
    cout << "\n\nIntroduzca el tiempo (s) en el que sucede el recorrido: "; cin >> t;
    cout << "Introduzca el angulo (grados) de inclinacion: "; cin >> alpha;
    Vel2D VelUser=DescVelocidad(t,LatUser1,LatUser2,LonUser1,LonUser2,alpha);
    //Verificacion de que velocidad esta en el marco Clásico de Newton
    int Relatividad=vPosible(VelUser);
     /**IMPOSIBILIDAD FÍSICA**/
     if (Relatividad==0)
     {
         cout << "Para el tiempo seleccionado se supera c, lo que es imposible en el marco fisico actual\n";
         return 0;
     }
     /**MARCO RELATIVISTA**/
     else if (Relatividad==1)
     {
         cout <<"Para el tiempo seleccionado v≈c, por tanto no se puede calcular bajo el marco clasico\n";
         return 0;
     }
     /**MARCO CLASICO IDEALIZADO**/
     else
     {
         //Inputs de m,h y t aplicacion+ calculo de F y Et
         cout <<"\n\n|v0|= "<<VelUser.v<<"m/s"
        <<"\nvx= "<<VelUser.vx<<"m/s"<<
        "\nvy= "<<VelUser.vy<<"m/s"<<
        "\n\nIntroduzca la masa (kg) del proyectil: ";
        double tApli,m,h;
        cin >> m;
        cout <<"Introduzca el tiempo(s) en el que se aplica la fuerza: ";
        cin >> tApli;
        F2D FUser=Farranque(tApli,m,VelUser);
        cout << "\n|F|= "<<FUser.F<<"N\n"
        <<"Fx= "<<FUser.Fx<<"N\n"
        <<"Fy= "<<FUser.Fy<<"N\n"
        <<"\nIntroduzca la altura h(m) con respescto al nivel del mar: ";
        cin >>h;

        double Et=Etotal(m,VelUser.v,h);
        cout << "La Energia necesaria para el comienzo del movimiento es, Em= "<<Et<<"J | "
        <<Et*2.390006e-13<<" Kilotons\n"<<"Ademas, la energia empleada cumple una relacion de: "
        <<(Et*2.390006e-13)/15<< "bombas de Hiroshima\n";

     }
}

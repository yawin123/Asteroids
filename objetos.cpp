#include "objetos.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "miniwin.h"
using namespace miniwin;

/////////////////////////////////////////////////////////////////////////
//OBJETO PIEZA
/////////////////////////////////////////////////////////////////////////

Pieza::Pieza(int x0=0,int y0=0,int ang=0,int p=0,int e=100,Coord v={0,0})
{
    orig.x=x0;
    orig.y=y0;
    angulo=float(ang);
    tam=p;
    perif=new Polar[tam];
    veloc=v;
    esc=e;
}

void Pieza::rota(int r)
{
    angulo+=float(r);
}
void Pieza::acelera()
{
    Polar aux=Polar(2,angulo/180*M_PI);
    veloc.x+=aux.ro*cos(aux.angle);
    veloc.y+=aux.ro*sin(aux.angle);
}
void Pieza::avanza()
{
    orig.x+=veloc.x;
    orig.y+=veloc.y;

    if(orig.x<0) {orig.x=ANCHO;}
    else if(orig.x>ANCHO) {orig.x=0;}

    if(orig.y<0) {orig.y=ALTO;}
    else if(orig.y>ALTO) {orig.y=0;}
}

void Pieza::pinta() const
{
    Polar aux[tam];
    for(int i=0;i<tam;i++)
    {
        aux[i].ro=perif[i].ro*(esc/100);
        aux[i].angle=(perif[i].angle+angulo)/180*M_PI;
    }

    float xy[tam][2];
    for(int i=0;i<tam;i++)
    {
        xy[i][0]=float(orig.x+aux[i].ro*cos(aux[i].angle));
        xy[i][1]=float(orig.y+aux[i].ro*sin(aux[i].angle));
    }

    if(tam>1)
    {
        for(int i=0;i<tam-1;i++)
        {
            linea(xy[i][0],xy[i][1],xy[i+1][0],xy[i+1][1]);
        }
        linea(xy[tam-1][0],xy[tam-1][1],xy[0][0],xy[0][1]);
    }
}
void Pieza::actualiza(){}

/////////////////////////////////////////////////////////////////////////
//END OBJETO PIEZA
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//OBJETO NAVE
/////////////////////////////////////////////////////////////////////////

Nave::Nave(int x0=0,int y0=0,int ang=0):Pieza(x0,y0,ang,4,100,Coord(0,0))
{
    periferico(0,Polar(20,225.00));
    periferico(1,Polar(32,0.00));
    periferico(2,Polar(20,135.00));
    periferico(3,Polar(5,180.00));
}

void Nave::actualiza()
{
    if(ha_chocado())
    {
        //Se muere

        ha_chocado(false);
    }

    avanza();
    pinta();
}

/////////////////////////////////////////////////////////////////////////
//END OBJETO NAVE
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//OBJETO ASTEROIDE
/////////////////////////////////////////////////////////////////////////
Asteroide::Asteroide():Pieza(-100,-100,0,9,2000,Coord(0,0))
{
    periferico(0,Polar(4,45.00));
    periferico(1,Polar(4,90.00));
    periferico(2,Polar(4,135.00));
    periferico(3,Polar(4,180.00));
    periferico(4,Polar(4,225.00));
    periferico(5,Polar(4,270.00));
    periferico(6,Polar(4,315.00));
    periferico(7,Polar(1,337));
    periferico(8,Polar(4,360.00));

    Coord c,p;
    c=Coord(rand()%ANCHO,rand()%ALTO);
    p=Coord((rand()%4)-2,(rand()%4)-2);
    coords(c);
    velocidad(p);

    r=rand()%2;
}

void Asteroide::actualiza(Pieza& p)
{
    if(colisiona(p))
    {
        ha_chocado(true);
        p.ha_chocado(true);
    }
}
void Asteroide::actualiza()
{
    if(ha_chocado())
    {
        //Se muere

    }

    rota(r>0?1:-1);
    avanza();
    pinta();
}

bool Asteroide::colisiona(Pieza& pieza)
{
    //Se calcula si el asteroide choca contra la nave
    Coord cast=coords();
    Coord cnav=pieza.coords();
    float dist=sqrt( ((cast.x-cnav.x)*(cast.x-cnav.x)) + ((cast.y-cnav.y)*(cast.y-cnav.y)) );

    if(dist<100.00)
    {
        return true;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////
//END OBJETO ASTEROIDE
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
//OBJETO LASER
/////////////////////////////////////////////////////////////////////////

Laser::Laser(Pieza& p):Pieza(0,0,0,2,300,Coord(0,0))
{
    periferico(0,Polar(1,0.00));
    periferico(1,Polar(1,180.00));

    Polar aux;
    Coord cAux;

    // Calculamos la posición del laser
        aux.ro=p.periferico(1).ro*(p.escala()/100);
        aux.angle=(p.periferico(1).angle+p.angle())/180*M_PI;

        cAux.x=p.x()+aux.ro*cos(aux.angle);
        cAux.y=p.y()+aux.ro*sin(aux.angle);

        coords(cAux);

    //Pasamos el ángulo del laser
        angle(p.angle());

    //Valculamos la velocidad del laser
        float ang=float(angle());
        aux.ro=15;
        aux.angle=(ang/180*M_PI);

        cAux.x=aux.ro*cos(aux.angle);
        cAux.y=aux.ro*sin(aux.angle);

        velocidad(cAux);
}

void Laser::actualiza()
{
    avanza();
    pinta();

    if(x()<0 || x()>ANCHO || y()<0 || y()>ANCHO) {ha_chocado(true);}
}

void Laser::avanza()
{
    x(x()+velocidad().x);
    y(y()+velocidad().y);
}

/////////////////////////////////////////////////////////////////////////
//END OBJETO LASER
/////////////////////////////////////////////////////////////////////////

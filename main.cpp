#include "miniwin.h"
#include <cstdlib>
#include <ctime>
#include <list>
#include "objetos.h"

using namespace miniwin;
using namespace std;




//Utilidades y globales
    list<Asteroide*> A;
    list<Asteroide*>::iterator Ait;
    list<Laser*> L;
    list<Laser*>::iterator Lit;

    void frame(Nave& nave)
    {
        borra();
        nave.actualiza();

        //Actualizamos los laseres
            Lit=L.begin();
            while(Lit!=L.end())
            {
                if((*Lit)->ha_chocado())
                {
                    delete(*Lit);
                    Lit=L.erase(Lit);
                }
                else
                {
                    Lit++;
                }
            }
            for(Lit=L.begin();Lit!=L.end();Lit++)
            {
                (*Lit)->actualiza();
            }

        //Actualizamos los asteroides
            Ait=A.begin();
            while(Ait!=A.end())
            {
                if((*Ait)->ha_chocado())
                {
                    delete (*Ait);
                    Ait=A.erase(Ait);
                }
                else
                {
                    Ait++;
                }
            }
            for(Ait=A.begin();Ait!=A.end();Ait++)
            {
                (*Ait)->actualiza(nave);

                /*for(Lit=L.begin();Lit!=L.end();Lit++)
                {
                   (*Ait)->actualiza((*Lit));
                }*/
                (*Ait)->actualiza();
            }

        refresca();
    }
//End utilidades y globales

int main()
{
    srand(time(0)); //Ponemos la semilla

    vredimensiona(ANCHO, ALTO);
    Nave nave(ANCHO/2,ALTO/2,270);

    for(int i=0;i<5;i++)
    {
        A.push_back(new Asteroide());
    }

    frame(nave);

    int t;
    do
    {
        switch(t)
        {
            case IZQUIERDA:
                nave.rota(-10);
                break;
            case DERECHA:
                nave.rota(10);
                break;
            case ARRIBA:
                nave.acelera();
                break;
            case ESPACIO:
                L.push_back(new Laser(nave));
                break;
        }

        frame(nave);

        espera(30);
        t=tecla();
    }while(t!=ESCAPE);

    refresca();
    vcierra();
    return 0;
}

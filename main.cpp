#include "miniwin.h"
#include <cstdlib>
#include <ctime>
#include <list>
#include "objetos.h"

using namespace miniwin;
using namespace std;


class Juego
{
    Nave nave;
    list<Asteroide*> A;
    list<Asteroide*>::iterator Ait;
    list<Laser*> L;
    list<Laser*>::iterator Lit;

    public:
        Juego():nave(ANCHO/2,ALTO/2,270)
        {
            srand(time(0)); //Ponemos la semilla
            vredimensiona(ANCHO, ALTO);

            for(int i=0;i<5;i++)
            {
                A.push_back(new Asteroide());
            }
        }

        void cuerpo(int& t)
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
        }

        void frame()
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
};

int main()
{
    int t;
    Juego *asteroids=new Juego();
    asteroids->frame();

   do
   {
        t=tecla();
        asteroids->cuerpo(t);
        asteroids->frame();

        espera(30);
    }while(t!=ESCAPE);

    refresca();
    vcierra();
    return 0;
}

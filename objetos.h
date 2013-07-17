#ifndef OBJETOS_H
#define OBJETOS_H

const int ANCHO=1280;   //Ancho del juego
const int ALTO=720;     //Alto del juego

//Estructura de coordenadas cartesianas
    struct Coord
    {
        int x,y;
        Coord(int x0=0,int y0=0){x=x0; y=y0;}
        Coord(const Coord& c){x=c.x; y=c.y;}
    };

//Estructura de coordenadas polares
    struct Polar
    {
        int ro;
        float angle;
        Polar(int ro0=0,float ang=0.00){ro=ro0; angle=ang;}
        Polar(const Polar& p){ro=p.ro; angle=p.angle;}
    };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CLASES
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Pieza
{
    private:
        Coord orig,veloc;   //Coordenadas de origen de la pieza, Velocidad en 'X' y en 'Y';
        float angulo;       //Ángulo de orientación de la pieza;
        Polar *perif;       //Puntero a tabla (alojada en el heap) con los puntos
                            //periféricos de la pieza en coordenadas polares;
        int tam,esc;        //Tamaño de la array de periféricos y escala de la pieza (en %);
        bool colision=false;      //Indica si está en colisión

    public:
        //Constructores
            Pieza(int x0,int y0,int ang,int p,int e,Coord v);

        //Setters y getters
            Coord coords(){return orig;}
            void coords(Coord c){ orig=c; }

            void x (int c) { orig.x=c;      }
             int x (     ) { return orig.x; }

            void y (int c) { orig.y=c;      }
             int y (     ) { return orig.y; }

             int angle ( ) { return int(angulo);}
            void angle (int ang) {angulo=float(ang);}

            int periferico(){return tam;}
            Polar periferico(int id){return id<tam ? perif[id]:-1;}
            void periferico(int id,Polar valor){ id<tam ? perif[id]=valor:-1;}

            Coord velocidad (       ) { return veloc;}
             void velocidad (Coord v) {veloc=v;}

             int escala (       ) { return esc;}
            void escala (int e) {esc=e;}

            bool ha_chocado (      ) { return colision;}
            void ha_chocado (bool c) {colision=c;}
        //End setters y getters

        void rota(int r);
        void acelera();
        void avanza();
        void pinta() const;
        virtual void actualiza();
};

class Nave: public Pieza
{
    public:
        //Constructores
            Nave(int x0,int y0,int ang);

        virtual void actualiza();
};

class Asteroide: public Pieza
{
    private:
        int r;

    public:
        //Constructores
            Asteroide();

        virtual void actualiza(Pieza& p);
        virtual void actualiza();
        bool colisiona(Pieza& nave);
};

class Laser: public Pieza
{
    public:
        //Constructores
            Laser(Pieza& p);

        virtual void actualiza();
        void avanza();
};


#endif // OBJETOS_H

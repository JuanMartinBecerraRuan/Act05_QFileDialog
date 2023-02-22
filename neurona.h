#ifndef NEURONA_H
#define NEURONA_H

class Neurona{
    private:
        int id, posicion_x,posicion_y,red,green,blue;
        double voltaje;
    public:
        Neurona(int,double,int,int,int,int,int);
        int getId();
        double getVoltaje();
        int getPosX();
        int getPosY();
        int getRed();
        int getGreen();
        int getBlue();
};

#endif // NEURONA_H

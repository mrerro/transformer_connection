#include "transformer.h"

Transformer::Transformer(double i1, double i2, double r1, double r2, double l1, double l2, double c1, double c2, double e, double p, double l12 , double duration) : RungeKutta (4)
{
    this->v1 = std::pow(l1 * c1,-0.5);
    this->v2 = std::pow(l2 * c2,-0.5);
    this->d1 = r1/(2*l1);
    this->d2 = r2/(2*l2);
    this->k1 = l12 / l1;
    this->k2 = l12 / l2;
    this->e = e;
    this->p = p;

    this->duration = duration * 1000.0;

    std::vector<double> Y0(4);
    Y0[0] = 0;
    Y0[1] = 0;
    Y0[2] = i1;
    Y0[3] = i2;
    SetInit(0, Y0);
}

std::vector<double> Transformer::F(double time, std::vector<double> &Y) {
    FY[0] = Y[2];
    FY[1] = Y[3];
    FY[2] = (-2*d2*k1*Y[3]-k1*v2*v2*Y[1]-2*d1*Y[2]-v1*v1*Y[0]+e*cos(p*time))/(1-k1*k2);
    FY[3] = (-2*d1*k2*Y[2]-k2*v1*v1*Y[0]-2*d2*Y[3]-v2*v2*Y[1]+e*k2*cos(p*time))/(1-k1*k2);
    return FY;
}

void Transformer::run() {
    for(double i = 0; i < duration; i += deltaDuration){
        NextStep(deltaDuration / 1000.0);
        I1.push_back(Y[2]);
        I2.push_back(Y[3]);
        T.push_back(i / 1000.0);
    }
    emit resultReady(I1, I2, T);
}

Transformer::~Transformer()
{
}

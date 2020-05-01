#pragma once

#include "RungeKutta.h"
#include <QThread>
#include <cmath>
#include <vector>


class Transformer : public QThread, public RungeKutta
{
   Q_OBJECT
        void run() override;
    signals:
        void resultReady(const std::vector<double> &I1, const std::vector<double> &I2, const std::vector<double> &T);

private:
    double d1, d2;
    double v1, v2;
    double k1, k2;
    double e;
    double p;

    double duration;
    double deltaDuration = 50.;

    std::vector<double> I1{};
    std::vector<double> I2{};
    std::vector<double> T{};

public:
    Transformer(double i1, double i2, double r1, double r2, double l1, double l2, double c1, double c2, double e, double p, double l12, double duration);
    ~Transformer();
    virtual std::vector<double> F (double t, std::vector<double> &Y) override;
};

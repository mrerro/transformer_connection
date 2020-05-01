#include "RungeKutta.h"

RungeKutta::RungeKutta(unsigned int N)
{
    Init(N);
}

RungeKutta::RungeKutta()
{
}

void RungeKutta::Init(unsigned int N)
{
    Y = std::vector<double>(N);
    YY = std::vector<double>(N);
    Y1 = std::vector<double>(N);
    Y2 = std::vector<double>(N);
    Y3 = std::vector<double>(N);
    Y4 = std::vector<double>(N);
    FY = std::vector<double>(N);
}

void RungeKutta::SetInit(double t0, std::vector<double> &Y0)
{
    t = t0;
    if (Y.empty())
    {
        Init(static_cast<unsigned int>(Y0.size()));
    }
    for (int i = 0; i < Y.size(); i++)
    {
        Y[i] = Y0[i];
    }
}

std::vector<double> RungeKutta::NextStep(double dt)
{
    int i;

    if (dt < 0)
    {
        throw std::exception();
    }

    // рассчитать Y1
    Y1 = F(t, Y);

    for (i = 0; i < Y.size(); i++)
    {
        YY[i] = Y[i] + Y1[i] * (dt / 2.0);
    }

    // рассчитать Y2
    Y2 = F(t + dt / 2.0, YY);

    for (i = 0; i < Y.size(); i++)
    {
        YY[i] = Y[i] + Y2[i] * (dt / 2.0);
    }

    // рассчитать Y3
    Y3 = F(t + dt / 2.0, YY);

    for (i = 0; i < Y.size(); i++)
    {
        YY[i] = Y[i] + Y3[i] * dt;
    }

    // рассчитать Y4
    Y4 = F(t + dt, YY);

    // рассчитать решение на новом шаге
    for (i = 0; i < Y.size(); i++)
    {
        Y[i] = Y[i] + dt / 6.0 * (Y1[i] + 2.0 * Y2[i] + 2.0 * Y3[i] + Y4[i]);
    }

    // рассчитать текущее время
    t = t + dt;

    return FY;
}

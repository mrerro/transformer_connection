#include <vector>
#include <stdexcept>

#pragma once

class RungeKutta
{
    /// <summary>
    /// Текущее время
    /// </summary>
public:
    double t = 0;

    /// <summary>
    /// Искомое решение Y[0] - само решение, Y[i] - i-тая производная решения
    /// </summary>
    ///
    std::vector<double> Y;
    /// <summary>
    /// Внутренние переменные
    /// </summary>
    ///
private:
    std::vector<double> YY, Y1, Y2, Y3, Y4;
protected:
    std::vector<double> FY;

    /// <summary>
    /// Конструктор
    /// </summary>
    /// <param name="N">размерность системы</param>
public:
    RungeKutta(unsigned int N);
    /// <summary>
    /// Конструктор
    /// </summary>
    RungeKutta();

    /// <summary>
    /// Выделение памяти под рабочие массивы
    /// </summary>
    /// <param name="N">Размерность массивов</param>
protected:
    void Init(unsigned int N);

    /// <summary>
    /// Установка начальных условий
    /// </summary>
    /// <param name="t0">Начальное время</param>
    /// <param name="Y0">Начальное условие</param>
public:
    void SetInit(double t0, std::vector<double> &Y0);

    /// <summary>
    /// Расчет правых частей системы
    /// </summary>
    /// <param name="t">текущее время</param>
    /// <param name="Y">вектор решения</param>
    /// <returns>правая часть</returns>
    virtual std::vector<double> F(double t, std::vector<double> &Y) = 0;

    /// <summary>
    /// Следующий шаг метода Рунге-Кутта
    /// </summary>
    /// <param name="dt">текущий шаг по времени (может быть переменным)</param>
    std::vector<double> NextStep(double dt);
};

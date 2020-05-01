#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCharts>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbForcedOsc_clicked();
    void chartUpdate (const std::vector<double> &I1, const std::vector<double> &I2 , const std::vector<double> &T);

private:
    Ui::MainWindow *ui;
    QChart *chart;
    QLineSeries *seriesI1T;
    QLineSeries *seriesI2T;
};
#endif // MAINWINDOW_H

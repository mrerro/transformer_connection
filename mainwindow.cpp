#include "mainwindow.h"
#include "transformer.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->chartView->setRenderHint(QPainter::Antialiasing);

    seriesI1T = new QLineSeries();
    seriesI2T = new QLineSeries();

    chart = new QChart();
    chart->addSeries(seriesI1T);
    chart->addSeries(seriesI2T);
    chart->createDefaultAxes();
    auto xAxis = chart->axes(Qt::Horizontal);
    auto yAxis = chart->axes(Qt::Vertical);
    xAxis[0]->setRange(-10, 100);
    yAxis[0]->setRange(-1000, 5000);
    chart->legend()->hide();

    ui->chartView->setChart(chart);

    qRegisterMetaType<std::vector<double> >("std::vector<double>");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbForcedOsc_clicked()
{
    Transformer *workerThread = new Transformer(ui->sbI1->value(),ui->sbI2->value(),ui->sbR1->value(),ui->sbR2->value(),ui->sbL1->value(),ui->sbL2->value(),ui->sbC1->value(),ui->sbC2->value(),10,ui->sbP->value(),ui->sbL12->value(),ui->sbDuration->value());
    connect(workerThread, &Transformer::resultReady, this, &MainWindow::chartUpdate);
    connect(workerThread, &Transformer::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

void MainWindow::chartUpdate(const std::vector<double> &I1, const std::vector<double> &I2 , const std::vector<double> &T){
    seriesI1T->clear();
    seriesI2T->clear();
    auto xAxis = chart->axes(Qt::Horizontal);
    xAxis[0]->setRange(-10, T.back());

    int i =0;
    for(double item : T){
        seriesI1T->append(I1[i],item);
        seriesI2T->append(I2[i],item);
        i++;
    }
    ui->chartView->update();
}

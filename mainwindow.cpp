#include "mainwindow.h"
#include "transformer.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,776);

    ui->chartView->setRenderHint(QPainter::Antialiasing);

    seriesI1T = new QLineSeries();
    seriesI2T = new QLineSeries();

    chart = new QChart();
    chart->addSeries(seriesI1T);
    chart->addSeries(seriesI2T);
    chart->createDefaultAxes();
    auto xAxis = chart->axes(Qt::Horizontal);
    auto yAxis = chart->axes(Qt::Vertical);
    xAxis[0]->setRange(0, 100);
    yAxis[0]->setRange(0, 100);
    xAxis[0]->setTitleText("Время,c");
    yAxis[0]->setTitleText("I,A");
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
    ui->pbForcedOsc->setEnabled(false);
    ui->pbFreeOsc->setEnabled(false);
    Transformer *workerThread = new Transformer(ui->sbI1->value(),ui->sbI2->value(),ui->sbR1->value(),ui->sbR2->value(),ui->sbL1->value(),ui->sbL2->value(),ui->sbC1->value(),ui->sbC2->value(),1,ui->sbP->value(),ui->sbL12->value(),ui->sbDuration->value());
    connect(workerThread, &Transformer::resultReady, this, &MainWindow::chartUpdate);
    connect(workerThread, &Transformer::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

void MainWindow::on_pbFreeOsc_clicked()
{
    ui->pbForcedOsc->setEnabled(false);
    ui->pbFreeOsc->setEnabled(false);
    Transformer *workerThread = new Transformer(ui->sbI1->value(),ui->sbI2->value(),ui->sbR1->value(),ui->sbR2->value(),ui->sbL1->value(),ui->sbL2->value(),ui->sbC1->value(),ui->sbC2->value(),0,ui->sbP->value(),ui->sbL12->value(),ui->sbDuration->value());
    connect(workerThread, &Transformer::resultReady, this, &MainWindow::chartUpdate);
    connect(workerThread, &Transformer::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

void MainWindow::chartUpdate(const std::vector<double> &I1, const std::vector<double> &I2 , const std::vector<double> &T){
    seriesI1T->clear();
    seriesI2T->clear();
    auto xAxis = chart->axes(Qt::Horizontal);
    xAxis[0]->setRange(0, T.back());
    const auto I1minmax = std::minmax_element(begin(I1), end(I1));
    const auto I2minmax = std::minmax_element(begin(I2), end(I2));
    auto yAxis = chart->axes(Qt::Vertical);
    yAxis[0]->setRange(*std::min(&(*I1minmax.first),&(*I2minmax.first)) - 2, *std::max(&(*I1minmax.second), &(*I2minmax.second)) + 2);
    int i =0;
    for(double t : T){
        seriesI1T->append(t, I1[i]);
        seriesI2T->append(t, I2[i]);
        i++;
    }
    ui->chartView->update();
    ui->pbForcedOsc->setEnabled(true);
    ui->pbFreeOsc->setEnabled(true);
}

void MainWindow::on_pbSave_clicked()
{
    QPixmap pic(ui->chartView->size());
    ui->chartView->QWidget::render(&pic);
    pic.save(QString::number(fileCounter) + ".png", "PNG");
    fileCounter++;
}

void MainWindow::on_pbErase_clicked()
{
    seriesI1T->clear();
    seriesI2T->clear();
}



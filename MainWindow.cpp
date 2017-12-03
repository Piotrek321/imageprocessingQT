#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_RunSobelFilter_clicked()
{
qDebug() << "XXXXX" ;
}

void MainWindow::on_RunGaussFilter_clicked()
{

}

void MainWindow::on_Reset_clicked()
{
//    QString fileName = QFileDialog::getSaveFileName(this,
//         tr("Save Address Book"), "",
//         tr("Address Book (*.abk);;All Files (*)"));
    QString name = QFileDialog::getOpenFileName(this,
                                          tr("Load image"), "",
                                          tr("Image file (*.jpeg);;All Files (*)"));
    qDebug() << "name: " << name << endl;
    Mat original= imread(name.toStdString(), IMREAD_GRAYSCALE ); //IMREAD_GRAYSCALE
    imshow("original", original);
}

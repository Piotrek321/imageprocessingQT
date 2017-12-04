#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  /////////////////////////////////////////////////
  createActions();
  createMenus();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_RunSobelFilter_clicked() { qDebug() << "XXXXX"; }

void MainWindow::on_RunGaussFilter_clicked() {}

void MainWindow::on_Reset_clicked() {}

void MainWindow::on_ConverToGrayScale_clicked() {
  if (m_OriginalColor.channels() != 1) {
    Mat greyMat;
    cvtColor(m_OriginalColor, greyMat, CV_BGR2GRAY);
    imshow("greyMat", greyMat);
  } else {
    qDebug() << "Image is already in grayscaler" << endl;
  }
}

void MainWindow::open() {
  m_FileName = QFileDialog::getOpenFileName(
      this, tr("Load image"), "", tr("Image file (*.jpeg);;All Files (*)"));
  m_OriginalColor = imread(m_FileName.toStdString()); // IMREAD_GRAYSCALE
  imshow("original", m_OriginalColor);
}

void MainWindow::save() {
  QString fileName =
      QFileDialog::getSaveFileName(this, tr("Save Address Book"), "",
                                   tr("Address Book (*.abk);;All Files (*)"));

  if (fileName.isEmpty())
    return;
  else {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
      QMessageBox::information(this, tr("Unable to open file"),
                               file.errorString());
      return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    out << "contacts";
  }
}

void MainWindow::createActions() {

  openAct = new QAction(tr("&Open..."), this);
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip(tr("Open an existing file"));
  connect(openAct, &QAction::triggered, this, &MainWindow::open);

  saveAct = new QAction(tr("&Save"), this);
  saveAct->setShortcuts(QKeySequence::Save);
  saveAct->setStatusTip(tr("Save the document to disk"));
  connect(saveAct, &QAction::triggered, this, &MainWindow::save);
}

void MainWindow::createMenus() {
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(openAct);
  fileMenu->addAction(saveAct);
}
QImage Mat2QImage(cv::Mat const &src) {
  cv::Mat temp;                    // make the same cv::Mat
  cvtColor(src, temp, CV_BGR2RGB); // cvtColor Makes a copt, that what i need
  QImage dest((const uchar *)temp.data, temp.cols, temp.rows, temp.step,
              QImage::Format_RGB888);
  dest.bits(); // enforce deep copy, see documentation
  // of QImage::QImage ( const uchar * data, int width, int height, Format
  // format )
  return dest;
}
// QImage img(scene->sceneRect().size().toSize(), QImage::Format_RGB32);

// QPainter painter(&img);
// scene->render(&painter);

// bool b = img.save("test.png");
cv::Mat QImage2Mat(QImage const &src) {
  cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar *)src.bits(),
              src.bytesPerLine());
  cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
  cvtColor(tmp, result, CV_BGR2RGB);
  return result;
}

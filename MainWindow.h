#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QActionGroup>
#include <QLabel>
#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_RunSobelFilter_clicked();

  void on_RunGaussFilter_clicked();

  void on_Reset_clicked();

  void on_ConverToGrayScale_clicked();

private:
  Ui::MainWindow *ui;
  QString m_FileName;
  Mat m_OriginalColor;

  /////////////////////////////////////////////
private slots:
  void open();
  void save();

private:
  void createActions();
  void createMenus();

  QMenu *fileMenu;
  QAction *openAct;
  QAction *saveAct;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

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
 void num_pressed();
 void on_pushButton_dot_released();
 void on_pushButton_eq_released();
 void on_pushButton_clean_released();

 void on_pushButton_graf_released();

 void on_pushButton_released();

private:
    Ui::MainWindow *ui;
    double xBegin, xEnd, h, X, Y;
    int N;

    QVector<double> x, y;
};
#endif // MAINWINDOW_H

#include "mainwindow.h"

#include <QByteArray>
#include <QDebug>
#include <QString>

#include "./ui_mainwindow.h"
#include "credit.h"
#include "qcustomplot.h"
extern "C" {
#include <../s21_smartcalc.h>
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_min, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_mul, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_mod, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_div, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_op, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_cl, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_sin, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_cos, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_tan, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_log, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_ln, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_asin, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_acos, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_atan, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_sqrt, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_pow, SIGNAL(released()), this, SLOT(num_pressed()));
  connect(ui->pushButton_X, SIGNAL(released()), this, SLOT(num_pressed()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::num_pressed() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->line_result->text().endsWith("") &&
      ui->line_result->text().size() == 0) {
    ui->line_result->setText(button->text());
    if (button->text() == "sin" || button->text() == "asin" ||
        button->text() == "cos" || button->text() == "sqrt" ||
        button->text() == "acos" || button->text() == "tan" ||
        button->text() == "atan" || button->text() == "log" ||
        button->text() == "ln") {
      ui->line_result->setText(ui->line_result->text() + "(");
    }
  } else {
    if (ui->line_result->text().endsWith("x") != 1 || button->text() != "x") {
      ui->line_result->setText(ui->line_result->text() + button->text());
      if (button->text() == "sin" || button->text() == "asin" ||
          button->text() == "cos" || button->text() == "sqrt" ||
          button->text() == "acos" || button->text() == "tan" ||
          button->text() == "atan" || button->text() == "log" ||
          button->text() == "ln") {
        ui->line_result->setText(ui->line_result->text() + "(");
      }
    }
  }
}

void MainWindow::on_pushButton_dot_released() {
  QPushButton *button = (QPushButton *)sender();
  ui->line_result->setText(ui->line_result->text() + button->text());
}

void MainWindow::on_pushButton_eq_released() {
  QByteArray str_bit = ui->line_result->text().toLocal8Bit();
  char *str = str_bit.data();
  str = remove_space(str);
  int valid = validator(str);
  if (valid) {
    ui->line_result->setText(QString::number(calculate(str)));
  } else {
    ui->line_result->setText("Incorrect expression");
  }
}

void MainWindow::on_pushButton_clean_released() {
  ui->line_result->setText("");
}

void MainWindow::on_pushButton_graf_released() {
  ui->widget->clearGraphs();
  x.clear();
  y.clear();
  QString new_label = ui->line_result->text();
  QString value, origin_string;
  h = 0.1;
  xBegin = ui->line_ot_1->text().toDouble();
  xEnd = ui->line_do_1->text().toDouble();
  double yBegin = ui->line_ot_2->text().toDouble();
  double yEnd = ui->line_do_2->text().toDouble();

  ui->widget->xAxis->setRange(xBegin, xEnd);
  ui->widget->yAxis->setRange(yBegin, yEnd);
  Y = 0;
  for (X = xBegin; X <= xEnd; X += h) {
    if (X < 0.01 && X > -0.01) X = 0;
    x.push_back(X);
    qDebug() << X;
    origin_string = new_label;
    value = origin_string.replace("X", ('(' + QString::number(X) + ')'));
    QByteArray str_bit = value.toLocal8Bit();
    char *res_str = str_bit.data();
    res_str = remove_space(res_str);
    qDebug() << res_str;
    int valid = validator(res_str);
    qDebug() << valid;
    if (valid == 0) {
      ui->line_result->setText("ERROR!!!");
    } else {
      Y = calculate(res_str);
      y.push_back(Y);
      //           qDebug() << Y;
    }
  }

  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void MainWindow::on_pushButton_released() {
  credit credit_window;
  credit_window.setModal(true);
  credit_window.exec();
}

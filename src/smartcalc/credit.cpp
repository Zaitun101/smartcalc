#include "credit.h"
#include "ui_credit.h"

credit::credit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::credit)
{
    ui->setupUi(this);
}

credit::~credit()
{
    delete ui;
}

void credit::on_pushButton_released()
{
    int sum = ui->lineSum->text().toInt();
    int term = ui->spinBox_term->text().toInt();
    double percent = ui->doubleSpinBox_percent->text().toDouble();
    int total = 0;
    int overpayment = 0;
    double monthly = 0;
    if (ui->comboBox->currentIndex() == 0 && sum != 0 && term != 0 && percent != 0) {
        percent = percent / 1200;
        monthly = sum * (percent*pow((1+percent),term)/(pow((1+percent), term)-1));
//        total = sum*(percent + (percent / (1+percent)*term-1));
        total = monthly * term;
        overpayment = total - sum;
//        monthly = total / term;
        QString qsum = QString::number(total);
        QString qmonth = QString::number(monthly);
        QString qover = QString::number(overpayment);
        ui->label_10->setText(qsum);
        ui->label_9->setText(qover);
        ui->label_6->setText(qmonth);
    } else if (ui->comboBox->currentIndex() == 1 && sum != 0 && term != 0 && percent != 0) {
        int debt_sum = sum / term;
        ui->label_6->setText("");
        for (int i = 1; i <= term; i++) {
            monthly = (sum * percent / 100 * 31/365) + debt_sum;
            QString qmonth = QString::number(monthly);
            QString qi = QString::number(i);
            ui->label_6->setText(ui->label_6->toPlainText() + qi+"-й месяц: "+ qmonth + "руб." + '\n');
            sum -= debt_sum;
            total += monthly;
        }
        overpayment = total - debt_sum * term;
        QString qsum = QString::number(total);
        QString qover = QString::number(overpayment);
        ui->label_10->setText(qsum);
        ui->label_9->setText(qover);
    }
}


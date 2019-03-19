#include "mainwindow.h"
#include "ui_mainwindow.h"

static double timeVal = 0.0;
static double vinitial = 0.0;
static double vfinal = 0.0;
static double accel = 0.0;
static double displacement = 0.0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_Answer->hide();
    ui->label_Question->hide();

    if (ui->checkBox_Time->isChecked() == true){
        timeVal = ui->doubleSpinBox_Time->value();
    }

 else if (ui->checkBox_Accel->isChecked() == true){
     accel = ui->doubleSpinBox_Acceleration->value();
 }

 else if (ui->checkBox_Vfinal->isChecked()==true){
     vfinal = ui->doubleSpinBox_Vfinal->value();
 }

 else if (ui->checkBox_Vinitial->isChecked()==true){
     vinitial = ui->doubleSpinBox_Vinitial->value();
 }

 else if (ui->checkBox_Displacement->isChecked()==true){
        displacement = ui->doubleSpinBox_Displacement->value();

}
    double test = timeVal+displacement;
    ui->label_Answer->setText(QString::number(test));




connect(ui->pushButton_solve, SIGNAL (released()),this, SLOT (SolvePressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SolvePressed(){




}

void MainWindow::QuestionFormat()
{

}

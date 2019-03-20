/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Basic Kinematics Solver 1.0
Daniel Harrington
03/20/2019 @ 12:00pm (EST)

This program is designed to solve kinematics problems as well
as display the proper format for approaching the question.
The secondary goal of this program is to make it as robust as possible.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Included headers, only non-generated one is <QButtonGroup>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QButtonGroup>


//Declaring global variables, qt editor doesnt like it if they aren't defined as static
static double timeVal = 0.0;
static double vinitial = 0.0;
static double vfinal = 0.0;
static double accel = 0.0;
static double displacement = 0.0;
static int knowncount = 0;
static QString unknownVariable = "?" ;
//Auto-Generated code from QT that acts as the main function
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Setting Up UI and the default state of some widgets
    ui->setupUi(this);
    ui->label_Answer->hide();
    ui->label_Question->hide();
    ui->pushButton_solve->setDisabled(1);
    /**************************************************************************************************
     Future Reference - This is the method I found for creating button groups that works nicest in c++
    and in the current version of QT. Creates a button group and then adds each button in.
     **************************************************************************************************/
    QButtonGroup* btngroup_Checked = new QButtonGroup(this);
    btngroup_Checked->addButton(ui->checkBox_Time);
    btngroup_Checked->addButton(ui->checkBox_Accel);
    btngroup_Checked->addButton(ui->checkBox_Vinitial);
    btngroup_Checked->addButton(ui->checkBox_Vfinal);
    btngroup_Checked->addButton(ui->checkBox_Displacement);
    //This is only hear because for some reason the group defaulted to exclusive despite the individual buttons all being non-exclusive.
    btngroup_Checked->setExclusive(false);
    //*************************************************************

    //This part makes it so that if any checkbox is clicked it checks if the problem is solvable
    connect(btngroup_Checked, static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            this, &MainWindow::MinimumKnownCheck);

    //Associating the solve button being pressed with the SolvePressed Function
    connect(ui->pushButton_solve, SIGNAL (released()),this, SLOT (SolvePressed()));
    //Connects the clear button
    connect(ui->pushButton_reset,SIGNAL (released()),this,SLOT(ResetButton()));
}

// Auto-Generated on project start, closes window when the user his close.
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::SolvePressed(){
    if (ui->checkBox_Time->isChecked() == false){
        unknownVariable = "t";
    }
   else if (ui->checkBox_Accel->isChecked() == false){
         unknownVariable = "a";
    }
    else if (ui->checkBox_Vfinal->isChecked()==false){
         unknownVariable = "vf";
    }
    else if (ui->checkBox_Vinitial->isChecked()==false){
        unknownVariable = "vi";
    }
    else if (ui->checkBox_Displacement->isChecked()==false){
        unknownVariable = "d";
    }
  accel = ui->doubleSpinBox_Acceleration->value();
  vfinal = ui->doubleSpinBox_Vfinal->value();
  vinitial = ui->doubleSpinBox_Vinitial->value();
  displacement = ui->doubleSpinBox_Displacement->value();
  timeVal= ui->doubleSpinBox_Time->value();
}

void MainWindow::QuestionFormat()
{

}

/*****************************************************************
 The kinematic equation requires atleast 4/5 values to be solvable,
 this function has a creates an array of booleans checking is each
 box is checked. If the total is 4 or greater the solve button is enabled.
 This function is called upon EVERY time a button is clicked on and so will
 register if the user chooses to uncheck a box and will disable the solve
 button accordingly.
 ******************************************************************/
void MainWindow::MinimumKnownCheck()
{
    bool CheckBoxes[] {ui->checkBox_Time->isChecked(),ui->checkBox_Accel->isChecked(),ui->checkBox_Vfinal->isChecked(),
                ui->checkBox_Vinitial->isChecked(),ui->checkBox_Displacement->isChecked()};
    for (int i=0;i<5;i+=1) {
       if (CheckBoxes[i] == true){
           knowncount+=1;
       }

    }
    if ((knowncount==4)||(knowncount==5)){
        ui->pushButton_solve->setDisabled(0);
        knowncount= 0;
    }
    else {
        knowncount = 0;
        ui->pushButton_solve->setDisabled(1);
    }
}

void MainWindow::ResetButton()
{
timeVal = 0.0;
vinitial = 0.0;
vfinal = 0.0;
accel = 0.0;
displacement = 0.0;
knowncount = 0;
unknownVariable = "?";
ui->doubleSpinBox_Displacement->setValue(0.00);
ui->doubleSpinBox_Vinitial->setValue(0.00);
ui->doubleSpinBox_Vfinal->setValue(0.00);
ui->doubleSpinBox_Acceleration->setValue(0.00);
ui->doubleSpinBox_Time->setValue(0.00);
ui->label_Answer->hide();
ui->label_Question->hide();
ui->pushButton_solve->setDisabled(1);
ui->checkBox_Time->setChecked(false);
ui->checkBox_Accel->setChecked(false);
ui->checkBox_Vfinal->setChecked(false);
ui->checkBox_Vinitial->setChecked(false);
ui->checkBox_Displacement->setChecked(false);
ui->label_Answer->clear();
ui->label_Question->clear();
}

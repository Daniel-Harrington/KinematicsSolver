/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Basic Kinematics Solver 1.0
Daniel Harrington
03/20/2019 @ 12:00pm (EST)
This program is designed to solve kinematics problems.
The secondary goal of this program is to make it as robust as possible.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

//Included headers,some auto generated.

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QButtonGroup>
#include <QMessageBox>
#include <QStringList>
#include <QVector>
#include <math.h>
//Declaring global variables
static double timeVal = 0.0;
static double vinitial = 0.0;
static double vfinal = 0.0;
static double accel = 0.0;
static double displacement = 0.0;
static int knowncount = 0;
static QStringList unknownVariables;

//Auto-Generated code from QT that acts as the main function
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //Setting Up UI and the default state of some widgets
    ui->setupUi(this);
    ui->label_Answer->hide();
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
    //This is only here because for some reason the group defaulted to exclusive despite the individual buttons all being non-exclusive.
    btngroup_Checked->setExclusive(false);
    //*************************************************************

    //This part makes it so that if any checkbox is clicked it checks if the problem is solvable
    connect(btngroup_Checked, static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            this, &MainWindow::MinimumKnownCheck);

    //Associating the solve button being pressed with the SolvePressed Function
    connect(ui->pushButton_solve, SIGNAL (released()),this, SLOT (SolvePressed()));

    //Connects the reset button to ResetButton()
    connect(ui->pushButton_reset,SIGNAL (released()),this,SLOT(ResetButton()));
}

// Auto-Generated on project start, closes window when the user his close.
MainWindow::~MainWindow()
{
    delete ui;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
This function handles purely the mathematical portion of the problems and will not
return as solved until the list of unknowns is empty. It first checks the number of
unknowns, if there is only 1 it will solve normally, if there are 2 is will iterate
through and solve each one without using a formula that requires the other.
It is a boolean with the default value set to false but can be initiated as true inside
the switch in SolvePressed to break the while loop.
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
bool MainWindow::Solution(bool Solved){
    QString txt_answer;
if(Solved==false){
    if(unknownVariables.size()>1){
        for (int list_Place=0;list_Place<unknownVariables.size();++list_Place) {
            if(unknownVariables.at(list_Place).contains("t")){
                if(unknownVariables.at(list_Place+1).contains("a")){
                    accel=
                }
            }
        }
    }
    else if(unknownVariables.isEmpty()== true)
    {
        txt_answer = "Time: "+QString::number(timeVal)+"    Initial Velocity: "+QString::number(vinitial)+"    Final Velocity: "+QString::number(vfinal)+\
                "    Displacement: "+QString::number(displacement)+"    Acceleration: "+ QString::number(accel);
        ui->label_Answer->setText(txt_answer);
        return true;
    }
    else if (unknownVariables.size()==1) {
    }
    return 57;
}
else {
    return true;
}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
This function ExceptionHandler() identifies any possible unique problems that could be encountered
based on the user inputs and returns them as a identified case to SolvePressed()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int MainWindow::ExceptionHandler(){
    if(ui->checkBox_Accel->isChecked()==true){
        //Checks if the problem is a physical possibility
        if(((vinitial/vfinal)!=1.0 && accel !=0.0)==true||(vinitial>vfinal && accel>0.0)==true||(vinitial<vfinal && accel<0.0)==true){
            return Case_Exception;
        }
        //Checks if time is set to 0 by user
        else if (timeVal == 0.0 && (ui->checkBox_Time->isChecked()==true)){
            return Case_T0;
        }
        //Checks if there is an obvious logical solution to finding one of the unknowns
        else if (accel == 0.0 &&(ui->checkBox_Vinitial->isChecked()==true ||ui->checkBox_Vfinal->isChecked()==true)) {
            return CaseVi_is_VF;
        }
    }
    //Checks to see if the combination of Vi and VF make acceleration immediately 0.0
    if(ui->checkBox_Accel->isChecked()==false && ui->checkBox_Vinitial->isChecked()==true && ui->checkBox_Vfinal->isChecked()==true && (vinitial/vfinal ==1.0)==true)
    {
        return Case_A0;
    }
    //If there is no special case and the problem can now be purely mathmatically.
    return Case_NoException;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SolvePressed() is run when the solve button is pushed, we know because of MinimumKnownCheck() that
the problem is certain to be solvable at this point. It commits the entered values to memory and
identifies the unknowns adding them to a list. it then checks the exception case and handles each case,
eliminating any unknowns solved logically until the problem returns as solved from the Solution() function.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::SolvePressed(){

    QString txt_answer;

    //Adds any unchecked boxes to the unknown list.
    if (ui->checkBox_Time->isChecked() == false){
        unknownVariables << "t";}
    else if (ui->checkBox_Accel->isChecked() == false){
        unknownVariables <<"a";}
    else if (ui->checkBox_Vfinal->isChecked()==false){
        unknownVariables << "vf";}
    else if (ui->checkBox_Vinitial->isChecked()==false){
        unknownVariables <<"vi";}
    else if (ui->checkBox_Displacement->isChecked()==false){
        unknownVariables << "d";}

    timeVal= ui->doubleSpinBox_Time->value();
    vinitial= ui->doubleSpinBox_Vinitial->value();
    vfinal= ui->doubleSpinBox_Vfinal->value();
    displacement= ui->doubleSpinBox_Displacement->value();
    accel= ui->doubleSpinBox_Acceleration->value();

    while (Solution()==false) {

        int exception_Case = ExceptionHandler();

        switch (exception_Case) {
        case Case_NoException: QMessageBox::critical(this,tr("Working?"),tr("solution branch"));
            Solution();
            break;

        case Case_Exception:  QMessageBox::critical(this,tr("Error"),tr("You have entered invalid parameters please try again. This program cannot support non-linear acceleration."));
            ui->label_Answer->setText("Error: Invalid Values");
            Solution(true);//This breaks the loop so the user isnt spammed with messages.
            break;

        case Case_T0:if(vinitial>vfinal){
                txt_answer= "Time: 0   Initial Velocity: 0    Final Velocity: 0    Displacement: 0    Acceleration: -∞";
                ui->label_Answer->setText(txt_answer);
                Solution(true);
                break;
            }
            else if (vfinal>vinitial) {
                txt_answer= "Time: 0   Initial Velocity: 0    Final Velocity: 0    Displacement: 0    Acceleration: ∞";
                ui->label_Answer->setText(txt_answer);
                Solution(true);
                break;
            }else if (unknownVariables.contains("vf")){
                vfinal=vinitial;
                txt_answer= "Time: 0   Initial Velocity: " +QString::number(vinitial)+ "    Final Velocity: "+QString::number(vfinal)+"    Displacement: 0    Acceleration: 0";
                ui->label_Answer->setText(txt_answer);
                Solution(true);
                break;
            }else if (unknownVariables.contains("vi")){
                vinitial=vfinal;
                txt_answer= "Time: 0   Initial Velocity: " +QString::number(vinitial)+ "    Final Velocity: "+QString::number(vfinal)+"    Displacement: 0    Acceleration: 0";
                ui->label_Answer->setText(txt_answer);
                Solution(true);
                break;
            }
            break;

        case CaseVi_is_VF: if(unknownVariables.contains("vi")){
                vinitial=vfinal;
                unknownVariables.removeOne("vi");
                Solution();
                break;
            }
            else if (unknownVariables.contains("vf")) {
                vfinal=vinitial;
                  Solution();
                unknownVariables.removeOne("vf");
                break;
            }
            break;
        case Case_A0: unknownVariables.removeOne("a");
            accel=0.0;
            Solution();
            break;

        }
    }
}

/*******************************************************************
 The kinematic equation requires atleast 3/5 values to be solvable,
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
    for(int i=0;i<5;i+=1){
        if (CheckBoxes[i] == true){
            knowncount+=1;}
    }
    if ((knowncount==3) ||(knowncount==4)||(knowncount==5)){
        ui->pushButton_solve->setDisabled(0);
        knowncount= 0;
    }else {
        knowncount = 0;
        ui->pushButton_solve->setDisabled(1);}
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 This function is so simple its almost relaxing. ResetButton()
 sets all values back to their default state.
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void MainWindow::ResetButton()
{
    timeVal = 0.0;
    vinitial = 0.0;
    vfinal = 0.0;
    accel = 0.0;
    displacement = 0.0;
    knowncount = 0;
    ui->doubleSpinBox_Displacement->setValue(0.00);
    ui->doubleSpinBox_Vinitial->setValue(0.00);
    ui->doubleSpinBox_Vfinal->setValue(0.00);
    ui->doubleSpinBox_Acceleration->setValue(0.00);
    ui->doubleSpinBox_Time->setValue(0.00);
    ui->label_Answer->hide();
    ui->pushButton_solve->setDisabled(1);
    ui->checkBox_Time->setChecked(false);
    ui->checkBox_Accel->setChecked(false);
    ui->checkBox_Vfinal->setChecked(false);
    ui->checkBox_Vinitial->setChecked(false);
    ui->checkBox_Displacement->setChecked(false);
    ui->label_Answer->clear();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void SolvePressed();
    void MinimumKnownCheck();
    void ResetButton();
    bool Solution(bool Solved=false);
    int ExceptionHandler();

};
enum Case{
    Case_Exception=1, Case_NoException=2, Case_T0=3, Case_A0=4, CaseVi_is_VF=5
};

#endif // MAINWINDOW_H

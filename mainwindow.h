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
    void Solution();
    int ExceptionHandler();

};
enum Case{
    Case_Exception=1, Case_NoException=2, Case_T0=3
};

#endif // MAINWINDOW_H

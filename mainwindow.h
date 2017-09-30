#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>

class List1;
class List2;

namespace Ui {
class MainWindow;
}


class List1
{
public:
    int info;
    List1 *next;
    List2 *down;
};
class List2
{
public:
    int info;
    List1 *back;
    List2 *next;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:
     List1       *Head, *current;
    int state;

private:
    Ui::MainWindow *ui;

private slots:

    void insertEven(List1 **, int);
    void insertUneven(List1 **, int);
    void on_addElements_clicked();
    void on_down_clicked();
    void on_first_clicked();
    void on_next_clicked();
    void on_display_clicked();
    void on_refresh_clicked();
    void on_Help_triggered();
    void on_actionSave_triggered();
};

#endif // MAINWINDOW_H

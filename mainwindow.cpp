#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include <save.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Списочная структура");

    ui->Secondary->hide();
    ui->display->setDisabled(true);
    this->setFixedSize(415,120);

}

void MainWindow::insertEven(List1 **link, int x)
{
    List1 *list = *link;
    List1 *previous = 0;

    List2 *down;
    while (list!=0)
    {
        previous = list;
        list=list->next;
    }

    previous->info=x;

    List1 *cur = new List1;
    cur->down=0;
    cur->info=0;
    cur->next=0;
    previous->next=cur;
}


void MainWindow::insertUneven(List1 **link, int x)
{
    List1 *list=*link;
    List2 *listDown;

    while ((list->down)!=0)
    {
        listDown=list->down;
        list=list->next;
    }

    List2 *linkDown = new List2;
    linkDown->back=NULL;
    linkDown->next=0;
    linkDown->info=x;
    listDown->next=linkDown;
    list->down=listDown->next;
}

void MainWindow::on_addElements_clicked()
{

   QString sequence = ui->createEdit->text() + " ";
   int sequenceNum=0, count = 1;
   if (!sequence.isEmpty())
   {
       ui->display->setDisabled(false);
   }
   for (int i=0;  i <sequence.count(); i++ )
    {
       while (sequence[i] != ' ')
       {
           sequenceNum = (sequence[i] +"").toInt();
           i++;
       }
       if  (count == 1)
       {
            Head = new List1;
            Head->next=NULL;
            Head->down=NULL;
            Head->info=0;

            List2 *list = new List2;
            list->info=sequenceNum;
            list->back=NULL;
            list->next=NULL;
            Head->down=list;
        }
        else if ( (count % 2) == 0)
        {
             insertEven(&Head,sequenceNum);
        }
        else
        {
             insertUneven(&Head,sequenceNum);
        }
    count++;
   }
   current=Head;state=1;
}

void MainWindow::on_first_clicked()
{
    ui->value->setText(QString::number(Head->info));
    current=Head;
    state = 1;
    ui->next->setDisabled(false);
   on_display_clicked();
}

void MainWindow::on_down_clicked()
{
    state = 0;
    if (current->down)
    ui->value->setText(QString::number(current->down->info));
   on_display_clicked();
}

void MainWindow::on_next_clicked()
{

    if (state == 1)
    {
        current=current->next;
        if (current->info!=0)
        {
            ui->value->setText( QString::number(current->info));
        }
        else  ui->next->setDisabled(true);
   }
   else if (state == 0)
    {
        current=current->next;
        if (current && current->down)
        {
            ui->value->setText( QString::number(current->down->info));
            state =0;
        }
         else ui->next->setDisabled(true);
    }
   on_display_clicked();
}

void MainWindow::on_display_clicked()
{
     this->setFixedSize(415,248);
     List1 *sequence = Head;
     QString seq = ""; QString seqDown = "", array="", array1="";
     if (sequence->down)
        if (sequence==current &&  state==0)
            seqDown=  seqDown + "<code> <strong>" + QString::number(sequence->down->info) + "</strong></code>" ;
        else
           seqDown=  seqDown + QString::number(sequence->down->info);
        if (sequence)
            if ( sequence == current &&  state == 1)
            {   seq=  seq + "<code><strong>" + QString::number(sequence->info) + "</strong></code>"; }
            else
            {    seq=  seq + QString::number(sequence->info); }
            if (sequence->next)
            {
                sequence=sequence->next;
                while (sequence->next)
                {
                    if (sequence==current && state == 1)
                        seq= seq+ "->" + "< code><strong>" + QString::number(sequence->info) + "</strong></code>" ;
                    else
                        seq=  seq + "->" + QString::number(sequence->info) ;
                    if (sequence==current &&  state ==0)
                        seqDown=  seqDown +"->" + "< code><strong>" + QString::number(sequence->down->info) + "</strong></code>" ;
                    else
                        seqDown=  seqDown + "->" +QString::number(sequence->down->info);
                    sequence=sequence->next;
                }
                if (sequence->down)
                    (sequence==current &&  state ==0) ? seqDown= seqDown +"->" + "< code><strong>" + QString::number(sequence->down->info) + "</strong></code>" : seqDown= seqDown + "->" +QString::number(sequence->down->info);
      }
       ui->textBrowser->setText("<br>" + seq + "<br>" + array + "<br>" +array1+ "<br>" + seqDown);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Help_triggered()
{
    Dialog dialog;
    dialog.setWindowFlags(Qt::WindowFullscreenButtonHint);
    dialog.exec();
}

void MainWindow::on_refresh_clicked()
{
    on_display_clicked();
}

void MainWindow::on_actionSave_triggered()
{
    QString pathF;
    this->setFixedSize(415,248);
    List1 *list = Head;

    QString seq = "", seqDown = "";
    if (list->down)
        seqDown=  seqDown + QString::number(list->down->info);
    if (list)
        seq=  seq + QString::number(list->info);
    if (list->next)
    {
        list=list->next;
        while (list->next)
        {
              seq=  seq + "->" + QString::number(list->info) ;
              seqDown=  seqDown + "->" +QString::number(list->down->info);
              list=list->next;
        }
        if (list->down)
            seqDown=  seqDown + "->" +QString::number(list->down->info);
     }
     Save save;
     save.setWindowFlags(Qt::WindowFullscreenButtonHint);
     save.saveSeq( seq + "\n" + seqDown);
     save.exec();
}

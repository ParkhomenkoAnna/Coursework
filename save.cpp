#include "save.h"
#include "ui_save.h"
#include <QDir>
#include <QFileSystemModel>
#include <QFileInfo>
#include <iostream>
#include <mainwindow.h>

using namespace std;

Save::Save(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Save)
{
    ui->setupUi(this);
    this->setWindowTitle("Сохранить");
    connect( ui->cancel,SIGNAL(clicked(bool)), this, SLOT(close()));
    mdlDir = new QFileSystemModel(this);
    mdlDir->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    mdlDir->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    mdlDir->setRootPath("~/");

    ui->listView->setModel(mdlDir);
    QModelIndex idx = mdlDir->index("~/");
    ui->listView->setRootIndex(idx);
    filePath = mdlDir->filePath(idx);;
}


void Save::on_listView_clicked(const QModelIndex &index)
{
    ui->treeView->setModel(mdlDir);
    ui->treeView->setRootIndex(index);
    ui->label_3->setText( mdlDir->filePath(index));
    filePath = mdlDir->filePath(index);
}

Save::~Save()
{
    delete ui;
}

void Save::on_treeView_clicked(const QModelIndex &index)
{
    ui->treeView->setModel(mdlDir);
    ui->treeView->setRootIndex(index);
    ui->label_3->setText( mdlDir->filePath(index));
    filePath = mdlDir->filePath(index);
}

void Save::on_save_clicked()
{
    filePath = filePath + "/" + ui->lineEdit->text() + ".txt";
    QFile *file = new QFile(filePath);
    file->open(QIODevice::WriteOnly);
    file->write(fileContent.toUtf8());
    file->close();
    close();
}

void Save::on_createDir_clicked()
{
    QDir dir(filePath);
    QModelIndex idx = mdlDir->index(filePath);
    dir.mkdir(filePath+"/New Dir");

}

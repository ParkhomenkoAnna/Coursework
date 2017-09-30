#ifndef SAVE_H
#define SAVE_H

#include <QDialog>
#include <QDirModel>
#include <QTreeWidget>
#include <QFileSystemModel>


namespace Ui {
class Save;
}

class Save : public QDialog
{
    Q_OBJECT

public:
    explicit Save(QWidget *parent = 0);
    ~Save();

    QString  filePath;
    void saveSeq(QString seq)
    {
        fileContent=seq;
    }

private slots:

    void on_listView_clicked(const QModelIndex &index);
    void on_treeView_clicked(const QModelIndex &index);
    void on_save_clicked();
    void on_createDir_clicked();
private:


    QFileSystemModel *mdlDir;
    QString fileContent;
    Ui::Save *ui;
};

#endif // SAVE_H

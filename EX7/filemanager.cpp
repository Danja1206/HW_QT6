#include "filemanager.h"
#include <QDir>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTreeView>
#include "mainwindow.h"
FileManager::FileManager(QWidget *parent) : QWidget(parent)
{
    QString sPath = "C:/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);

    gridLay = new QGridLayout(this);
    this->setLayout(gridLay);
    tree = new QTreeView(this);
    gridLay->addWidget(tree, 1, 0, 10, 10);
    setMinimumSize(500, 300);
    tree->setModel(dirmodel);
    QObject::connect(tree,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(test(QModelIndex)));

}

void FileManager::test(const QModelIndex& index)
{
    filePath = dirmodel->fileInfo(index).absoluteFilePath();
    static_cast<MainWindow*>(this->parent())->openFileTest(filePath);

}
void FileManager::show()
{
   tree->show();
}

void FileManager::hide()
{
   tree->hide();
}

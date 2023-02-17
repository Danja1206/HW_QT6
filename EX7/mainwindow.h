#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filemanager.h"
#include <QMdiArea>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void openFileTest(QString path);
    QMdiSubWindow *active;


protected:
    virtual void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void createFile();

    void openFile();

    void saveFile();

    void info();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void changeTheme();

    void changeLanguage();

    void printDocs();


private:
    Ui::MainWindow *ui;
    QShortcut *key1;
    QShortcut *key2;
    QShortcut *key3;
    QShortcut *key4;
    FileManager *fileManager;
    QMdiArea *mdiArea;

};
#endif // MAINWINDOW_H

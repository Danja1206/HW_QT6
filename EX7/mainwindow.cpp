#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QShortcut>
#include <QTranslator>
#include "filemanager.h"
#include <QtPrintSupport/QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include <QMenu>
#include <QMdiArea>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label->hide();
    MainWindow::key4 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    MainWindow::key2 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(openFile()));
    MainWindow::key1 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), this, SLOT(createFile()));
    MainWindow::key3 = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this, SLOT(saveFile()));
    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
    ui->pushButton_8->hide();
    ui->pushButton_7->hide();
    ui->pushButton_6->hide();
    MainWindow::fileManager = new FileManager(this);
    fileManager->hide();

    QGridLayout *lt = new QGridLayout();
    QMenu*   fileMenu   = new QMenu(tr("Файл"));
    QMenu*   settingsMenu   = new QMenu(tr("Настройки"));
    QAction *choose =settingsMenu->addAction("Светлая тема", this, SLOT(changeTheme()));
    choose->setCheckable(true);
    choose->setChecked(true);
    QAction *chooseLanguage =settingsMenu->addAction("Русский язык", this, SLOT(changeLanguage()));
    chooseLanguage->setCheckable(true);
    chooseLanguage->setChecked(true);
    chooseLanguage->setEnabled(false);
    QAction *openFile =fileMenu->addAction("Открыть файл", this, SLOT(openFile()));
    QAction *createFile =fileMenu->addAction("Создать файл", this, SLOT(createFile()));
    QAction *saveFile =fileMenu->addAction("Сохранить файл как", this, SLOT(saveFile()));
    QAction *printFile =fileMenu->addAction("Печать", this, SLOT(printDocs()));

    fileMenu->addAction("Выйти", qApp, SLOT(quit()));
    QMenuBar *mb = new QMenuBar;
    mb->addMenu(fileMenu);
    mb->addMenu(settingsMenu);
    mb->addSeparator();
    QAction *info =mb->addAction("?", this, SLOT(info()));

    lt->setMenuBar(mb);

    mdiArea = new QMdiArea(this);
    QWidget *wgt = new QWidget(this);
    setCentralWidget(wgt);
    wgt->setLayout(lt);
    lt->addWidget(mdiArea,1,0,10,1);
    mdiArea->addSubWindow(ui->plainTextEdit);
    mdiArea->addSubWindow(new QPlainTextEdit(this));


}

MainWindow::~MainWindow()
{
    delete ui;
}

QString path;
int changeID;

void MainWindow::on_pushButton_clicked()
{
    //openFile();
    ui->plainTextEdit->setReadOnly(0);

}

void MainWindow::on_pushButton_2_clicked()
{
    saveFile();
}

void MainWindow::on_pushButton_3_clicked()
{
    info();
}

void MainWindow::info()
{
    QFile file(":/infoTxt/FAO.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray ba = file.readAll();
        QString text(ba);
            QMessageBox::about(this,"",text);
    }
}

void MainWindow::createFile()
{
    QWidget *wid = mdiArea->activeSubWindow()->widget();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Создать файл"),path, "*.txt");
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        QString text = ((QPlainTextEdit*)wid)->toPlainText();
        QByteArray ba = text.toUtf8();
        file.write(ba,ba.length());
    }

}

void MainWindow::openFile()
{
    QWidget *wid = mdiArea->activeSubWindow()->widget();
    path = QFileDialog::getOpenFileName(this,"Открыть файл", QDir::currentPath(), "*.txt");
    if(path.isEmpty()) return;
    ((QPlainTextEdit*)wid)->setWindowTitle(path);
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray ba = file.readAll();
        QString text(ba);
        ((QPlainTextEdit*)wid)->setPlainText(text);
    }
}

void MainWindow::saveFile()
{
    QWidget *wid = mdiArea->activeSubWindow()->widget();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить файл как"),path, "*.txt;;*.html");
    if(fileName.isEmpty()) return;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        QString text = ((QPlainTextEdit*)wid)->toPlainText();
        QByteArray ba = text.toUtf8();
        file.write(ba,ba.length());
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    //openFile();
    ui->plainTextEdit->setReadOnly(1);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->pushButton_10->show();
    ui->pushButton_9->show();
    ui->pushButton_8->show();
    ui->pushButton_7->show();
    ui->pushButton_6->show();
    ui->pushButton_5->hide();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    bool check = false;
    switch (changeID) {
    case 1:
        delete key1;
        MainWindow::key1 = new QShortcut(QKeySequence(event->key()), this, SLOT(createFile()));
        check = true;
        break;
    case 2:
        delete key2;
        MainWindow::key2 = new QShortcut(QKeySequence(event->key()), this, SLOT(openFile()));
        check = true;
        break;
    case 3:
        delete key3;
        MainWindow::key3 = new QShortcut(QKeySequence(event->key()), this, SLOT(saveFile()));
        check = true;
        break;
    case 4:
        delete key4;
        MainWindow::key4 = new QShortcut(QKeySequence(event->key()), this, SLOT(close()));
        check = true;
        break;
    }
    changeID = 0;
    if(check)
        QMessageBox::about(this,"Обновление сочетания клавиш","Сочетание изменено!");
}

void MainWindow::on_pushButton_9_clicked()
{
    changeID = 1;
}

void MainWindow::on_pushButton_8_clicked()
{
    changeID = 2;
}

void MainWindow::on_pushButton_6_clicked()
{
    changeID = 3;
}

void MainWindow::on_pushButton_10_clicked()
{
    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
    ui->pushButton_8->hide();
    ui->pushButton_7->hide();
    ui->pushButton_6->hide();
    ui->pushButton_5->show();
}
bool isTranslated = false;
void MainWindow::on_pushButton_11_clicked()
{
    changeLanguage();
}

void MainWindow::changeLanguage()
{
    QTranslator translator;
    if(!isTranslated)
    {
    translator.load(":/tr/QtLanguage_en.qm");
    qApp->installTranslator(&translator);
    //ui->retranslateUi(this);
    isTranslated = true;
    }
    else
    {
        translator.load(":/tr/QtLanguage_ru.qm");
        qApp->installTranslator(&translator);
        isTranslated = false;
    }
    ui->retranslateUi(this);
}

bool isDarkTheme = false;

void MainWindow::on_pushButton_12_clicked()
{
    if(isDarkTheme)
    {
        this->setStyleSheet("QMainWindow{background-color:white} QPlainTextEdit{background-color:white;}");
        isDarkTheme = false;
        ui->pushButton_12->hide();
        ui->pushButton_14->show();
    }
   // ui->retranslateUi(this);
}
bool isFileManagerOpen = false;

void MainWindow::on_pushButton_13_clicked()
{

    if(!isFileManagerOpen)
    {
       fileManager->show();
       isFileManagerOpen = true;
    }
    else
    {
       fileManager->hide();
       isFileManagerOpen = false;
    }
}

void MainWindow::openFileTest(QString path)
{
    ui->label->setText(path);
    ui->label->show();
    QFileInfo flInfo(path);
    if(flInfo.isFile())
    {
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray ba = file.readAll();
        QString text(ba);
        ui->plainTextEdit->setPlainText(text);
        fileManager->hide();
        isFileManagerOpen = false;
    }
    }
}

void MainWindow::on_pushButton_14_clicked()
{
    if(!isDarkTheme)
    {
        this->setStyleSheet("QMainWindow{background-color:black} QPlainTextEdit{background-color:black; color:white}");
        isDarkTheme = true;
        ui->pushButton_12->show();
        ui->pushButton_14->hide();
    }
}

void MainWindow::changeTheme()
{
    if(isDarkTheme)
    {
        this->setStyleSheet("QGridLayout{background-color:white} QPlainTextEdit{background-color:white;}");
        isDarkTheme = false;
    }
    else
    {
        this->setStyleSheet("QMainWindow{background-color:black} QPlainTextEdit{background-color:black; color:white}");
        isDarkTheme = true;
    }
   // ui->retranslateUi(this);
}

void MainWindow::on_pushButton_15_clicked()
{
   printDocs();
}

void MainWindow::printDocs()
{

    QWidget *wid = mdiArea->activeSubWindow()->widget();
    QPlainTextEdit* text = ((QPlainTextEdit*)wid);
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle("Print");
    if (dlg.exec() != QDialog::Accepted)
    return;
    text->print(&printer);

}

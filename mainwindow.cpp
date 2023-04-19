#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <QSystemTrayIcon>
#include <QDir>
#include <QDate>

using namespace std;

struct info
{
    int day = 0;
    int month = 0;
    int year = 0;
    string str = "";
};

struct DATA
{
    int day;
    int month;
    int year = 0;
} today;


vector<info> ReadFromFile(char* file)
{
    vector<info>telBook;
    QDir dir = QDir::currentPath();
    QString rootPath = dir.absolutePath();
    QString str1 = QDir::toNativeSeparators(QCoreApplication::applicationDirPath());
    QByteArray ba = str1.toLocal8Bit();
    char *c_str2 = ba.data();
    strcat(c_str2, file);
    const char* filename = c_str2;
    info one;

    ifstream in(filename);
    if (!in)
    {
        cerr << "file can't founded.";
        exit(0);
    }
    while (!in.eof())
    {
        in >> one.day;
        in >> one.month;
        in >> one.year;
        getline(in,one.str);
        telBook.push_back(one);
    }
    in.close();
    return telBook;
}

bool checkEndOfMonth(DATA d,info inf){
    if(d.month==1 or d.month ==3 or d.month==5 or d.month==7 or d.month==8 or d.month==10 or d.month==12){
        if(d.day==31 && inf.day==1 && inf.month%12==1 && d.month ==12 ){
            return true;
        }else{
            return false;
        }
    }else if(d.month==2 && inf.month==3 && d.day==28 && inf.day==1){
        return true;
    }else if((d.year%4==0)&&(d.month==2 && inf.month==3 && d.day==29 && inf.day==1)){
        return true;
    }else{
        if(d.day==30 && inf.day==1 && inf.month==d.month+1){
          return true;
         }else{
            return false;
        }
    }
}

void GetCurrentTime()
{
    QDate current = QDate::currentDate();
    today.day = current.day();
    today.month = current.month();
    today.year = current.year();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
        ui->setupUi(this);
        popUp = new PopUp();
        vector<info>telBook = ReadFromFile("\\Birthday(from).txt");
        GetCurrentTime();
        QString s;
        QString tomorrow;
        QString qstr;
        QString tqstr;
            for (unsigned int i = 0; i < telBook.size(); i++)
            {
                if (today.day == telBook[i].day && today.month == telBook[i].month)
                {
                    int currentAge = (int)today.year -  (int)telBook[i].year;

                    if (currentAge % 10 == 1 && currentAge % 100 != 11) {
                            s+= QString::number(currentAge) + QString::fromStdString(" год исполняется") + QString::fromStdString(telBook[i].str) + "\n";
                        } else if (currentAge % 10 >= 2 && currentAge % 10 <= 4 && (currentAge % 100 < 10 || currentAge % 100 >= 20)) {
                            s+= QString::number(currentAge) + QString::fromStdString(" года исполняется") + QString::fromStdString(telBook[i].str) + "\n";
                        } else {
                            s+= QString::number(currentAge) + QString::fromStdString(" лет исполняется") + QString::fromStdString(telBook[i].str) + "\n";
                        }
                }
                if((today.day+1==telBook[i].day && today.month == telBook[i].month) || checkEndOfMonth(today, telBook[i])){
                    int currentAge = (int)today.year -  (int)telBook[i].year;

                    if (currentAge % 10 == 1 && currentAge % 100 != 11) {
                            tomorrow += QString::number(currentAge) + QString::fromStdString(" год исполняется") + QString::fromStdString(telBook[i].str) + "\n";
                        } else if (currentAge % 10 >= 2 && currentAge % 10 <= 4 && (currentAge % 100 < 10 || currentAge % 100 >= 20)) {
                            tomorrow += QString::number(currentAge) + QString::fromStdString(" года исполняется") + QString::fromStdString(telBook[i].str) + "\n";
                        } else {
                            tomorrow += QString::number(currentAge) + QString::fromStdString(" лет исполняется") + QString::fromStdString(telBook[i].str) + "\n";
                        }
                }
            }
            if(s!=""){
                 qstr = s;

            }else{
                 qstr = QString::fromStdString("Отсутствуют");
            }
            if(tomorrow!=""){
                tqstr = tomorrow;
            }else{
                tqstr = QString::fromStdString("Отсутствуют");
           }

        popUp->setPopupText(qstr, tqstr);
        popUp->setStyleSheet(QString("font-size: %1px; color:white; background: rgba(0,0,0,0.5); margin: 0; padding:0; border-top:2px solid white").arg(16));
        popUp->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

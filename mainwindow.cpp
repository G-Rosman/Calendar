#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <QSystemTrayIcon>
#include <QDir>

using namespace std;

struct info
{
    int day = 0;
    int month = 0;
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
    time_t rawtime;
    struct tm* timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    today.day = timeinfo->tm_mday;
    today.month =timeinfo->tm_mon + 1;
    today.year = timeinfo->tm_year;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
        ui->setupUi(this);
        popUp = new PopUp();
        vector<info>telBook = ReadFromFile("\\Birthday(from).txt");
        GetCurrentTime();
        string s;
        string tomorrow;
        QString qstr;
        QString tqstr;
            for (unsigned int i = 0; i < telBook.size(); i++)
            {
                if (today.day == telBook[i].day && today.month == telBook[i].month)
                    s+= telBook[i].str + "\n";
                if((today.day+1==telBook[i].day && today.month == telBook[i].month) || checkEndOfMonth(today, telBook[i])){
                    tomorrow+=telBook[i].str + "\n";
                }
            }
            if(s!=""){
                 qstr = QString::fromStdString(s);

            }else{
                 qstr = QString::fromStdString("Отсутствуют");
            }
            if(tomorrow!=""){
                tqstr = QString::fromStdString(tomorrow);
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

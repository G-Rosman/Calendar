#include "popup.h"
#include <QPainter>
#include <QApplication>
#include <QDir>
#include <QDesktopWidget>
#include <QMessageBox>
#include <fstream>
#include <string.h>

using namespace std;
struct info2
{
    int day = 0;
    int month = 0;
    string str = "";
};

PopUp::PopUp(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );// |        // Отключаем оформление окна
      //             Qt::Tool |                       // Отменяем показ в качестве отдельного окна
        //           Qt::WindowStaysOnTopHint);       // Устанавливаем поверх всех окон
    setAttribute(Qt::WA_TranslucentBackground);     // Указываем, что фон будет прозрачным
    setAttribute(Qt::WA_ShowWithoutActivating);     // При показе, виджет не получается фокуса автоматически

    animation.setTargetObject(this);                // Устанавливаем целевой объект анимации
    animation.setPropertyName("popupOpacity");      // Устанавилваем анимируемое свойство
    connect(&animation, &QAbstractAnimation::finished, this, &PopUp::hide);

    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // Устанавилваем по центру
    label1.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // Устанавилваем по центру
    Button.setAlignment(Qt::AlignCenter);
    Button2.setAlignment(Qt::AlignCenter);
    Button3.setAlignment(Qt::AlignCenter);

    NewText.setStyleSheet("padding:10px");
    label.setStyleSheet("padding:10px");
    label1.setStyleSheet("padding:10px");
    h1.setStyleSheet("padding:10px");
    h2.setStyleSheet("padding:10px");
    Button.setStyleSheet("padding: 10px");
    Button.setStyleSheet("background-color: rgb(50, 50, 50)");
    Button.setText("<h3>Добавить дату</h3>");

    Button2.setStyleSheet("padding: 10px");
    Button2.setStyleSheet("background-color: rgb(50, 50, 50)");
    Button2.setText("<h3>Увидеть все данные</h3>");

    Button3.setStyleSheet("padding: 10px");
    Button3.setStyleSheet("background-color: rgb(50, 50, 50)");
    Button3.setText("<h3>Пересохранить файл</h3>");


    //NewText.setFixedSize(510,100);
    //h1.setFixedHeight(100);
    //h2.setFixedHeight(100);
    //label.setFixedHeight(100);
    //label1.setFixedHeight(100);
    NewText.setFixedHeight(75);
    Button.setFixedHeight(75);
    Button2.setFixedHeight(50);
    Button3.setFixedHeight(50);
    NewText.setStyleSheet("background-color: rgb(80, 80, 80)");

    layout.setSpacing(0);
    layout.addWidget(&h1, 0, 0);
    layout.addWidget(&label, 0, 1);
    layout.addWidget(&h2, 1, 0);
    layout.addWidget(&label1, 1, 1);
    layout.addWidget(&Button, 2, 0,1,1);
    layout.addWidget(&NewText, 2, 1,1,1);
    layout.addWidget(&Button2,3,0,1,2);
    layout.addWidget(&Button3,4,0,1,2);
    setLayout(&layout);

    // По сигналу таймера будет произведено скрытие уведомления, если оно видимо
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &PopUp::hideAnimation);
}

void PopUp::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Включаем сглаживание

    // Подготавливаем фон. rect() возвращает внутреннюю геометрию виджета уведомления, по содержимому
    QRect roundedRect;
    roundedRect.setX(rect().x() + 1);
    roundedRect.setY(rect().y() + 1);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);
    QString str1 = QDir::toNativeSeparators(QCoreApplication::applicationDirPath());
    QByteArray ba = str1.toLocal8Bit();
    char *c_str2 = ba.data();
    strcat(c_str2, "\\rf.jpg");
    QPixmap qp(c_str2);
    painter.setBrush(QBrush(qp.scaled(QSize(this->width(), this->height()), Qt::IgnoreAspectRatio, Qt::FastTransformation)));
    painter.setPen(Qt::NoPen); // Край уведомления не будет выделен
    painter.setOpacity(0.9);

    // Отрисовываем фон с закруглением краёв в 10px
    painter.drawRoundedRect(roundedRect, 5, 5);
}

void PopUp::setPopupText(const QString &text,const QString &text1)
{
    label.setText(text);
    label1.setText(text1);
    QString s1=QString::fromStdString("<h3>События сегодня</h3>");
    QString s2=QString::fromStdString("<h3>События завтра</h3>");
    h1.setText(s1);
    h2.setText(s2);
    adjustSize();
}

void PopUp::show()
{
    setWindowOpacity(0.0);
    animation.setDuration(150);     // Настравиваем длительность анимации
    animation.setStartValue(0.0);   // Стартовое значение будет 0 (полностью прозрачный виджет)
    animation.setEndValue(1.0);     // Конечное - полностью непрозрачный виджет

    setGeometry(QApplication::desktop()->availableGeometry().width()/4 +
                QApplication::desktop() -> availableGeometry().x(),
                QApplication::desktop()->availableGeometry().height()/4 + QApplication::desktop() -> availableGeometry().y(),
                          width()+400,
                          height()*1.5);
    QWidget::show();                // Отображаем виджет, который полностью прозрачен

    animation.start();              // И запускаем анимацию
    timer->start(900000000);
}

void PopUp::hideAnimation()
{
    timer->stop();                  // Останавлвиваем таймер
    animation.setDuration(1000);    // Настравиваем длительность анимации
    animation.setStartValue(1.0);   // Стартовое значение будет 1 (полностью непрозрачный виджет)
    animation.setEndValue(0.0);     // Конечное - полностью прозрачный виджет
    animation.start();              // И запускаем анимацию
}

void PopUp::hide()
{
    // Если виджет прозрачный, то скрываем его
    if(getPopupOpacity() == 0.0){
        QWidget::hide();
        exit(1);
    }
}

void PopUp::setPopupOpacity(float opacity)
{
    popupOpacity = opacity;

    setWindowOpacity(opacity);
}


float PopUp::getPopupOpacity() const
{
    return popupOpacity;
}

void FileWrite(string str)
{
     ofstream out;
     QDir dir = QDir::currentPath();
     QString rootPath = dir.absolutePath();
     QString str1 = QDir::toNativeSeparators(QCoreApplication::applicationDirPath());
     QByteArray ba = str1.toLocal8Bit();
     char *c_str2 = ba.data();
     strcat(c_str2, "\\Birthday(from).txt");
     const char* filename = c_str2;
     out.open(filename, std::ios::app);
     out << "\n" + str;
}
bool PopUp::Check_and_Write()
{
    info2 NewData;
    try {
        NewData.day = NewText.toPlainText().split(" ")[0].toInt();
        NewData.month  = NewText.toPlainText().split(" ")[1].toInt();
        NewData.str = (NewText.toPlainText().toUtf8().constData());
        if (NewData.day>0 and NewData.day<32 and NewData.month>0 and NewData.month<13 and NewData.str.length())
        {
            FileWrite(NewData.str);
            QMessageBox messageBox;
            messageBox.information(this,"Success", NewText.toPlainText() + " - Событие добавлено");
            messageBox.setWindowFlags(Qt::WindowStaysOnTopHint);
            messageBox.setFixedSize(500,200);
            return 1;
        }
        else
            throw(NewText.toPlainText());
}
    catch(QString str)
    {
        QMessageBox messageBox;
        messageBox.critical(this,"Error", str + " - is not valid");
        messageBox.setWindowFlags(Qt::WindowStaysOnTopHint);
        messageBox.setFixedSize(500,200);
        return 0;
    }
}

void Clickable::mousePressEvent(QMouseEvent* event)
{
    QWidget::mousePressEvent(event);
    PopUp* pPopUp = qobject_cast<PopUp*>(parent());
    pPopUp->Check_and_Write();
}

void Lable::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    PopUp* pPopUp = qobject_cast<PopUp*>(parent());
    pPopUp->hideAnimation();
}
void FileCheck::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    QDir dir = QDir::currentPath();
    QString rootPath = dir.absolutePath();
    QString str1 = QDir::toNativeSeparators(QCoreApplication::applicationDirPath());
    QByteArray ba = str1.toLocal8Bit();
    char *c_str2 = ba.data();
    strcat(c_str2, "\\Birthday(from).txt");
    const char* filename = c_str2;
    QFile f1(filename);
    f1.open(QIODevice::ReadOnly | QIODevice::Text);
    QString s = f1.readAll();
    PopUp* pPopUp = qobject_cast<PopUp*>(parent());
    pPopUp->Text.setPlainText("");
    pPopUp->Text.appendPlainText(s);
    pPopUp->Text.setFixedSize(500,500);
    pPopUp->Text.setWindowFlags(Qt::WindowStaysOnTopHint);
    pPopUp->Text.show();
}
void FileSave::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    fstream ofs;
    QDir dir = QDir::currentPath();
    QString rootPath = dir.absolutePath();
    QString str1 = QDir::toNativeSeparators(QCoreApplication::applicationDirPath());
    QByteArray ba = str1.toLocal8Bit();
    char *c_str2 = ba.data();
    strcat(c_str2, "\\Birthday(from).txt");
    const char* filename = c_str2;
    ofs.open(filename, ios::out | ios::trunc);
    ofs.close();

    QFile out( filename );
    if( out.open( QIODevice::WriteOnly ) )
    {
        QTextStream stream( &out );
        stream.setCodec("UTF-8");
        PopUp* pPopUp = qobject_cast<PopUp*>(parent());
        stream << pPopUp->Text.toPlainText();
        out.close();
     }
}

#ifndef POPUP_H
#define POPUP_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QFile>
#include <QDataStream>

class FileSave :public QLabel
    {
        Q_OBJECT
    signals:
    public:
        void mousePressEvent(QMouseEvent* event);
        using QLabel::QLabel;
    };
class Clickable :public QLabel
    {
        Q_OBJECT
    signals:
    public:
        void mousePressEvent(QMouseEvent* event);
        using QLabel::QLabel;
    };
class FileCheck :public QLabel
    {
        Q_OBJECT
    signals:
    public:
        void mousePressEvent(QMouseEvent* event);
        using QLabel::QLabel;
    };
class Lable :public QLabel
    {
        Q_OBJECT
    signals:
    public:
        void mousePressEvent(QMouseEvent* event);
        using QLabel::QLabel;
    };


class PopUp : public QWidget
{
    Q_OBJECT
    // Свойство полупрозрачности
    Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

    void setPopupOpacity(float opacity);
    float getPopupOpacity() const;

public:
    explicit PopUp(QWidget *parent = 0);
    QGridLayout layout;     // Размещение для лейбла
    QPlainTextEdit Text;
protected:
    void paintEvent(QPaintEvent *event);    // Фон будет отрисовываться через метод перерисовки

public slots:
    void setPopupText(const QString& text,const QString &text1); // Установка текста в уведомление
    void show();
    bool Check_and_Write();
    void hideAnimation();                   // Слот для запуска анимации скрытия

private slots:
    void hide();                            /* По окончании анимации, в данном слоте делается проверка,
                                           * виден ли виджет, или его необходимо скрыть
                                             * */
private:
    Lable label;
    Lable label1;
    Lable h1;
    Lable h2;
    Clickable Button;
    FileCheck Button2;
    FileSave Button3;

    QPropertyAnimation animation;   // Свойство анимации для всплывающего сообщения
    float popupOpacity;     // Свойства полупрозрачности виджета
    QTimer *timer;          // Таймер, по которому виджет будет скрыт
    QTextEdit NewText;
};

#endif // POPUP_H

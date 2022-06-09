#ifndef NEWLINEEDIT_H
#define NEWLINEEDIT_H
//можно удалить
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QLineEdit>

class NewLineEdit :public QLineEdit
{
    //Q_OBJECT
public:
    NewLineEdit();
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // NEWLINEEDIT_H

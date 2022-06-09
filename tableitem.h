#ifndef TABLEITEM_H
#define TABLEITEM_H
//один ряд модели, элемент Hash
#include <QObject>
#include <QWidget>
#include <QString>

class TableItem
{
    //Q_OBJECT
public:
    TableItem();
    int PersonalID;
    QString Name, PhoneNumber, WorkplacePosition;
    TableItem(int PersonalID, QString Name, QString PhoneNumber, QString WorkplacePosition);
};

#endif // TABLEITEM_H

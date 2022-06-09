#ifndef MODEL_USERTABLEJSON_H
#define MODEL_USERTABLEJSON_H

#endif // MODEL_USERTABLEJSON_H

#include <tableitem.h>//добавляемый в QHash элемент

#include <QAbstractItemModel> //работа с QHash
#include <QAbstractTableModel>
#include <QHash>

#include <QJsonDocument>//работа с файлами
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QFileDialog>


class ModelUserTableJSON : public QAbstractTableModel
{
    Q_OBJECT
public:
    ModelUserTableJSON();

    int rowCount(const QModelIndex &parent) const;//количество строк
    int columnCount(const QModelIndex &parent) const;//количество столбцов
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int,TableItem*> getHash();

    void setHash(QHash<int,TableItem*> Hash);

    void addTableItem(TableItem *newTableItem);

    void removeTableRows(int selectedRow);

    void editTableItem(TableItem *newTableItem, int selectedRow);
    QFile file();

    static bool load(const QString& fileName, ModelUserTableJSON & model);
    static bool save(const QString& fileName, const ModelUserTableJSON & model);



private:
    QHash<int, TableItem*> Hash;//массив
};

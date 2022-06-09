#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Model_UserTableJSON.h>
//файл формы
#include <QMainWindow>
#include <QStringListModel>
#include <QDebug>
#include <QItemSelectionModel>
#include <qitemselectionmodel.h>
#include <QAbstractTableModel>
#include <QAbstractItemModel>

#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ModelUserTableJSON *model;
    //кнопка - добавить
    void addNewEntryToModel(QString name, QString phone, QString workplace_position);
    //кнопка - удалить
    void deleteEntryFromModel();
    //кнопка - изменить элемент
    void editEntryInModel(int selectedRow, QString name, QString phone, QString workplace_position);
public  slots:
        void  load();
        void  save();
private slots:
    void onClick();
    void onClick_Delete();
    void onClick_Edit();



    void clearForm();
    void onKeyUp(QString text);
};
#endif // MAINWINDOW_H

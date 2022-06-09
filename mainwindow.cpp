#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new ModelUserTableJSON();
    ui->tableView->setModel(model);

    //присоединение кнопок и методов
    connect(ui->pushButton_AddNewEntry, &QPushButton::clicked,
                                        this, &MainWindow::onClick);
    connect(ui->pushButton_DeleteEntry, &QPushButton::clicked,
                                        this, &MainWindow::onClick_Delete);
    connect(ui->pushButton_ChangeEntry, &QPushButton::clicked,
                                        this, &MainWindow::onClick_Edit);
    connect(ui->pushButton_LoadFromFile,&QPushButton::clicked,
                                        this, &MainWindow::load);
    connect(ui->pushButton_SaveToFile,  &QPushButton::clicked,
                                        this, &MainWindow::save);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewEntryToModel(QString name, QString phone, QString workplace_position)
{   //добавление нового элемента
    model->addTableItem(new TableItem(NULL,name, phone, workplace_position));
}

void MainWindow::deleteEntryFromModel()
{

}

void MainWindow::editEntryInModel(int selectedRow, QString name, QString phone, QString workplace_position)
{//изменение элемента
    model->editTableItem(new TableItem(NULL,name, phone, workplace_position),selectedRow);
}

void MainWindow::load()
{   //диалоговое окно выбора файла
    qDebug()<<"Loading... -------------";
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName.isEmpty()){return;}

    ModelUserTableJSON::load(fileName, *model);
    qDebug()<<"File name (MainWindow):"<<fileName;
}

void MainWindow::save()
{
    qDebug()<<"Saving... -------------";
    QString fileName = QFileDialog::getOpenFileName(this);
    if(fileName.isEmpty()){return;}

    ModelUserTableJSON::save(fileName, *model);
    qDebug()<<"File name (MainWindow):"<<fileName;
}

void MainWindow::onClick()
{   //кнопка добавления
    QString Name = ui->lineEdit_Name->text();
    QString Phone = ui->lineEdit_Phone->text();
    QString WorkplacePosition = ui->lineEdit_WorkplacePosition->text();

    ui->lineEdit_Name->clear();
    ui->lineEdit_Phone->clear();
    ui->lineEdit_WorkplacePosition->clear();

    addNewEntryToModel(Name,Phone,WorkplacePosition);
}

void MainWindow::onClick_Delete()
{
    qDebug()<<"Deletion... -------------";
    QItemSelectionModel *select = ui->tableView->selectionModel();

    if(select->hasSelection()==false)
    {
        qDebug()<<"No selection";
    }else
    {
        model->removeTableRows(select->selectedRows().data()->row());
    }
}

void MainWindow::onClick_Edit()
{
    QString Name = ui->lineEdit_Name->text();
    QString Phone = ui->lineEdit_Phone->text();
    QString WorkplacePosition = ui->lineEdit_WorkplacePosition->text();

    ui->lineEdit_Name->clear();
    ui->lineEdit_Phone->clear();
    ui->lineEdit_WorkplacePosition->clear();

    QItemSelectionModel *select = ui->tableView->selectionModel();

    if(select->hasSelection()==false)
    {
        qDebug()<<"No selection";
    }else{
        editEntryInModel(select->selectedRows().data()->row(),Name, Phone, WorkplacePosition);
    }
}

void MainWindow::clearForm()
{
}

void MainWindow::onKeyUp(QString text)
{
    qDebug()<<"onKeyUp:"<<text;
}


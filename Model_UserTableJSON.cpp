#include <Model_UserTableJSON.h>

ModelUserTableJSON::ModelUserTableJSON(){//конструктор
    //Hash.insert(1, new TableItem(1,"Sergei","+80000000","Programmer"));
    qDebug()<< Hash.isEmpty();
    qDebug() << Hash.size();
}

int ModelUserTableJSON::rowCount(const QModelIndex &parent) const{
    return Hash.size();
}

int ModelUserTableJSON::columnCount(const QModelIndex &parent) const{
    return 4;
}

QVariant ModelUserTableJSON::data(const QModelIndex &index, int role) const{
    if(role ==Qt::DisplayRole){//получение данных из модели
        if(index.isValid()){
            int row = index.row();
            int column = index.column();

            TableItem *tableitem = Hash.value(row);
//            if(!tableitem) {
//                return QVariant();
//            }

            if(column==0){
                return tableitem->PersonalID;
            };
            if(column==1){
                return tableitem->Name;
            };
            if(column==2){
                return tableitem->PhoneNumber;
            };
            if(column==3){
                return tableitem->WorkplacePosition;
            };
        }
    }else if (role == Qt::EditRole){

    }
    return QVariant();
}

QHash<int, TableItem*> ModelUserTableJSON::getHash(){
    return Hash;
}

void ModelUserTableJSON::setHash(QHash<int, TableItem *> Hash)
{
    beginResetModel();
    this->Hash = Hash;
    endResetModel();

}

void ModelUserTableJSON::addTableItem(TableItem *newTableItem)
{
    beginInsertRows(QModelIndex(),Hash.size(),Hash.size());

    int New_ID = Hash.size();//назначение ключа key - value
    newTableItem->PersonalID = New_ID;

    qDebug()<<"Name: "<<newTableItem->Name;

    Hash.insert(New_ID,newTableItem);

    qDebug()<< "Is empty? : "<<Hash.isEmpty();
    qDebug() << "Hash size: "<<Hash.size();
    endInsertRows();
}

void ModelUserTableJSON::removeTableRows(int selectedRow)//удаляет выбранный ряд
{
    qDebug() <<"Selected row: " << selectedRow;
    beginRemoveRows(QModelIndex(),selectedRow,selectedRow);
    Hash.remove(selectedRow);
    endRemoveRows();
    qDebug()<< "Is empty? : "<<Hash.isEmpty();
    qDebug() << "Hash size: "<<Hash.size();
    qDebug()<<"Deleted!";
}

void ModelUserTableJSON::editTableItem(TableItem *newTableItem, int selectedRow)
{   //редактирует весь выбранный ряд
    newTableItem->PersonalID = selectedRow;
    Hash[selectedRow] = newTableItem;
    setHash(Hash);
    qDebug()<<"Edited!";
}

bool ModelUserTableJSON::load(const QString &fileName, ModelUserTableJSON &model)
{
    QFile loadFile(fileName);
    qDebug()<<"Load function called -";
    if(!loadFile.open(QIODevice::ReadOnly)){
        qWarning("Couldn't open this file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
    QJsonObject json = loadDoc.object();

    model.Hash.clear();//очистка от старых элементов

    const int rowCount = json["rowCount"].toInt();
    const int columnCount = json["columnCount"].toInt();
    QJsonArray data = json["data"].toArray();

    for(int i = 0;i<rowCount;i++){
        QJsonArray row = data[i].toArray();

        model.addTableItem(new TableItem(   i,
                                            row[1].toString(),
                                            row[2].toString(),
                                            row[3].toString()
                                        ));
    }
    qDebug()<<"Loaded!  -------------";
    return true;
}

bool ModelUserTableJSON::save(const QString &fileName, const ModelUserTableJSON &model)
{
    QFile saveFile(fileName);
    qDebug()<<"Save function called -";
    if(!saveFile.open(QIODevice::WriteOnly)){
        qWarning("Couldn't open this file.");
        return false;
    }
    qDebug()<<"File name:"<<fileName;

    QJsonObject json;
    json["rowCount"] = model.Hash.size();
    json["columnCount"] = 4;

    QJsonArray data;
    for (int i = 0; i<model.Hash.size();i++){
        QJsonArray row;
        row.append(QJsonValue(model.Hash[i]->PersonalID));
        row.append(QJsonValue(model.Hash[i]->Name));
        row.append(QJsonValue(model.Hash[i]->PhoneNumber));
        row.append(QJsonValue(model.Hash[i]->WorkplacePosition));

        data.append(row);
    }
    json["data"] = data;

    QJsonDocument saveDoc(json);
    saveFile.write(saveDoc.toJson());
    qDebug()<<"Saved!   -------------";

    return true;
}

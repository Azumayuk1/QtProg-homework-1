#include "tableitem.h"

TableItem::TableItem()
{
    PersonalID = NULL;
    Name = NULL;
    PhoneNumber = NULL;
    WorkplacePosition = NULL;
}

TableItem::TableItem(int PersonalID, QString Name, QString PhoneNumber, QString WorkplacePosition)
{
    this->PersonalID = PersonalID;
    this->Name = Name;
    this->PhoneNumber = PhoneNumber;
    this->WorkplacePosition = WorkplacePosition;
}

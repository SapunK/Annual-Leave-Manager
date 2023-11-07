#include "UserSqlQModel.h"

#include <QDate>
#include <QSqlRecord>

UserSqlQModel::UserSqlQModel(QObject *parent)
    : QSqlQueryModel(parent)
{

}

QVariant UserSqlQModel::data(const QModelIndex &item, int role) const
{
    if(role == Qt::DisplayRole && (item.column() == Users_NS::dateBirth || item.column() == Users_NS::dateEmployment)) {
        QDate dateTime = record(item.row()).value(item.column()).toDate();
        return QVariant(dateTime.toString("dd-MM-yyyy"));
    }

    return QSqlQueryModel::data(item, role);
}

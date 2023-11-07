#include "ALDSqlQModel.h"

#include <QDate>
#include <QSqlRecord>

#include "util/EALDTableColumns.h"

ALDSqlQModel::ALDSqlQModel(QObject *parent)
    : QSqlQueryModel(parent)
{

}

QVariant ALDSqlQModel::data(const QModelIndex &item, int role) const
{
    if(role == Qt::DisplayRole &&
        (item.column() == EALDTableColumns::dateFrom || item.column() == EALDTableColumns::dateTo)) {
        QDate dateTime = record(item.row()).value(item.column()).toDate();
        return QVariant(dateTime.toString("dd-MM-yyyy"));
    }

    return QSqlQueryModel::data(item, role);
}

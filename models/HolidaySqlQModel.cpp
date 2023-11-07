#include "HolidaySqlQModel.h"

#include <QDate>
#include <QSqlRecord>

HolidaySqlQModel::HolidaySqlQModel(QObject *parent)
    : QSqlQueryModel(parent)
{

}

QVariant HolidaySqlQModel::data(const QModelIndex &item, int role) const
{
    if(role == Qt::DisplayRole && item.column() == Holiday_NS::date ) {
        QDate dateTime = record(item.row()).value(item.column()).toDate();
        return QVariant(dateTime.toString("dd-MM-yyyy"));
    }

    return QSqlQueryModel::data(item, role);
}

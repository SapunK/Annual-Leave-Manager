#ifndef HOLIDAYSQLQMODEL_H
#define HOLIDAYSQLQMODEL_H

#include <QSqlQueryModel>

namespace Holiday_NS {
enum EHolidayColumns{
    id,
    date,
    description
};
}

class HolidaySqlQModel : public QSqlQueryModel
{
public:
    HolidaySqlQModel(QObject *parent);

private:
    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const override;
};

#endif // HOLIDAYSQLQMODEL_H

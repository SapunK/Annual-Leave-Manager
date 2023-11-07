#ifndef ALDSQLQMODEL_H
#define ALDSQLQMODEL_H

#include <QSqlQueryModel>

class ALDSqlQModel : public QSqlQueryModel
{
public:
    ALDSqlQModel(QObject *parent);

private:
    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const override;
};

#endif // ALDSQLQMODEL_H

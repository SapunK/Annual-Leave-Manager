#ifndef USERSQLQMODEL_H
#define USERSQLQMODEL_H

#include <QSqlQueryModel>

namespace Users_NS {
enum EUserColumns {
    firstName,
    lastName,
    personalEmail,
    workEmail,
    dateBirth,
    dateEmployment,
    gender,
    roleName,
    id
};
}

class UserSqlQModel : public QSqlQueryModel
{
public:
    UserSqlQModel(QObject *parent);
private:
    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const override;
};

#endif // USERSQLQMODEL_H

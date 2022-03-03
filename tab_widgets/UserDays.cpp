#include "UserDays.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDate>
#include <QPushButton>
#include <QToolBar>
#include <QSpinBox>

#include "dialogs/AddModifyUserDays.h"
#include "custom_widgets/CustomTableView.h"


namespace UserDays_NS {
static const char* USER = "User";
static const char* DAYS = "Days";
static const char* YEAR = "Year";
static const char* NAME = "Name";


static const char* DELETE_TITLE = "Delete";
static const char* DELETE_MSG = "Are you sure you want to delete this record?";
static const char* MODEL_QUERY = "SELECT u.first_name || ' ' || u.last_name, ud.year, ud.days, ud.id "
                                 "FROM user_days ud "
                                 "INNER JOIN users u on u.id = ud.user_id "
                                 "WHERE ud.year = :year;";

static const char* DELETE_UD_QUERY = "DELETE FROM user_days WHERE id = :udId";

}

using namespace UserDays_NS;

UserDays::UserDays(QWidget *parent)
    : CustomTabWidget(parent)
{
    m_sbYear = new QSpinBox(this);
    m_sbYear->setMaximum(QDate::currentDate().year() + 100);
    m_sbYear->setValue(QDate::currentDate().year());

    connect(m_sbYear, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]{
        setModelQuery();
    });

    m_tb->addWidget(m_sbYear);

    setupModelView();
}

void UserDays::setupModelView()
{
    setModelQuery();
    m_table->setModel(m_model);
    m_table->resizeColumnsToContents();
    connect(m_table->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]{
        m_pbModify->setEnabled(m_table->currentIndex().isValid());
        m_pbDelete->setEnabled(m_table->currentIndex().isValid());
    });
    m_table->hideColumn(id);


    m_model->setHeaderData(name, Qt::Horizontal, NAME);
    m_model->setHeaderData(year, Qt::Horizontal, YEAR);
    m_model->setHeaderData(days, Qt::Horizontal, DAYS);
    m_model->setHeaderData(id, Qt::Horizontal, USER);
}

void UserDays::setModelQuery()
{
    QSqlQuery q;
    q.prepare(MODEL_QUERY);
    q.bindValue(":year", m_sbYear->value());
    q.exec();

    m_model->setQuery(std::move(q));
    m_table->resizeColumnsToContents();
    m_pbModify->setEnabled(m_table->currentIndex().isValid());
    m_pbDelete->setEnabled(m_table->currentIndex().isValid());
}

void UserDays::addClicked()
{
    AddModifyUserDays *dlg = new AddModifyUserDays(this, -1, m_sbYear->value());
    connect(dlg, &QDialog::accepted, this, [this]{
        setModelQuery();
    });
    dlg->exec();
}

void UserDays::modifyClicked()
{
    AddModifyUserDays *dlg = new AddModifyUserDays(this, m_model->index(m_table->currentIndex().row(), UserDays_NS::id).data().toInt(), m_sbYear->value());
    connect(dlg, &QDialog::accepted, this, [this]{
        setModelQuery();
    });
    dlg->exec();
}

void UserDays::deleteClicked()
{
    if(QMessageBox::question(this, DELETE_TITLE, DELETE_MSG) == QMessageBox::Yes){
        QSqlQuery q;
        q.prepare(DELETE_UD_QUERY);
        q.bindValue(":udId", m_model->index(m_table->currentIndex().row(), UserDays_NS::id).data().toInt());
        q.exec();

        setModelQuery();
    }
}

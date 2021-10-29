#include "Users.h"

#include <QLayout>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QToolBar>

#include "custom_widgets/CustomTableView.h"
#include "dialogs/AddEditUser.h"

namespace Users_NS {
static const char* ADD = "Add";

static const char* MODEL_QUERY = "SELECT first_name, last_name, personal_email, work_email, date_birth, date_employment "
                                 "FROM users;";

}

using namespace Users_NS;

Users::Users(QWidget *parent) : QWidget(parent)
{
    setupUi();
}

void Users::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *toolBarLayout = new QHBoxLayout();
    QHBoxLayout *tableLayout = new QHBoxLayout();

    QToolBar *tb = new QToolBar(this);

    m_pbAdd = new QPushButton(ADD, this);

    tb->addWidget(m_pbAdd);

    m_model = new QSqlQueryModel(this);
    m_model->setQuery(MODEL_QUERY);
    m_table = new CustomTableView(this);
    m_table->setModel(m_model);

    toolBarLayout->addWidget(tb);
    tableLayout->addWidget(m_table);

    mainLayout->addLayout(toolBarLayout);
    mainLayout->addLayout(tableLayout);

    connect(m_pbAdd, &QPushButton::clicked, this, [this] {
       AddEditUser *dlg = new AddEditUser(this);
       dlg->exec();
    });
}

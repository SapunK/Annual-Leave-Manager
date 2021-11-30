#include "CustomTabWidget.h"

#include <QLayout>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QToolBar>

#include "custom_widgets/CustomTableView.h"

namespace CustomTW_NS {
static const char* ADD = "Add";
static const char* MODIFY = "Modify";
static const char* DELETE = "Delete";

}

using namespace CustomTW_NS;

CustomTabWidget::CustomTabWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUi();

    connect(m_pbAdd, &QAbstractButton::clicked, this, &CustomTabWidget::addClicked);
    connect(m_pbModify, &QAbstractButton::clicked, this, &CustomTabWidget::modifyClicked);
    connect(m_pbDelete, &QPushButton::clicked, this, &CustomTabWidget::deleteClicked);
}

void CustomTabWidget::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *toolBarLayout = new QHBoxLayout();
    QHBoxLayout *tableLayout = new QHBoxLayout();

    QToolBar *tb = new QToolBar(this);

    m_pbAdd = new QPushButton(ADD, this);
    m_pbModify = new QPushButton(MODIFY, this);
    m_pbDelete = new QPushButton(DELETE, this);

    tb->addWidget(m_pbAdd);
    tb->addWidget(m_pbModify);
    tb->addWidget(m_pbDelete);

    m_model = new QSqlQueryModel(this);
    m_table = new CustomTableView(this);
    m_table->setModel(m_model);

    toolBarLayout->addWidget(tb);
    tableLayout->addWidget(m_table);

    mainLayout->addLayout(toolBarLayout);
    mainLayout->addLayout(tableLayout);
}

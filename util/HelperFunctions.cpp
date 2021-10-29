#include "HelperFunctions.h"

#include <QWidget>
#include <QApplication>
#include <QScreen>
#include <QLineEdit>

#include "appconsts.h"

int HelperFunctions::m_desktopWidth = 0;
int HelperFunctions::m_desktopHeight = 0;


HelperFunctions::HelperFunctions()
{

}

void HelperFunctions::setWidgetProperties(QWidget &widget)
{
    if(widget.metaObject()->className() == QString("QPushButton")){
        widget.setFixedWidth(m_desktopWidth * 0.15);
        widget.setFixedHeight(m_desktopHeight * 0.05);
        widget.setStyleSheet(FONT_WEIGHT_BOLD);
        widget.setStyleSheet(PB_FONTSIZE);
        return;
    }

    if(widget.metaObject()->className() == QString("QLineEdit"))
    {
        widget.setFixedWidth(m_desktopWidth * 0.5);
        widget.setFixedHeight(m_desktopHeight * 0.05);
        widget.setStyleSheet(LE_SEARCH_FONTSIZE);
    }
}

int HelperFunctions::desktopWidth()
{
    return m_desktopWidth;
}

int HelperFunctions::desktopHeight()
{
    return m_desktopHeight;
}

void HelperFunctions::setDesktopSize()
{
    m_desktopWidth = qApp->primaryScreen()->availableGeometry().width();
    m_desktopHeight = qApp->primaryScreen()->availableGeometry().height();
}

void HelperFunctions::setTabOrder(QWidget *w, QVector<QWidget *> vWidgets)
{
    for(int i = 0 ; i < vWidgets.size() - 1 ; i++)
    {
        w->setTabOrder(vWidgets.at(i), vWidgets.at(i + 1));
    }

}

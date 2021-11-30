#include "AddModifyVacDays.h"

#include <QComboBox>

namespace AddModifyVacDays_NS {

}

using namespace AddModifyVacDays_NS;

AddModifyVacDays::AddModifyVacDays(QWidget *parent, int vdId)
    : QDialog(parent),
      m_vdId(vdId)
{
    setupUi();

    if(vdId > 0 )
        fillVdInfo();
}

void AddModifyVacDays::setupUi()
{
    m_cbUser = new QComboBox(this);
}

void AddModifyVacDays::fillVdInfo()
{

}

#include "label_master.h"

LabelMaster::LabelMaster()
{    
}

void LabelMaster::setLabelText(QLabel *label, QString text)
{
    label->setText(text);
}

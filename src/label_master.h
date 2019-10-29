#ifndef LABEL_MASTER_H
#define LABEL_MASTER_H

#include <QWidget>
#include <QLabel>

class LabelMaster
{
private:
    QLabel* m_qLabel;

public:
    LabelMaster();
    LabelMaster(QLabel* label);
    void setLabelText(QLabel* label, QString text);
};

#endif // LABEL_MASTER_H

#ifndef DUMMYINSTRUMENT_H
#define DUMMYINSTRUMENT_H

#include <QWidget>
#include "tool.hpp"

namespace Ui {
class DummyInstrument;
}

namespace adiscope {
class DummyInstrument : public Tool
{
	Q_OBJECT

public:
	explicit DummyInstrument(QPushButton *runBtn, ToolLauncher *parent = nullptr);
	~DummyInstrument();

private:
	Ui::DummyInstrument *ui;
};
}
#endif // DUMMYINSTRUMENT_H

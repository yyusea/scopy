#ifndef DUMMYINSTRUMENT_H
#define DUMMYINSTRUMENT_H

#include <QWidget>
#include "tool.hpp"
#include "dmm.hpp"
#include "dmm_api.hpp"

namespace Ui {
class DummyInstrument;
}

namespace adiscope {
class DummyInstrument : public Tool
{
	Q_OBJECT

public:
	explicit DummyInstrument(QPushButton *runBtn, DMM* dmm, ToolLauncher *parent = nullptr);
	~DummyInstrument();

private Q_SLOTS:
	void on_run_btn_clicked();

	void updateSensor();
private:
	Ui::DummyInstrument *ui;
	//boost::shared_ptr<iio_manager> manager;
	DMM *dmm;
	DMM_API* dmm_api;
	QTimer *timer;
};
}
#endif // DUMMYINSTRUMENT_H

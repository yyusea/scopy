#ifndef DUMMYINSTRUMENT_H
#define DUMMYINSTRUMENT_H

#include <QWidget>
#include "tool.hpp"
#include "dmm.hpp"
#include "dmm_api.hpp"
#include "power_controller.hpp"
#include "power_controller_api.hpp"

namespace Ui {
class DummyInstrument;
}

namespace adiscope {
class DummyInstrument : public Tool
{
	Q_OBJECT

public:
	explicit DummyInstrument(QPushButton *runBtn, DMM* dmm, PowerController* ps, ToolLauncher *parent = nullptr);
	~DummyInstrument();

private Q_SLOTS:
	void on_run_btn_clicked();

	void updateSensor();
private:
	Ui::DummyInstrument *ui;
	//boost::shared_ptr<iio_manager> manager;
	DMM *dmm;
	DMM_API* dmm_api;
	PowerController *ps;
	PowerController_API *ps_api;
	QTimer *timer;

	double ps_pos_val;
	double ps_neg_val;
};
}
#endif // DUMMYINSTRUMENT_H

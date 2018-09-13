#include "dummyinstrument.h"
#include "iio_manager.hpp"
#include "filter.hpp"
#include "ui_dummyinstrument.h"
#include <QTimer>

using namespace adiscope;


QString sensorStylesheet = "border-radius: 20px;\n  min-height: 100px;\n  min-width: 100px;\n  max-width:100px;\n  background-color:";

DummyInstrument::DummyInstrument(QPushButton *runBtn, DMM* dmm, PowerController* ps, ToolLauncher *parent) :
	Tool(nullptr, runBtn, nullptr, "DummyInstrument", parent),
	ui(new Ui::DummyInstrument),dmm(dmm),ps(ps)
{
	ui->setupUi(this);
	ui->lightSensor->setStyleSheet(sensorStylesheet+"gray");
	dmm_api = dynamic_cast<DMM_API*>(dmm->api);
	ps_api = dynamic_cast<PowerController_API*>(ps->api);
	timer = new QTimer();
	timer->setInterval(100);
	connect(timer,SIGNAL(timeout(void)),this,SLOT(updateSensor(void)));

	ps_pos_val=5.0;
	ps_neg_val=0.0;

	ui->VPlus->setText(QString::number(ps_pos_val));
	ui->VMinus->setText(QString::number(ps_neg_val));
}

DummyInstrument::~DummyInstrument()
{
	delete ui;
}

void adiscope::DummyInstrument::updateSensor()
{
	auto val = dmm_api->read_ch1();

	if(val<ps_neg_val)
		val=ps_neg_val;
	if(val>ps_pos_val)
		val=ps_pos_val;


	ui->VOut->setText(QString::number(val));
	int colorCode = int(((val - ps_neg_val) * (255/ps_pos_val)));
	ui->lightSensor->setStyleSheet(sensorStylesheet+QColor(colorCode,colorCode,0).name());
}
void adiscope::DummyInstrument::on_run_btn_clicked()
{
	static bool running=false;
	running=!running;

	ps_pos_val = ui->VPlus->text().toDouble();
	ps_neg_val = ui->VMinus->text().toDouble();


	ps_api->setValueDac1(ps_pos_val);
	ps_api->setValueDac2(ps_neg_val);

	dmm_api->run(running);
	ps_api->setDac1Enabled(running);
	ps_api->setDac2Enabled(running);

	ui->VPlus->setEnabled(!running);
	ui->VMinus->setEnabled(!running);


	if(running)
		timer->start();
	else
		timer->stop();

}

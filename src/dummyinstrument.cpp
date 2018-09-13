#include "dummyinstrument.h"
#include "ui_dummyinstrument.h"

using namespace adiscope;

DummyInstrument::DummyInstrument(QPushButton *runBtn, ToolLauncher *parent) :
	Tool(nullptr, runBtn, nullptr, "AudioPlayer", parent),
	ui(new Ui::DummyInstrument)
{
	ui->setupUi(this);
}

DummyInstrument::~DummyInstrument()
{
	delete ui;
}

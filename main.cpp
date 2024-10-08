#include <iostream>
#include <QApplication>
#include <QDebug>
#include "ui/recorder_widget.h"
#include "win_capturer/mf_device.h"

#pragma comment(lib, "mfreadwrite")
#pragma comment(lib, "mfplat")
#pragma comment(lib, "mfuuid")
#pragma comment(lib, "Mf")

int main(int argc, char* argv[]) {

	MfDevice mf_device;

	QApplication a(argc, argv);
	qDebug() << "test...";

	RecorderWidget w;
	w.initLayout();
	w.resize(800, 600);
	w.initDevice();

	w.show();

	return a.exec();
}
#include <iostream>
#include <QApplication>
#include <QDebug>
#include "ui/recorder_widget.h"

int main(int argc, char* argv[]) {

	QApplication a(argc, argv);
	qDebug() << "test...";

	RecorderWidget w;
	w.initLayout();
	w.resize(800, 600);
	w.show();

	return a.exec();
}
#include "messages.h"

void Messages::error(const QString& msg) {
	showMessage("Error", msg);
}

void Messages::info(const QString& msg) {
	showMessage("Info", msg);
}

void Messages::showMessage(const QString& title, const QString& msg) {
	QMessageBox msgBox;
	msgBox.setWindowTitle(title);
	msgBox.setText(msg);
	msgBox.setModal(true);
	msgBox.exec();
}
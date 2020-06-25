#include "filewindow.h"

FileWindow::FileWindow(const QFileInfo& filePath, QWidget *parent)
	: QWidget(parent)
{
	setupUi();
}

//
void FileWindow::setupUi() {
	m_verticalLayout = new QVBoxLayout(this);
	m_verticalLayout->setSpacing(6);
	m_verticalLayout->setContentsMargins(11, 11, 11, 11);
	m_wordsTable = new QTableWidget(this);
	m_wordsTable ->setColumnCount(2);
	m_wordsTable->setShowGrid(true);
	//m_wordsTable->setHorizontalHeaderLabels(m_tableHeader);
	m_wordsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	m_verticalLayout->addWidget(m_wordsTable);
}
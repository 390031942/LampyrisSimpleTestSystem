/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */

 // Project Include(s)
#include "DesignWindow.h"
#include "OptionEditorWindow.h"

// QT Include(s)
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>

DesignWindow::DesignWindow(QWidget* parent)
	: QMainWindow(parent)
	, m_rowCount(0)
	, m_contextMenuRow(-1) {
	m_ui.setupUi(this);

	QWidget* centralWidget = m_ui.centralWidget;
	QVBoxLayout* layout = new QVBoxLayout(centralWidget);

	m_tableWidget = new QTableWidget(0, 3, this);
	setupTable();
	layout->addWidget(m_tableWidget);

	QPushButton* addRowButton = new QPushButton("Add Row", this);
	connect(addRowButton, &QPushButton::clicked, this, &DesignWindow::onAddRow);
	layout->addWidget(addRowButton);

	setCentralWidget(centralWidget);

	m_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(m_tableWidget, &QTableWidget::customContextMenuRequested, this, &DesignWindow::showContextMenu);

	connect(m_tableWidget, &QTableWidget::cellDoubleClicked, this, &DesignWindow::onCellDoubleClicked);
}

void DesignWindow::onCellDoubleClicked(int row, int column) {
	QMessageBox::information(this, "Cell Double Clicked", QString("Row: %1, Column: %2").arg(row).arg(column));
}

DesignWindow::~DesignWindow()
{}

void DesignWindow::setupTable() {
	QStringList headers = { "Editable Text", "Image", "Options" };
	m_tableWidget->setHorizontalHeaderLabels(headers);
	m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void DesignWindow::onAddRow() {
	m_tableWidget->insertRow(m_rowCount);

	// Index
	QTableWidgetItem* indexItem = new QTableWidgetItem(QString::number(m_rowCount + 1));
	indexItem->setFlags(indexItem->flags() & ~Qt::ItemIsEditable);

	// Editable Text
	QLineEdit* lineEdit = new QLineEdit(this);
	m_tableWidget->setCellWidget(m_rowCount, 0, lineEdit);

	// Image
	QPushButton* imageButton = new QPushButton("Add Image", this);
	int rowCount = m_rowCount;
	connect(imageButton, &QPushButton::clicked, [this, rowCount]() { onSelectImage(rowCount); });
	m_tableWidget->setCellWidget(m_rowCount, 1, imageButton);

	// Options
	QWidget* optionsWidget = new QWidget(this);
	optionsWidget->setContextMenuPolicy(Qt::CustomContextMenu);

	QHBoxLayout* optionsLayout = new QHBoxLayout(optionsWidget);
	optionsLayout->setContentsMargins(0, 0, 0, 0);
	optionsWidget->setLayout(optionsLayout);
	optionsWidget->installEventFilter(this);
	m_tableWidget->setCellWidget(m_rowCount, 2, optionsWidget);
	connect(optionsWidget, &QWidget::customContextMenuRequested, [this, rowCount]() { onEditOptions(rowCount); });

	m_rowCount++;
}

void DesignWindow::onSelectImage(int row) {
	QString filePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp)");
	if (!filePath.isEmpty()) {
		QLabel* imageLabel = new QLabel(this);
		QPixmap pixmap(filePath);
		if (pixmap.isNull()) {
			QMessageBox::warning(this, "Error", "Invalid image file.");
			return;
		}
		imageLabel->setPixmap(pixmap);
		imageLabel->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
		m_tableWidget->setCellWidget(row, 1, imageLabel);
	}
}

void DesignWindow::onEditOptions(int row) {
	OptionEditorWindow editor(this);
	if (editor.exec() == QDialog::Accepted) {
		QStringList options = editor.getOptions();
		int selectedOption = editor.getSelectedOption();

		QWidget* optionsWidget = m_tableWidget->cellWidget(row, 2);
		QHBoxLayout* optionsLayout = qobject_cast<QHBoxLayout*>(optionsWidget->layout());

		// Clear previous options
		QLayoutItem* child;
		while ((child = optionsLayout->takeAt(0)) != nullptr) {
			delete child->widget();
			delete child;
		}

		// Add new options
		for (int i = 0; i < options.size(); ++i) {
			QLabel* label = new QLabel(options[i], this);
			if (i == selectedOption) {
				label->setStyleSheet("color: red;");
			}
			optionsLayout->addWidget(label);
		}
	}
}

void DesignWindow::onDeleteRow() {
	if (m_contextMenuRow >= 0) {
		m_tableWidget->removeRow(m_contextMenuRow);
		m_rowCount--;
		m_contextMenuRow = -1;
	}
}

void DesignWindow::showContextMenu(const QPoint& pos) {
	QMenu contextMenu(this);
	QAction deleteAction("Delete", this);
	connect(&deleteAction, &QAction::triggered, this, &DesignWindow::onDeleteRow);
	contextMenu.addAction(&deleteAction);

	m_contextMenuRow = m_tableWidget->indexAt(pos).row();
	contextMenu.exec(m_tableWidget->viewport()->mapToGlobal(pos));
}
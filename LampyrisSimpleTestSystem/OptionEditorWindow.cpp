/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */

 // Project Include(s)
#include "OptionEditorWindow.h"

// QT Include(s)
#include <QHeaderView>

OptionEditorWindow::OptionEditorWindow(QWidget* parent)
	: QDialog(parent)
	, selectedOption(-1) {
	QVBoxLayout* layout = new QVBoxLayout(this);

	optionTable = new QTableWidget(0, 2, this);
	QStringList headers = { "Select", "Option" };
	optionTable->setHorizontalHeaderLabels(headers);
	optionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	layout->addWidget(optionTable);

	confirmButton = new QPushButton("Confirm", this);
	connect(confirmButton, &QPushButton::clicked, this, &OptionEditorWindow::onConfirm);
	layout->addWidget(confirmButton);
	this->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(this, &OptionEditorWindow::customContextMenuRequested, this, &OptionEditorWindow::showContextMenu);
}

void OptionEditorWindow::setOptions(const QStringList& options) {
	this->options = options;
	optionTable->setRowCount(options.size());
	for (int i = 0; i < options.size(); ++i) {
		QCheckBox* checkBox = new QCheckBox(this);
		optionTable->setCellWidget(i, 0, checkBox);
		QTableWidgetItem* item = new QTableWidgetItem(options[i]);
		optionTable->setItem(i, 1, item);
	}
}

QStringList OptionEditorWindow::getOptions() const {
	QStringList options;
	for (int i = 0; i < optionTable->rowCount(); ++i) {
		options << optionTable->item(i, 1)->text();
	}
	return options;
}

int OptionEditorWindow::getSelectedOption() const {
	return selectedOption;
}

void OptionEditorWindow::onConfirm() {
	for (int i = 0; i < optionTable->rowCount(); ++i) {
		QCheckBox* checkBox = qobject_cast<QCheckBox*>(optionTable->cellWidget(i, 0));
		if (checkBox->isChecked()) {
			selectedOption = i;
			break;
		}
	}
	accept();
}

void OptionEditorWindow::onAddOption() {
	int row = optionTable->rowCount();
	optionTable->insertRow(row);

	QCheckBox* checkBox = new QCheckBox(this);
	optionTable->setCellWidget(row, 0, checkBox);
	QTableWidgetItem* item = new QTableWidgetItem("New Option");
	optionTable->setItem(row, 1, item);
}

void OptionEditorWindow::onDeleteOption() {
	if (contextMenuRow >= 0) {
		optionTable->removeRow(contextMenuRow);
		contextMenuRow = -1;
	}
}

void OptionEditorWindow::showContextMenu(const QPoint& pos) {
	QMenu contextMenu(this);
	QAction addAction("Add", this);
	connect(&addAction, &QAction::triggered, this, &OptionEditorWindow::onAddOption);
	contextMenu.addAction(&addAction);

	QAction deleteAction("Delete", this);
	connect(&deleteAction, &QAction::triggered, this, &OptionEditorWindow::onDeleteOption);
	contextMenu.addAction(&deleteAction);

	contextMenuRow = optionTable->indexAt(pos).row();
	if (contextMenuRow < 0) {
		deleteAction.setEnabled(false);
	}

	contextMenu.exec(optionTable->viewport()->mapToGlobal(pos));
}
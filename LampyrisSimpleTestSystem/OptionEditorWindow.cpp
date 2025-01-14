/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */

 // Project Include(s)
#include "OptionEditorWindow.h"
#include "DataDef.h"

// QT Include(s)
#include <QHeaderView>

#pragma execution_character_set("utf-8")

OptionEditorWindow::OptionEditorWindow(QWidget* parent)
	: QDialog(parent)
	, buttonGroup(new QButtonGroup(this)) {
	QVBoxLayout* layout = new QVBoxLayout(this);

	optionTable = new QTableWidget(0, 2, this);
	QStringList headers = { "�Ƿ��", "ѡ��" };
	optionTable->setHorizontalHeaderLabels(headers);
	optionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	layout->addWidget(optionTable);

	confirmButton = new QPushButton("����ѡ��", this);
	connect(confirmButton, &QPushButton::clicked, this, &OptionEditorWindow::onConfirm);
	layout->addWidget(confirmButton);
	this->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(this, &OptionEditorWindow::customContextMenuRequested, this, &OptionEditorWindow::showContextMenu);

	buttonGroup->setExclusive(true);
	this->setWindowTitle("����ѡ��");
}

void OptionEditorWindow::setQuestionInfo(QuestionInfo& questionInfo) {
	this->options = &(questionInfo.options);
	optionTable->setRowCount(options->size());
	for (int i = 0; i < options->size(); ++i) {
		QCheckBox* checkBox = new QCheckBox(this);
		buttonGroup->addButton(checkBox);

		checkBox->setChecked((*options)[i].answer);
		optionTable->setCellWidget(i, 0, checkBox);
		QTableWidgetItem* item = new QTableWidgetItem((*options)[i].text);
		optionTable->setItem(i, 1, item);
	}
}

void OptionEditorWindow::onConfirm() {
	if (!this->options)
		return;

	this->options->clear();
	for (int i = 0; i < optionTable->rowCount(); ++i) {
		QCheckBox* checkBox = qobject_cast<QCheckBox*>(optionTable->cellWidget(i, 0));
		QTableWidgetItem* item = optionTable->item(i, 1);
		this->options->push_back({ item->text(),checkBox->isChecked() });
	}
	accept();
}

void OptionEditorWindow::onAddOption() {
	int row = optionTable->rowCount();
	optionTable->insertRow(row);

	QCheckBox* checkBox = new QCheckBox(this);
	optionTable->setCellWidget(row, 0, checkBox);
	QTableWidgetItem* item = new QTableWidgetItem("��ѡ��");
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
	QAction addAction("���ѡ��", this);
	connect(&addAction, &QAction::triggered, this, &OptionEditorWindow::onAddOption);
	contextMenu.addAction(&addAction);

	QAction deleteAction("ɾ��ѡ��", this);
	connect(&deleteAction, &QAction::triggered, this, &OptionEditorWindow::onDeleteOption);
	contextMenu.addAction(&deleteAction);

	contextMenuRow = optionTable->indexAt(pos).row();
	if (contextMenuRow < 0) {
		deleteAction.setEnabled(false);
	}

	contextMenu.exec(optionTable->viewport()->mapToGlobal(pos));
}
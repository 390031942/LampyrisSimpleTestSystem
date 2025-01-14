/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-14
 * Author: TengZ.
 */

 // Project Include(s)
#include "TestQuestionSelectWindow.h"
#include "QuestionItem.h"

TestQuestionSelectWindow::TestQuestionSelectWindow(QWidget* parent)
	: QWidget(parent) {
	scrollArea = new QScrollArea(this);
	containerWidget = new QWidget(scrollArea);
	layout = new QGridLayout(containerWidget);
	layout->setSpacing(10);
	layout->setContentsMargins(10, 10, 10, 10);
	containerWidget->setLayout(layout);

	scrollArea->setWidget(containerWidget);
	scrollArea->setWidgetResizable(true);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(scrollArea);
	setLayout(mainLayout);
}

void TestQuestionSelectWindow::setQuestionStatuses(const std::vector<QuestionStatusInfo>& statuses) {
	int row = 0;
	int column = 0;
	int columns = 4; // 每行显示4个题目

	this->clearLayout(layout);

	for (const auto& status : statuses) {
		QuestionItem* item = new QuestionItem(status.questionNumber, status.status, this);
		layout->addWidget(item, row, column);
		column++;
		if (column >= columns) {
			column = 0;
			row++;
		}
	}

	// 添加一个QSpacerItem到布局的最后一行
	layout->setRowStretch(row + 1, 1);
}

void TestQuestionSelectWindow::clearLayout(QLayout* layout) {
	if (layout == nullptr)
		return;

	QLayoutItem* item;
	while ((item = layout->takeAt(0)) != nullptr) {
		if (item->widget()) {
			delete item->widget();
		}
		if (item->layout()) {
			clearLayout(item->layout());
		}
		delete item;
	}
}

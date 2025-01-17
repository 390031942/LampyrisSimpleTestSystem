/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-14
 * Author: TengZ.
 */

#ifdef LAMPYRIS_TEST
 // Project Include(s)
#include "TestQuestionSelectWindow.h"
#include "GlobalEventObject.h"

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

	connect(&GlobalEventObject, &GlobalEventObjectClass::onQuestionIndexChanged, [this](int index) {
		if (itemList.size() > index) {
			if (m_lastSelectedItem != nullptr) {
				m_lastSelectedItem->setIsCurrentShow(false);
			}
			auto item = itemList[index];
			item->setIsCurrentShow(true);
			m_lastSelectedItem = item;
		}
	});

	connect(&GlobalEventObject, &GlobalEventObjectClass::onQuestionItemClicked, [this](int index) {
		if (itemList.size() > index) {
			if (m_lastSelectedItem != nullptr) {
				m_lastSelectedItem->setIsCurrentShow(false);
			}
			auto item = itemList[index];
			item->setIsCurrentShow(true);
			m_lastSelectedItem = item;
		}
	});

	connect(&GlobalEventObject, &GlobalEventObjectClass::onAnswerStatusChanged, [this](int index, QuestionStatus status) {
		if (itemList.size() > index) {
			if (m_lastSelectedItem != nullptr) {
				m_lastSelectedItem->setQuestionStatus(status);
			}
		}
	});

	connect(&GlobalEventObject, &GlobalEventObjectClass::onSubmitAnswers, [this]() {
		for (int i = 0; i < itemList.size(); i++) {
			itemList[i]->setQuestionStatus(GlobalDataObject::answerInfo[i].status);
		}
	});
}

void TestQuestionSelectWindow::initialize() {
	int row = 0;
	int column = 0;
	int columns = 4; // 每行显示4个题目

	this->clearLayout(layout);

	for (int i = 0; i < GlobalDataObject::answerInfo.size(); i++) {
		QuestionItem* item = new QuestionItem(GlobalDataObject::answerInfo[i].questionIndex, GlobalDataObject::answerInfo[i].status, this);
		itemList.push_back(item);
		layout->addWidget(item, row, column);
		column++;
		if (column >= columns) {
			column = 0;
			row++;
		}
		if (i == 0) {
			item->setIsCurrentShow(true);
			m_lastSelectedItem = item;
		}
	}

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
#endif // !LAMPYRIS_TEST
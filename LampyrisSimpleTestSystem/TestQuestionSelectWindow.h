/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-14
 * Author: TengZ.
 */
#pragma once

// Project Include(s)
#include "DataDef.h"
#include "QuestionItem.h"

// QT Include(s)
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>

class TestQuestionSelectWindow : public QWidget {
	Q_OBJECT
	using ItemList = std::vector<QuestionItem*>;
public:
	               TestQuestionSelectWindow(QWidget* parent = nullptr);
	void           initialize();
private:		   
	QScrollArea*   scrollArea;
	QWidget*       containerWidget;
	QGridLayout*   layout;
	ItemList       itemList;
	QuestionItem*  m_lastSelectedItem;
	void           clearLayout(QLayout* layout);
};

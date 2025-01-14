/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-14
 * Author: TengZ.
 */
#pragma once

// Project Include(s)
#include <DataDef.h>

// QT Include(s)
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>

class TestQuestionSelectWindow : public QWidget {
	Q_OBJECT

public:
	             TestQuestionSelectWindow(QWidget* parent = nullptr);
	void         setQuestionStatuses(const std::vector<QuestionStatusInfo>& statuses);
private:
	QScrollArea* scrollArea;
	QWidget*     containerWidget;
	QGridLayout* layout;

	void         clearLayout(QLayout* layout);
};

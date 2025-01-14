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

class QuestionItem : public QWidget {
	Q_OBJECT
public:
	               QuestionItem(int questionNumber, QuestionStatus status, QWidget* parent = nullptr);
protected:
	void           paintEvent(QPaintEvent* event) override;
private:
	int            questionNumber;
	QuestionStatus status;
};
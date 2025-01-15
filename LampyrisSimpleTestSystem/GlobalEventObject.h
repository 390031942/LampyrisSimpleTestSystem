/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */
#pragma once

// Project Include(s)
#include "DataDef.h"

// QT Include(s)
#include <QObject>

class GlobalEventObjectClass:public QObject {
	Q_OBJECT
public:
	static GlobalEventObjectClass globalEvent;
Q_SIGNALS:
	void onQuestionItemClicked(int questionIndex);
	void onQuestionIndexChanged(int questionIndex);
	void onSubmitAnswers();
	void onAnswerStatusChanged(int questionIndex, QuestionStatus status);
};

#ifndef GlobalEventObject
#define GlobalEventObject GlobalEventObjectClass::globalEvent
#endif // !GlobalEventObject
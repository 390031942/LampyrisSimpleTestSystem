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
	               QuestionItem(int questionIndex, QuestionStatus status, QWidget* parent = nullptr);
	inline void    setIsCurrentShow(bool value) { isCurrentShow = value; update(); }
	inline void    setQuestionStatus(QuestionStatus status) { this->status = status; update(); }
protected:
	void           paintEvent(QPaintEvent* event) override;
	void           mousePressEvent(QMouseEvent* event) override;
	void           enterEvent(QEvent* event) override;
	void           leaveEvent(QEvent* event) override;
private:
	int            questionIndex;
	QuestionStatus status;
	bool           isMouseInside;
	bool           isCurrentShow;
};
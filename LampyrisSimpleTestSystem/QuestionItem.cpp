/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-14
 * Author: TengZ.
 */

// Project Include(s)
#include "QuestionItem.h"

// QT Include(s)
#include <QPainter>
#include <QFontMetrics>

QuestionItem::QuestionItem(int questionNumber, QuestionStatus status, QWidget* parent)
	: QWidget(parent), questionNumber(questionNumber), status(status) {
	setFixedSize(50, 50);
}

void QuestionItem::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QColor backgroundColor;
	switch (status) {
	case QuestionStatus::Unanswered:
		backgroundColor = QColor(211, 211, 211); // »ÒÉ«
		break;
	case QuestionStatus::Answered:
		backgroundColor = QColor(173, 216, 230); // Ç³À¶É«
		break;
	case QuestionStatus::Correct:
		backgroundColor = QColor(144, 238, 144); // Ç³ÂÌÉ«
		break;
	case QuestionStatus::Incorrect:
		backgroundColor = QColor(255, 182, 193); // Ç³ºìÉ«
		break;
	}

	painter.setBrush(backgroundColor);
	painter.setPen(Qt::NoPen);

	QRect rect = this->rect();
	int diameter = qMin(rect.width(), rect.height()) - 10;
	QRect circleRect((rect.width() - diameter) / 2, (rect.height() - diameter) / 2, diameter, diameter);
	painter.drawEllipse(circleRect);

	painter.setPen(Qt::black);
	QFontMetrics metrics(font());
	QString text = QString::number(questionNumber);
	int textWidth = metrics.horizontalAdvance(text);
	int textHeight = metrics.height();
	painter.drawText(circleRect, Qt::AlignCenter, text);
}
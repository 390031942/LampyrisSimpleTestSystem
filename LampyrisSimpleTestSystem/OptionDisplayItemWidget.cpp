/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */

// Project Include(s)
#include "OptionDisplayItemWidget.h"

// QT Include(s)
#include <QPainter>

OptionDisplayItemWidget::OptionDisplayItemWidget(const QString& text, bool answer, QWidget* parent)
	: QWidget(parent), text(text), answer(answer) {
	setFixedHeight(30);
}

QSize OptionDisplayItemWidget::sizeHint() const {
	QFontMetrics metrics(font());
	int textWidth = metrics.horizontalAdvance(text);
	return QSize(textWidth + 20, 30); // 20 is padding
}

void OptionDisplayItemWidget::paintEvent(QPaintEvent* event) {
	Q_UNUSED(event);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	QColor backgroundColor = answer ? QColor(255, 182, 193) : QColor(144, 238, 144); // Ç³ºìÉ«»òÇ³ÂÌÉ«
	painter.setBrush(backgroundColor);
	painter.setPen(Qt::NoPen);

	QRect rect = this->rect();
	painter.drawRoundedRect(rect, 10, 10);

	painter.setPen(Qt::black);
	painter.drawText(rect, Qt::AlignCenter, text);
}
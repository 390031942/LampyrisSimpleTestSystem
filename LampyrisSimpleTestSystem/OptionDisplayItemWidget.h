/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */
#pragma once

 // QT Include(s)
#include <QWidget>

class OptionDisplayItemWidget : public QWidget {
	Q_OBJECT
public:
	        OptionDisplayItemWidget(const QString& text, bool important, QWidget* parent = nullptr);
protected:
	void    paintEvent(QPaintEvent* event) override;
	QSize   sizeHint() const override;
private:
	QString text;
	bool    answer;
};
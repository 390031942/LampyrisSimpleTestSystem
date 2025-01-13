/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */
#pragma once

 // QT Include(s)
#include <QWidget>
#include <QHBoxLayout>

// Project Include(s)
#include <DataDef.h>

class OptionDisplayWidget : public QWidget {
	Q_OBJECT
public:
	OptionDisplayWidget(QWidget* parent = nullptr);
	void setOptions(const std::vector<OptionInfo>& options);
private:
	QHBoxLayout* layout;
};

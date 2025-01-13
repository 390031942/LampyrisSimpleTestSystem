/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */
#pragma once

 // QT Include(s)
#include <QWidget>

// Project Include(s)
#include "ui_TestEntryWindow.h"

class TestEntryWindow : public QWidget {
	Q_OBJECT
public:
	TestEntryWindow(QWidget *parent = nullptr);
	~TestEntryWindow();

private slots:
	void onclickBtnStartTest();

private:
	Ui::TestEntryWindowClass m_ui;
};

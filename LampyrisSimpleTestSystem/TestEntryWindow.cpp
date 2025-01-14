/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */

 // Project Include(s)
#include "TestEntryWindow.h"
#include "TestWindow.h"

TestEntryWindow::TestEntryWindow(QWidget *parent)
	: QWidget(parent) {
	m_ui.setupUi(this);

	connect(m_ui.btnStartTest, &QPushButton::clicked, this, &TestEntryWindow::onclickBtnStartTest);
}

TestEntryWindow::~TestEntryWindow()
{}

void TestEntryWindow::onclickBtnStartTest() {
	(new TestWindow(m_ui.inputWorkNumber->text()))->show();
}
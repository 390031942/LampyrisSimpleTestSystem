/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */

#ifdef LAMPYRIS_TEST
 // Project Include(s)
#include "TestEntryWindow.h"
#include "TestWindow.h"
#include "PathUtil.h"

// QT Include(s)
#include <QMessageBox>

#pragma execution_character_set("utf-8")
TestEntryWindow::TestEntryWindow(QWidget *parent)
	: QWidget(parent) {
	m_ui.setupUi(this);

	this->setFixedSize(size());
	connect(m_ui.btnStartTest, &QPushButton::clicked, this, &TestEntryWindow::onclickBtnStartTest);

	// 加载出题目
	GlobalDataObject::testInfo.deserializeFromFile(PathUtil::getTestInfoJsonPath());
	if (GlobalDataObject::testInfo.questions.empty()) {
		QMessageBox::information(NULL, "提示", "测试内容为空，程序将退出");
		QApplication::quit();
	}

	this->m_ui.labelTestName->setText(GlobalDataObject::testInfo.name);
	this->setWindowTitle("天马微内部测试系统");
}

TestEntryWindow::~TestEntryWindow()
{}

void TestEntryWindow::onclickBtnStartTest() {
	if (m_ui.inputWorkNumber->text().isEmpty()) {
		QMessageBox::warning(NULL, "进入测试", "提示，工号不能为空，请输入工号再试");
		return;
	}
	close();
	(new TestWindow(m_ui.inputWorkNumber->text()))->show();
}
#endif // !LAMPYRIS_TEST
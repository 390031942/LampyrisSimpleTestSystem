/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */

 // Project Include(s)
#include "TestWindow.h"

// QT Include(s)
#include <QHBoxLayout>

TestWindow::TestWindow(const QString& workerNumber,QWidget *parent)
    : QWidget(parent), m_workerNumber(workerNumber) {
	m_answerWindow = new TestAnswerWindow(this);
	m_answerWindow->setFixedWidth(250);
	m_selectWindow = new TestQuestionSelectWindow(this);

	QHBoxLayout* layout = new QHBoxLayout(this);
	this->setLayout(layout);

	layout->addWidget(m_selectWindow);
	layout->addWidget(m_answerWindow);
}

TestWindow::~TestWindow()
{}

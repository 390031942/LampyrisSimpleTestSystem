/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */
#ifdef LAMPYRIS_TEST
 // Project Include(s)
#include "TestWindow.h"
#include "PathUtil.h"
#include "GlobalEventObject.h"

// QT Include(s)
#include <QHBoxLayout>
#include <QTimer>
#include <QMessageBox>

#pragma execution_character_set("utf-8")

TestWindow::TestWindow(const QString& workerNumber,QWidget *parent)
    : QWidget(parent), m_workerNumber(workerNumber) {
	m_answerWindow = new TestAnswerWindow(this);
	m_selectWindow = new TestQuestionSelectWindow(this);
	m_selectWindow->setFixedWidth(280);

	QHBoxLayout* layout = new QHBoxLayout(this);
	this->setLayout(layout);

	layout->addWidget(m_selectWindow);
	layout->addWidget(m_answerWindow);

	GlobalDataObject::answerInfo.resize(GlobalDataObject::testInfo.questions.size());
	for (int i = 0; i < GlobalDataObject::answerInfo.size(); i++) {
		GlobalDataObject::answerInfo[i].questionIndex = i;
	}

	m_selectWindow->initialize();
	m_answerWindow->initialize();

	m_startDateTime = QDateTime::currentDateTime();
	m_endDateTime = m_startDateTime;
	m_endDateTime = m_endDateTime.addSecs(GlobalDataObject::testInfo.limitTimeSec);

	m_timer = new QTimer(this);
	m_timer->setInterval(1000);
	connect(m_timer,&QTimer::timeout, [this]() {
		this->updateWindowTitle();
	});
	this->updateWindowTitle();
	m_timer->start();

	connect(&GlobalEventObject, &GlobalEventObjectClass::onSubmitAnswers, [this]() {
		m_timer->stop();
		QString title = QString("查看测试结果 厦门天马微电子 工号:%1")
			.arg(m_workerNumber);
		this->setWindowTitle(title);
	});

	this->setFixedSize(1280, 720);

	GlobalDataObject::testInfo.workerNumber = this->m_workerNumber;
}

TestWindow::~TestWindow()
{}

void TestWindow::updateWindowTitle() {
	QDateTime dt = QDateTime::currentDateTime();

	// 计算时间差（秒数）
	qint64 secondsDiff = dt.secsTo(m_endDateTime);

	if (secondsDiff <= 0) {
		m_timer->stop();
		QMessageBox::information(NULL, "提示", "测试时间到，强制交卷");
		m_answerWindow->checkAnswers();
		return;
	}

	// 将秒数差转换为"hh:mm:ss"格式
	qint64 hours   = secondsDiff / 3600;
	qint64 minutes = (secondsDiff % 3600) / 60;
	qint64 secs    = secondsDiff % 60;

	QString timeDiffStr = QString("%1:%2:%3")
		.arg(hours, 2, 10, QChar('0'))
		.arg(minutes, 2, 10, QChar('0'))
		.arg(secs, 2, 10, QChar('0'));

	QString title = QString("%1 测试倒计时:【%2】 厦门天马微电子 工号:%3")
		.arg(GlobalDataObject::testInfo.name)
		.arg(timeDiffStr)
		.arg(m_workerNumber);
		
	this->setWindowTitle(title);
}
#endif // !LAMPYRIS_TEST

/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */
#pragma once

// QT Include(s)
#include <QtWidgets/QWidget>
#include <QDateTime>

// Project Include(s)
#include "TestAnswerWindow.h"
#include "TestQuestionSelectWindow.h"

class TestWindow : public QWidget {
    Q_OBJECT
public:
                              TestWindow(const QString& workerNumber, QWidget *parent = nullptr);
                             ~TestWindow();
private slots:
    void                      updateWindowTitle();
private:
	TestAnswerWindow*         m_answerWindow;
    TestQuestionSelectWindow* m_selectWindow;
    QString                   m_workerNumber;
	QDateTime                 m_startDateTime;
	QDateTime                 m_endDateTime;
	QTimer*                   m_timer;
};

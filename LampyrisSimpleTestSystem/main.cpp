/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ. 
 */

// Project Include(s)
#include "TestEntryWindow.h"
#include "DesignWindow.h"
#include "Args.h"
#include "TestAnswerWindow.h"
#include "PathUtil.h"

// QT Include(s)
#include <QtWidgets/QApplication>
#include <QFileDialog>
#include <QMessageBox>

#pragma execution_character_set("utf-8")

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon(":/resources/logo_small.png"));

	// ����ȫ������Ϊ"����"
	QFont font("����");
	a.setFont(font);

	ARGS->init(argc, argv);

    QWidget* mainWindowToShow = nullptr;
    if (ARGS->hasArgs("--design")) {
		if (!QDir("data").exists() && !QDir().mkpath("data")) {
			QMessageBox::critical(NULL, "����΢ ���Ա༭��", "�޷�����data�ļ��У������˳�");
			return -1;
		}

        mainWindowToShow = new DesignWindow;
    }
    else {
		if (!QDir("data").exists()) {
			QMessageBox::critical(NULL, "����΢ �������", "�޷��ҵ�data�ļ��У������𻵣������˳�");
			return -1;
		}
		if (!QFile("data/test_info.json").exists()) {
			QMessageBox::critical(NULL, "����΢ �������", "�޷��ҵ�test_info.json�ļ��������𻵣������˳�");
			return -1;
		}
		mainWindowToShow = new TestEntryWindow;
    }
    mainWindowToShow->show();

    int returnVal = a.exec();
    delete mainWindowToShow;

    return returnVal;
}

int main1(int argc, char* argv[]) {
	QApplication a(argc, argv);
	ARGS->init(argc, argv);

    a.setWindowIcon(QIcon(":/resources/logo_small.png"));
	TestAnswerWindow* mainWindowToShow = new TestAnswerWindow;
	mainWindowToShow->show();
	int returnVal = a.exec();
	delete mainWindowToShow;

	return returnVal;
}
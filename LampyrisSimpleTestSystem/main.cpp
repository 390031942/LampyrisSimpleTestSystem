/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ. 
 */

// Project Include(s)
#include "TestEntryWindow.h"
#include "DesignWindow.h"
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
	
	QWidget* mainWindowToShow = nullptr;
#ifdef LAMPYRIS_DESIGN
	if (!PathUtil::existsOrCreateDataPath()) {
		QMessageBox::critical(NULL, "����΢ ���Ա༭��", "�޷�����data�ļ��У������˳�");
		return -1;
	}
	mainWindowToShow = new DesignWindow;
#elif defined(LAMPYRIS_TEST)
	if (!PathUtil::existsDataPath()) {
		QMessageBox::critical(NULL, "����΢ �������", "�޷��ҵ�data�ļ��У������𻵣������˳�");
		return -1;
	}
	if (!PathUtil::existsTestInfoJsonPath()) {
		QMessageBox::critical(NULL, "����΢ �������", "�޷��ҵ�test_info.json�ļ��������𻵣������˳�");
		return -1;
	}
	mainWindowToShow = new TestEntryWindow;
#else
    #error no specific target macro to compile.
#endif
    mainWindowToShow->show();

    int returnVal = a.exec();
    delete mainWindowToShow;

    return returnVal;
}
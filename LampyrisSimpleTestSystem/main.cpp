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

// QT Include(s)
#include <QtWidgets/QApplication>
#include <QFileDialog>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
    ARGS->init(argc, argv);

    QWidget* mainWindowToShow = nullptr;
    if (!ARGS->hasArgs("--design")) {
        mainWindowToShow = new DesignWindow;
    }
    else {
		mainWindowToShow = new TestEntryWindow;
    }
    mainWindowToShow->show();

    int returnVal = a.exec();
    delete mainWindowToShow;

    return returnVal;
}

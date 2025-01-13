/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */
#pragma once

#include <QtWidgets/QWidget>
#include "ui_TestWindow.h"

class TestWindow : public QWidget
{
    Q_OBJECT

public:
    TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private:
    Ui::TestWindowClass ui;
};

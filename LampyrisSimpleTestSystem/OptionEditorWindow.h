/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */
#pragma once

// QT Include(s)
#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QButtonGroup>

// Project Include(s)
#include "ui_OptionEditorWindow.h"
#include "DataDef.h"

class OptionEditorWindow : public QDialog {
	Q_OBJECT
	using OptionListPtr = std::vector<OptionInfo>*;
public:
	              OptionEditorWindow(QWidget* parent = nullptr);
	void          setQuestionInfo(QuestionInfo& questionInfo);
private slots:
    void          onConfirm();
    void          onAddOption();
    void          onDeleteOption();

private:
	void          showContextMenu(const QPoint& pos);
	QTableWidget* optionTable;
	QPushButton*  confirmButton;
	OptionListPtr options;
	int           contextMenuRow;
	QButtonGroup* buttonGroup;
};

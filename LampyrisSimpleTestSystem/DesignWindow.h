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
#include <QShortcut>

// Project Include(s)
#include "ui_DesignWindow.h"
#include "DataDef.h"

class DesignWindow : public QMainWindow {
	Q_OBJECT
public:
	                      DesignWindow(QWidget *parent = nullptr);
	                     ~DesignWindow();
private slots:
	void                  onSave();
	void                  onAddRow();
	void                  onAddRowFromInfo(const QuestionInfo& info);
	void                  onEditOptions(int row);
	void                  accpetOptions(int row, const std::vector<OptionInfo>& options);
	void                  onSelectImage(int row);
	void                  createImageCell(const QString& filePath, int row);
	void                  onDeleteRow(int row);
	void                  showContextMenu(const QPoint& pos);
private:
	void                  setupTable();
	void                  onCellDoubleClicked(int row, int column);

	QTableWidget*         m_tableWidget;
	int                   m_rowCount;
	int                   m_contextMenuRow;
	QShortcut*            m_shortcut;
	Ui::DesignWindowClass m_ui;
};

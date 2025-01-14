/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-14
 * Author: TengZ.
 */
#pragma once

// QT Include(s)
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QDialog>

class ClickableLabel : public QLabel {
	Q_OBJECT
public:
	explicit ClickableLabel(QWidget* parent = nullptr) : QLabel(parent) {}

signals:
	void clicked();
protected:
	void mousePressEvent(QMouseEvent* event) override {
		emit clicked();
	}
};

class TestAnswerWindow : public QWidget {
	Q_OBJECT

public:
	                TestAnswerWindow(QWidget* parent = nullptr);
private slots:
	void            showOriginalImage();
	void            onAnswerSelected(const QString& answer);
private:
	QLabel*         questionLabel;
	ClickableLabel* imageLabel;
	QComboBox*      answerComboBox;
	QPushButton*    prevButton;
	QPushButton*    nextButton;
	QPushButton*    submitButton;

	void setupUI();
	void loadQuestion(int questionNumber);
};

class ImageDialog : public QDialog {
	Q_OBJECT
public:
	        ImageDialog(const QPixmap& pixmap, QWidget* parent = nullptr);
private:
	QLabel* imageLabel;
	QPixmap originalPixmap;
};
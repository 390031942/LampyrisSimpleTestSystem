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
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

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
	void            checkAnswers();
	void            initialize();
private slots:
	void            showOriginalImage();
	void            onAnswerSelected(const QString& answer);
	void            updateRightAnswer();
private:
	QLabel*         questionLabel;
	ClickableLabel* imageLabel;
	QComboBox*      answerComboBox;
	QLabel*         answerLabel;
	QPushButton*    prevButton;
	QPushButton*    nextButton;
	QPushButton*    submitButton;
	QPixmap         pixmap;
	int             questionIndex;
	QWidget*        rightAnswerWidget;
	QLabel*         rightAnswerLabel;
	QStringList     answerList;
	QStringList     rightAnswerList;
	bool            showAnswer;
	QPixmap         pixmapNull;
	bool            isPixmapNull;

	void            loadQuestion();
};

class ImageDialog : public QDialog {
	Q_OBJECT
public:
	ImageDialog(const QPixmap& pixmap, QWidget* parent = nullptr);
protected:
	void                 wheelEvent(QWheelEvent* event) override;
	void                 mousePressEvent(QMouseEvent* event) override;
	void                 mouseMoveEvent(QMouseEvent* event) override;
	void                 mouseReleaseEvent(QMouseEvent* event) override;
private:
	QGraphicsView*       graphicsView;
	QGraphicsScene*      graphicsScene;
	QGraphicsPixmapItem* pixmapItem;
	QPoint               lastMousePos;
	bool                 isDragging;
	QLabel*              imageLabel;
	QPixmap              originalPixmap;
};
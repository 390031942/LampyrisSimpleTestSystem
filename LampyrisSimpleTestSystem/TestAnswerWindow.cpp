/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-14
 * Author: TengZ.
 */

 // Project Include(s)
#include "TestAnswerWindow.h"

 // QT Include(s)
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMessageBox>
#include <QResizeEvent>

#pragma execution_character_set("utf-8")

TestAnswerWindow::TestAnswerWindow(QWidget* parent)
	: QWidget(parent) {
	setupUI();
	loadQuestion(1);
}

void TestAnswerWindow::setupUI() {
	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	// ��һ�У���Ŀ����
	questionLabel = new QLabel(this);
	questionLabel->setWordWrap(true);
	questionLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	mainLayout->addWidget(questionLabel);

	// �ڶ��У�ͼƬ
	imageLabel = new ClickableLabel(this);
	imageLabel->setPixmap(QPixmap(":/resources/logo.png").scaled(200, 200, Qt::KeepAspectRatio));
	imageLabel->setCursor(Qt::PointingHandCursor);
	imageLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	connect(imageLabel, &ClickableLabel::clicked, this, &TestAnswerWindow::showOriginalImage);
	mainLayout->addWidget(imageLabel);

	// �����У���
	QHBoxLayout* answerLayout = new QHBoxLayout();
	QLabel* yourAnswerLabel = new QLabel("��Ĵ�: ", this);
	answerComboBox = new QComboBox(this);
	answerComboBox->addItems({ "ѡ", "ѡ12312312��B", "ѡ��312312321C", "ѡ��21312312311232D" });
	connect(answerComboBox, &QComboBox::currentTextChanged, this, &TestAnswerWindow::onAnswerSelected);
	answerLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	answerLayout->addWidget(yourAnswerLabel);
	answerLayout->addWidget(answerComboBox);
	answerLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	mainLayout->addLayout(answerLayout);

	// ���·���������ť
	QHBoxLayout* buttonLayout = new QHBoxLayout();
	prevButton = new QPushButton("��һ��", this);
	nextButton = new QPushButton("��һ��", this);
	submitButton = new QPushButton("�ύ", this);
	buttonLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	buttonLayout->addWidget(prevButton);
	buttonLayout->addWidget(nextButton);
	buttonLayout->addWidget(submitButton);
	buttonLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	mainLayout->addLayout(buttonLayout);

	setLayout(mainLayout);
}

void TestAnswerWindow::loadQuestion(int questionNumber) {
	// ʾ����Ŀ����
	QString questionText = QString("��%1��: ����һ��ʾ����Ŀ���ݣ����ܻ��ж�����ʾ��").arg(questionNumber);
	questionLabel->setText(questionText);
}

void TestAnswerWindow::showOriginalImage() {
	QPixmap pixmap(":/resources/logo.png");
	ImageDialog* dialog = new ImageDialog(pixmap, this);
	dialog->exec();
}

void TestAnswerWindow::onAnswerSelected(const QString& answer) {
}

ImageDialog::ImageDialog(const QPixmap& pixmap, QWidget* parent)
	: QDialog(parent), originalPixmap(pixmap) {
	QVBoxLayout* layout = new QVBoxLayout(this);
	imageLabel = new QLabel(this);
	imageLabel->setPixmap(pixmap);
	imageLabel->setAlignment(Qt::AlignCenter); // ����ͼƬ���ж���
	layout->addWidget(imageLabel);
	setLayout(layout);

	// ���öԻ����С��pixmap��Сһ��
	QSize size(std::max(450, pixmap.size().width()), std::max(260, pixmap.size().height()));
	resize(size);
	this->setMinimumSize(size);

	this->setWindowTitle("�鿴ͼƬ");
}
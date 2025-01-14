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

	// 第一行：题目内容
	questionLabel = new QLabel(this);
	questionLabel->setWordWrap(true);
	questionLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	mainLayout->addWidget(questionLabel);

	// 第二行：图片
	imageLabel = new ClickableLabel(this);
	imageLabel->setPixmap(QPixmap(":/resources/logo.png").scaled(200, 200, Qt::KeepAspectRatio));
	imageLabel->setCursor(Qt::PointingHandCursor);
	imageLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	connect(imageLabel, &ClickableLabel::clicked, this, &TestAnswerWindow::showOriginalImage);
	mainLayout->addWidget(imageLabel);

	// 第三行：答案
	QHBoxLayout* answerLayout = new QHBoxLayout();
	QLabel* yourAnswerLabel = new QLabel("你的答案: ", this);
	answerComboBox = new QComboBox(this);
	answerComboBox->addItems({ "选", "选12312312项B", "选项312312321C", "选项21312312311232D" });
	connect(answerComboBox, &QComboBox::currentTextChanged, this, &TestAnswerWindow::onAnswerSelected);
	answerLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	answerLayout->addWidget(yourAnswerLabel);
	answerLayout->addWidget(answerComboBox);
	answerLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	mainLayout->addLayout(answerLayout);

	// 最下方：操作按钮
	QHBoxLayout* buttonLayout = new QHBoxLayout();
	prevButton = new QPushButton("上一题", this);
	nextButton = new QPushButton("下一题", this);
	submitButton = new QPushButton("提交", this);
	buttonLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	buttonLayout->addWidget(prevButton);
	buttonLayout->addWidget(nextButton);
	buttonLayout->addWidget(submitButton);
	buttonLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	mainLayout->addLayout(buttonLayout);

	setLayout(mainLayout);
}

void TestAnswerWindow::loadQuestion(int questionNumber) {
	// 示例题目内容
	QString questionText = QString("第%1题: 这是一个示例题目内容，可能会有多行显示。").arg(questionNumber);
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
	imageLabel->setAlignment(Qt::AlignCenter); // 设置图片居中对齐
	layout->addWidget(imageLabel);
	setLayout(layout);

	// 设置对话框大小与pixmap大小一致
	QSize size(std::max(450, pixmap.size().width()), std::max(260, pixmap.size().height()));
	resize(size);
	this->setMinimumSize(size);

	this->setWindowTitle("查看图片");
}
/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-14
 * Author: TengZ.
 */

 // Project Include(s)
#include "TestAnswerWindow.h"
#include "DataDef.h"
#include "GlobalEventObject.h"

 // QT Include(s)
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMessageBox>
#include <QResizeEvent>
#include <QApplication>
#include <QScrollBar>

#pragma execution_character_set("utf-8")

TestAnswerWindow::TestAnswerWindow(QWidget* parent)
	: QWidget(parent), showAnswer(false), isPixmapNull(false) {
	pixmapNull = QPixmap(":/resources/image_empty.png")
		.scaled(800, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);

	// 第一行：题目内容
	questionLabel = new QLabel(this);
	questionLabel->setWordWrap(true);
	questionLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	mainLayout->addWidget(questionLabel);

	// 第二行：图片
	mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
	imageLabel = new ClickableLabel(this);
	imageLabel->setCursor(Qt::PointingHandCursor);
	imageLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	connect(imageLabel, &ClickableLabel::clicked, this, &TestAnswerWindow::showOriginalImage);
	mainLayout->addWidget(imageLabel);
	mainLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

	// 第三行：答案
	QHBoxLayout* answerLayout = new QHBoxLayout();
	QLabel* yourAnswerLabel = new QLabel("你的答案: ", this);
	answerComboBox = new QComboBox(this);
	answerComboBox->setMinimumWidth(120);
	answerLabel = new QLabel(this);
	connect(answerComboBox, &QComboBox::currentTextChanged, this, &TestAnswerWindow::onAnswerSelected);
	answerLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	answerLayout->addWidget(yourAnswerLabel);
	answerLayout->addWidget(answerComboBox);
	answerLayout->addWidget(answerLabel);
	mainLayout->addLayout(answerLayout);
	answerLabel->hide();

	// 第三行末尾追加：正確答案
	QHBoxLayout* rightAnswerLayout = new QHBoxLayout();
	rightAnswerLayout->setContentsMargins(0, 0, 0, 0);
	rightAnswerWidget = new QWidget(this);
	rightAnswerWidget->setLayout(rightAnswerLayout);
	rightAnswerLabel = new QLabel(this);
	rightAnswerLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	rightAnswerLayout->addWidget(new QLabel("正确答案: ", this));
	rightAnswerLayout->addWidget(rightAnswerLabel);
	rightAnswerLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	rightAnswerWidget->hide();

	answerLayout->addWidget(rightAnswerWidget);
	answerLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

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

	connect(answerComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index) {
		if (GlobalDataObject::answerInfo.size() > questionIndex) {
			QuestionStatus status;
			if (index > 0) {
				status = GlobalDataObject::answerInfo[questionIndex].status = QuestionStatus::Answered;
			}
			else {
				status = GlobalDataObject::answerInfo[questionIndex].status = QuestionStatus::Unanswered;
			}
			GlobalDataObject::answerInfo[questionIndex].selectedOption = index - 1;
			emit GlobalEventObject.onAnswerStatusChanged(questionIndex,status);
		}
	});

	connect(prevButton, &QPushButton::clicked, [this]() {
		if (questionIndex >= 1) {
			questionIndex--;
		}
		prevButton->setEnabled(questionIndex >= 1);
		nextButton->setEnabled(questionIndex < GlobalDataObject::testInfo.questions.size() - 1);

		loadQuestion();
		emit GlobalEventObject.onQuestionIndexChanged(questionIndex);
	});

	connect(nextButton, &QPushButton::clicked, [this]() {
		if (questionIndex < GlobalDataObject::testInfo.questions.size() - 1) {
			questionIndex++;
		}
		prevButton->setEnabled(questionIndex >= 1);
		nextButton->setEnabled(questionIndex < GlobalDataObject::testInfo.questions.size() - 1);

		loadQuestion();
		emit GlobalEventObject.onQuestionIndexChanged(questionIndex);
	});

	connect(submitButton, &QPushButton::clicked, [this]() {
		for (int i = 0; i < GlobalDataObject::answerInfo.size(); i++) {
			if (GlobalDataObject::answerInfo[i].status == QuestionStatus::Unanswered) {
				QMessageBox::information(NULL,"提交答案","提交答案失败，尚有未作答的题");
				return;
			}
		}

		checkAnswers();
	});

	connect(&GlobalEventObject, &GlobalEventObjectClass::onQuestionItemClicked, [this](int index) {
		questionIndex = index;
		prevButton->setEnabled(questionIndex >= 1);
		nextButton->setEnabled(questionIndex < GlobalDataObject::testInfo.questions.size() - 1);
		loadQuestion();
	});
}

void TestAnswerWindow::checkAnswers() {
	// 验证答案
	int correctCount = 0;
	answerList.clear();

	for (int i = 0; i < GlobalDataObject::answerInfo.size(); i++) {
		int optionIndex = GlobalDataObject::answerInfo[i].selectedOption;
		auto& options = GlobalDataObject::testInfo.questions[i].options;

		if (optionIndex >= 0 && optionIndex < options.size()) {
			if (options[optionIndex].answer) {
				GlobalDataObject::answerInfo[i].status = QuestionStatus::Correct;
				correctCount++;
				rightAnswerList.push_back(options[optionIndex].text);
			}
			else {
				GlobalDataObject::answerInfo[i].status = QuestionStatus::Incorrect;
				bool found = false;
				for (int j = 0; j < options.size(); j++) {
					if (options[j].answer) {
						rightAnswerList.push_back(options[j].text);
						found = true;
						break;
					}
				}
				if (!found) {
					rightAnswerList.push_back("");
				}
			}
			answerList.push_back(options[optionIndex].text);
		}
		else {
			GlobalDataObject::answerInfo[i].status = QuestionStatus::Incorrect;
			answerList.push_back("");
			rightAnswerList.push_back("");
		}
	}

	float perc = (float)correctCount / (float)(GlobalDataObject::answerInfo.size());
	QMessageBox::information(NULL, "测试结果", QString("您的正确率为%1%").arg(perc * 100.0f, 0, 'f', 1));
	emit GlobalEventObject.onSubmitAnswers();
	submitButton->hide();
	rightAnswerWidget->show();
	answerComboBox->hide();
	answerLabel->show();
	showAnswer = true;

	this->updateRightAnswer();
}

void TestAnswerWindow::initialize() {
	questionIndex = 0;
	loadQuestion();
	prevButton->setEnabled(questionIndex >= 1);
	nextButton->setEnabled(questionIndex < GlobalDataObject::testInfo.questions.size() - 1);
}

void TestAnswerWindow::loadQuestion() {
	auto& questions = GlobalDataObject::testInfo.questions;
	if (GlobalDataObject::testInfo.questions.size() > questionIndex) {
		const auto& questionInfo = GlobalDataObject::testInfo.questions[questionIndex];
		questionLabel->setText(QString("第%1题:%2").arg(questionIndex + 1).arg(questionInfo.title));
		pixmap = QPixmap(QApplication::applicationDirPath() + questionInfo.path);
		if (pixmap.isNull()) {
			pixmap = pixmapNull;
			isPixmapNull = true;
			imageLabel->setPixmap(pixmap);
		}
		else {
			isPixmapNull = false;
			imageLabel->setPixmap(pixmap.scaled(800, 600, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		}

		if (showAnswer) {
			this->updateRightAnswer();
		}
		else {
			QStringList optionList;
			optionList.push_back("未选择");
			for (int i = 0; i < questionInfo.options.size(); i++) {
				optionList.push_back(questionInfo.options[i].text);
			}
			answerComboBox->blockSignals(true);
			answerComboBox->clear();
			answerComboBox->addItems(optionList);
			answerComboBox->setCurrentIndex(GlobalDataObject::answerInfo[questionIndex].selectedOption + 1);
			answerComboBox->blockSignals(false);
		}
	}
}

void TestAnswerWindow::showOriginalImage() {
	if (isPixmapNull)
		return;

	ImageDialog* dialog = new ImageDialog(pixmap, this);
	dialog->exec();
}

void TestAnswerWindow::onAnswerSelected(const QString& answer) {
}

void TestAnswerWindow::updateRightAnswer(){
	bool correct = GlobalDataObject::answerInfo[questionIndex].status == QuestionStatus::Correct;
	answerLabel->setText(answerList[questionIndex]);
	rightAnswerLabel->setText(rightAnswerList[questionIndex]);
	rightAnswerWidget->setHidden(correct);

	answerLabel->setStyleSheet(correct ? "color: green;" : "color: red;");
}

ImageDialog::ImageDialog(const QPixmap& pixmap, QWidget* parent)
	: QDialog(parent), isDragging(false) {
	QVBoxLayout* layout = new QVBoxLayout(this);

	graphicsView = new QGraphicsView(this);
	graphicsScene = new QGraphicsScene(this);
	pixmapItem = new QGraphicsPixmapItem(pixmap);

	graphicsScene->addItem(pixmapItem);
	graphicsView->setScene(graphicsScene);
	graphicsView->setAlignment(Qt::AlignCenter);

	layout->addWidget(graphicsView);
	setLayout(layout);

	// 设置对话框大小与pixmap大小一致
	QSize size(std::min(1280, std::max(450, pixmap.size().width())), std::min(720, std::max(260, pixmap.size().height())));
	resize(size);
	this->setMinimumSize(size);

	this->setWindowTitle("查看图片 【Ctrl+鼠标滚轮可以缩放图片】");

	// 调整视图的缩放比例以适应整个图片
	graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
	graphicsView->scale(25,25);
}

void ImageDialog::wheelEvent(QWheelEvent* event) {
	if (event->modifiers() & Qt::ControlModifier) {
		if (event->angleDelta().y() > 0) {
			graphicsView->scale(1.1, 1.1);
		}
		else {
			graphicsView->scale(1.0 / 1.1, 1.0 / 1.1);
		}
		event->accept();
	}
	else {
		QDialog::wheelEvent(event);
	}
}

void ImageDialog::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		lastMousePos = event->pos();
		isDragging = true;
	}
	else {
		QDialog::mousePressEvent(event);
	}
}

void ImageDialog::mouseMoveEvent(QMouseEvent* event) {
	if (isDragging) {
		QPoint delta = event->pos() - lastMousePos;
		lastMousePos = event->pos();

		graphicsView->horizontalScrollBar()->setValue(graphicsView->horizontalScrollBar()->value() - delta.x());
		graphicsView->verticalScrollBar()->setValue(graphicsView->verticalScrollBar()->value() - delta.y());

		event->accept();
	}
	else {
		QDialog::mouseMoveEvent(event);
	}
}

void ImageDialog::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		isDragging = false;
		event->accept();
	}
	else {
		QDialog::mouseReleaseEvent(event);
	}
}
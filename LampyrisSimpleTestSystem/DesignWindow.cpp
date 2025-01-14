/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */

 // Project Include(s)
#include "DesignWindow.h"
#include "OptionEditorWindow.h"
#include "DataDef.h"
#include "PathUtil.h"

// QT Include(s)
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QDesktopServices>

#pragma execution_character_set("utf-8")

DesignWindow::DesignWindow(QWidget* parent)
	: QMainWindow(parent)
	, m_rowCount(0)
	, m_contextMenuRow(-1) {
	m_ui.setupUi(this);

	// ���Լ���
	g_testInfo.deserializeFromFile(PathUtil::getTestInfoJsonPath());

	QWidget* centralWidget = m_ui.centralWidget;
	QVBoxLayout* layout = new QVBoxLayout(centralWidget);
	{
		{
			QWidget* topWidget = new QWidget(centralWidget);
			QHBoxLayout* topWidgetLayout = new QHBoxLayout(topWidget);

			QLineEdit* inputTestName = new QLineEdit(topWidget);
			connect(inputTestName, &QLineEdit::textChanged, [](const QString& text) {
				g_testInfo.name = text;
			});

			QLineEdit* inputLimitTimeSec = new QLineEdit(topWidget);
			connect(inputLimitTimeSec, &QLineEdit::textChanged, [](const QString& text) {
				g_testInfo.limitTimeSec = text.toInt();
			});

			inputLimitTimeSec->setValidator(new QIntValidator(60, 99999999));

			topWidgetLayout->addWidget(new QLabel("��������", topWidget));
			topWidgetLayout->addWidget(inputTestName);
			topWidgetLayout->addWidget(new QLabel("��ʱ(��)", topWidget));
			topWidgetLayout->addWidget(inputLimitTimeSec);
			topWidgetLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Preferred));
			layout->addWidget(topWidget);

			inputTestName->setText(g_testInfo.name);
			inputLimitTimeSec->setText(QString::number(g_testInfo.limitTimeSec));
		}

		{
			m_tableWidget = new QTableWidget(0, 4, this);
			setupTable();
			layout->addWidget(m_tableWidget);

			for (int i = 0; i < g_testInfo.questions.size(); i++) {
				this->onAddRowFromInfo(g_testInfo.questions[i]);
			}
		}

		{
			QPushButton* addRowButton = new QPushButton("���һ��", this);
			connect(addRowButton, &QPushButton::clicked, this, &DesignWindow::onAddRow);
			layout->addWidget(addRowButton);
		}
	}

	setCentralWidget(centralWidget);
	connect(m_tableWidget, &QTableWidget::cellDoubleClicked, this, &DesignWindow::onCellDoubleClicked);
	this->setWindowTitle("����༭��");

	// ������ݼ� Ctrl+S
	m_shortcut = new QShortcut(QKeySequence("Ctrl+S"), this);
	connect(m_shortcut, &QShortcut::activated, this, &DesignWindow::onSave);
}

DesignWindow::~DesignWindow()
{}

void DesignWindow::setupTable() {
	QStringList headers = { "����", "ͼƬ", "ѡ��", "����"};
	m_tableWidget->setHorizontalHeaderLabels(headers);
	m_tableWidget->setColumnWidth(3, 60); // ���һ�п��Ϊ�̶�60
	m_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void DesignWindow::onSave() {
	if (g_testInfo.name.isEmpty()) {
		QMessageBox::information(NULL, "����༭��", "����������Ϊ��");
		return;
	}
	QString str = "";
	for (int i = 0; i < g_testInfo.questions.size(); i++) {
		auto& question = g_testInfo.questions[i];
		if (question.options.empty()) {
			str = str + "[��" + (i + 1) + "��]δ����ѡ��;\n";
		}
		if (question.options.empty()) {
			str = str + "[��" + (i + 1) + "��]δ����ѡ��;\n";
		}
	}
	g_testInfo.serializeToPath(PathUtil::getTestInfoJsonPath());
	QMessageBox::information(NULL, "����༭��", "����ɹ�");
}

void DesignWindow::onAddRow() {
	g_testInfo.questions.push_back({});
	onAddRowFromInfo({});
}

void DesignWindow::onSelectImage(int row) {
	QString dataPath = PathUtil::getDataPath();
	QString filePath = QFileDialog::getOpenFileName(this, "ѡ������ͼƬ", dataPath, "Images (*.png *.jpg *.bmp)");
	if (!filePath.isEmpty()) {
		if (!filePath.startsWith(dataPath)) {
			QMessageBox::warning(NULL, "����༭��", "������ѡ��data�ļ������ͼƬ");
			QDesktopServices::openUrl(QUrl::fromLocalFile(dataPath));
			return;
		}
		filePath = "/data" + filePath.replace(dataPath, "");
		createImageCell(filePath, row);
		g_testInfo.questions[row].path = filePath;
	}
}

void DesignWindow::createImageCell(const QString& filePath, int row) {
	QLabel* imageLabel = new QLabel(this);
	QString realPath = QApplication::applicationDirPath() + filePath;
	QPixmap pixmap(realPath);
	if (pixmap.isNull()) {
		QMessageBox::warning(this, "ѡ������ͼƬ ����", "��Ч��ͼƬ");
		return;
	}

	int width = pixmap.width();
	int height = pixmap.height();
	float ratio = width / (float)height;
	if (width > 500) {
		width = 500;
		height = width / ratio;
	}
	pixmap = pixmap.scaled(width, height, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);

	imageLabel->setPixmap(pixmap);
	imageLabel->setScaledContents(true);
	imageLabel->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
	m_tableWidget->setCellWidget(row, 1, imageLabel);
	// �����п���и�
	m_tableWidget->setColumnWidth(1, width);
	m_tableWidget->setRowHeight(row, height);
}

void DesignWindow::onAddRowFromInfo(const QuestionInfo& info) {
	int rowCount = m_rowCount;
	m_tableWidget->insertRow(m_rowCount);

	QTableWidgetItem* indexItem = new QTableWidgetItem(QString::number(m_rowCount + 1));
	indexItem->setFlags(indexItem->flags() & ~Qt::ItemIsEditable);

	QLineEdit* lineEdit = new QLineEdit(this);
	lineEdit->setText(info.title);
	m_tableWidget->setCellWidget(m_rowCount, 0, lineEdit);
	connect(lineEdit, &QLineEdit::editingFinished, [this, rowCount, lineEdit]() {
		g_testInfo.questions[rowCount].title = lineEdit->text();
	});

	QString realPath = QApplication::applicationDirPath() + info.path;
	QPixmap pixmap(realPath);

	if (pixmap.isNull()) {
		QPushButton* imageButton = new QPushButton("����ͼƬ", this);
		connect(imageButton, &QPushButton::clicked, [this, rowCount]() {
			onSelectImage(rowCount); 
		});
		m_tableWidget->setCellWidget(m_rowCount, 1, imageButton);
	}
	else {
		createImageCell(info.path, rowCount);
	}

	QWidget* optionsWidget = new QWidget(this);
	QHBoxLayout* optionsLayout = new QHBoxLayout(optionsWidget);
	optionsLayout->setContentsMargins(0, 0, 0, 0);
	optionsWidget->setLayout(optionsLayout);
	optionsWidget->installEventFilter(this);
	m_tableWidget->setCellWidget(m_rowCount, 2, optionsWidget);
	connect(optionsWidget, &QWidget::customContextMenuRequested, [this, rowCount]() { onEditOptions(rowCount); });

	accpetOptions(rowCount, info.options);

	QPushButton* delButton = new QPushButton("ɾ��", this);
	connect(delButton, &QPushButton::clicked, [this, rowCount, delButton]() {
		// ��ȡ�����źŵİ�ť
		if (delButton) {
			// ��ȡ��ť���ڵ���
			int row = m_tableWidget->indexAt(delButton->pos()).row();
			onDeleteRow(row);
		}
	});
	m_tableWidget->setCellWidget(m_rowCount, 3, delButton);

	m_rowCount++;
}

void DesignWindow::onEditOptions(int row) {
	OptionEditorWindow editor(this);
	if (g_testInfo.questions.size() <= row) {
		return;
	}
	auto& options = g_testInfo.questions[row].options;
	editor.setQuestionInfo(g_testInfo.questions[row]);

	if (editor.exec() == QDialog::Accepted) {
		accpetOptions(row, options);
	}
}

void DesignWindow::accpetOptions(int row, const std::vector<OptionInfo>& options) {
	QWidget* optionsWidget = m_tableWidget->cellWidget(row, 2);
	QHBoxLayout* optionsLayout = qobject_cast<QHBoxLayout*>(optionsWidget->layout());

	QLayoutItem* child;
	while ((child = optionsLayout->takeAt(0)) != nullptr) {
		delete child->widget();
		delete child;
	}
	for (int i = 0; i < options.size(); ++i) {
		QLabel* label = new QLabel(options[i].text, this);
		if (options[i].answer) {
			label->setStyleSheet("color: red;");
		}
		optionsLayout->addWidget(label);
	}
}

void DesignWindow::onDeleteRow(int row) {
	if (row >= 0) {
		m_tableWidget->removeRow(row);
		m_rowCount--;
		g_testInfo.questions.erase(g_testInfo.questions.begin() + row);
	}
}

void DesignWindow::showContextMenu(const QPoint& pos) {
	
}

void DesignWindow::onCellDoubleClicked(int row, int column) {
	if (column == 1) {
		onSelectImage(row);
	}
	else if (column == 2) {
		onEditOptions(row);
	}
}
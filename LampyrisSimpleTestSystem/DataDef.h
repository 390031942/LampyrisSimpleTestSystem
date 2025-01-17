/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */
#pragma once

// QT Include(s)
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>

// STD Include(s)
#include <vector>

struct OptionInfo {
	QString text;
	bool    answer;
};

struct QuestionInfo {
	QString                 title;
	QString                 path;
	std::vector<OptionInfo> options;
};

struct TestInfo {
	QString                   name;
	int                       limitTimeSec;
	std::vector<QuestionInfo> questions;
	QString                   workerNumber;

	bool serializeToPath(const QString& path) {
		QJsonObject testInfoObj;
		testInfoObj["name"] = this->name;
		testInfoObj["limitTimeSec"] = this->limitTimeSec;

		QJsonArray questionsArray;
		for (const auto& question : this->questions) {
			QJsonObject questionObj;
			questionObj["title"] = question.title;
			questionObj["path"] = question.path;

			QJsonArray optionsArray;
			for (const auto& option : question.options) {
				QJsonObject optionObj;
				optionObj["text"] = option.text;
				optionObj["answer"] = option.answer;
				optionsArray.append(optionObj);
			}
			questionObj["options"] = optionsArray;

			questionsArray.append(questionObj);
		}
		testInfoObj["questions"] = questionsArray;

		QFile file(path);
		if (!file.open(QIODevice::WriteOnly)) {
			return false;
		}
		file.write(QJsonDocument(testInfoObj).toJson());
		file.close();

		return true;
	}

	void deserializeFromFile(const QString& path) {
		QFile file(path);
		if (!file.open(QIODevice::ReadOnly)) {
			return;
		}
		QByteArray jsonData = file.readAll();
		file.close();

		QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
		if (jsonDoc.isNull()) {
			return;
		}

		QJsonObject testInfoObj = jsonDoc.object();

		this->name = testInfoObj["name"].toString();
		this->limitTimeSec = testInfoObj["limitTimeSec"].toInt();

		QJsonArray questionsArray = testInfoObj["questions"].toArray();
		for (const auto& questionValue : questionsArray) {
			QJsonObject questionObj = questionValue.toObject();
			QuestionInfo question;

			question.title = questionObj["title"].toString();
			question.path = questionObj["path"].toString();

			QJsonArray optionsArray = questionObj["options"].toArray();
			for (const auto& optionValue : optionsArray) {
				QJsonObject optionObj = optionValue.toObject();
				OptionInfo option;

				option.text = optionObj["text"].toString();
				option.answer = optionObj["answer"].toBool();

				question.options.push_back(option);
			}

			this->questions.push_back(question);
		}
	}
};

enum class QuestionStatus {
	Unanswered,
	Answered,
	Correct,
	Incorrect
};

struct QuestionStatusInfo {
	int            questionIndex;
	int            selectedOption = -1;
	QuestionStatus status = QuestionStatus::Unanswered;
};

class GlobalDataObject {
public:
	static TestInfo                        testInfo;
	static std::vector<QuestionStatusInfo> answerInfo;
};
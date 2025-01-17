/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-14
 * Author: TengZ.
 */
#pragma once

// QT Include(s)
#include <QDir>
#include <QString>
#include <QApplication>
#include <QDateTime>

class PathUtil {
public:
	static bool successGetOrCreateDataPath() {
		QString path = getDataPath();
		return !QDir(path).exists() && !QDir().mkpath(path);
	}

	static QString getDataPath() {
		QString ret = QDir(QApplication::applicationDirPath()).absolutePath() + "/data";
		return ret;
	}

	static QString getTestInfoJsonPath() {
		QString ret = getDataPath() + "/test_info.json";
		return ret;
	}

	static bool existsOrCreateDataPath() {
		QString path = getDataPath();
		return QDir(path).exists() || !QDir().mkpath(path);
	}

	static bool existsDataPath() {
		QString path = getDataPath();
		return QDir(path).exists();
	}

	static bool existsTestInfoJsonPath() {
		QString path = getTestInfoJsonPath();
		return QFile(path).exists();
	}

#ifdef LAMPYRIS_TEST
	static QString getExcelOutputPath(const QString& workNumber) {
		QString path = QDir(QApplication::applicationDirPath()).absolutePath() + "/result";
		if (!QDir(path).exists()) {
			QDir().mkpath(path);
		}
		return path + "/result_" + workNumber + "_" + QDateTime::currentDateTime().toString("yyyyMMdd") + ".xlsx";
	}
#endif // !LAMPYRIS_TEST
};
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
};
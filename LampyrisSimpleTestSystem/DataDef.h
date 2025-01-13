/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */
#pragma once

// QT Include(s)
#include <QString>

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
};
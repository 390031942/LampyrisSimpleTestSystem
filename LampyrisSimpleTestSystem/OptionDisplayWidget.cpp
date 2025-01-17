/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */

#ifdef LAMPYRIS_DESIGN

// Project Include(s)
#include "OptionDisplayWidget.h"
#include "OptionDisplayItemWidget.h"

OptionDisplayWidget::OptionDisplayWidget(QWidget* parent)
	: QWidget(parent) {
	layout = new QHBoxLayout(this);
	layout->setSpacing(10);
	layout->setContentsMargins(10, 10, 10, 10);
	setLayout(layout);
}

void OptionDisplayWidget::setOptions(const std::vector<OptionInfo>& options) {
	for (const auto& option : options) {
		OptionDisplayItemWidget* item = new OptionDisplayItemWidget(option.text, option.answer, this);
		layout->addWidget(item);
	}
}
#endif // !LAMPYRIS_DESIGN
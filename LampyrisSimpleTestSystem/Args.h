/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */
#pragma once

// QT Include(s)
#include <QString>
#include <QStringList>
#include <QMap>
#include <QVector>

// Project Include(s)
#include <Singleton.h>

namespace __hidden {
	class Args :public Singleton<Args> {
	public:
		/*
		 * 初始化命令行参数
	   	 */
		void init(int argc, char* argv[]) {
			if (!m_inited) {
				parseArgs(argc, argv);
			}

			m_inited = true;
		}

		/*
		 * 是否包含命令行参数
		 */
		bool hasArgs(const QString& arg) const {
			return m_argsMap.contains(arg);
		}

		/*
		 * 获取命令行参数后的参数列表，比如"abc.exe -p A B C"，传递arg = "-p"，则返回列表{"A","B","C"}
		 */
		QVector<QString> getArgs(const QString& arg) const {
			if (m_argsMap.contains(arg)) {
				return m_argsMap.value(arg);
			}
			return QVector<QString>();
		}

	private:
		/*
		 * 解析命令行参数
	   	 */
		void parseArgs(int argc, char* argv[]) {
			QString currentArg;
			for (int i = 1; i < argc; ++i) {
				QString arg = argv[i];
				if (arg.startsWith('-')) {
					currentArg = arg;
					m_argsMap[currentArg] = QVector<QString>();
				}
				else {
					if (!currentArg.isEmpty()) {
						m_argsMap[currentArg].append(arg);
					}
				}
			}
		}

		QMap<QString, QVector<QString>> m_argsMap;
		bool                            m_inited;
	};
} // end of namespace '__hidden'

#ifndef Args
#define ARGS __hidden::Args::getInstance()
#endif // !Args
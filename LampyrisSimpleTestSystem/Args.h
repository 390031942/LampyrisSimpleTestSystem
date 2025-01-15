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
		 * ��ʼ�������в���
	   	 */
		void init(int argc, char* argv[]) {
			if (!m_inited) {
				parseArgs(argc, argv);
			}

			m_inited = true;
		}

		/*
		 * �Ƿ���������в���
		 */
		bool hasArgs(const QString& arg) const {
			return m_argsMap.contains(arg);
		}

		/*
		 * ��ȡ�����в�����Ĳ����б�����"abc.exe -p A B C"������arg = "-p"���򷵻��б�{"A","B","C"}
		 */
		QVector<QString> getArgs(const QString& arg) const {
			if (m_argsMap.contains(arg)) {
				return m_argsMap.value(arg);
			}
			return QVector<QString>();
		}

	private:
		/*
		 * ���������в���
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
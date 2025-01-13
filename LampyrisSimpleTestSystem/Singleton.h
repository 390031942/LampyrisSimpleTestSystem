/*
 * Copyright (C) 2024 Xiamen Tianma Microelectronics Co.
 * This file is part of Lampyris Simple Test System.
 * File created at 2025-01-13
 * Author: TengZ.
 */
#pragma once

// STD Include(s)
#include <type_traits>
#include <concepts>

// QT Include(s)
#include <QObject>

template<class T>
class Singleton {
public:
	static T* getInstance() {
		static T t;
		return &t;
	}
};

template<class T, class U = QObject>
class SingletonQObject :public U {
public:
	static T* getInstance() {
		static T t;
		return &t;
	}
};

#ifndef LAMPYRIS_QOBJECT_SINGLETON
#define LAMPYRIS_QOBJECT_SINGLETON(T) \
		public: \
		inline static T* getInstance() { static T t; return &t; } \
		private:
#endif // !LAMPYRIS_QOBJECT_SINGLETON
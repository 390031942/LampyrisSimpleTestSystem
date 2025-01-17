@echo off
SetLocal EnableDelayedExpansion
(set QT_VERSION=0.3.0)
(set QT_VER=0.3)
(set QT_VERSION_TAG=030)
(set QT_INSTALL_DOCS=D:/Qt-static/doc)
(set BUILDDIR=C:/Users/Administrator/source/repos/QtXlsxWriter/src/xlsx)
D:\Qt-static\bin\qdoc.exe %*
EndLocal

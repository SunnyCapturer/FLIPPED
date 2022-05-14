﻿/*******************************************************************
 * Copyright (c) 2021-2022 偕臧  All rights reserved.
 *
 * Author: XMuli <xmulitech@gmail.com>
 * GitHub: https://github.com/XMuli
 * Blog:   https://xmuli.tech
 *
 * Date:   2021.11.06
 * Description:
 ******************************************************************/
#ifndef WINTOOLBAR_H
#define WINTOOLBAR_H

#include "../widget/xroundwidget.h"
#include "drawhelper.h"
#include <QWidget>
#include <QVector>

QT_BEGIN_NAMESPACE
class QToolButton;
class QStringList;
QT_END_NAMESPACE

// 绘画工具栏（图形选择）
class SubGrapToolBar : public QWidget
{
    Q_OBJECT
public:
    SubGrapToolBar(QWidget *parent = nullptr);
    virtual ~SubGrapToolBar();

    bool isToolBtnChecked();
    QToolButton* getCheckedToolBtn(int ignoreLastBtnNum = 4);

private:
    void initUI();

signals:
    void sigDrawStart();       // 处于绘画状态
    void sigDrawEnd();         // 处于绘画状态
    void sigDrawShape(DrawShape shape, bool checked);
    void sigUndo();
    void sigRedo();
    void sigDownload();
    void sigCopy();

public slots:
    void onToolBtn();

private:
    QStringList m_toolBtnName;
    QVector<QToolButton *> m_vecToolBar;
};

#endif // WINTOOLBAR_H

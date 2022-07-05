﻿/*******************************************************************
 * Copyright (c) 2021-2022 偕臧  All rights reserved.
 *
 * Author: XMuli <xmulitech@gmail.com>
 * GitHub: https://github.com/XMuli
 * Blog:   https://xmuli.tech
 *
 * Date:   2022.06.21
 * Description: 取色器面板
 ******************************************************************/
#ifndef COLORPARABAR_H
#define COLORPARABAR_H

#include <QColor>
#include <QMap>
#include <QString>
#include <QWidget>

class XLabel;
class QGridLayout;
class ColorParaBar : public QWidget
{
    Q_OBJECT
public:
    ColorParaBar(Qt::Orientations orien = Qt::Horizontal, QWidget *parent = nullptr);
    virtual ~ColorParaBar();
    void initUI();

signals:
    void sigColorChange(QColor);

public:
    bool eventFilter(QObject *watched, QEvent *event) override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    double m_scal;
    Qt::Orientations m_orien;
    QGridLayout* m_layout;
    QMap<QString, QString> m_labMap;
};

#endif // COLORPARABAR_H

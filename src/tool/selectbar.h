﻿// SPDX-License-Identifier:
// SPDX-FileCopyrightText: 2021-2023 XMuli <xmulitech@gmail.com>
//
// Source: https://github.com/XMuli/Flipped

#ifndef SELECTBAR_H
#define SELECTBAR_H

#include <memory>
#include "../screen/drawhelper.h"
#include "base/blurwidget.h"

class BlurWidget;
class QToolButton;
class QStringList;
class QBoxLayout;
class QAbstractButton;
class QButtonGroup;

// rectangle
// ellipse
// arrow
// custompath
// mosaic、smooth
// text
// serialnumber、
// pin
// gif 暂不添加
// revocation
// renewal
// save
// cancel
// finish
class SelectBar : public QWidget
{
    Q_OBJECT
public:
    SelectBar(Qt::Orientations orien = Qt::Horizontal, QWidget *parent = nullptr);
    virtual ~SelectBar() = default;
    void setBlurBackground(const QPixmap& pix, int blurRadius);

private:
    void initUI();
    void addWidget(QWidget *w);
    void addSpacer();
    inline bool isEnableDraw();

public slots:
    void onToolBtn();

signals:
    void sigEnableDraw(bool enable);
    void sigSelShape(DrawShape shape, bool checked);
    void sigRevocation();
    void sigRenewal();
    void sigPin();
    void sigSave();
    void sigCancel();
    void sigFinish();
    void sigInterruptEdit(const QPoint& pos);

protected: 
    void enterEvent(QEvent* event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    double m_scal;
    Qt::Orientations m_orien;
    QBoxLayout* m_layout;
    std::unique_ptr<BlurWidget> m_blur;
    std::vector<std::tuple<QToolButton*, QString, QString, bool, bool>> m_vBtns;   // pTb, btnName, tr(), bCheckable, bAddSpacer
};

#endif // SELECTBAR_H

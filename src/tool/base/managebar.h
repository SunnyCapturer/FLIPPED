/*******************************************************************
 * Copyright (c) 2021-2022 ���  All rights reserved.
 *
 * Author: XMuli <xmulitech@gmail.com>
 * GitHub: https://github.com/XMuli
 * Blog:   https://xmuli.tech
 *
 * Date:   2022.06.26
 * Description: ������������һ���֣���Ϊ�����ࣺ���Ρ���Բ����ͷ�������˵�
 ******************************************************************/
#ifndef MANAGEBAR_H
#define MANAGEBAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QBoxLayout;
QT_END_NAMESPACE

class ManageBar : public QWidget
{
    Q_OBJECT
public:
    explicit ManageBar(Qt::Orientations orien = Qt::Horizontal, QWidget* parent = nullptr);
    virtual ~ManageBar() = default;

private:
    void initUI();
    void addWidget(QWidget* w);
    void addSpacer();

signals:

private:
    int m_scal;
    Qt::Orientations m_orien;
    QBoxLayout* m_layout;
};

#endif // MANAGEBAR_H

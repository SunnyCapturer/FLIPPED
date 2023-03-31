﻿// SPDX-License-Identifier:
// SPDX-FileCopyrightText: 2021-2023 XMuli <xmulitech@gmail.com>
//
// Source: https://github.com/XMuli/Flipped

#include "drawhelper.h"
#include <QScreen>
#include <QFile>
#include <QByteArray>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QSvgRenderer>
#include <QDomElement>
#include <QDomElement>
#include <QIcon>
#include <QGraphicsEffect>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainterPath>
#include <QLine>
#include <QDir>
#include <QSettings>
#include <QDateTime>
#include <QStandardPaths>
#include "../xglobal.h"
#include "../preference/appellation.h"
#include "screenshot.h"

QString XDrawStep::serialText = "0_0_0_0";

XHelper::XHelper()
    : QObject(nullptr)
    , m_boardStyle("flipped")
    , m_borderColor(READ_CONFIG_INI(INIT_INTERFACE, tiBorderColor, "#1F7AFF").toString())
    , m_borderWidth(READ_CONFIG_INI(INIT_INTERFACE, tiBorderWidth, 1).toInt())
    , m_crosshairColor(READ_CONFIG_INI(INIT_INTERFACE, tiCrosshairColor, "#1F7AFF").toString())
    , m_crosshairWidth(READ_CONFIG_INI(INIT_INTERFACE, tiCrosshairWidth, 1).toInt())
    , m_enableSmartWindow(READ_CONFIG_INI(INIT_INTERFACE, tiSmartWindow, true).toBool())
    , m_enableCrosshair(READ_CONFIG_INI(INIT_INTERFACE, tiCrosshair, false).toBool())
    , m_enableShowCursor(READ_CONFIG_INI(INIT_INTERFACE, tiShowCursor, false).toBool())
    , m_enableAutoCpoyClip(READ_CONFIG_INI(INIT_INTERFACE, tiAutoCopyToClipboard, true).toBool())
    , m_imgQuailty(READ_CONFIG_INI(INIT_OUTPUT, toImageQuailty, -1).toInt())
    , m_winShadow(READ_CONFIG_INI(INIT_PIN, tpWindowShadow, true).toBool())
    , m_pinOpacity(READ_CONFIG_INI(INIT_PIN, tpOpacity, 100).toInt())
    , m_pinMaxSize(READ_CONFIG_INI(INIT_PIN, tpMaxSize, 100000).toInt())
{
    //m_path = { {toFileName, "picshot_$yyyyMMdd_hhmmss$.png"},
    //           {toQuickSavePath, qApp->applicationDirPath() + "/History/QuickSave"},
    //           {toAutoSavePath, qApp->applicationDirPath() + "/History/AutoSave"},
    //           {toConfigPath, qApp->applicationDirPath() + "/History/Config"}};

    m_path = { {toFileName, "picshot_$yyyyMMdd_hhmmss$.png"},
           {toQuickSavePath, QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first()},
           {toAutoSavePath, QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).first()},
           {toConfigPath, QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first()} };
}

const QString XHelper::formatToName(const QString str /*= path(toFileName)*/)
{
    auto fileName = str.trimmed();
    auto first = fileName.indexOf("$");
    auto second = fileName.lastIndexOf("$");
    auto nameTime = fileName.mid(first + 1, second - first - 1);
    auto finalyName = fileName.replace(first, second - first + 1, QDateTime::currentDateTime().toString(nameTime));

    return finalyName;
}

/*!
 * \brief changeSVGColor 修改 .svg 的填充色
 * \param path   .svg 文件路径
 * \param shape  欲修改的图形， 通常是 path、偶尔是 rect 等
 * \param color  填充的颜色
 * \param size   svg 伸缩后的尺寸
 * \return 一个 QIcon 对象
 */
QIcon XHelper::ChangeSVGColor(QString path, QString shape, QColor color, QSize size)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray baData = file.readAll();

    QDomDocument doc;
    doc.setContent(baData);
    QDomElement elem = doc.documentElement(); // const 和 值传递
    SetAttrRecur(elem, shape, "fill", color.name());

    QSvgRenderer svgRenderer(doc.toByteArray());
    // create pixmap target (could be a QImage)
    QPixmap pix(svgRenderer.defaultSize().scaled(size.width(), size.height(), Qt::KeepAspectRatio));  // fix: 修改 svg 颜色后略有模糊
    pix.fill(Qt::transparent);
    // create painter to act over pixmap
    QPainter pixPainter(&pix);
    // use renderer to render over painter which paints on pixmap
    svgRenderer.render(&pixPainter);
    QIcon myicon(pix);
    return myicon;
}

void XHelper::SetAttrRecur(QDomElement &elem, QString strtagname, QString strattr, QString strattrval)
{
    // if it has the tagname then overwritte desired attribute
    if (elem.tagName().compare(strtagname) == 0)
        elem.setAttribute(strattr, strattrval);

    // loop all children
    for (int i = 0; i < elem.childNodes().count(); i++) {
        if (!elem.childNodes().at(i).isElement())
            continue;

        QDomElement t = elem.childNodes().at(i).toElement();
        SetAttrRecur(t, strtagname, strattr, strattrval);
    }
}

const QPixmap* XHelper::smoothMosaic(QPixmap* pixmap, int radius)
{
    if (!pixmap)
        return nullptr;

    radius = qMax<int>(10, radius);
    QGraphicsBlurEffect* blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(radius);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(*pixmap);
    item->setGraphicsEffect(blur);

    QGraphicsScene scene;
    scene.addItem(item);

    QPainter painter(pixmap);
    const double DPI = ScreenShot::GetDevicePixelRatio();
    const QRect tRt(pixmap->rect().topLeft() / DPI, pixmap->rect().size() / DPI);
    scene.render(&painter, tRt, QRectF());

    blur->setBlurRadius(radius + 2);
    // multiple repeat for make blur effect stronger
    scene.render(&painter, tRt, QRectF());

    return pixmap;
}

const QImage XHelper::pixlelatedMosaic(QPixmap* pixmap, int px /*= 20*/)
{
    if (!pixmap)
        return QImage();

    const QImage& image = pixmap->toImage();
    QImage* pImage = const_cast<QImage*>(&image);
    const int width = image.width();
    const int height = image.height();

    for (int i = 0; i < width; i += px) {
        for (int j = 0; j < height; j += px) {
            QSize size(px, px);
            if (width - i < px)
                size.setWidth(width - i);
            if (height - j < px)
                size.setHeight(height - j);

            const QPoint topLeft(i, j);
            const QRect rt(topLeft, size);
            //qDebug()<<"--------->>i:"<< i << "  j:" << j << "  rt:" << rt;
            QColor color = pImage->pixelColor(rt.topLeft());
            for (int x = rt.x(); x <= rt.right(); ++x) {
                for (int y = rt.y(); y <= rt.bottom(); ++y)
                    pImage->setPixelColor(x, y, color);
            }
        }
    }

    return image;
}



QString XHelper::path(const QString key) const
{
    return m_path.value(key, "");
}

void XHelper::setPath(const QString key, const QString val)
{
    m_path.insert(key, val);
}

int XHelper::pinOpacity() const
{
    return m_pinOpacity;
}

void XHelper::setPinOpacity(int opacity)
{
    m_pinOpacity = opacity;
    emit sigChangeOpacity(opacity);
}

int XHelper::pinMaxSize() const
{
    return m_pinMaxSize;
}

void XHelper::setPinMaxSize(int val)
{
    m_pinMaxSize = val;
    emit sigChangeMaxSize(val);
}

bool XHelper::winShadow() const
{
    return m_winShadow;
}

void XHelper::setWinShadow(bool enable)
{
    m_winShadow = enable;
    emit sigChangeWinShadow(enable);
}

double XHelper::getScale(QScreen *screen)
{
    // or defined(Q_WS_WIN) || defined(Q_WS_X11)
    #if defined(Q_OS_WIN) ||  defined(Q_OS_LINUX)
        double scale = screen->logicalDotsPerInch() / 96.0;
        if (scale < 1.25)
            return 1;
        else if (1.25 <= scale && scale < 1.5)
            return 1.25;
        else if (1.5 <= scale && scale < 1.75)
            return 1.5;
        else if (1.75 <= scale && scale < 2)
            return 1.75;
        else if (2 <= scale && scale < 2.25)
            return 2;
        else if (2.25 <= scale && scale < 2.5)
            return 2.25;
        else if (2.5 <= scale && scale < 3)
            return 2.5;
        else if (3 <= scale && scale < 3.5)
            return 3;
        else if (3.5 <= scale && scale < 4)
            return 3.5;
        else
            return scale;
    #elif  defined(Q_OS_MAC)
        double scale = screen->logicalDotsPerInch() / 72.0;
        return scale;
    #endif
}

void XDrawStep::showDebug() const
{
    const auto& t = pen.widthF();
    qDebug() << "showDebug(): this:" << this;
    qDebug() << "p1:" << p1 << "   p2:" << p2 << "   rt:" << rt << "   shape:" << int(shape) << "   shapePara:" << int(shapePara);
    qDebug() << &pen << "  " << pen << "   " << pen.color().name() << "   " << pen.widthF() << "  t:" << &t << "  " << t;
    qDebug() << &brush << "  " << brush << "   " << brush.color().name();
    qDebug() << &text << "  " << text << "   font:" << font << "   textParas:" << textParas << "   serialText:" << serialText << Qt::endl;
}

void XDrawStep::partClear()
{
    p1 = QPoint();
    p2 = QPoint();
    rt = QRect();
    custPath.clear();
}

void XDrawStep::destroyClear()
{
    p1 = QPoint();
    p2 = QPoint();
    rt = QRect();
    shape = DrawShape::NoDraw;
    shapePara = ShapePara::SP_0;
    custPath.clear();
    text.clear();

    font.setBold(false);
    font.setItalic(false);
    textParas = TextPara(0);
}

void XHelper::setRunOnStart()
{
#if defined(Q_OS_WIN)
    settingIni->beginGroup(INIT_GENERAL);
    const bool bAutoRun = settingIni->value(tgSelfStarting, true).toBool();
    settingIni->endGroup();

    QSettings reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if (bAutoRun) {
        QString strAppPath = QDir::toNativeSeparators(qApp->applicationFilePath());
        strAppPath.replace(QChar('/'), QChar('\\'), Qt::CaseInsensitive);
        reg.setValue("Flipped", strAppPath);
    }
    else {
        reg.setValue("Flipped", "");
    }
#else
    // TODO 2023.03.31:
#endif
}

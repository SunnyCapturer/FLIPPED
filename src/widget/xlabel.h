#ifndef XLABEL_H
#define XLABEL_H

#include <QLabel>

class QWidget;
class QString;
class QColor;
class QWidget;
class QPainter;
class XLabel : public QLabel
{
    Q_OBJECT
public:
    explicit XLabel(QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    explicit XLabel(const QString &text, QWidget *parent=nullptr, Qt::WindowFlags f=Qt::WindowFlags());
    virtual ~XLabel();

//    void setEllipse(QColor color, double alpha, QRect rt);
//    void setOutEllipseColor(QColor color, double alpha);

    void setMargin(double margin);
    void setInEllipseR(double r); //半径

    void setInEllipseColor(QColor color, double alpha);
    void setOutEllipseColor(QColor color, double alpha);
    void setEnablemGradient(bool enablem = false);
private:
    void init();
    void setConicalGradientColor(QPainter &pa);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QColor m_inEllipse;
    double m_inAlpha;
    QColor m_outEllipse;
    double m_outAlpha;
    bool m_bGradient;

    double m_nMargin;
    double m_nInEllipseR; // 内部圆半径
};

#endif // XLABEL_H

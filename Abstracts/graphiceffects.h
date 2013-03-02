#ifndef GRAPHICEFFECTS_H
#define GRAPHICEFFECTS_H

#include <QObject>
#include <QAbstractAnimation>
#include <QSequentialAnimationGroup>
#include <QAnimationGroup>
#include <QPropertyAnimation>
#include <QWidget>

class GraphicEffects : public QObject
{
    Q_OBJECT
public:
    explicit GraphicEffects(QObject *parent = 0);

    void setAnimation(QWidget *widget, QRect startGeometry, QRect endGeometry, int time,QEasingCurve easingCurve);

    QPropertyAnimation* createAnimation(QWidget *widget, QRect startGeometry,
                                       QRect endGeometry, int time, QEasingCurve easingCurve);

    QPropertyAnimation* createAnimation(QWidget *widget,QRect endGeometry,
                                        int time, QEasingCurve easingCurve);

    void setGroupAnimation(QPropertyAnimation *animation1, QPropertyAnimation *animation2);    

signals:

    void startAnimation();

public slots:    

public:

    QPropertyAnimation *simpleAnimation;
    QSequentialAnimationGroup * groupAnimation;

};

#endif // GRAPHICEFFECTS_H

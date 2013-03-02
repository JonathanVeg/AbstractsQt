#include "graphiceffects.h"
#include <QRect>
#include <QDebug>

GraphicEffects::GraphicEffects(QObject *parent) :
    QObject(parent)
{

}

QPropertyAnimation * GraphicEffects::createAnimation(QWidget *widget, QRect startGeometry, QRect endGeometry, int time, QEasingCurve easingCurve)
{
    QPropertyAnimation *animation = new QPropertyAnimation(widget,"geometry");

    animation->setDuration(time);

    animation->setEasingCurve(easingCurve);

    animation->setStartValue(QRect(startGeometry));

    animation->setEndValue(QRect(endGeometry));

    return animation;
}

QPropertyAnimation *GraphicEffects::createAnimation(QWidget *widget, QRect endGeometry, int time, QEasingCurve easingCurve)
{
    QPropertyAnimation *animation = new QPropertyAnimation(widget,"geometry");

    animation->setDuration(time);

    animation->setEasingCurve(easingCurve);

    animation->setStartValue(QRect(widget->geometry()));

    animation->setEndValue(QRect(endGeometry));

    return animation;
}

void GraphicEffects::setGroupAnimation(QPropertyAnimation *animation1, QPropertyAnimation *animation2)
{
    groupAnimation = new QSequentialAnimationGroup();

    groupAnimation->addAnimation(animation1);

    groupAnimation->addAnimation(animation2);

    groupAnimation->start();
}

void GraphicEffects::setAnimation(QWidget *widget, QRect startGeometry, QRect endGeometry, int time,QEasingCurve easingCurve)
{
    simpleAnimation = new QPropertyAnimation(widget,"geometry");

    simpleAnimation->setDuration(time);

    simpleAnimation->setEasingCurve(easingCurve);

    simpleAnimation->setStartValue(QRect(startGeometry));

    simpleAnimation->setEndValue(QRect(endGeometry));

    simpleAnimation->start();

    emit startAnimation();
}

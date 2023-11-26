#pragma once

#include <QtWidgets/QWidget>
#include "ui_XVideoUI.h"

class XVideoUI : public QWidget
{
    Q_OBJECT

public:
    XVideoUI(QWidget *parent = nullptr);
    void timerEvent(QTimerEvent* e);
    ~XVideoUI();
 public slots:
     void Open();
     void Set();
     void Export();
private:
    Ui::XVideoUIClass ui;
};

#pragma once

#include <QtWidgets/QWidget>
#include "ui_XVideoUI.h"

class XVideoUI : public QWidget
{
    Q_OBJECT

public:
    XVideoUI(QWidget *parent = nullptr);
    ~XVideoUI();
 public slots:
     void Open();

private:
    Ui::XVideoUIClass ui;
};

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SmartLinkForDrCOM.h"

class SmartLinkForDrCOM : public QMainWindow
{
    Q_OBJECT

public:
    SmartLinkForDrCOM(QWidget *parent = nullptr);
    ~SmartLinkForDrCOM();

private:
    Ui::SmartLinkForDrCOMClass ui;
};


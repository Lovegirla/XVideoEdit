#include "XVideoUI.h"
#include <QtWidgets/qfiledialog.h>
#include<string>
#include <QtWidgets/qmessagebox.h>
#include "XVideoThread.h"
#include "XVideoWidget.h"
#include "XFilter.h"
XVideoUI::XVideoUI(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    qRegisterMetaType<cv::Mat>("cv::Mat");
    //SRC
    QObject::connect(XVideoThread::Get(),
        SIGNAL(ViewDes(cv::Mat)),
        ui.desvideo,
        SLOT(SetImage(cv::Mat))
        );
    //DES
    QObject::connect(XVideoThread::Get(),
        SIGNAL(ViewImage1(cv::Mat)),
        ui.src1video,
        SLOT(SetImage(cv::Mat))
    );
    startTimer(40);
}

void XVideoUI::timerEvent(QTimerEvent* e)
{
   double pos =  XVideoThread::Get()->GetPos();
   ui.PlaySlider->setValue(pos*1000);
}

XVideoUI::~XVideoUI()
{}

void XVideoUI::Set()
{
    XFilter::GetInstance()->Clear();
    if (ui.bright->value()>0||ui.constrat->value()>1)
    {
        XFilter::GetInstance()->Add(XTask{ XTASK_GAIN,{(double)ui.bright->value(),ui.constrat->value()} });
    }
}

void XVideoUI::Open()
{
   QString name =  QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("请选择视频文件"));
   if (name.isEmpty())
   {
       return;
   }
  std::string file =  name.toLocal8Bit().data();
  /*QMessageBox::information(this, "", name);*/
  if (!XVideoThread::Get()->Open(file)) {
      QMessageBox::information(this, "", name+"open failed!");
      return;
  }
}
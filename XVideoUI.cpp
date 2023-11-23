#include "XVideoUI.h"
#include <QtWidgets/qfiledialog.h>
#include<string>
#include <QtWidgets/qmessagebox.h>
#include "XVideoThread.h"
#include "XVideoWidget.h"
XVideoUI::XVideoUI(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    qRegisterMetaType<cv::Mat>("cv::Mat");
    QObject::connect(XVideoThread::Get(),
        SIGNAL(ViewImage1(cv::Mat)),
        ui.src1video,
        SLOT(SetImage(cv::Mat))
        );
}

XVideoUI::~XVideoUI()
{}

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
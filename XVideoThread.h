#pragma once
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <opencv2/core.hpp>
#include <string>
using namespace std;
class XVideoThread:public QThread
{
	Q_OBJECT

public:
	int fps = 0;
	static XVideoThread* Get() 
	{
		static XVideoThread vt;
		return &vt;
	};
	bool Open(const string file);
	//���ص�ǰ���ŵ�λ��
	double GetPos();
	~XVideoThread();
	bool StartSave(const std::string filename ,int width=0 ,int height=0 ) ;
	void StopSave();
	void run();
signals:
	void ViewImage1(cv::Mat mat);
	void ViewDes(cv::Mat mat);
protected:
	XVideoThread();
	bool isWrite = false;
	QMutex mutex;
};


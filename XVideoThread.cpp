#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include <iostream>
#include "XFilter.h"
using namespace std;
using namespace cv;
//一号视频
static VideoCapture cap1;
static VideoWriter vw;
static bool isexit = false;

bool XVideoThread::Open(const string file)
{
	cout << "open:" << file << endl;
	mutex.lock();
	int re = cap1.open(file);
	mutex.unlock();
	cout << re << endl;
	if (!re)
	{
		return false;
	}
	fps = cap1.get(CAP_PROP_FPS);
	if (fps <= 0) fps = 25;
	return true;
}

XVideoThread::XVideoThread()
{
	start();
}

double XVideoThread::GetPos()
{
	double pos = 0;
	mutex.lock();
	if (!cap1.isOpened())
	{
		mutex.unlock();
		return pos;
	}
	double count = cap1.get(CAP_PROP_FRAME_COUNT);
	double cur = cap1.get(CAP_PROP_POS_FRAMES);
	if (count>0.001)
	{
		pos = cur / count;
	}
	
	mutex.unlock();
	return pos;
}

XVideoThread::~XVideoThread()
{
	mutex.lock();
	isexit = true;
	mutex.unlock();
	wait();
}

bool XVideoThread::StartSave(const std::string filename, int width, int height)
{
	cout << "开始导出" << endl;
	
	if (cap1.isOpened())
	{
		return false;
	}
	if (width <=0 )
	{
		width = cap1.get(CAP_PROP_FRAME_WIDTH);
	}
	if (height <= 0)
	{
		height = cap1.get(CAP_PROP_FRAME_HEIGHT);
	}
	mutex.lock();
	
	vw.open(filename,VideoWriter::fourcc('X','2','6','4'),
		this->fps,Size(width,height));
	if (!vw.isOpened())
	{
		mutex.unlock();
		cout << "start save failed" << endl;
		return false;
	}
	this->isWrite = true;
	mutex.unlock();
	return true;
}

void XVideoThread::StopSave()
{
	cout << "停止导出" << endl;
	mutex.lock();
	vw.release();
	isWrite = false;
	mutex.unlock();
}

void XVideoThread::run()
{
	Mat mat1;
	for (;;)
	{
		mutex.lock();
		if (isexit)
		{
			mutex.unlock();
			break;
		}
		if (!cap1.isOpened()) {
			mutex.unlock();
			msleep(5);
			continue;
		}
		if (!cap1.read(mat1)||mat1.empty()) {
			
			mutex.unlock();
			if (isWrite)
			{
				StopSave();
			}
			msleep(5);
			continue;
		}
		ViewImage1(mat1);
		Mat des  = XFilter::GetInstance()->Filter(mat1,Mat());
		ViewDes(des);

		if (isWrite)
		{
			vw.write(des);
		}
		/*msleep(40);*/
		int s = 0;
		s = 1000 / fps;
		msleep(s);
		mutex.unlock();

		
	}
}

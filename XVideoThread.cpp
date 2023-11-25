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
//“ª∫≈ ”∆µ
static VideoCapture cap1;
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
			msleep(5);
			continue;
		}
		ViewImage1(mat1);
		Mat des  = XFilter::GetInstance()->Filter(mat1,Mat());
		ViewDes(des);
		/*msleep(40);*/
		int s = 0;
		s = 1000 / fps;
		msleep(s);
		mutex.unlock();

		
	}
}

#include "XVideoThread.h"
#include <opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include <iostream>
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
	return re;
}

XVideoThread::XVideoThread()
{
	start();
}

XVideoThread::~XVideoThread()
{
	mutex.lock();
	isexit = true;
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
			msleep(5);
			continue;
		}
		ViewImage1(mat1);
		msleep(40);
		mutex.unlock();

		
	}
}

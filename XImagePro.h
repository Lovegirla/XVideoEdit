#pragma once
#include <opencv2/core.hpp>
class XImagePro
{
public:
	void Set(cv::Mat mat1, cv::Mat mat2);
	cv::Mat Get() { return des; }
	//0-100
	//1.0-3.0
	void Gain(double bright,double contrast);
	XImagePro();
	~XImagePro();
private:
	//origin pic
	cv::Mat src1, src2;
	//des pic
	cv::Mat des;
};


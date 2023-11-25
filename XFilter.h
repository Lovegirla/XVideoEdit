#pragma once
#include <opencv2/core.hpp>
#include <vector>
enum XTskType
{
	XTASK_NONE,
	XTASK_GAIN,
};
class XTask {
public:
	XTskType type;
	std::vector<double> para;
};

class XFilter
{
public:
	virtual cv::Mat Filter(cv::Mat mat1, cv::Mat mat2)=0;
	virtual void Add(XTask task) = 0;
	static XFilter *GetInstance();
	virtual void Clear() = 0;
	virtual ~XFilter();

protected:
	XFilter();
};


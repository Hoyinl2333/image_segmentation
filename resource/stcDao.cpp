#include "stcDao.h"



stcDao::stcDao():blockNum(0),encodeTime(0),decodeTime(0),PSNRValue(0),BPPValue(0)
{}

int stcDao::getSegTimes()
{
    return segTimes;
}

int stcDao::getBlockNum()
{
    return blockNum;
}

cv::Mat stcDao::getSegImg()
{
    return segImg;
}

cv::Mat stcDao::getCompressedImg()
{
    return compressedImg;
}

double stcDao::getEncodeTime()
{
    return encodeTime;
}

double stcDao::getDecodeTime()
{
    return decodeTime;
}

double stcDao::getPSNRValue()
{
    return PSNRValue;
}

double stcDao::getBPPValue()
{
    return BPPValue;
}

void stcDao::setSegTimes(const int times)
{
    segTimes = times;
}

void stcDao::setBlockNum(const int num)
{
    blockNum = num;
}

void stcDao::setSegImg(const cv::Mat &img)
{
    segImg = img;
}

void stcDao::setCompressedImg(const cv::Mat &img)
{
    compressedImg = img;
}

void stcDao::setEncodeTime(const double &time)
{
    encodeTime = time;
}

void stcDao::setDecodeTime(const double &time)
{
    decodeTime = time;
}

void stcDao::setPSNRValue(const double &val)
{
    PSNRValue = val;
}

void stcDao::setBPPValue(const double &val)
{
    BPPValue = val;
}

void stcDao::clear()
{
    blockNum = 0;
    encodeTime = 0;
    decodeTime = 0;
    PSNRValue = 0;
    BPPValue = 0;
    segImg.release();
    compressedImg.release();
}



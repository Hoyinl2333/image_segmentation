#include "rnamDao.h"

rnamDao::rnamDao():blockNum(0),encodeTime(0),decodeTime(0),PSNRValue(0),BPPValue(0),CRValue(0)
{}


int rnamDao::getBlockNum()
{
    return blockNum;
}

cv::Mat rnamDao::getSegImg()
{
    return segImg;
}

cv::Mat rnamDao::getCompressedImg()
{
    return compressedImg;
}

double rnamDao::getEncodeTime()
{
    return encodeTime;
}

double rnamDao::getDecodeTime()
{
    return decodeTime;
}

double rnamDao::getPSNRValue()
{
    return PSNRValue;
}

double rnamDao::getBPPValue()
{
    return BPPValue;
}

double rnamDao::getCRValue()
{
    return CRValue;
}

void rnamDao::setBlockNum(const int num)
{
    blockNum = num;
}

void rnamDao::setSegImg(const cv::Mat &img)
{
    segImg = img;
}

void rnamDao::setCompressedImg(const cv::Mat &img)
{
    compressedImg = img;
}

void rnamDao::setEncodeTime(const double &time)
{
    encodeTime = time;
}

void rnamDao::setDecodeTime(const double &time)
{
    decodeTime = time;
}

void rnamDao::setPSNRValue(const double &val)
{
    PSNRValue = val;
}

void rnamDao::setBPPValue(const double &val)
{
    BPPValue = val;
}

void rnamDao::setCRValue(const double &val)
{
    CRValue = val;
}

void rnamDao::clear()
{
    blockNum = 0;
    encodeTime = 0;
    decodeTime = 0;
    PSNRValue = 0;
    BPPValue = 0;
    CRValue = 0;
    segImg.release();
    compressedImg.release();
}

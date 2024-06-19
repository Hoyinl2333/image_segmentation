#ifndef RNAM_DAO_H
#define RNAM_DAO_H

#include<opencv2/opencv.hpp>
class rnamDao
{
private:
    double encodeTime;//单位：ms
    double decodeTime;//单位：ms
    int blockNum;//块数
    cv::Mat segImg;//分割图
    cv::Mat compressedImg;//压缩灰度图
    double BPPValue;
    double PSNRValue;
    double CRValue;

public:
    rnamDao();

    //传入
    int getBlockNum();
    cv::Mat getSegImg();
    cv::Mat getCompressedImg();
    double getEncodeTime();
    double getDecodeTime();
    double getPSNRValue();
    double getBPPValue();
    double getCRValue();

    //传出
    void setBlockNum(const int num);
    void setSegImg(const cv::Mat &img);
    void setCompressedImg(const cv::Mat &img);
    void setEncodeTime(const double& time);
    void setDecodeTime(const double& time);
    void setPSNRValue(const double &val);
    void setBPPValue(const double &val);
    void setCRValue(const double &val);

    //清理
    void clear();
};

#endif // RNAM_DAO_H

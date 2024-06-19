#ifndef STCDAO_H
#define STCDAO_H

#include<opencv2/opencv.hpp>

class stcDao
{
private:
    int segTimes;//分割次数
    int blockNum;//块数
    cv::Mat segImg;//分割结果S
    cv::Mat compressedImg;//解码结果
    double encodeTime;//单位：ms
    double decodeTime;//单位：ms
    double PSNRValue;//PSNR
    double BPPValue;//BPP
public:
    stcDao();

    //传出
    int getSegTimes();
    int getBlockNum();
    cv::Mat getSegImg();
    cv::Mat getCompressedImg();
    double getEncodeTime();
    double getDecodeTime();
    double getPSNRValue();
    double getBPPValue();

    //传入
    void setSegTimes(const int times);
    void setBlockNum(const int num);
    void setSegImg(const cv::Mat &img);
    void setCompressedImg(const cv::Mat &img);
    void setEncodeTime(const double& time);
    void setDecodeTime(const double& time);
    void setPSNRValue(const double &val);
    void setBPPValue(const double &val);

    //清理
    void clear();
};

#endif // STCDAO_H

#ifndef RNAM_H
#define RNAM_H

#include<opencv2/opencv.hpp>

//颜色表
class Color
{
    cv::Point lt;
    cv::Point rb;
    cv::Scalar grey;
public:
    Color() { grey[0] = grey[1] = grey[2] = grey[3] = -1; }
    void setLt(cv::Point lt) { this->lt = lt; }
    void setRb(cv::Point rb) { this->rb = rb; }
    cv::Point getLt() { return lt; }
    cv::Point getRb() { return rb; }
    void setGrey(cv::Scalar grey) { this->grey = grey; }
    cv::Scalar getGrey() { return grey; }
};

class RNAM
{
public:
    double encodeTime;//单位：ms
    double decodeTime;//单位：ms
    int blockNum;//块数
    cv::Mat segImg;//分割图
    cv::Mat compressedImg;//压缩灰度图
    double BPPValue;
    double PSNRValue;
    double CRValue;

    enum class segMethod{Diagonal};
public:
    RNAM();

    void do_RNAM(const cv::Mat& imgOrigin,double epsilon,RNAM::segMethod method);

    bool isSameBlock(cv::Mat f, cv::Mat mark, cv::Point lt, cv::Point rb, int xgm);
    void mark(cv::Mat& mark, cv::Point lt, cv::Point rb);
    void EnCode(cv::Mat& R, int height, int width, std::vector<char>& Q);
    void Decode(cv::Mat& R, int height, int width, const std::vector<char>& Q);
    cv::Point REHelper(cv::Mat f, cv::Mat mark, int M, int N, cv::Point start, int xgm);
    void RNAMCEncoding(cv::Mat f, cv::Mat& R, cv::Mat& markMatrix, int M, int N, std::vector<Color>& p, std::vector<char>& q, int xgm);
    void RDHelper(cv::Mat& R, Color p1);
    void RNAMCDecoding(cv::Mat& R, int M, int N, std::vector<Color> p, std::vector<char> q);
    double PSNR(cv::Mat f, cv::Mat R, int M, int N);
    double BPP(std::vector<Color> p, int M, int N, std::vector<char> q);
    void segmentDisplay(cv::Mat& display, std::vector<Color> p);

    void clear();

};
#endif // RNAM_H

#ifndef STC_H
#define STC_H

#include<opencv2/opencv.hpp>
/*
规定：
在cv::Vec4i中，
cv::Vec4i[0]:左上角
cv::Vec4i[1]:右上角
cv::Vec4i[2]:左下角
cv::Vec4i[3]:右下角
*/

struct TreeNode
{
public:
    TreeNode* parent;
    TreeNode* nwchild;
    TreeNode* nechild;
    bool confirm;//标识符
public:
    TreeNode();
    void insert();
};
class STC
{
public:
    std::vector<cv::Vec4i>P;//颜色表P
    std::vector<cv::Vec4i>C;//区域表C

    int buildTree_callCount;
    int blockNum;//块数
    cv::Mat segImg;//分割结果S
    cv::Mat compressedImg;//解码结果
    double encodeTime;//单位：ms
    double decodeTime;//单位：ms
    double PSNRValue;//PSNR
    double BPPValue;//BPP

    enum class segMethod{Vertical, Horizonal};
public:
    STC();

    void do_stc(cv::Mat imgOrigin, double homoThres, STC::segMethod method);//meanThres和varThres估计不会用上

    void buildTree(cv::Mat img, TreeNode* root, cv::Vec4i area,double epsilon , STC::segMethod method);//创建树
    bool isSameBlock(cv::Mat img, cv::Vec4i area, double epsilon);//判断是否为同类块
    void protractSegImg(cv::Mat img,cv::Vec4i area);//绘制segImg
    void decode(cv::Mat img);//绘制decodingImg

    void clear();//清空对象
};

#endif // STC_H

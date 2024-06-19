#ifndef STC_H
#define STC_H

#include"stcDao.h"

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
    stcDao *stc_dao_object;

    std::vector<cv::Vec4i>P;//颜色表P
    std::vector<cv::Vec4i>C;//区域表C
    int buildTree_callCount;//分割次数

    enum class segMethod{Vertical, Horizonal};
public:
    STC();
    ~STC();

    //实现
    void do_stc(cv::Mat imgOrigin, double homoThres, STC::segMethod method);//meanThres和varThres估计不会用上

    void buildTree(cv::Mat img, TreeNode* root, cv::Vec4i area,double epsilon , STC::segMethod method,
                   cv::Mat&segImg,int&blockNum);//创建树
    bool isSameBlock(cv::Mat img, cv::Vec4i area, double epsilon);//判断是否为同类块
    void protractSegImg(cv::Mat img,cv::Vec4i area,cv::Mat&segImg,int&blockNum);//绘制segImg
    void decode(cv::Mat img,cv::Mat&compressedImg);//绘制decodingImg

    //传出
    int getBlockNum();
    cv::Mat getSegImg();
    cv::Mat getCompressedImg();
    double getEncodeTime();
    double getDecodeTime();
    double getPSNRValue();
    double getBPPValue();

    void clear();//清空对象
};

#endif // STC_H

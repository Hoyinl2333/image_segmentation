#include "STC.h"
#include<chrono>

STC::STC() :buildTree_callCount(0), blockNum(0), encodeTime(0), decodeTime(0), PSNRValue(0), BPPValue(0)
{
}

void STC::do_stc(cv::Mat imgOrigin, double homoThres, STC::segMethod method)
{

    /*预处理*/

    //初始化变量
    cv::Mat img_gray;

    //转换为单通道灰度图
    cv::cvtColor(imgOrigin, img_gray, cv::COLOR_BGR2GRAY);

    blockNum = 0;
    buildTree_callCount = 0;

    int img_rows = img_gray.rows;
    int img_cols = img_gray.cols;
    std::cout << img_rows << " " << img_cols << std::endl;//for test
    segImg = cv::Mat(img_gray.size(), CV_8UC1,cv::Scalar(255,255,255));
    TreeNode* root =new TreeNode();//根节点


    /*编码过程*/
    auto start = std::chrono::high_resolution_clock::now();

    buildTree(img_gray, root, cv::Vec4i(0, 0, img_rows - 1, img_cols - 1), homoThres, method);

    auto end = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    encodeTime = static_cast<double>(encode_duration.count());


    /*解码过程*/
    compressedImg = cv::Mat::zeros(img_gray.size(), CV_8UC1);
    start = std::chrono::high_resolution_clock::now();

    decode(img_gray);

    end = std::chrono::high_resolution_clock::now();
    auto decode_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    decodeTime = static_cast<double>(decode_duration.count());


    /*计算PSNR*/
    double temp = 0.0;
    for (int x = 0; x < img_gray.rows; ++x)
    {
        for (int y = 0; y < img_gray.cols; ++y)
        {
            temp += pow(img_gray.at<uchar>(x,y) - compressedImg.at<uchar>(x,y), 2);
        }
    }
    PSNRValue =  10 * log10f(pow(255.0, 2) * img_gray.rows * img_gray.cols / temp);

    /*计算BPP*/
    BPPValue = (buildTree_callCount + 32.0 * P.size()) / (img_gray.rows * img_gray.cols);

    ///*后处理*/
    //C.clear();
    //P.clear();
}

void STC::buildTree(cv::Mat img, TreeNode* root, cv::Vec4i area, double epsilon,  STC::segMethod method)
{
    ++buildTree_callCount;
    root->insert();//插入两个分支叶节点
    int x1 = area[0];
    int y1 = area[1];
    int x2 = area[2];
    int y2 = area[3];
    switch (method)
    {
    case STC::segMethod::Horizonal://水平分割
    {
        if (x1 == x2)//停止分割
        {
            root->confirm = true;
            delete root->nechild;
            root->nechild = NULL;
            delete root->nwchild;
            root->nwchild = NULL;

            //绘图
            protractSegImg(img, area);
            return;
        }
        //上半部分nwchild
        if (isSameBlock(img, cv::Vec4i(x1, y1, (x1 + x2 - 1) / 2, y2),epsilon))
        {
            root->nwchild->confirm = 1;
            protractSegImg(img, cv::Vec4i(x1, y1, (x1 + x2 - 1) / 2, y2));
        }
        else
        {
            buildTree(img, root->nwchild, cv::Vec4i(x1, y1, (x1 + x2 - 1) / 2, y2), epsilon, STC::segMethod::Vertical);
            //stc_buildTree(img, S, root->nwchild, x1, y1, (x1 + x2 - 1) / 2, y2, 0);
        }

        //下半部分nechild
        if (isSameBlock(img, cv::Vec4i((x1 + x2 + 1) / 2, y1, x2, y2),epsilon))
        {
            root->nechild->confirm = 1;
            protractSegImg(img, cv::Vec4i((x1 + x2 + 1) / 2, y1, x2, y2));
            //stc_record(img, S, (x1 + x2 + 1) / 2, y1, x2, y2);
        }
        else
        {
            buildTree(img, root->nechild, cv::Vec4i((x1 + x2 + 1) / 2, y1, x2, y2), epsilon, STC::segMethod::Vertical);
            //stc_buildTree(img, S, root->nechild, (x1 + x2 + 1) / 2, y1, x2, y2, 0);
        }
        break;
    }
    case STC::segMethod::Vertical:
    {
        if (y1 == y2)//停止分割
        {
            root->confirm = 1;
            delete root->nechild;
            root->nechild = NULL;
            delete root->nwchild;
            root->nwchild = NULL;
            protractSegImg(img, area);
            //stc_record(img, S, x1, y1, x2, y2);
            return;
        }
        //左半部分nwchild
        if (isSameBlock(img, cv::Vec4i(x1, y1, x2,(y1 + y2 - 1) / 2),epsilon))
        {
            root->nwchild->confirm = 1;
            protractSegImg(img, cv::Vec4i(x1, y1, x2, (y1 + y2 - 1) / 2));
            //stc_record(img, S, x1, y1, x2, (y1 + y2 - 1) / 2);
        }
        else
        {
            buildTree(img, root->nwchild, cv::Vec4i(x1, y1, x2, (y1 + y2 - 1) / 2), epsilon, STC::segMethod::Horizonal);
            //stc_buildTree(img, S, root->nwchild, x1, y1, x2, (y1 + y2 - 1) / 2, 1);
        }
        //右半部分nechild
        if (isSameBlock(img, cv::Vec4i(x1, (y1 + y2 + 1) / 2, x2, y2),epsilon))
        {
            root->nechild->confirm = 1;
            protractSegImg(img, cv::Vec4i(x1, (y1 + y2 + 1) / 2, x2, y2));
            //stc_record(img, S, x1, (y1 + y2 + 1) / 2, x2, y2);
        }
        else
        {
            buildTree(img, root->nechild, cv::Vec4i(x1, (y1 + y2 + 1) / 2, x2, y2), epsilon, STC::segMethod::Horizonal);
            //stc_buildTree(img, S, root->nechild, x1, (y1 + y2 + 1) / 2, x2, y2, 1);
        }
        break;
    }
    default:
        break;
    }
}

bool STC::isSameBlock(cv::Mat img, cv::Vec4i area, double epsilon)
{
    int x1 = area[0];
    int y1 = area[1];
    int x2 = area[2];
    int y2 = area[3];

    // 计算区域四个角的像素值
    uchar g1 = img.at<uchar>(x1,y1);
    uchar g2 = img.at<uchar>(x1,y2);
    uchar g3 = img.at<uchar>(x2,y1);
    uchar g4 = img.at<uchar>(x2,y2);

    for (int x = x1; x <= x2; x++)
    {
        uchar* ptr = img.ptr<uchar>(x);

        for (int y = y1; y <= y2; y++)
        {
            uchar g = ptr[y];
            //双线性差值
            double i1 = (double)(x - x1) / (x2 - x1);
            double i2 = (double)(y - y1) / (y2 - y1);
            double g5 = g1 + (g2 - g1) * i2;
            double g6 = g3 + (g4 - g3) * i2;
            double gest = g5 + (g6 - g5) * i1;
            // 如果当前像素与插值的差值超过epsilon，则不是同类块
            if (abs(g - gest) > epsilon)
            {
                return false;
            }
        }
    }
    return true;
}

void STC::protractSegImg(cv::Mat img,cv::Vec4i area)
{
    int x1 = area[0];
    int y1 = area[1];
    int x2 = area[2];
    int y2 = area[3];

    C.push_back(area);
    P.push_back({ img.at<uchar>(x1,y1),img.at<uchar>(x1,y2),img.at<uchar>(x2,y1),img.at<uchar>(x2,y2) });
    //绘制垂线
    for (int x = x1; x <= x2; ++x)
    {
        segImg.at<uchar>(x,y2) = 0;
    }
    //绘制水平线
    for (int y = y1; y <= y2; ++y)
    {
        segImg.at<uchar>(x2,y) = 0;
    }
    ++blockNum;
    /*if (blockNum < 500)
    {
        cv::imshow("apic", segImg);
        cv::waitKey(1);
    }
    //for test
    */
    return;
}

void STC::decode(cv::Mat img)
{
    for (const auto& area :C)
    {
        int x1 = area[0];
        int y1 = area[1];
        int x2 = area[2];
        int y2 = area[3];
        for (int x = x1; x <= x2; ++x)
        {
            for (int y = y1; y <= y2; ++y)
            {
                uchar g1 = img.at<uchar>(x1, y1);
                uchar g2 = img.at<uchar>(x1, y2);
                uchar g3 = img.at<uchar>(x2, y1);
                uchar g4 = img.at<uchar>(x2, y2);
                double i1 = (double)(x - x1) / (x2 - x1);
                double i2 = (double)(y - y1) / (y2 - y1);
                double g5 = g1 + (g2 - g1) * i2;
                double g6 = g3 + (g4 - g3) * i2;
                double gest = g5 + (g6 - g5) * i1;
                compressedImg.at<uchar>(x,y) = gest;
            }
        }
    }
}

void STC::clear()
{
    P.clear();
    C.clear();

    buildTree_callCount =0;
    blockNum =0;
    encodeTime =0;
    decodeTime = 0;
    BPPValue = 0;
    PSNRValue = 0;

    segImg.release();
    compressedImg.release();
}




TreeNode::TreeNode():nwchild(NULL),nechild(NULL),parent(NULL),confirm(false)
{}

void TreeNode::insert()
{
    nwchild = new TreeNode();
    nechild = new TreeNode();
    nwchild->parent = nechild->parent = this;
}





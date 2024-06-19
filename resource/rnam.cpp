#include "RNAM.h"
#include<chrono>

RNAM::RNAM():rnam_dao_object(new rnamDao())
{}

RNAM::~RNAM()
{
    if(rnam_dao_object!=nullptr)
    {
        delete rnam_dao_object;
        rnam_dao_object = nullptr;
    }
}

void RNAM::do_RNAM(const cv::Mat& imgOrigin, double epsilon,RNAM::segMethod method)
{
    int blockNum = 0;//块数
    cv::Mat segImg;//分割结果S
    cv::Mat compressedImg;//解码结果
    double encodeTime = 0;//单位：ms
    double decodeTime = 0;//单位：ms
    double PSNRValue = 0;//PSNR
    double BPPValue = 0;//BPP
    double CRValue = 0;

    if (imgOrigin.empty())
    {
        return;
    }

    /*分割同类块及编码*/
    int img_rows = imgOrigin.rows;
    int img_cols = imgOrigin.cols;

    cv::Mat img_gray ;
    cvtColor(imgOrigin, img_gray, cv::COLOR_BGR2GRAY);
    cv::Mat markMatrix = cv::Mat::zeros(img_rows, img_cols, CV_8UC1);
    cv::Mat R = cv::Mat::zeros(img_rows, img_cols, CV_8UC1);

    std::vector<Color> colorList;
    std::vector<char> coordinateList;

    auto start = std::chrono::high_resolution_clock::now();

    /*分块*/
    RNAMCEncoding(img_gray, R, markMatrix, img_rows, img_cols, colorList, coordinateList, epsilon);

    /*矩阵编码*/
    EnCode(R, img_rows, img_cols, coordinateList);

    auto end = std::chrono::high_resolution_clock::now();
    auto encode_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    encodeTime = static_cast<double>(encode_duration.count());

    /*二，还原图像矩阵及图像*/
    compressedImg = cv::Mat::zeros(img_rows, img_cols, CV_8UC1);

    start = std::chrono::high_resolution_clock::now();

    Decode(compressedImg, img_rows, img_cols, coordinateList);
    RNAMCDecoding(compressedImg, img_rows, img_cols, colorList, coordinateList);

    end = std::chrono::high_resolution_clock::now();
    encode_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    decodeTime = static_cast<double>(encode_duration.count());

    /*相关信息*/
    blockNum = colorList.size();
    PSNRValue = PSNR(img_gray, compressedImg, img_rows, img_cols);
    BPPValue = BPP(colorList, img_rows, img_cols, coordinateList);
    CRValue = 8.0 / BPPValue;

    /*分割图*/
    segImg = cv::Mat(img_rows, img_cols, CV_8UC1, cv::Scalar::all(255));
    segmentDisplay(segImg, colorList);

    rnam_dao_object->setBlockNum(blockNum);
    rnam_dao_object->setBPPValue(BPPValue);
    rnam_dao_object->setCompressedImg(compressedImg);
    rnam_dao_object->setCRValue(CRValue);
    rnam_dao_object->setDecodeTime(decodeTime);
    rnam_dao_object->setEncodeTime(encodeTime);
    rnam_dao_object->setPSNRValue(PSNRValue);
    rnam_dao_object->setSegImg(segImg);
}

//使用改良isSameBlock阴影法判断是否同类块
bool RNAM::isSameBlock(cv::Mat f, cv::Mat mark, cv::Point lt, cv::Point rb, int xgm)
{
    uchar g1 = f.at<uchar>(lt);
    uchar g2 = f.at<uchar>(cv::Point(rb.x, lt.y));
    uchar g3 = f.at<uchar>(cv::Point(lt.x, rb.y));
    uchar g4 = f.at<uchar>(rb);
    //标准矩形
    if (lt.x < rb.x && lt.y < rb.y)
    {
        int flag = 1;
        for (int j = lt.y; j <= rb.y; j++)
        {
            for (int i = lt.x; i <= rb.x; i++)
            {
                double i1 = (j - lt.y) / (double)(rb.y - lt.y);
                double i2 = (i - lt.x) / (double)(rb.x - lt.x);
                double g5 = g1 + (g2 - g1) * i2;
                double g6 = g3 + (g4 - g3) * i2;
                double gest = g5 + (g6 - g5) * i1;
                //cout << g1 << " " << g2 << " " << g3 << " " << g4 << " " << g5 << " " << g6 << " " << gest << " "<<f.at<uchar>(cv::Point(i,j))<<endl;
                if (abs(f.at<uchar>(cv::Point(i, j)) - gest) > xgm || mark.at<uchar>(cv::Point(i, j)) == 1)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 0)break;
        }
        return flag;
    }
    //宽为1的矩形
    else if (lt.x != rb.x && lt.y == rb.y)
    {
        int flag = 1;
        for (int i = lt.x; i <= rb.x; i++)
        {
            double i2 = (i - lt.x) / (double)(rb.x - lt.x);
            double gest = g1 + (g4 - g1) * i2;
            if (abs(f.at<uchar>(cv::Point(i, lt.y)) - gest) > xgm || mark.at<uchar>(cv::Point(i, lt.y)) == 1)
            {
                flag = 0;
                break;
            }
        }
        return flag;
    }
    //长为1的矩形
    else if (lt.x == rb.x && lt.y != rb.y)
    {
        int flag = 1;
        for (int j = lt.y; j <= rb.y; j++)
        {
            double i1 = (j - lt.y) / (double)(rb.y - lt.y);
            double gest = g1 + (g4 - g1) * i1;
            if (abs(f.at<uchar>(cv::Point(lt.x, j)) - gest) > xgm || mark.at<uchar>(cv::Point(lt.x, j)) == 1)
            {
                flag = 0;
                break;
            }
        }
        return flag;
    }
    //孤立点矩形
    else if (lt.x == rb.x && lt.y == rb.y)
    {
        //double g1 = f.at<uchar>(lt);
        if (mark.at<uchar>(lt) == 1)return 0;
        return 1;
    }
}

//给灰度图f已经搜索过的矩形子模式做标记
void RNAM::mark(cv::Mat& mark, cv::Point lt, cv::Point rb)
{
    for (int i = lt.y; i <= rb.y; i++)
        for (int j = lt.x; j <= rb.x; j++)
            mark.at<uchar>(i, j) = 1;
}

void RNAM::EnCode(cv::Mat& R, int height, int width, std::vector<char>& Q)
{
    int c = 0;
    int offsetValue = 0;
    int count = 0;

    for (int i = 0; i < height; i++)
    {
        c = 0;
        offsetValue = 0;
        count = 0;
        //Q.push_back(' ');
        for (int j = 0; j < width; j++)
        {
            int value = R.at<uchar>(i, j);
            if (0 == value)
            {
                if (j == width - 1)
                {
                    Q.push_back('0');
                }
            }
            else
            {
                if (1 == value)
                {
                    Q.push_back('1');
                    Q.push_back('1');

                }
                else if (2 == value)
                {
                    Q.push_back('1');
                    Q.push_back('0');
                    Q.push_back('1');
                }
                else if (3 == value)
                {
                    Q.push_back('1');
                    Q.push_back('0');
                    Q.push_back('0');

                }

                //位置从1开始 不是从0开始 所以多减去1
                int b = ceil(log((double)(width - c - count)) / log(2.0f));
                if (0 == count)
                {
                    offsetValue = j;
                }
                else
                {
                    offsetValue = j - c - 1;
                }

                b = (b == 0) ? 1 : b;
                count = 1;
                c = j;

                for (int v = b - 1; v >= 0; v--)
                {
                    if ((offsetValue & (1 << v)) == 0)
                    {
                        Q.push_back('0');
                    }
                    else
                    {
                        Q.push_back('1');
                    }
                }
            }
        }
    }
}

void RNAM::Decode(cv::Mat& R, int height, int width, const std::vector<char>& Q)
{
    int n = 0;
    int count = 0;
    //上个非零元素的位置
    int c = 0;
    int row = 0;
    int num = 0;
    for (int pos = 0; pos < Q.size(); pos++)
    {
        if ('1' == Q[pos])
        {
            pos++;
            if ('1' == Q[pos])
            {
                n = 1;

            }
            else
            {
                pos++;
                if ('1' == Q[pos])
                {
                    n = 2;
                }
                else
                {
                    n = 3;
                }
            }
        }
        else
        {
            row++;
            count = 0;
            c = 0;
            num = 0;
            continue;
        }

        int b = ceil(log((double)(width - c - count)) / log(2.0f));
        b = b == 0 ? 1 : b;
        count = 1;

        int value = 0;
        for (int i = b - 1; i >= 0; i--)
        {
            pos++;
            if ('1' == Q[pos])
            {
                value += 1 << i;
            }
        }

        if (0 == num)
        {
            c = c + value;
        }
        else
        {
            c = c + value + 1;
        }

        num++;


        R.at<uchar>(row, c) = n;

        if (c == (width - 1))
        {
            row++;
            count = 0;
            c = 0;
            num = 0;
        }
    }
}

//寻找最大的矩形子模式
cv::Point RNAM::REHelper(cv::Mat f, cv::Mat mark, int M, int N, cv::Point start, int xgm)
{
    cv::Point end = start;
    cv::Point end1, end2;
    while (end.x < M && end.y < N && (mark.at<uchar>(end) == 0) && (mark.at<uchar>(start) == 0)) {
        if (!isSameBlock(f, mark, start, end, xgm)) break;
        end.x++;
        end.y++;
    }
    end.x--;
    end.y--;

    end1 = end;

    while (end1.x < M && (mark.at<uchar>(end1) == 0)) {
        if (!isSameBlock(f, mark, start, end1, xgm)) break;
        end1.x++;
    }
    end1.x--;

    end2 = end;
    while (end2.y < N && (mark.at<uchar>(end2) == 0)) {
        if (!isSameBlock(f, mark, start, end2, xgm)) break;
        end2.y++;
    }
    end2.y--;


    if ((end2.x - start.x + 1) * (end2.y - start.y + 1) > (end1.x - start.x + 1) * (end1.y - start.y + 1))return end2;
    else return end1;

}


void RNAM::RNAMCEncoding(cv::Mat f, cv::Mat& R, cv::Mat& markMatrix, int M, int N, std::vector<Color>& p, std::vector<char>& q, int xgm)
{
    cv::Point start, end;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
        {
            if (markMatrix.at<uchar>(i, j) == 0)
            {
                start = cv::Point(j, i);
                end = REHelper(f, markMatrix, M, N, start, xgm);
                Color p1;
                p1.setLt(start);
                p1.setRb(end);
                uchar g1 = f.at<uchar>(start);
                uchar g2 = f.at<uchar>(cv::Point(end.x, start.y));
                uchar g3 = f.at<uchar>(cv::Point(start.x, end.y));
                uchar g4 = f.at<uchar>(end);
                if (start.x < end.x && start.y < end.y)
                {
                    p1.setGrey(cv::Scalar(g1, g2, g3, g4));
                    R.at<uchar>(start) = 1;
                    R.at<uchar>(end) = 2;
                }
                //宽为1的矩形
                if (start.x != end.x && start.y == end.y)
                {
                    p1.setGrey(cv::Scalar(g1, 0, 0, g4));
                    R.at<uchar>(start) = 1;
                    R.at<uchar>(end) = 2;
                }
                //长为1的矩形
                if (start.x == end.x && start.y != end.y)
                {
                    p1.setGrey(cv::Scalar(g1, 0, 0, g4));
                    R.at<uchar>(start) = 1;
                    R.at<uchar>(end) = 2;
                }
                //孤立点矩形
                if (start.x == end.x && start.y == end.y)
                {
                    p1.setGrey(cv::Scalar(g1, 0, 0, 0));
                    R.at<uchar>(start) = 3;
                }
                p.push_back(p1);
                mark(markMatrix, start, end);
            }
        }
}

//恢复矩形子模式的值
void RNAM::RDHelper(cv::Mat& R, Color p1)
{
    cv::Point lt = p1.getLt();
    cv::Point rb = p1.getRb();
    uchar g1 = p1.getGrey()[0];
    uchar g2 = p1.getGrey()[1];
    uchar g3 = p1.getGrey()[2];
    uchar g4 = p1.getGrey()[3];
    //标准矩形
    if (lt.x < rb.x && lt.y < rb.y)
    {

        for (int j = lt.y; j <= rb.y; j++)
        {
            for (int i = lt.x; i <= rb.x; i++)
            {
                double i1 = (j - lt.y) / (double)(rb.y - lt.y);
                double i2 = (i - lt.x) / (double)(rb.x - lt.x);
                double g5 = g1 + (g2 - g1) * i2;
                double g6 = g3 + (g4 - g3) * i2;
                double gest = g5 + (g6 - g5) * i1;
                R.at<uchar>(cv::Point(i, j)) = gest;
            }
        }
    }
    //宽为1的矩形
    if (lt.x != rb.x && lt.y == rb.y)
    {
        for (int i = lt.x; i <= rb.x; i++)
        {
            double i2 = (i - lt.x) / (double)(rb.x - lt.x);
            double gest = g1 + (g4 - g1) * i2;
            R.at<uchar>(cv::Point(i, lt.y)) = gest;
        }
    }
    //长为1的矩形
    if (lt.x == rb.x && lt.y != rb.y)
    {
        for (int j = lt.y; j <= rb.y; j++)
        {
            double i1 = (j - lt.y) / (double)(rb.y - lt.y);
            double gest = g1 + (g4 - g1) * i1;
            R.at<uchar>(cv::Point(lt.x, j)) = gest;
        }
    }
    //孤立点矩形
    if (lt.x == rb.x && lt.y == rb.y)
    {
        R.at<uchar>(cv::Point(lt.x, lt.y)) = g1;
    }
}

void RNAM::RNAMCDecoding(cv::Mat& R, int M, int N, std::vector<Color> p, std::vector<char> q)
{
    for (int i = 0; i < p.size(); i++)
        RDHelper(R, p[i]);
}

double RNAM::PSNR(cv::Mat f, cv::Mat R, int M, int N)
{
    double mid = 0;;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            mid += pow(f.at<uchar>(i, j) - R.at<uchar>(i, j), 2);
        }
    return 10 * log10f(pow(255., 2) * M * N / mid);
}

double RNAM::BPP(std::vector<Color> p, int M, int N, std::vector<char> q)
{
    int a1 = 0, a2 = 0, a3 = 0;
    for (int i = 0; i < p.size(); i++) {
        if (p[i].getGrey()[0] != -1 && p[i].getGrey()[3] != -1) a1++;
        else if (p[i].getGrey()[1] == -1 && p[i].getGrey()[2] == -1) a3++;
        else  a2++;
    }
    double BPPValue = (q.size() + 16 * a1 + 8 * a2 + 4.0 * a3) / (M * N);
    return BPPValue;
}

void RNAM::segmentDisplay(cv::Mat& display, std::vector<Color> p)
{
    for (int i = 0; i < p.size(); i++) {
        rectangle(display, p[i].getLt(), p[i].getRb(), cv::Scalar(0), 1);
    }
}

void RNAM::clear()
{
    rnam_dao_object->clear();
}

int RNAM::getBlockNum()
{
    return rnam_dao_object->getBlockNum();
}

cv::Mat RNAM::getSegImg()
{
    return rnam_dao_object->getSegImg();
}

cv::Mat RNAM::getCompressedImg()
{
    return rnam_dao_object->getCompressedImg();
}

double RNAM::getEncodeTime()
{
    return rnam_dao_object->getEncodeTime();
}

double RNAM::getDecodeTime()
{
    return rnam_dao_object->getDecodeTime();
}

double RNAM::getPSNRValue()
{
    return rnam_dao_object->getPSNRValue();
}

double RNAM::getBPPValue()
{
    return rnam_dao_object->getBPPValue();
}

double RNAM::getCRValue()
{
    return rnam_dao_object->getCRValue();
}






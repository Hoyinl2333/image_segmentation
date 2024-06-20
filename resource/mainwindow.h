/*mainwindow.h*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class STC;
class RNAM;
class QLabel;
class QPixmap;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inputAction_triggered();

    void on_initAction_triggered();

    void on_startAction_triggered();

    void on_outputAction_triggered();

private:
    Ui::MainWindow *ui;


private:
    //存储原始图像
    QPixmap m_image;

    //图像分割对象
    STC *stcObject;
    RNAM *rnamObject;

    //初始化函数
    void init();//在这个界面添加初始化界面内容

    //状态栏右侧Label
    QLabel* statusBarLabel;

    //显示图片相关
    enum displayOptions{Height_Priority,Width_Priority,Adaptive,Original_Size};
    void displayImgInLabel(QPixmap m_img,QLabel*label,displayOptions method);

    //QImage、QPixmap和cv::Mat之间的转换
    cv::Mat QImageTocvMat(const QImage& image,bool isCloneImageData);

    cv::Mat QPixmapTocvMat(const QPixmap& pixmap,bool isCloneImageData);

    QImage cvMatToQImage(const cv::Mat& mat);

    QPixmap cvMatToQPixmap(const cv::Mat& mat);

//自定义的槽函数
private slots:
    void doAdaptiveActionsTriggered();

};
#endif // MAINWINDOW_H

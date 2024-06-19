#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"stc.h"
#include"rnam.h"

#include<QLabel>
#include<QPixmap>
#include<QFileDialog>
#include<QFileInfo>
#include<QList>
#include<QMessageBox>
#include<QProgressBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete stcObject;
    delete rnamObject;
    delete ui;
}

//初始化界面
void MainWindow::init()
{
    //创建分割方法对象
    stcObject = new STC();
    rnamObject = new RNAM();

    //信息栏初始化
    ui->lblImgOrigin->setText("原图像显示区");
    ui->textEdit->setText("信息显示区");

    //工具栏
    ui->initAction->setEnabled(true);
    ui->inputAction->setEnabled(true);
    ui->outputAction->setEnabled(false);
    ui->startAction->setEnabled(false);
    ui->adaptHeightHction->setEnabled(false);
    ui->adaptWidthAction->setEnabled(false);
    ui->setOriginSizeAction->setEnabled(false);

    // 将三个调整图片动作连接到同一个槽函数
    connect(ui->adaptHeightHction, &QAction::triggered, this, &MainWindow::doAdaptiveActionsTriggered);
    connect(ui->adaptWidthAction, &QAction::triggered, this, &MainWindow::doAdaptiveActionsTriggered);
    connect(ui->setOriginSizeAction, &QAction::triggered, this, &MainWindow::doAdaptiveActionsTriggered);

    //结果显示区

    // ui->lbl_RNAM_segmentation->setText("分割结果显示区");
    // ui->lbl_RNAM_compression->setText("压缩图像显示区");
    // ui->lbl_STC_segmentation->setText("分割结果显示区");
    // ui->lbl_STC_compression->setText("压缩图像显示区");

    //默认参数
    ui->doubleSpinBox_RNAM_epsilon->setValue(30.0);
    ui->doubleSpinBox_STC_epsilon->setValue(30.0);
    ui->comboBox_RNAM_segMethod->setCurrentIndex(0);
    ui->comboBox_STC_segMethod->setCurrentIndex(0);


    //状态栏
    statusBarLabel = new QLabel(this);
    statusBar()->showMessage("就绪");
    statusBar()->addPermanentWidget(statusBarLabel);
}

void MainWindow::displayImgInLabel(QPixmap m_img, QLabel *label, displayOptions method)
{
    switch(method)
    {
    case displayOptions::Height_Priority:
    {
        int lblHeight = label->height();
        QPixmap pix = m_img.scaledToHeight(lblHeight-2);
        label->setPixmap(pix);
        break;
    }
    case displayOptions::Width_Priority:
    {
        int lblWidth = label->width();
        QPixmap pix = m_img.scaledToHeight(lblWidth-2);
        label->setPixmap(pix);
        break;
    }
    case displayOptions::Adaptive:
    {
        QPixmap pix;
        if(m_img.height()>m_img.width())
        {
            int lblHeight = label->height();
            pix = m_img.scaledToHeight(lblHeight-2);
        }
        else
        {
            int lblWidth = label->width();
            pix = m_img.scaledToWidth(lblWidth-2);
        }
        label->setPixmap(pix);
        break;
    }
    case displayOptions::Original_Size:
    {
        label->setPixmap(m_img);
        break;
    }
    default:
        break;
    }
}

cv::Mat MainWindow::QImageTocvMat(const QImage &image, bool isCloneImageData)
{
    QImage inImage = image;

    switch ( inImage.format() )
    {
    // 8-bit, 4 channel
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
    {
        cv::Mat  mat( inImage.height(), inImage.width(),
                    CV_8UC4,
                    const_cast<uchar*>(inImage.bits()),
                    static_cast<size_t>(inImage.bytesPerLine())
                    );

        return (isCloneImageData ? mat.clone() : mat);
    }

    // 8-bit, 3 channel
    case QImage::Format_RGB32:
    case QImage::Format_RGB888:
    {
        if ( !isCloneImageData )
        {
            qWarning() << "CVS::QImageToCvMat() - Conversion requires cloning because we use a temporary QImage";
        }

        QImage   swapped = inImage;

        if ( inImage.format() == QImage::Format_RGB32 )
        {
            swapped = swapped.convertToFormat( QImage::Format_RGB888 );
        }

        swapped = swapped.rgbSwapped();

        return cv::Mat( swapped.height(), swapped.width(),
                       CV_8UC3,
                       const_cast<uchar*>(swapped.bits()),
                       static_cast<size_t>(swapped.bytesPerLine())
                       ).clone();
    }

    // 8-bit, 1 channel
    case QImage::Format_Indexed8:
    {
        cv::Mat  mat( inImage.height(), inImage.width(),
                    CV_8UC1,
                    const_cast<uchar*>(inImage.bits()),
                    static_cast<size_t>(inImage.bytesPerLine())
                    );

        return (isCloneImageData ? mat.clone() : mat);
    }

    default:
        qWarning() << "CVS::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
        break;
    }
    return cv::Mat();
}

cv::Mat MainWindow::QPixmapTocvMat(const QPixmap &pixmap, bool isCloneImageData)
{
    return QImageTocvMat(pixmap.toImage(),isCloneImageData);
}

QImage MainWindow::cvMatToQImage(const cv::Mat &mat)
{
    switch ( mat.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( mat.data,
                     mat.cols, mat.rows,
                     static_cast<int>(mat.step),
                     QImage::Format_ARGB32 );

        return image;
    }

    // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( mat.data,
                     mat.cols, mat.rows,
                     static_cast<int>(mat.step),
                     QImage::Format_RGB888 );

        return image.rgbSwapped();
    }

    // 8-bit, 1 channel
    case CV_8UC1:
    {
        QImage image( mat.data,
                     mat.cols, mat.rows,
                     static_cast<int>(mat.step),
                     QImage::Format_Grayscale8 );
        return image;
    }

    default:
        qWarning() << "CVS::cvMatToQImage() - cv::Mat image type not handled in switch:" << mat.type();
        break;
    }

    return QImage();
}

QPixmap MainWindow::cvMatToQPixmap(const cv::Mat &mat)
{
    return QPixmap::fromImage( cvMatToQImage( mat));
}

void MainWindow::doAdaptiveActionsTriggered()
{
    displayOptions method;
    QObject* sender = QObject::sender();
    if(sender==ui->adaptHeightHction)
    {
        method = displayOptions::Height_Priority;
    }
    else if(sender==ui->adaptWidthAction)
    {
        method = displayOptions::Width_Priority;
    }
    else
    {
        method = displayOptions::Original_Size;
    }

    displayImgInLabel(m_image,ui->lblImgOrigin,method);
    displayImgInLabel(cvMatToQPixmap(stcObject->getCompressedImg()),ui->lbl_STC_compression,method);
    displayImgInLabel(cvMatToQPixmap(stcObject->getSegImg()),ui->lbl_STC_segmentation,method);
    displayImgInLabel(cvMatToQPixmap(rnamObject->getCompressedImg()),ui->lbl_RNAM_compression,method);
    displayImgInLabel(cvMatToQPixmap(rnamObject->getSegImg()),ui->lbl_RNAM_segmentation,method);
}

void MainWindow::on_inputAction_triggered()
{
    //清理容器
    stcObject->clear();
    rnamObject->clear();

    //清理结果显示区
    ui->lbl_RNAM_compression->setPixmap(QPixmap());
    ui->lbl_RNAM_segmentation->setPixmap(QPixmap());
    ui->lbl_STC_compression->setPixmap(QPixmap());
    ui->lbl_STC_segmentation->setPixmap(QPixmap());


    //导入图片
    QString imgDir =QFileDialog::getOpenFileName(this,
                                                  tr("Open File"),
                                                  QDir::currentPath(),
                                                  tr("Images (*.png *.jpg *.jpeg *.bmp)")
                                                  );

    if(imgDir.isNull())
    {
        ui->statusbar->showMessage("图片导入失败！");
        return;
    }
    m_image.load(imgDir);
    if(m_image.isNull())
    {
        ui->statusbar->showMessage("图片导入失败！");
        return;
    }
    //显示文件名
    QFileInfo fileInfo(imgDir);
    QString fileName = fileInfo.fileName();
    statusBarLabel->setText("文件名：" + fileName);

    //显示图片
    displayImgInLabel(m_image,ui->lblImgOrigin,displayOptions::Adaptive);

    //action状态更改
    ui->startAction->setEnabled(true);
    ui->adaptHeightHction->setEnabled(true);
    ui->adaptWidthAction->setEnabled(true);
    ui->setOriginSizeAction->setEnabled(true);

    //状态栏显示
    statusBar()->showMessage("图片导入成功！");
}


void MainWindow::on_initAction_triggered()
{
    //内部数据初始化
    m_image = QPixmap();
    stcObject->clear();
    rnamObject->clear();

    //信息区初始化
    ui->lblImgOrigin->setPixmap(QPixmap());
    ui->lblImgOrigin->setText("原始图像显示区");
    ui->textEdit->clear();

    //默认参数初始化
    ui->doubleSpinBox_RNAM_epsilon->setValue(30.0);
    ui->doubleSpinBox_STC_epsilon->setValue(30.0);
    ui->comboBox_RNAM_segMethod->setCurrentIndex(0);
    ui->comboBox_STC_segMethod->setCurrentIndex(0);

    //结果显示区初始化
    ui->lbl_RNAM_compression->setPixmap(QPixmap());
    ui->lbl_RNAM_segmentation->setPixmap(QPixmap());
    ui->lbl_STC_compression->setPixmap(QPixmap());
    ui->lbl_STC_segmentation->setPixmap(QPixmap());

    //工具栏初始化
    ui->initAction->setEnabled(true);
    ui->inputAction->setEnabled(true);
    ui->outputAction->setEnabled(false);
    ui->startAction->setEnabled(false);
    ui->adaptHeightHction->setEnabled(false);
    ui->adaptWidthAction->setEnabled(false);
    ui->setOriginSizeAction->setEnabled(false);

    //状态栏初始化
    statusBarLabel->clear();
    statusBar()->showMessage("初始化完毕！");
}


void MainWindow::on_startAction_triggered()
{
    statusBar()->showMessage("任务开始执行");
    auto start = std::chrono::high_resolution_clock::now();

    //获取参数
    double stc_epsilon = ui->doubleSpinBox_STC_epsilon->value();
    STC::segMethod stc_method = ui->comboBox_STC_segMethod->currentIndex()==0?STC::segMethod::Vertical:STC::segMethod::Horizonal;
    double rnam_epsilon = ui->doubleSpinBox_RNAM_epsilon->value();
    RNAM::segMethod rnam_method = RNAM::segMethod::Diagonal;//这里暂时只有一种方法

    //转变图像类型
    cv::Mat img = QPixmapTocvMat(m_image,true);

    //实现
    stcObject->do_stc(img,stc_epsilon,stc_method);
    rnamObject->do_RNAM(img,rnam_epsilon,rnam_method);

    //显示图片
    displayOptions display_method = displayOptions::Adaptive;
    displayImgInLabel(cvMatToQPixmap(stcObject->getCompressedImg()),ui->lbl_STC_compression,display_method);
    displayImgInLabel(cvMatToQPixmap(stcObject->getSegImg()),ui->lbl_STC_segmentation,display_method);
    displayImgInLabel(cvMatToQPixmap(rnamObject->getCompressedImg()),ui->lbl_RNAM_compression,display_method);
    displayImgInLabel(cvMatToQPixmap(rnamObject->getSegImg()),ui->lbl_RNAM_segmentation,display_method);

    //打印信息
    ui->textEdit->append("==========info==========");
    ui->textEdit->append("图片名称："+statusBarLabel->text());
    ui->textEdit->append("STC---------->");
    QString stc_info = QString("同类块阈值：%1\n编码时间：%2 ms\n解码时间：%3 ms\n块数：%4\nPSNR：%5\nBPP：%6")
                           .arg(stc_epsilon)
                           .arg(stcObject->getEncodeTime())
                           .arg(stcObject->getDecodeTime())
                           .arg(stcObject->getBlockNum())
                           .arg(stcObject->getPSNRValue())
                           .arg(stcObject->getBPPValue());
    ui->textEdit->append(stc_info);
    ui->textEdit->append("RNAM---------->");
    QString rnam_info = QString("同类块阈值：%1\n编码时间：%2 ms\n解码时间：%3 ms\n块数：%4\nPSNR：%5\nBPP：%6\nCR：%7")
                           .arg(rnam_epsilon)
                           .arg(rnamObject->getEncodeTime())
                           .arg(rnamObject->getDecodeTime())
                           .arg(rnamObject->getBlockNum())
                           .arg(rnamObject->getPSNRValue())
                           .arg(rnamObject->getBPPValue())
                            .arg(rnamObject->getCRValue());
    ui->textEdit->append(rnam_info);
    ui->textEdit->append("========================\n");

    //工具栏更新
    ui->outputAction->setEnabled(true);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    statusBar()->showMessage("任务执行成功！ 共耗时"+QString::number(duration.count())+" ms");
}


void MainWindow::on_outputAction_triggered()
{
    QString savePath = QFileDialog::getExistingDirectory(nullptr,
                                                              "选择保存目录",
                                                              QDir::currentPath());
    if (savePath.isEmpty())
    {
        QMessageBox::warning(nullptr, "警告", "没有选择目录！");
        return;
    }

    QList<QPixmap>pixmapsList = {
        cvMatToQPixmap(stcObject->getCompressedImg()),
        cvMatToQPixmap(stcObject->getSegImg()),
        cvMatToQPixmap(rnamObject->getCompressedImg()),
        cvMatToQPixmap(rnamObject->getSegImg())};
    QList<QString>fileNames={"STC_compression.png",
                                "STC_segmentation.png",
                                "RNAM_compression.png",
                                "RNAM_segmentation.png",
                                "infomation.txt"};//保存的文件名

    // 创建进度条

    //保存图像
    QString fileName;
    int i = 0;
    for (i = 0; i < pixmapsList.size(); ++i)
    {
        QPixmap image = pixmapsList.at(i);
        if (!image.isNull())
        {
            fileName = QDir(savePath).filePath(statusBarLabel->text()+"_"+fileNames.at(i));//添加上图片名和完整路径
            if (!image.save(fileName))
            {
                QMessageBox::critical(nullptr, "错误", "保存图像失败！");
                return;
            }
        }
    }

    //保存文本
    QString text = ui->textEdit->toPlainText();
    if(text.isNull())
    {
        QMessageBox::warning(nullptr, "警告", "没有文本可保存！");
        return;
    }
    fileName = QDir(savePath).filePath(fileNames.at(i));
    //创建文件
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);
        textStream << text; // 写入文本内容

        file.close(); // 关闭文件
        QMessageBox::information(nullptr,"成功", "所有内容保存成功！");
    }
    else
    {
        QMessageBox::critical(nullptr, "错误", "无法打开文件以写入！");
    }
    statusBar()->showMessage("导出成功！");
}

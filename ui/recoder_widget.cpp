﻿#include "ui/recorder_widget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDebug>

#include "win_capturer/mf_device.h"
#include "win_capturer/video_capturer.h"

#pragma execution_character_set("utf-8")

RecorderWidget::RecorderWidget()
    :QWidget(nullptr)
{}

void RecorderWidget::initLayout()
{
    QLabel* title = new QLabel(tr("摄像头录像机"));

    QHBoxLayout* bodyLayout = new QHBoxLayout;

    QVBoxLayout* bodyLeftLayout = new QVBoxLayout;
    QVBoxLayout* bodyRightLayout = new QVBoxLayout;

    auto rightPlayer = new QWidget;
    rightPlayer->setFixedSize(400, 300);
    bodyRightLayout->addWidget(rightPlayer);

    auto deviceLayout = getDeviceLayout();
    bodyLeftLayout->addLayout(deviceLayout);
    bodyLeftLayout->addSpacing(20);
    bodyLeftLayout->addLayout(getPathLayout());
    bodyLeftLayout->addSpacing(20);
    bodyLeftLayout->addLayout(getOptionLayout());
    bodyLeftLayout->addStretch();
    bodyLeftLayout->addLayout(getBtnLayout());
    bodyLeftLayout->addSpacing(20);


    bodyLayout->addLayout(bodyLeftLayout, 2);
    bodyLayout->addLayout(bodyRightLayout, 3);

    QVBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->addSpacing(10);
    mainLayout->addWidget(title);
    mainLayout->addSpacing(50);
    mainLayout->addLayout(bodyLayout);

    setLayout(mainLayout);
}

void RecorderWidget::initDevice()
{
   _video_devices = MfDevice::get_video_devices();
    for (auto ptr : _video_devices)
    {
        _cb_camera->addItem(QString::fromStdWString(ptr->name));
    }
}

QBoxLayout* RecorderWidget::getDeviceLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* hLayout1 = new QHBoxLayout;
    QHBoxLayout* hLayout2 = new QHBoxLayout;

    QLabel* lbl_camera = new QLabel(tr("摄像头"));
    QLabel* lbl_mic = new QLabel(tr("麦克风"));

    _cb_camera = new QComboBox;
    _cb_mic = new QComboBox;

    hLayout1->addWidget(lbl_camera);
    hLayout1->addWidget(_cb_camera);

    hLayout2->addWidget(lbl_mic);
    hLayout2->addWidget(_cb_mic);

    layout->addLayout(hLayout1);
    layout->addLayout(hLayout2);

    return layout;
}

QBoxLayout* RecorderWidget::getPathLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;
    QLabel* lbl_select = new QLabel(tr("保存路径"));
    QLineEdit* le_path = new QLineEdit;
    QPushButton* btn_select = new QPushButton(tr("选择路径"));

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(btn_select);
    hLayout->addStretch();

    layout->addWidget(lbl_select);
    layout->addWidget(le_path);
    layout->addLayout(hLayout);
    return layout;
}

QBoxLayout* RecorderWidget::getOptionLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* layout1 = new QHBoxLayout;
    QHBoxLayout* layout2 = new QHBoxLayout;
    QHBoxLayout* layout3 = new QHBoxLayout;
    QHBoxLayout* layout4 = new QHBoxLayout;
    QHBoxLayout* layout5 = new QHBoxLayout;

    QLabel* lbl_option = new QLabel(tr("高级选项"));
    QLabel* lbl_rate = new QLabel(tr("码率"));
    QLabel* lbl_fps = new QLabel(tr("帧率"));
    QLabel* lbl_pic = new QLabel(tr("图像质量"));
    QLabel* lbl_hwenc = new QLabel(tr("硬件编码器"));

    QLineEdit* le_rate = new QLineEdit;
    QComboBox* cb_fps = new QComboBox;
    QComboBox* cb_pic = new QComboBox;
    QComboBox* cb_hwenc = new QComboBox;

    layout1->addWidget(lbl_option);
    layout1->addStretch();

    layout2->addWidget(lbl_rate);
    layout2->addWidget(le_rate);

    layout3->addWidget(lbl_fps);
    layout3->addWidget(cb_fps);

    layout4->addWidget(lbl_pic);
    layout4->addWidget(cb_pic);

    layout5->addWidget(lbl_hwenc);
    layout5->addWidget(cb_hwenc);

    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->addLayout(layout5);

    return layout;
}

QBoxLayout* RecorderWidget::getBtnLayout()
{
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addStretch();

    QPushButton* btn_pause = new QPushButton(tr("暂停"));
    QPushButton* btn_start = new QPushButton(tr("开始录制"));
    QPushButton* btn_stop = new QPushButton(tr("结束录制"));

    connect(btn_start, &QPushButton::clicked, this, &RecorderWidget::slot_start);

    btn_stop->setVisible(false);
    hLayout->addWidget(btn_pause);
    hLayout->addSpacing(30);
    hLayout->addWidget(btn_start);
    hLayout->addWidget(btn_stop);

    return hLayout;
}

////////////////////////

void RecorderWidget::slot_start()
{
    int width = 1280;
    int height = 720;
    int fps = 30;
    _video_capturer = std::make_shared<VideoCapturer>(width, height, fps, 0);
    int ret = _video_capturer->start_capture();
    qDebug() << "start_capture, ret = " << ret;
}
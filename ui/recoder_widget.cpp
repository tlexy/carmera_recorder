#include "ui/recorder_widget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

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
    bodyLeftLayout->addStretch();


    bodyLayout->addLayout(bodyLeftLayout);
    bodyLayout->addLayout(bodyRightLayout);

    QVBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->addWidget(title);
    mainLayout->addSpacing(50);
    mainLayout->addLayout(bodyLayout);

    setLayout(mainLayout);
}

QBoxLayout* RecorderWidget::getDeviceLayout()
{
    QVBoxLayout* layout = new QVBoxLayout;
    QHBoxLayout* hLayout1 = new QHBoxLayout;
    QHBoxLayout* hLayout2 = new QHBoxLayout;

    QLabel* lbl_camera = new QLabel(tr("摄像头"));
    QLabel* lbl_mic = new QLabel(tr("麦克风"));

    QLineEdit* le_camera = new QLineEdit;
    QLineEdit* le_mic = new QLineEdit;

    hLayout1->addWidget(lbl_camera);
    hLayout1->addWidget(le_camera);

    hLayout2->addWidget(lbl_mic);
    hLayout2->addWidget(le_mic);

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
}
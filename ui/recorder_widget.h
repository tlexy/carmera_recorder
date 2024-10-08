#include <QWidget>
#include <memory>
#include <vector>

#pragma execution_character_set("utf-8")

class QBoxLayout;
class QComboBox;
struct DeviceUnit;
class VideoCapturer;

class RecorderWidget : public QWidget 
{
    Q_OBJECT
public:
    RecorderWidget();

    void initLayout();
    void initDevice();

    void slot_start();

private:
    QBoxLayout* getDeviceLayout();
    QBoxLayout* getPathLayout();
    QBoxLayout* getOptionLayout();
    QBoxLayout* getBtnLayout();

private:
    QComboBox* _cb_camera;
    QComboBox* _cb_mic;

    std::vector<std::shared_ptr<DeviceUnit>> _video_devices;
    std::shared_ptr<VideoCapturer> _video_capturer;
};
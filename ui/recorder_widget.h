#include <QWidget>

#pragma execution_character_set("utf-8")

class QBoxLayout;
class QComboBox;

class RecorderWidget : public QWidget 
{
    Q_OBJECT
public:
    RecorderWidget();

    void initLayout();
    void initDevice();

private:
    QBoxLayout* getDeviceLayout();
    QBoxLayout* getPathLayout();
    QBoxLayout* getOptionLayout();
    QBoxLayout* getBtnLayout();

private:
    QComboBox* _cb_camera;
    QComboBox* _cb_mic;
};
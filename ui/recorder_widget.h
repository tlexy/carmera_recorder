#include <QWidget>

#pragma execution_character_set("utf-8")

class QBoxLayout;

class RecorderWidget : public QWidget 
{
    Q_OBJECT
public:
    RecorderWidget();

    void initLayout();

private:
    QBoxLayout* getDeviceLayout();
    QBoxLayout* getPathLayout();
    QBoxLayout* getOptionLayout();
};
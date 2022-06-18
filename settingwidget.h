#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <settingobject.h>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();
    SettingObject* settingObj;
    void loadCurValue();
    void settingApply();


private slots:
    void on_pushButton_clicked();

private:
    Ui::SettingWidget *ui;
signals:
    void signalToChangeText();
};

#endif // SETTINGWIDGET_H

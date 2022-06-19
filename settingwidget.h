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

    void on_colorSelect_clicked();

    void on_horizontal_valueChanged(int arg1);

    void on_fontSize_valueChanged(int arg1);

    void on_vertical_valueChanged(int arg1);

    void on_width_valueChanged(int arg1);

    void on_heigth_valueChanged(int arg1);

    void on_wallpaperBtn_clicked();

private:
    Ui::SettingWidget *ui;
signals:
    void signalToChangeSettings();
};

#endif // SETTINGWIDGET_H

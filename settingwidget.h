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
    void loadCurValue(int currentNum);
    void settingApply();
    void closeEvent(QCloseEvent * event) override;



private slots:
    void on_pushButton_clicked();

    void on_colorSelect_clicked();

    void on_horizontal_valueChanged(int arg1);

    void on_fontSize_valueChanged(int arg1);

    void on_vertical_valueChanged(int arg1);

    void on_width_valueChanged(int arg1);

    void on_heigth_valueChanged(int arg1);

    void on_wallpaperBtn_clicked();

    void on_shadowHorizontal_valueChanged(int arg1);

    void on_shadowVertical_valueChanged(int arg1);

    void on_shadowBlur_valueChanged(int arg1);

    void on_shadowColorBtn_clicked();

    void on_resetWallnotePath_clicked();

    void on_screenSelect_currentIndexChanged(int index);

private:
    Ui::SettingWidget *ui;
signals:
    void signalToChangeSettings(int screenNumber);
    void exitSettingWidget();
    void signalToChangeSettingObj(int screenNumber);
};

#endif // SETTINGWIDGET_H

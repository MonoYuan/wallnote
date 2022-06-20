#include "settingwidget.h"
#include "ui_settingwidget.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QApplication>

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}
void SettingWidget::loadCurValue(){
    if(this->settingObj==NULL){
        return;
    }
    ui->fontColor->setText(settingObj->fontColor);
    ui->fontFamily->setCurrentFont(QFont(settingObj->fontFamily));
    ui->textContext->setText(settingObj->textContext);
    ui->fontSize->setValue(settingObj->fontSize);
    ui->horizontal->setValue(settingObj->horizontal);
    ui->vertical->setValue(settingObj->vertical);
    ui->width->setValue(settingObj->width);
    ui->height->setValue(settingObj->height);
    ui->wallpaperText->setText(settingObj->wallpaperPath);
}
void SettingWidget::settingApply(){
    this->settingObj->textContext = ui->textContext->toPlainText();
    this->settingObj->fontColor = ui->fontColor->text();
    this->settingObj->fontFamily = ui->fontFamily->currentFont().family();
    this->settingObj->fontSize = ui->fontSize->value();
    this->settingObj->horizontal = ui->horizontal->value();
    this->settingObj->vertical = ui->vertical->value();
    this->settingObj->width = ui->width->value();
    this->settingObj->height = ui->height->value();
    this->settingObj->wallpaperPath = ui->wallpaperText->text();
}

void SettingWidget::on_pushButton_clicked()
{
    settingApply();
    emit signalToChangeSettings();
}


void SettingWidget::on_colorSelect_clicked()
{
    QColor color = QColorDialog::getColor(Qt::red,this,tr("颜色选择"),QColorDialog::ShowAlphaChannel);
    QString rgb = QString("rgb(%1,%2,%3)")
            .arg(color.red())
            .arg(color.green())
            .arg(color.blue());
    settingObj->fontColor = rgb;
    ui->fontColor->setText(rgb);
    emit signalToChangeSettings();
}

void SettingWidget::on_fontSize_valueChanged(int sizeVal)
{
    settingObj->fontSize = sizeVal;
    emit signalToChangeSettings();
}

void SettingWidget::on_horizontal_valueChanged(int horizontalVal)
{
    settingObj->horizontal = horizontalVal;
    emit signalToChangeSettings();
}

void SettingWidget::on_vertical_valueChanged(int verticalVal)
{
    settingObj->vertical = verticalVal;
    emit signalToChangeSettings();
}

void SettingWidget::on_width_valueChanged(int widthVal)
{
    settingObj->width = widthVal;
    emit signalToChangeSettings();
}


void SettingWidget::on_heigth_valueChanged(int heightVal)
{
    settingObj->height = heightVal;
    emit signalToChangeSettings();
}

void SettingWidget::on_wallpaperBtn_clicked()
{
    QString wallpaperFilePath = QFileDialog::getOpenFileName(this,"选择一个图片",
                                                         QApplication::applicationDirPath(),
                                                         "IMAGE(*.jpg *.png);;GIF(*.gif)");
    qDebug() << "选择图片完毕, 进行加载";
    if(!wallpaperFilePath.isEmpty()){
        settingObj->wallpaperPath = wallpaperFilePath;
        emit signalToChangeSettings();
    }
}
void SettingWidget::closeEvent(QCloseEvent * event){
    emit exitSettingWidget();
}

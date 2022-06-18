#include "settingwidget.h"
#include "ui_settingwidget.h"

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
    ui->fontSize->setValue(QString::fromStdString(settingObj->fontSize).toInt());
    ui->fontColor->setText(QString::fromStdString(settingObj->fontColor));
    ui->fontFamily->setCurrentFont(QFont(QString::fromStdString(settingObj->fontFamily)));
    ui->textContext->setText(QString::fromStdString(settingObj->textContext));
}
void SettingWidget::settingApply(){
    this->settingObj->textContext = ui->textContext->toPlainText().toStdString();
    this->settingObj->fontColor = ui->fontColor->displayText().toStdString();
    this->settingObj->fontFamily = ui->fontFamily->currentFont().family().toStdString();
    this->settingObj->fontSize = ui->fontSize->text().toStdString();
}

void SettingWidget::on_pushButton_clicked()
{
    settingApply();
    emit signalToChangeText();
}


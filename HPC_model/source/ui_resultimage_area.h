#ifndef UI_RESULT_IMAGE_AREA_H
#define UI_RESULT_IMAGE_AREA_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>  

#include <string>

#include <QIcon>
#include <QWidget>
#include <QStringList>
#include <QString>
#include <QVBoxLayout>
#include <QDir>
#include <QLabel>
#include <QGroupBox>

const QString path_data = "/home/lamluong/Desktop/data/";

class UI_ResultImageArea : public QWidget {
  Q_OBJECT
 public:
  explicit UI_ResultImageArea(QWidget *parent = Q_NULLPTR);
  void UpdateResultImage(QString image_lable);

 private:
  void GetRamdomFile(QString image_lable);
 private:
  QDir data_dir;
  QLabel result_image_[10];
  QHBoxLayout* mainLayout_;
  QGroupBox *group_images_;
  QFileInfoList list_showing_file_;
};

#endif

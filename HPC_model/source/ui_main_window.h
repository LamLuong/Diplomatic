/* file ui_main_window.h
   author 
   date
*/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtWidgets>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>

#include "ui_resultimage_area.h"
#include "objectness.h"
#include "predict_api.h"

class UI_Window : public QWidget {

 Q_OBJECT

 public:
  UI_Window(QWidget *parent = 0);

 public slots:
  void LoadInputImageFile();
  void ShowPredic();
 private:
  void ShowInputImageFile(ImageType type);

 private:
  std::vector<cv::Vec4i> pos_objectness_;
  QString input_file_name_;
// UI members
  QGridLayout * main_layout_;

  QPushButton *browse_button_;
  QPushButton *predic_button_;
  QPushButton *close_button_;

  QLabel *origin_image_;
  QLabel *origin_boudingbox_image_;

  QGroupBox *origin_image_box_;
  QGroupBox *origin_boudingbox_image_box_;

  UI_ResultImageArea *predic_result_[5];
  QGroupBox *prediction_box_;
};

#endif //end file

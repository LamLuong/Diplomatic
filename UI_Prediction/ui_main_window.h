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

class UI_Window : public QWidget {

 Q_OBJECT

 public:
  UI_Window(QWidget *parent = 0);

 public slots:
  void LoadInputImageFile();
  void ShowPredic();
 private:
  void ShowInputImageFile(QString path_file);

 private:
// UI members
  QGridLayout * main_layout_;

  QPushButton *browse_button_;
  QPushButton *predic_button_;
  QPushButton *close_button_;

  QLabel *origin_image_;
  QGroupBox *origin_image_box_;

  UI_ResultImageArea *predic_result_[5];
  QGroupBox *prediction_box_;
};

#endif //end file

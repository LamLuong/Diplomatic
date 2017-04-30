#include <QBoxLayout>
#include "ui_main_window.h"

class QPushButton;
UI_Window::UI_Window(QWidget *parent) : QWidget(parent) {

  main_layout_ = new QGridLayout(this);

// Button
  browse_button_ = new QPushButton(tr("&Browse"));
  predic_button_ = new QPushButton(tr("&Predic"));
  close_button_ = new QPushButton(tr("&Close"));
  QVBoxLayout * button_contron_layout = new QVBoxLayout;
  button_contron_layout->addWidget(browse_button_);
  button_contron_layout->addWidget(predic_button_);
  button_contron_layout->addWidget(close_button_);

//input image
  origin_image_ = new QLabel;
  origin_image_box_ = new QGroupBox(tr("Origin Image"));
  QVBoxLayout * origin_image_layout = new QVBoxLayout;

  origin_image_box_->setCheckable(false);
  origin_image_box_->setChecked(true);
  origin_image_layout->addWidget(origin_image_);
  origin_image_box_->setLayout(origin_image_layout);
  
// resultimage
  QVBoxLayout *prediction_layout = new QVBoxLayout;
  prediction_box_ = new QGroupBox(tr("Image Result Area"));
  prediction_box_->setCheckable(false);
  prediction_box_->setChecked(true);

  for (unsigned i = 0; i < 5; i++) {
    predic_result_[i] = new UI_ResultImageArea;
    prediction_layout->addWidget(predic_result_[i]);
  }
  prediction_box_->setLayout(prediction_layout);

// main layout
  main_layout_->addLayout(button_contron_layout, 0, 0);
  main_layout_->addWidget(origin_image_box_, 1, 0);
  main_layout_->addWidget(prediction_box_, 0, 1, 5, 5);

// Handle

  connect(close_button_, SIGNAL(clicked()), this, SLOT(close()));
  connect(browse_button_, &QAbstractButton::clicked, this,
          &UI_Window::LoadInputImageFile);
  connect(predic_button_, &QAbstractButton::clicked, this,
          &UI_Window::ShowPredic);

// Style Window
  setWindowTitle(tr("Prediction"));
  resize(1366, 768);
}

void UI_Window::LoadInputImageFile() {
  QString file_name = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "/home/lamluong/Desktop/data",
                                                tr("Images (*.png *.jpg)"));
  if (!file_name.isEmpty()) {
    ShowInputImageFile(file_name);
  }
}

void UI_Window::ShowInputImageFile(QString path_file) {
  QPixmap pix_image(path_file);
  origin_image_->setPixmap(pix_image.scaled(250, 250, Qt::KeepAspectRatio));
}

void UI_Window::ShowPredic() {
  predic_result_[0]->UpdateResultImage("pho");
}


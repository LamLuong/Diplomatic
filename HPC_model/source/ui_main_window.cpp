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

  origin_boudingbox_image_ = new QLabel;
  origin_boudingbox_image_box_ = new QGroupBox(tr("BoundingBox Image"));
  QVBoxLayout * origin_boudingbox_image_layout = new QVBoxLayout;

  origin_image_box_->setCheckable(false);
  origin_image_box_->setChecked(true);
  origin_image_layout->addWidget(origin_image_);
  origin_image_box_->setLayout(origin_image_layout);

  origin_boudingbox_image_box_->setCheckable(false);
  origin_boudingbox_image_box_->setChecked(true);
  origin_boudingbox_image_layout->addWidget(origin_boudingbox_image_);
  origin_boudingbox_image_box_->setLayout(origin_boudingbox_image_layout);
  
  text_edit_ = new QTextEdit;
  text_edit_->setMaximumSize(200, 200);
  text_edit_->setReadOnly(true);
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
  main_layout_->addWidget(origin_boudingbox_image_box_, 2, 0);
  main_layout_->addWidget(text_edit_, 3, 0);
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
  input_file_name_ = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "~/Desktop/",
                                                tr("Images (*.png *.jpg)"));
  if (!input_file_name_.isEmpty()) {
    Objectness::GetInstance()->LoadImage(input_file_name_.toUtf8().constData());

    ShowInputImageFile(ImageType::ORIGIN_IMAGE);
    Objectness::GetInstance()->GetBondingBox(pos_objectness_);
    ShowInputImageFile(ImageType::BOUNDINGBOX_IMAGE);
  }
}

void UI_Window::ShowInputImageFile(ImageType type) {
  cv::Mat _input = Objectness::GetInstance()->GetInputImage(type);
  cv::imwrite("hehe.jpg", _input);
  cv::cvtColor(_input, _input, CV_BGR2RGB);
  QPixmap pix_image = QPixmap::fromImage(QImage((uchar*) _input.data,
                                         _input.cols,
                                         _input.rows,
                                         _input.step,
                                         QImage::Format_RGB888));

  if (type == ImageType::ORIGIN_IMAGE) {
    origin_image_->setPixmap(pix_image.scaled(250, 250, Qt::KeepAspectRatio));
  }

  if (type == ImageType::BOUNDINGBOX_IMAGE) {

    origin_boudingbox_image_->setPixmap(pix_image.scaled(250, 250, Qt::KeepAspectRatio));
 }
}

void UI_Window::ShowPredic() {
  std::vector<std::string> results;
  PredictionApi::GetInstance()->Predict(std::string(input_file_name_.toUtf8().constData()),
                                        pos_objectness_,
                                        results);

  Objectness::GetInstance()->DrawLabelBoundigBox(results);
  ShowInputImageFile(ImageType::BOUNDINGBOX_IMAGE);

  std::string img_label = "";
  for (int i = 0; i < 5; i++) {
    predic_result_[i]->UpdateResultImage(QString::fromStdString(results[i]));
    img_label = img_label + results[i] + "\n";
  }
  text_edit_->clear();
  text_edit_->setPlainText(QString::fromStdString(img_label));
}


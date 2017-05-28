#include <ui_resultimage_area.h>

UI_ResultImageArea::UI_ResultImageArea(QWidget *parent) : QWidget(parent) {

  srand (time(NULL));

  QWidget *centralWidget = new QWidget(this);
  mainLayout_ = new QHBoxLayout(centralWidget);
  group_images_ = new QGroupBox();
  group_images_->setCheckable(false);
  group_images_->setChecked(true);

  data_dir.cd("../../train_test_data/data/test/pho");

  QHBoxLayout* image_layout = new QHBoxLayout();
  for (int i = 0; i < 10; i ++) {
    image_layout->addWidget(&result_image_[i]);
  }

  group_images_->setLayout(image_layout);
  setStyleSheet("QGroupBox { background-color: white;} \
                 QGroupBox::title { top: 10px; left: 10px; }");

  mainLayout_->addWidget(group_images_);

  UpdateResultImage("zunknow");
}

void UI_ResultImageArea::UpdateResultImage(QString image_lable) {
  GetRamdomFile(image_lable);
  group_images_->setTitle(image_lable);

  for (int i = 0; i < 10; i ++) {
    int iter = rand() % list_showing_file_.size();
    QPixmap image(list_showing_file_.at(iter).filePath());
    result_image_[i].setPixmap(image.scaled(100, 100, Qt::KeepAspectRatio));
  }
}

void UI_ResultImageArea::GetRamdomFile(QString image_lable) {
  QString dir_label_path = "../" + image_lable;
  
  data_dir.cd(dir_label_path);

  QStringList filters;
  filters << "*.png" << "*.jpg" << "*.bmp";
  list_showing_file_ = data_dir.entryInfoList(filters, QDir::Files|QDir::NoDotAndDotDot);
}


#include "objectness.h"

Objectness* Objectness::instance = new Objectness();

void Objectness::InitData(std::string traning_path) {
  numobjects_ = 0;

  objectness_bing_ = cv::makePtr<cv::saliency::ObjectnessBING>();
  objectness_bing_->setTrainingPath(traning_path);
  objectness_bing_->setBBResDir(traning_path + "/Results");
}

bool Objectness::LoadImage(std::string path_image) {
  input_image_ = cv::imread(path_image.c_str());
  if(!input_image_.data) {
    return false;
  }

  boundingbox_image_ = input_image_.clone();
  CaculateBoudingBox();
  DrawBoundingBox();
  return true;
}
cv::Mat Objectness::GetInputImage(ImageType type) {
  if (type == ImageType::ORIGIN_IMAGE) {
    return input_image_;
  }

  if (type == ImageType::BOUNDINGBOX_IMAGE) {
    return boundingbox_image_;
  }
}

void Objectness::DrawBoundingBox() {
  for (unsigned i = 0; i < 5; i++) {
    cv::Vec4i pos = objectness_boundingbox_[i];
    cv::rectangle(
                boundingbox_image_,
                cv::Point(pos[0], pos[1]),
                cv::Point(pos[2], pos[3]),
                cvScalar(0, 255, 255)
               );
  }

}

void Objectness::DrawLabelBoundigBox(const std::vector<std::string>& input_text) {
  cv::cvtColor(boundingbox_image_, boundingbox_image_, CV_BGR2RGB);
  for (unsigned i = 0; i < 5; i++) {
    cv::Mat clone = input_image_.clone();

    cv::Vec4i pos = objectness_boundingbox_[i];
    std::cout << input_text[i] << "  " << pos[0] << "  " <<  pos[1] <<  "  " << pos[2] << "  " <<  pos[3]<< std::endl;
    cv::putText(boundingbox_image_, input_text[i], cv::Point(pos[0], pos[1] + 30),
                cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 3);


    cv::rectangle(clone, cv::Point(pos[0], pos[1]), cv::Point(pos[2], pos[3]), cv::Scalar(0, 0, 255), 4);
    putText(clone, input_text[i], cv::Point(pos[0], pos[1]+30),
            cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 3);

    char filename[256];
    sprintf(filename, "bing_%05d.jpg", i);
    cv::imwrite(filename, clone);
  }
}

void Objectness::CaculateBoudingBox() {
  if (objectness_bing_->computeSaliency(input_image_, objectness_boundingbox_) ) {
    std::vector<float> values = objectness_bing_->getobjectnessValues();
    printf("detected candidates: %lu\n", objectness_boundingbox_.size());
    printf("scores: %lu\n", values.size());
  }
}

void Objectness::GetBondingBox(std::vector<cv::Vec4i>& objectness_boundingbox) {
  objectness_boundingbox.resize(objectness_boundingbox_.size());
  memcpy(objectness_boundingbox.data(), objectness_boundingbox_.data(), 
         sizeof(cv::Vec4i) * objectness_boundingbox_.size());
}

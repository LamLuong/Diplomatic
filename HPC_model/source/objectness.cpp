#include "objectness.h"

Objectness::Objectness(std::string traning_path) {
  numobjects_ = 0;

  objectness_bing_ = cv::makePtr<cv::saliency::ObjectnessBING>();
  objectness_bing_->setTrainingPath(traning_path);
  objectness_bing_->setBBResDir(traning_path + "/Results");
}

Objectness::~Objectness() {

}
void Objectness::LoadImage(std::string path_image) {
  input_image_ = cv::imread(path_image.c_str());
}

void Objectness::GetBondingBox(std::vector<cv::Vec4i>& objectness_boundingbox) {
  if (objectness_bing_->computeSaliency(input_image_, objectness_boundingbox) ) {
    std::vector<float> values = objectness_bing_->getobjectnessValues();
    printf("detected candidates: %lu\n", objectness_boundingbox.size());
    printf("scores: %lu\n", values.size());
  }
}

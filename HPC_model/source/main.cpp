#include <iostream>

#include "objectness.h"
#include "predict_api.h"


PredictionApi* PredictionApi::instance = new PredictionApi();

int main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cout << "need input image" << std::endl;
    return 1;
  }

  PredictionApi::GetInstance()->Initialize(argc, argv);
  
  std::vector<cv::Vec4i> pos_objectness;

  Objectness::GetInstance()->InitData("/home/lamluong/Downloads/opencv_contrib/modules/saliency/samples/ObjectnessTrainedModel");

  if (!Objectness::GetInstance()->LoadImage(argv[1])) {
    std::cout <<  "Could not open or find the image" << std::endl;
    return 1;
  }

  Objectness::GetInstance()->GetBondingBox(pos_objectness);

  PredictionApi::GetInstance()->LoadModel();

  std::vector<std::string> results;
  PredictionApi::GetInstance()->Predict(std::string(argv[1]), pos_objectness, results);

  for (int i = 0; i < results.size(); i++) {
    std::cout << results[i] << std::endl;

  }
  return 0;
}

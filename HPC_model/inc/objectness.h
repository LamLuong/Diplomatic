#include <string>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/saliency.hpp>

class Objectness {
 public:
  Objectness(std::string traning_path);
  ~Objectness();
  void LoadImage(std::string path_image);
  void GetBondingBox(std::vector<cv::Vec4i>& objectness_boundingbox);

 private:
  unsigned numobjects_;
  cv::Ptr<cv::saliency::ObjectnessBING> objectness_bing_;
  cv::Mat input_image_;
};

#include <string>
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/saliency.hpp>
enum ImageType {
  ORIGIN_IMAGE,
  BOUNDINGBOX_IMAGE,
};

class Objectness {
 public:
  Objectness() {};
  ~Objectness() {};

  void InitData(std::string traning_path);

  static Objectness* GetInstance() { 
		if (!instance) {
      instance = new Objectness();
    }

		return instance; 
	};

  bool LoadImage(std::string path_image);
  void GetBondingBox(std::vector<cv::Vec4i>& objectness_boundingbox);
  cv::Mat GetInputImage(ImageType type);
  void DrawLabelBoundigBox(const std::vector<std::string>&);
 private:
  void CaculateBoudingBox();
  void DrawBoundingBox();

 private:
  static Objectness* instance;

  unsigned numobjects_;
  cv::Ptr<cv::saliency::ObjectnessBING> objectness_bing_;
  cv::Mat input_image_;
  cv::Mat boundingbox_image_;
  std::vector<cv::Vec4i> objectness_boundingbox_;
};

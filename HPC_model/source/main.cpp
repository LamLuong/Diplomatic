#include <QApplication>

#include "ui_main_window.h"

PredictionApi* PredictionApi::instance = new PredictionApi();

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  UI_Window window;
  PredictionApi::GetInstance()->Initialize(argc, argv);
#ifdef OBJECTNESS_TRAIN
  Objectness::GetInstance()->InitData(OBJECTNESS_TRAIN);
#else
// Objectness::GetInstance()->InitData("/home/lamluong/Downloads/opencv_contrib/modules/saliency/samples/ObjectnessTrainedModel");
#endif
  PredictionApi::GetInstance()->LoadModel();

  window.show();

  return app.exec();
}

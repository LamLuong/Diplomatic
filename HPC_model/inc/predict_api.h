#include <Python.h>
#include <boost/python.hpp>

#include <opencv2/opencv.hpp>

const unsigned g_numobject = 5;
const unsigned g_num_coord = 4;

class PredictionApi {
 public:
  PredictionApi() {}

  ~PredictionApi() {}

  static PredictionApi* GetInstance() { 
		if (!instance) {
      instance = new PredictionApi();
    }

		return instance; 
	};

  void Initialize(int num_agc, char* num_argv[]) {
    setenv("PYTHONPATH", "../predic_api_py", 1);
    Py_Initialize();
    PySys_SetArgv(num_agc, num_argv);

  }
  void LoadModel() {
    prediction_module = boost::python::import("prediction");
  }

  void Predict(const std::string& image_path, 
               const std::vector<cv::Vec4i>& pos_objectness,
               std::vector<std::string>& lables) {
    try {
      boost::python::list list_pos_objects;

      for (int i = 0; i < g_numobject; i++) {
        boost::python::list pos_object;
        cv::Vec4i pos = pos_objectness[i];
        for (int j = 0; j < g_num_coord; j++) {
          pos_object.append(pos[j]);
        }
        list_pos_objects.append(pos_object);
      }

      boost::python::object list_label = prediction_module.attr("PredicImage")(image_path, list_pos_objects);

      for (unsigned i = 0; i < boost::python::len(list_label); i++) {
        lables.push_back(boost::python::extract<std::string>(list_label[i]));
      }
      
    } catch (const boost::python::error_already_set&) {
      PyErr_Print();
      return ;
    }
  }

 private:
  static PredictionApi* instance;
  boost::python::object prediction_module;
};

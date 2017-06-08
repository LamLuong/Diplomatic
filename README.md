# Diplomatic
requrement

keras

opencv 3.0

Qt5 set up follow https://wiki.qt.io/Install_Qt_5_on_Ubuntu

boost set up by typing sudo apt-get install libboost-all-dev

download data (suggestion) in https://drive.google.com/file/d/0B-JQu_IRuMY4VjJnTXZpdkoxUE0/view?usp=sharing, extract to train_test_data

download model in https://drive.google.com/file/d/0B-JQu_IRuMY4eDZXNDhFTTdXSE0/view?usp=sharing  copy to HCP_model/model\\

goto HCP_model folder

mkdir build

cd build

  cmake -D CMAKE_PREFIX_PATH=path_to/Qt5.7.0/5.7/gcc_64/lib/cmake 
      -D OBJECTNESS_TRAIN='"path_to/opencv_contrib/modules/saliency/samples/ObjectnessTrainedModel"'
..

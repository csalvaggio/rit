#include <iostream>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

using namespace std;

int main() {
  const string srcFilename = "../data/images/misc/lenna_grayscale.pgm";
  cv::Mat src = cv::imread(srcFilename, cv::IMREAD_GRAYSCALE);

  const string videoFilename = "movie.mpg";

  cv::VideoWriter video;
  int apiPreference = cv::CAP_FFMPEG;
  int fourcc = cv::VideoWriter::fourcc('M', 'P', 'E', 'G');
  double fps = 30;
  cv::Size frameSize = cv::Size(src.cols, src.rows);
  bool isColor = false;
  video.open(videoFilename, apiPreference, fourcc, fps, frameSize, isColor);

  cv::Mat frame = src.clone();
  for (int idx=0; idx<256; idx++) {
    video.write(frame);
    frame -= 1;
  }

  video.release();
}

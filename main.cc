#include "cxxopts.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <regex>
#include <string>

const std::string TITLE = "SmthsmthExtractor";
const std::string DESCRIPTION =
    "Simple opencv based program to extract series of images from video.";

cxxopts::ParseResult parse_args(int argc, char *argv[]) {
  cxxopts::Options options(TITLE, DESCRIPTION);
  options.add_options()("i,input", "Input video file",
                        cxxopts::value<std::string>());

  auto result = options.parse(argc, argv);

  if (!result.count("input")) {
    throw cxxopts::exceptions::exception("input argument missing, this is a required argument.");
  }
  return result;
}

int main(int argc, char *argv[]) {

  cxxopts::ParseResult args;
  try {
    args = parse_args(argc, argv);
  } catch (const cxxopts::exceptions::exception& e) {
    std::cerr << "Error parsing options: " << e.what() << std::endl;
    return 1;
  }

  auto infile = args["input"].as<std::string>();

  cv::VideoCapture cap(infile);

  if (!cap.isOpened()) {
    std::cerr << "Error opening video file (" << infile << ")" << std::endl;
    return 2;
  }

  cv::Mat frame0;
  cap >> frame0;

  std::string outfile = "frame0.jpg";
  cv::imwrite(outfile, frame0);

  cap.release();

  std::cout << "Frame extracted successfully." << std::endl;

  return 0;
}

#include "census.h"
#include "s_census.h"
#include "log_report.h"

#include "opencv2/opencv.hpp"

std::string src_image_path = "../example/raw_image.png";

void TestDefault(const Image &src_image, Image &dst_image) {
    ReportInfo(YELLOW ">> Test default image processor." << RESET_COLOR);

    IMAGE_PROCESSOR::ImageProcessor processor;
    processor.Process(src_image, dst_image);

    cv::Mat show_image(dst_image.rows(), dst_image.cols(), CV_8UC1, dst_image.data());
    cv::imshow("default process", show_image);
    cv::waitKey(0);
}

void TestCensus(const Image &src_image, Image &dst_image) {
    ReportInfo(YELLOW ">> Test census image processor." << RESET_COLOR);

    IMAGE_PROCESSOR::CensusProcessor processor;
    processor.Process(src_image, dst_image);

    cv::Mat show_image(dst_image.rows(), dst_image.cols(), CV_8UC1, dst_image.data());
    cv::imshow("census process", show_image);
    cv::waitKey(0);
}

void TestSCensus(const Image &src_image, Image &dst_image) {
    ReportInfo(YELLOW ">> Test census image processor." << RESET_COLOR);

    IMAGE_PROCESSOR::SCensusProcessor processor;
    processor.Process(src_image, dst_image);

    cv::Mat show_image(dst_image.rows(), dst_image.cols(), CV_8UC1, dst_image.data());
    cv::imshow("s-census process", show_image);
    cv::waitKey(0);
}

int main(int argc, char **argv) {
    ReportInfo(YELLOW ">> Test image processor." << RESET_COLOR);

    cv::Mat cv_src_image = cv::imread(src_image_path, 0);
    cv::Mat cv_dst_image = cv::imread(src_image_path, 0);
    Image src_image(cv_src_image.data, cv_src_image.rows, cv_src_image.cols);
    Image dst_image(cv_dst_image.data, cv_dst_image.rows, cv_dst_image.cols);
    cv::imshow("raw image", cv_src_image);
    cv::waitKey(0);

    TestDefault(src_image, dst_image);
    TestCensus(src_image, dst_image);
    TestSCensus(src_image, dst_image);

    return 0;
}

#include "census.h"
#include "s_census.h"

#include "slam_log_reporter.h"
#include "slam_memory.h"
#include "visualizor_2d.h"

using namespace SLAM_VISUALIZOR;

std::string src_image_path = "../example/raw_image.png";

void TestDefault(const GrayImage &src_image, GrayImage &dst_image) {
    ReportInfo(YELLOW ">> Test default image processor." << RESET_COLOR);

    IMAGE_PROCESSOR::ImageProcessor processor;
    processor.Process(src_image, dst_image);

    Visualizor::ShowImage("default process", dst_image);
}

void TestCensus(const GrayImage &src_image, GrayImage &dst_image) {
    ReportInfo(YELLOW ">> Test census image processor." << RESET_COLOR);

    IMAGE_PROCESSOR::CensusProcessor processor;
    processor.Process(src_image, dst_image);

    Visualizor::ShowImage("census process", dst_image);
}

void TestSCensus(const GrayImage &src_image, GrayImage &dst_image) {
    ReportInfo(YELLOW ">> Test census image processor." << RESET_COLOR);

    IMAGE_PROCESSOR::SCensusProcessor processor;
    processor.Process(src_image, dst_image);

    Visualizor::ShowImage("s-census process", dst_image);
}

int main(int argc, char **argv) {
    ReportInfo(YELLOW ">> Test image processor." << RESET_COLOR);

    GrayImage src_image;
    Visualizor::LoadImage(src_image_path, src_image);

    uint8_t *dst_buf = (uint8_t *)SlamMemory::Malloc(src_image.rows() * src_image.cols() * sizeof(uint8_t));
    GrayImage dst_image(dst_buf, src_image.rows(), src_image.cols(), true);

    TestDefault(src_image, dst_image);
    TestCensus(src_image, dst_image);
    TestSCensus(src_image, dst_image);

    Visualizor::WaitKey(0);
    return 0;
}

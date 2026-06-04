#include "census.h"
#include "histogram_equalization.h"
#include "s_census.h"

#include "slam_log_reporter.h"
#include "slam_memory.h"
#include "tick_tock.h"
#include "visualizor_2d.h"

using namespace slam_visualizor;

std::string src_image_path = "../example/raw_image.png";

int main(int argc, char **argv) {
    ReportInfo(YELLOW ">> Test image processor." << RESET_COLOR);

    GrayImage src_image;
    Visualizor2D::LoadImage(src_image_path, src_image);

    uint8_t *dst_buf = (uint8_t *)SlamMemory::Malloc(src_image.rows() * src_image.cols() * sizeof(uint8_t));
    GrayImage dst_image(dst_buf, src_image.rows(), src_image.cols(), true);

    // Instantiate all processors once.
    image_processor::ImageProcessor processor_default;
    image_processor::CensusProcessor processor_census;
    image_processor::SCensusProcessor processor_s_census;
    image_processor::HistogramEqualizationProcessor processor_hist_eq;

    // A single lambda replaces the four duplicate test functions.
    // It uses virtual dispatch through the base-class reference and
    // wraps Process() with TickTock timing.
    auto run_test = [&](const std::string &test_name, const std::string &window_name, image_processor::ImageProcessor &processor) {
        ReportInfo(YELLOW ">> Test " << test_name << " image processor." << RESET_COLOR);

        slam_utility::TickTock tick_tock;
        processor.Process(src_image, dst_image);
        const double elapsed_ms = tick_tock.TockTickInMillisecond();

        ReportInfo(">> " << test_name << " elapsed: " << elapsed_ms << " ms.");
        Visualizor2D::ShowImage(window_name, dst_image);
    };

    run_test("default", "default process", processor_default);
    run_test("census", "census process", processor_census);
    run_test("s-census", "s-census process", processor_s_census);
    run_test("histogram equalization", "histogram equalization process", processor_hist_eq);

    Visualizor2D::WaitKey(0);
    return 0;
}

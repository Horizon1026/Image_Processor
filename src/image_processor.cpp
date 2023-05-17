#include "image_processor.h"
#include "log_report.h"

namespace IMAGE_PROCESSOR {

bool ImageProcessor::Process(const Image &src_image, Image &dst_image) {
    if (kernel_.rows() % 2 == 0 || kernel_.cols() % 2 == 0) {
        ReportInfo(">> ImageProcessor : kernel size must be odd.");
        return false;
    }

    if (src_image.data() == nullptr || dst_image.data() == nullptr) {
        ReportInfo(">> ImageProcessor : source image or destination image is nullptr.");
        return false;
    }

    const int32_t row_bound_size = kernel_.rows() / 2;
    const int32_t col_bound_size = kernel_.cols() / 2;

    for (int32_t row = row_bound_size; row < dst_image.rows() - row_bound_size; ++row) {
        for (int32_t col = col_bound_size; col < dst_image.cols() - col_bound_size; ++col) {
            float value = 0;
            for (int32_t drow = -row_bound_size; drow <= row_bound_size; ++drow) {
                for (int32_t dcol = -col_bound_size; dcol <= col_bound_size; ++dcol) {
                    value += static_cast<float>(src_image.GetPixelValueNoCheck(row + drow, col + dcol)) *
                             kernel_(drow + row_bound_size, dcol + col_bound_size);
                }
            }
            value /= kernel_.rows() * kernel_.cols();
            value = std::max(0.0f, value);
            dst_image.SetPixelValueNoCheck(row, col, value < 256 ? static_cast<uint8_t>(value) : 255);
        }
    }

    return true;
}

}

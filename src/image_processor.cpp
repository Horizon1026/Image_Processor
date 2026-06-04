#include "image_processor.h"
#include "slam_log_reporter.h"

#include "algorithm"
#include "vector"

namespace image_processor {

bool ImageProcessor::Process(const GrayImage &src_image, GrayImage &dst_image) {
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
    const int32_t kernel_rows = kernel_.rows();
    const int32_t kernel_cols = kernel_.cols();
    const float inv_kernel_size = 1.0f / static_cast<float>(kernel_rows * kernel_cols);

    // Pre-flatten kernel from column-major (Eigen default) to row-major layout,
    // enabling sequential memory access in the inner convolution loop.
    std::vector<float> kernel_flat(kernel_rows * kernel_cols);
    for (int32_t i = 0; i < kernel_rows; ++i) {
        for (int32_t j = 0; j < kernel_cols; ++j) {
            kernel_flat[i * kernel_cols + j] = kernel_(i, j);
        }
    }

    const uint8_t *src_data = src_image.data();
    uint8_t *dst_data = dst_image.data();
    const int32_t src_cols = src_image.cols();
    const int32_t dst_cols = dst_image.cols();
    const int32_t dst_rows = dst_image.rows();

    // Main convolution loop with direct pointer-based pixel access.
    // For each row-offset drow, compute the source row pointer once and reuse,
    // avoiding repeated row * cols multiplications.
    for (int32_t row = row_bound_size; row < dst_rows - row_bound_size; ++row) {
        for (int32_t col = col_bound_size; col < dst_cols - col_bound_size; ++col) {
            float value = 0;
            int32_t kidx = 0;

            for (int32_t drow = -row_bound_size; drow <= row_bound_size; ++drow) {
                const uint8_t *src_row = src_data + (row + drow) * src_cols;
                for (int32_t dcol = -col_bound_size; dcol <= col_bound_size; ++dcol) {
                    value += static_cast<float>(src_row[col + dcol]) * kernel_flat[kidx++];
                }
            }

            value *= inv_kernel_size;
            // Clamp to [0, 255] in a single branch-free step
            value = std::max(0.0f, std::min(255.0f, value));
            dst_data[row * dst_cols + col] = static_cast<uint8_t>(value);
        }
    }

    return true;
}

}  // namespace image_processor

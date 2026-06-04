#include "census.h"

namespace image_processor {

bool CensusProcessor::Process(const GrayImage &src_image, GrayImage &dst_image) {
    if (src_image.data() == nullptr || dst_image.data() == nullptr) {
        return false;
    }

    const uint8_t *src_data = src_image.data();
    uint8_t *dst_data = dst_image.data();
    const int32_t cols = src_image.cols();
    const int32_t rows = src_image.rows();

    // Use row pointers to avoid repeated row * cols multiplications.
    // Manually unroll the 8-neighbor census pattern, matching the
    // original index_offset_ order:
    //   {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}
    for (int32_t row = 1; row < rows - 1; ++row) {
        const uint8_t *row_prev = src_data + (row - 1) * cols;
        const uint8_t *row_curr = src_data + row * cols;
        const uint8_t *row_next = src_data + (row + 1) * cols;

        for (int32_t col = 1; col < cols - 1; ++col) {
            const uint8_t center = row_curr[col];
            uint8_t census = 0;

            census = (census << 1) | (row_prev[col - 1] > center);
            census = (census << 1) | (row_prev[col] > center);
            census = (census << 1) | (row_prev[col + 1] > center);
            census = (census << 1) | (row_curr[col - 1] > center);
            census = (census << 1) | (row_curr[col + 1] > center);
            census = (census << 1) | (row_next[col - 1] > center);
            census = (census << 1) | (row_next[col] > center);
            census = (census << 1) | (row_next[col + 1] > center);

            dst_data[row * cols + col] = census;
        }
    }

    return true;
}

}  // namespace image_processor

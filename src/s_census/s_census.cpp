#include "s_census.h"

namespace image_processor {

bool SCensusProcessor::Process(const GrayImage &src_image, GrayImage &dst_image) {
    if (src_image.data() == nullptr || dst_image.data() == nullptr) {
        return false;
    }

    const uint8_t *src_data = src_image.data();
    uint8_t *dst_data = dst_image.data();
    const int32_t cols = src_image.cols();
    const int32_t rows = src_image.rows();

    // Use row pointers to avoid repeated row * cols multiplications.
    // Fetch all 8 neighbor values once (used for both mean and comparison),
    // then manually unroll the census comparisons, matching the original
    // index_offset_ order:
    //   {-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}
    for (int32_t row = 1; row < rows - 1; ++row) {
        const uint8_t *row_prev = src_data + (row - 1) * cols;
        const uint8_t *row_curr = src_data + row * cols;
        const uint8_t *row_next = src_data + (row + 1) * cols;

        for (int32_t col = 1; col < cols - 1; ++col) {
            // Single pass: fetch all 8 neighbor values
            const uint8_t n0 = row_prev[col - 1];
            const uint8_t n1 = row_prev[col];
            const uint8_t n2 = row_prev[col + 1];
            const uint8_t n3 = row_curr[col - 1];
            const uint8_t n4 = row_curr[col + 1];
            const uint8_t n5 = row_next[col - 1];
            const uint8_t n6 = row_next[col];
            const uint8_t n7 = row_next[col + 1];

            // Compute mean of the 8 neighbors
            const uint8_t mean = static_cast<uint8_t>((static_cast<uint16_t>(n0) + n1 + n2 + n3 + n4 + n5 + n6 + n7) / 8);

            // Build census bits
            uint8_t census = 0;
            census = (census << 1) | (n0 > mean);
            census = (census << 1) | (n1 > mean);
            census = (census << 1) | (n2 > mean);
            census = (census << 1) | (n3 > mean);
            census = (census << 1) | (n4 > mean);
            census = (census << 1) | (n5 > mean);
            census = (census << 1) | (n6 > mean);
            census = (census << 1) | (n7 > mean);

            dst_data[row * cols + col] = census;
        }
    }

    return true;
}

}  // namespace image_processor

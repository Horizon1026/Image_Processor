#include "census.h"
#include "simd_wrapper.h"

namespace image_processor {

bool CensusProcessor::Process(const GrayImage &src_image, GrayImage &dst_image) {
    if (src_image.data() == nullptr || dst_image.data() == nullptr) {
        return false;
    }

    if (options_.kEnableSimd) {
        const int32_t rows = src_image.rows();
        const int32_t cols = src_image.cols();
        const uint8_t* src_ptr = src_image.data();
        uint8_t* dst_ptr = dst_image.data();

        for (int32_t row = 1; row < rows - 1; ++row) {
            int32_t col = 1;
            // Process 16 pixels at a time
            for (; col <= cols - 17; col += 16) {
                using namespace slam_utility::simd;
                uint8x16_t center = LoadU(src_ptr + row * cols + col);
                uint8x16_t census_vec = LoadU(dst_ptr + row * cols + col); // Initialize with current values (optional)
                census_vec = LoadU(dst_ptr + row * cols + col); // Actually just zero it out
                census_vec = uint8x16_t{}; // zero

                for (int32_t i = 0; i < 8; ++i) {
                    uint8x16_t neighbor = LoadU(src_ptr + (row + index_offset_[i][0]) * cols + (col + index_offset_[i][1]));
                    uint8x16_t mask = CompareGreater(neighbor, center); // 0xFF if neighbor > center
                    census_vec = ShiftLeft1(census_vec);
                    census_vec = Or(census_vec, AndOne(mask));
                }
                StoreU(dst_ptr + row * cols + col, census_vec);
            }
            // Residual pixels
            for (; col < cols - 1; ++col) {
                uint8_t census = 0;
                const uint8_t a = src_image.GetPixelValueNoCheck(row, col);
                for (int32_t i = 0; i < 8; ++i) {
                    const uint8_t b = src_image.GetPixelValueNoCheck(row + index_offset_[i][0], col + index_offset_[i][1]);
                    census <<= 1;
                    census += b > a ? 1 : 0;
                }
                dst_image.SetPixelValueNoCheck(row, col, census);
            }
        }
    } else {
        uint8_t census = 0;
        for (int32_t row = 1; row < src_image.rows() - 1; ++row) {
            for (int32_t col = 1; col < src_image.cols() - 1; ++col) {
                census = 0;
                for (int32_t i = 0; i < 8; ++i) {
                    const uint8_t b = src_image.GetPixelValueNoCheck(row + index_offset_[i][0], col + index_offset_[i][1]);
                    const uint8_t a = src_image.GetPixelValueNoCheck(row, col);
                    census <<= 1;
                    census += b > a ? 1 : 0;
                }
                dst_image.SetPixelValueNoCheck(row, col, census);
            }
        }
    }

    return true;
}

}  // namespace image_processor

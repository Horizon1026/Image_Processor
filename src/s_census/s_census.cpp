#include "s_census.h"

namespace image_processor {

bool SCensusProcessor::Process(const GrayImage &src_image, GrayImage &dst_image) {
    if (src_image.data() == nullptr || dst_image.data() == nullptr) {
        return false;
    }

    uint8_t census = 0;
    for (int32_t row = 1; row < src_image.rows() - 1; ++row) {
        for (int32_t col = 1; col < src_image.cols() - 1; ++col) {
            census = 0;
            uint16_t sum = 0;
            for (int32_t i = 0; i < 8; ++i) {
                sum += src_image.GetPixelValueNoCheck(row + index_offset_[i][0], col + index_offset_[i][1]);
            }

            for (int32_t i = 0; i < 8; ++i) {
                const uint8_t b = src_image.GetPixelValueNoCheck(row + index_offset_[i][0], col + index_offset_[i][1]);
                const uint8_t a = sum / 8;
                census <<= 1;
                census += b > a ? 1 : 0;
            }
            dst_image.SetPixelValueNoCheck(row, col, census);
        }
    }

    return true;
}

}  // namespace image_processor

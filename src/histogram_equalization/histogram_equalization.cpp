#include "histogram_equalization.h"

#include "algorithm"
#include "cmath"
#include "cstring"

namespace image_processor {

bool HistogramEqualizationProcessor::Process(const GrayImage &src_image, GrayImage &dst_image) {
    if (src_image.data() == nullptr || dst_image.data() == nullptr) {
        return false;
    }

    const int32_t rows = src_image.rows();
    const int32_t cols = src_image.cols();
    const int32_t total_pixels = rows * cols;

    if (total_pixels <= 0) {
        return false;
    }

    const uint8_t *src_data = src_image.data();

    // Step 1: Build histogram (256 bins for uint8 grayscale)
    int32_t histogram[256] = {0};
    for (int32_t i = 0; i < total_pixels; ++i) {
        ++histogram[src_data[i]];
    }

    // Step 2: Compute cumulative distribution function (CDF)
    //         and locate the first non-zero bin.
    int32_t cdf[256];
    int32_t cdf_min = -1;

    cdf[0] = histogram[0];
    if (histogram[0] > 0) {
        cdf_min = cdf[0];
    }

    for (int32_t i = 1; i < 256; ++i) {
        cdf[i] = cdf[i - 1] + histogram[i];
        if (cdf_min < 0 && histogram[i] > 0) {
            cdf_min = cdf[i];
        }
    }

    // If the image has no valid pixel data or all pixels share the same value,
    // skip equalization and copy src to dst as-is.
    if (cdf_min < 0 || cdf[255] <= cdf_min) {
        uint8_t *dst_data = dst_image.data();
        std::memcpy(dst_data, src_data, static_cast<size_t>(total_pixels) * sizeof(uint8_t));
        return true;
    }

    // Step 3: Build lookup table for the equalization mapping.
    //         h(v) = round((cdf(v) - cdf_min) / (N - cdf_min) * 255)
    uint8_t lut[256];
    const float scale = 255.0f / static_cast<float>(cdf[255] - cdf_min);
    for (int32_t i = 0; i < 256; ++i) {
        const int32_t mapped = static_cast<int32_t>(std::round(static_cast<float>(cdf[i] - cdf_min) * scale));
        lut[i] = static_cast<uint8_t>(std::max(0, std::min(255, mapped)));
    }

    // Step 4: Apply the LUT to every pixel.
    uint8_t *dst_data = dst_image.data();
    for (int32_t i = 0; i < total_pixels; ++i) {
        dst_data[i] = lut[src_data[i]];
    }

    return true;
}

}  // namespace image_processor

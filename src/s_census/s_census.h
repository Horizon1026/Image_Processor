#ifndef _IMAGE_PROCESSOR_S_CENSUS_H_
#define _IMAGE_PROCESSOR_S_CENSUS_H_

#include "image_processor.h"

namespace image_processor {

class SCensusProcessor: public ImageProcessor {

public:
    SCensusProcessor() = default;
    virtual ~SCensusProcessor() = default;
    SCensusProcessor(const SCensusProcessor &image_processor) = delete;

    virtual bool Process(const GrayImage &src_image, GrayImage &dst_image) override;

private:
    std::array<std::array<int32_t, 2>, 8> index_offset_ = {{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};
};

}  // namespace image_processor

#endif  // end of _IMAGE_PROCESSOR_S_CENSUS_H_

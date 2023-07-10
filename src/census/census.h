#ifndef _IMAGE_PROCESSOR_CENSUS_H_
#define _IMAGE_PROCESSOR_CENSUS_H_

#include "image_processor.h"

namespace IMAGE_PROCESSOR {

class CensusProcessor : public ImageProcessor {

public:
    CensusProcessor() = default;
    virtual ~CensusProcessor() = default;
    CensusProcessor(const CensusProcessor &image_processor) = delete;

    virtual bool Process(const GrayImage &src_image, GrayImage &dst_image) override;

private:
    std::array<std::array<int32_t, 2>, 8> index_offset_ = {{
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0, -1},
        {0, 1},
        {1, -1},
        {1, 0},
        {1, 1}
    }};

};

}

#endif // end of _IMAGE_PROCESSOR_CENSUS_H_

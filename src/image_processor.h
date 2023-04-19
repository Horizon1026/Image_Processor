#ifndef _IMAGE_PROCESSOR_H_
#define _IMAGE_PROCESSOR_H_

#include "datatype_basic.h"
#include "datatype_image.h"

namespace IMAGE_PROCESSOR {

class ImageProcessor {

public:
    ImageProcessor() = default;
    virtual ~ImageProcessor() = default;
    ImageProcessor(const ImageProcessor &image_processor) = delete;

    virtual bool Process(const Image &src_image, Image &dst_image);

    Mat &kernel() { return kernel_; }

private:
    Mat kernel_ = Mat3::Ones();
};

}

#endif // end of _IMAGE_PROCESSOR_H_

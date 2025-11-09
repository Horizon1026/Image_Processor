#ifndef _IMAGE_PROCESSOR_H_
#define _IMAGE_PROCESSOR_H_

#include "basic_type.h"
#include "datatype_image.h"

namespace IMAGE_PROCESSOR {

class ImageProcessor {

public:
    ImageProcessor() = default;
    virtual ~ImageProcessor() = default;
    ImageProcessor(const ImageProcessor &image_processor) = delete;

    virtual bool Process(const GrayImage &src_image, GrayImage &dst_image);

    Mat &kernel() { return kernel_; }

private:
    Mat kernel_ = Mat3::Ones();
};

}  // namespace IMAGE_PROCESSOR

#endif  // end of _IMAGE_PROCESSOR_H_

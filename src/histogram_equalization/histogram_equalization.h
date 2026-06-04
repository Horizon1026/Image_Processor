#ifndef _IMAGE_PROCESSOR_HISTOGRAM_EQUALIZATION_H_
#define _IMAGE_PROCESSOR_HISTOGRAM_EQUALIZATION_H_

#include "image_processor.h"

namespace image_processor {

/* Class HistogramEqualizationProcessor Declaration. */
class HistogramEqualizationProcessor : public ImageProcessor {

public:
    HistogramEqualizationProcessor() = default;
    virtual ~HistogramEqualizationProcessor() = default;
    HistogramEqualizationProcessor(const HistogramEqualizationProcessor &image_processor) = delete;

    virtual std::string ImageProcessorTypeName() const override { return "kHistogramEqualization"; }
    virtual bool Process(const GrayImage &src_image, GrayImage &dst_image) override;
};

}  // namespace image_processor

#endif  // end of _IMAGE_PROCESSOR_HISTOGRAM_EQUALIZATION_H_

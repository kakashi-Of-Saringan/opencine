#include <Catch2/catch.hpp>

#include <chrono>

#include "../OCcore/Image/BilinearDebayerOMP.h"
#include "../OCcore/Image/ImageProvider.h"
#include "../OCcore/Image/VideoClip.h"
#include "../OCcore/Log/Logger.h"
#include "../OCcore/Memory/StaticAllocator.h"

#define NUM_TRIES 50

TEST_CASE("Bilinear OMP Benchmark", "[OC::Image]")
{
    RawPoolAllocator* poolAllocator = new RawPoolAllocator();
       
    std::unique_ptr<OC::Image::OCImage> image(new OC::Image::OCImage());
    
    OC_LOG_INFO("Loading image.");
    std::unique_ptr<ImageProvider> provider(new ImageProvider());
    provider->Load("bench_frame.dng", OC::Image::FileFormat::DNG, *image.get(), *poolAllocator);
    OC_LOG_INFO("Load finished.");

    OC_LOG_INFO("Benchmarking...");

    std::unique_ptr<BilinearDebayerOMP> debayer(new BilinearDebayerOMP(*image));
    auto demosaicTime = 0;

    for(int i = 0; i < NUM_TRIES; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();

        debayer.get()->Process();

        auto diffTime = std::chrono::high_resolution_clock::now() - start;
        demosaicTime += std::chrono::duration_cast<std::chrono::milliseconds>(diffTime).count();
    }

    OC_LOG_INFO("\nBenchmark finished:\nALGORITHM> BilinearOMP\nNUM_TRIES> " + std::to_string(NUM_TRIES) + "\nAVG TIME > " +
                std::to_string(demosaicTime / NUM_TRIES) + "ms\n");
}

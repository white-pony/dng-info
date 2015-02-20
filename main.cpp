#include <iostream>
#include <string>
#include <vector>

#include <libraw/libraw.h>

void writeRaw(unsigned short* rawImage, int width, int height, const std::string& filename)
{
    FILE* f = fopen(filename.c_str(), "wb");
    fwrite(rawImage, sizeof(unsigned short), width * height, f);
    fclose(f);
}

int main(int argc, char* argv[])
{
    int retValue;

    std::string inputFn = std::string(argv[1]);
    // std::string outputFn = std::string(argv[2]);

    LibRaw rawProcessor;

    if((retValue = rawProcessor.open_file(inputFn.c_str())) != LIBRAW_SUCCESS)
    {
        std::cout << "Cann't open file: " << inputFn << "\n";
        return -1;
    }

    if((retValue = rawProcessor.unpack() ) != LIBRAW_SUCCESS)
    {
        std::cout << "Cann't unpack file: " << inputFn << "\n";
        return -1;
    }

    int rawWidth = rawProcessor.imgdata.sizes.raw_width, rawHeight = rawProcessor.imgdata.sizes.raw_height;

    printf("Size of the image: %d x %d\n", rawWidth, rawHeight);

    writeRaw(rawProcessor.imgdata.rawdata.raw_image, rawWidth, rawHeight, "test.raw");

    return 0;
}

#include "tracer.h"

Tracer::Tracer()
{
    // some sane defaults
    renderWidth = 640;
    renderHeight = 480;
}

Tracer::~Tracer()
{
    delete [] screen;
}

void Tracer::setRenderResolution(int width, int height)
{
    renderWidth = width;
    renderHeight = height;
}

bool Tracer::init()
{
    screenSize = renderWidth*renderHeight;
    screen = new Colour[screenSize];

    return true;
}

bool Tracer::loadExampleScene()
{
    return true;
}

void Tracer::trace()
{
    for (int i = 0; i < screenSize; ++i ) {
        // find which pixel this screen cell is for        
        int x = i % renderWidth;
        int y = (i - x) / renderWidth;

        // find where pixel x,y is in 3D space
        // project ray through pixel, see what it intersects
        if (x*y % 2 == 0)
            screen[i] = Colour(255,255,255);
    }
}

void Tracer::writeScreenToBmp(string filename)
{
    // short == 2 bytes
    // int   == 4 bytes

    struct BitMapFileHeader
    {
        short	magic;
        int		size;
        short	reserved1;
        short	reserved2;
        int		offbits;
    };

    struct BitMapInfoHeader
    {
        int		size;
        int		width;
        int		height;
        short	planes;
        short	bitCount;
        int		compression;
        int		sizeImage;
        int		xPixelsPerMeter;
        int		yPixelsPerMeter;
        int		clrUsed;
        int		clrImportant;
    };

    struct BitMapFileHeader	header;
    struct BitMapInfoHeader	info;

    // magic bytes
    int extraBytes = (4 - (renderWidth * 3) % 4) % 4; // each row must be multiple of four
    int imageBufferSize = (renderWidth * 3 + extraBytes) * renderHeight;

    header.magic = 0x4d42; // 'BM'
    header.size	= 14 + 40 + imageBufferSize;
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.offbits = 14 + 40;

    info.size = 40;
    info.width = renderWidth;
    info.height = renderHeight;
    info.planes = 1;
    info.bitCount = 24;
    info.compression = 0;
    info.sizeImage = imageBufferSize;
    info.xPixelsPerMeter = 2952;
    info.yPixelsPerMeter = 2952;
    info.clrUsed = 0;
    info.clrImportant = 0;

    char *imageBuffer = new char[imageBufferSize];

    // zero everything (make it black, zero the extra bytes)
    memset(imageBuffer, 0, sizeof(char)*imageBufferSize);

    for (int i = 0; i < screenSize; ++i ) {
        int x = i % renderWidth;
        int y = (i - x) / renderWidth;

        // use x and y to find offset n
        // this is because the bitmap format expects the last row first
        int n = (renderHeight - 1 - y) * (renderWidth * 3 + extraBytes) + (x * 3);

        // set blue, green, and red byte
        imageBuffer[n]		= (char)screen[i].blue;
        imageBuffer[n+1]	= (char)screen[i].green;
        imageBuffer[n+2]	= (char)screen[i].red;
    }

    // write to file
    ofstream outputFile(filename, ios::binary);

    // file header
    // we write each member of the struct one by one
    // this is to avoid some packing issues
    outputFile.write((char*)&header.magic, sizeof(header.magic));
    outputFile.write((char*)&header.size, sizeof(header.size));
    outputFile.write((char*)&header.reserved1, sizeof(header.reserved1));
    outputFile.write((char*)&header.reserved2, sizeof(header.reserved2));
    outputFile.write((char*)&header.offbits, sizeof(header.offbits));

    // info header and imageBuffer
    // we can write these directly because they're the correct size
    outputFile.write((char*)&info, sizeof(info));
    outputFile.write(imageBuffer, imageBufferSize);

    // close file handle
    outputFile.close();

    // clean up
    delete [] imageBuffer;
}
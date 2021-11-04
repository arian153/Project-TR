#include "TextResource.hpp"
#include <fstream>

namespace GAM400
{
    PixelData::PixelRGB::PixelRGB()
        : r(0), g(0), b(0)
    {
    }

    PixelData::PixelRGB::PixelRGB(Real value)
        : r(value), g(value), b(value)
    {
    }

    PixelData::PixelRGB::PixelRGB(Real red, Real green, Real blue)
        : r(red), g(green), b(blue)
    {
    }

    PixelData::PixelData()
        : w(0), h(0), pixels(nullptr)
    {
    }

    PixelData::PixelData(const U32& width, const U32& height)
        : w(width), h(height), pixels(nullptr)
    {
        pixels = new PixelRGB[w * h];
        for (U32 i = 0; i < w * h; ++i)
        {
            pixels[i] = PixelRGB(0.0f);
        }
    }

    PixelData::~PixelData()
    {
        if (pixels != nullptr)
            delete[] pixels;
    }

    TextResource::TextResource(const std::wstring& path)
        : Resource(path)
    {
    }

    TextResource::~TextResource()
    {
    }

    void TextResource::Initialize()
    {
        if (m_file_type_w == L".ppm")
        {
            m_b_loaded = LoadPPM();
        }
        else if (m_file_type_w == L".txt")
        {
            m_b_loaded = LoadText();
        }
    }

    void TextResource::Shutdown()
    {
        if (m_pixel_data != nullptr)
        {
            delete m_pixel_data;
        }

        m_b_unloaded = true;
    }

    bool TextResource::LoadText()
    {
        std::wifstream file;
        file.open(m_file_path_w);
        if (file)
        {
            m_text.clear();
            file.seekg(0, file.end);
            size_t length = file.tellg();
            file.seekg(0, file.beg);
            m_text.reserve(length);
            //read
            while (file.eof() == false)
            {
                std::wstring line;
                std::getline(file, line);
                m_text.append(line + L"\n");
            }
            file.close();
            return true;
        }
        return false;
    }

    std::wstring TextResource::GetText() const
    {
        return m_text;
    }

    bool TextResource::LoadPPM()
    {
        // need to spec. binary mode for Windows users
        std::ifstream file(m_file_path_m, std::ios::binary);
        if (file.is_open())
        {
            m_pixel_data = new PixelData();

            std::string header;
            int         w, h, b;
            file >> header;

            if (strcmp(header.c_str(), "P6") != 0)
            {
                //Can't read input file
                return false;
            }
            file >> w >> h >> b;
            m_pixel_data->w      = w;
            m_pixel_data->h      = h;
            m_pixel_data->pixels = new PixelData::PixelRGB[w * h];

            // skip empty lines in necessary until we get to the binary data 
            file.ignore(256, '\n');
            unsigned char pixel[3];
            // read each pixel one by one and convert bytes to floats
            for (U32 i = 0; i < w * h; ++i)
            {
                file.read(reinterpret_cast<char*>(pixel), 3);
                m_pixel_data->pixels[i].r = pixel[0] / 255.f;
                m_pixel_data->pixels[i].g = pixel[1] / 255.f;
                m_pixel_data->pixels[i].b = pixel[2] / 255.f;
            }
            file.close();
            return true;
        }

        //can't open file.
        file.close();
        return false;
    }

    bool TextResource::SavePPM(PixelData* data, const std::string& new_path)
    {
        if (data->w == 0 || data->h == 0)
        {
            // Null size of data, can't save an empty ppm.
            return false;
        }
        std::ofstream ofs(new_path, std::ios::binary);

        if (ofs.is_open())
        {
            ofs << "P6\n" << data->w << " " << data->h << "\n255\n";
            // loop over each pixel in the image, clamp and convert to byte format
            for (int i = 0; i < data->w * data->h; ++i)
            {
                unsigned char r = static_cast<unsigned char>(std::min(1.f, data->pixels[i].r) * 255);
                unsigned char g = static_cast<unsigned char>(std::min(1.f, data->pixels[i].g) * 255);
                unsigned char b = static_cast<unsigned char>(std::min(1.f, data->pixels[i].b) * 255);
                ofs << r << g << b;
            }
            ofs.close();
            return true;
        }
        //Can't open file
        ofs.close();
        return false;
    }

    PixelData* TextResource::GetPixelData() const
    {
        return m_pixel_data;
    }
}

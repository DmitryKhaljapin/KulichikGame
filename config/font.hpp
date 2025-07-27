#include <dwrite.h>

struct Font {
    const wchar_t* family = L"Segoe Script";
    DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_EXTRA_BOLD;
    DWRITE_FONT_STYLE style = DWRITE_FONT_STYLE_NORMAL;
    DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL;
    float size = 24.0f;
};
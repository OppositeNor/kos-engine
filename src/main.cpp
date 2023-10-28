
#include "cos_graphics/graphics.h"

int main()
{
    CGWindowSubProperty window_property = CGConstructDefaultWindowSubProperty();
    window_property.resizable = CG_TRUE;
    window_property.anti_aliasing = CG_TRUE;
    CGWindow* window = CGCreateWindow(1260, 720, CGSTR("Polygon Test"), window_property);
    CGVector2 polygon_vertices[6] = {
        (CGVector2){0, 0},
        (CGVector2){10, -120},
        (CGVector2){100, -100},
        (CGVector2){160, 60},
        (CGVector2){-100, 100},
        (CGVector2){-30, -100}
    };
    CGPolygon* polygon = CGCreatePolygon(polygon_vertices, 6, CG_FALSE);

    while (!CGShouldWindowClose(window))
    {
        CGTickRenderStart(window);
        
        CGDrawPolygon(polygon, NULL, window);
        CGVisualImage* text = CGCreateTextVisualImageRaw(CGSTR("Test text qwertyuiop QWERTYUIOP 中文测试"), 
            CGSTR("default_font"), CGConstructTextProperty(60, 60, 30, 2), window, CG_TRUE);
        CGDrawVisualImage(text, NULL, window);
        CGWindowDraw(window);
        CGTickRenderEnd();
    }
    CGFree(polygon);
    CGTerminateGraphics();
    return 0;
}
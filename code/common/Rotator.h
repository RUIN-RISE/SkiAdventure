#pragma once

// #include "stb_image.h"
// #include "stb_image_write.h"

#ifndef M_PI
const double M_PI = acos(-1);
#endif


// --- RotatableCharacter 类 ---
class RotatableCharacter : public Fl_Box {
    // 存储原始图像的像素数据
    std::vector<unsigned char> m_original_pixels;
    std::vector<unsigned char> rotated_pixels;
    int m_original_w = 0, m_original_h = 0, m_original_d = 0; // 原始图像的宽高深

    std::unique_ptr<Fl_RGB_Image> m_current_rotated_image; // 存储当前旋转后的Fl_RGB_Image
    double m_rotation_angle; // 旋转角度，单位：度
    bool fail_ ;
	
public:
    RotatableCharacter(int x, int y, int w, int h, const char* image_path)
        : Fl_Box(x, y, w, h), m_rotation_angle(0.0) {
		if(image_path != nullptr){
            Fl_PNG_Image png_image(image_path);
			// 使用 stb_image 加载图像。强制加载为 RGBA (4通道)以便处理透明度
			// unsigned char* loaded_pixels = stbi_load(image_path, &m_original_w, &m_original_h, &m_original_d, STBI_rgb_alpha);
			if (png_image.fail()) {
				Fl::error("Failed to load image with stb_image: %s", image_path);
                fail_ = true ;
				return;
			}
            // std::string debug_output_path = "debug_loaded_image.png";
            // if (stbi_write_png(debug_output_path.c_str(), m_original_w, m_original_h, m_original_d, loaded_pixels, m_original_w * m_original_d)) {
            //     std::cerr << "DEBUG: Successfully wrote loaded pixels to " << debug_output_path << std::endl;
            // } else {
            //     std::cerr << "DEBUG: Failed to write loaded pixels to " << debug_output_path << std::endl;
            // }

            // std::cerr << "w,h,d:" << m_original_w << ' ' << m_original_h << ' ' << m_original_d << std::endl;
			// `STBI_rgb_alpha` 会强制加载为4通道，所以这里 d 强制为4
			
			// 将加载的像素数据复制到 std::vector 中，以便管理内存
			// m_original_pixels.assign(loaded_pixels, loaded_pixels + (m_original_w * m_original_h * m_original_d));

            // // stbi_image_free(loaded_pixels); // 释放 stb_image 分配的内存
			// // 初始化时生成一次旋转图像 (0度)
			// update_rotated_image();
            // fail_ = false ;

            m_original_w = png_image.w();
            m_original_h = png_image.h();
            // 注意：FLTK加载的RGBA图像，其深度d()可能为3或4。
            // 为了与你的旋转逻辑统一，我们需要确保数据是4通道的。
            // Fl_PNG_Image 会自动处理透明度，所以d()通常就是4。
            m_original_d = png_image.d(); 

            const unsigned char* loaded_pixels = (const unsigned char*)png_image.data()[0];

            // 4. 将加载的像素数据复制到你的 vector 中，以便后续处理
            m_original_pixels.assign(loaded_pixels, loaded_pixels + (m_original_w * m_original_h * m_original_d));
            update_rotated_image();
            fail_ = false ;
		}
        else{
            fail_ = true ;
        }
    }

	void set_angle(double angle);

	void update_rotated_image();

	void draw() override;

    bool fail(){return fail_;}
};

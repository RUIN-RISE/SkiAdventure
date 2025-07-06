#include "Rotator.h"

std::vector<unsigned char> rotate_image_pixels(
    const unsigned char* original_data, int original_w, int original_h, int original_d,
    double angle_degrees, int& rotated_w, int& rotated_h) {

    double angle_rad = angle_degrees * M_PI / 180.0;
    double cos_a = cos(angle_rad);
    double sin_a = sin(angle_rad);

    // 计算旋转后图像的边界框，以确定新的宽和高
    // 这确保旋转后的图像不会被裁剪，即使它变大了
    double corners[8] = {
        0, 0, // Top-left
        (double)original_w, 0, // Top-right
        0, (double)original_h, // Bottom-left
        (double)original_w, (double)original_h // Bottom-right
    };

    double min_x = 0, max_x = 0, min_y = 0, max_y = 0;

    for (int i = 0; i < 4; ++i) {
        double x = corners[i * 2];
        double y = corners[i * 2 + 1];

        // 旋转后的坐标
        double new_x = x * cos_a - y * sin_a;
        double new_y = x * sin_a + y * cos_a;

        if (new_x < min_x) min_x = new_x;
        if (new_x > max_x) max_x = new_x;
        if (new_y < min_y) min_y = new_y;
        if (new_y > max_y) max_y = new_y;
    }

    rotated_w = static_cast<int>(ceil(max_x - min_x));
    rotated_h = static_cast<int>(ceil(max_y - min_y));

    std::vector<unsigned char> rotated_pixels(rotated_w * rotated_h * original_d);
    // 初始化为透明或背景色
    if (original_d == 4) { // 如果是RGBA，设置为全透明
        for (int i = 0; i < rotated_w * rotated_h; ++i) {
            rotated_pixels[i * original_d + 3] = 0; // Set alpha to 0 for transparency
        }
    } else {
        // For RGB, initialize to black or other background color
        memset(rotated_pixels.data(), 0, rotated_w * rotated_h * original_d);
    }

    // 计算原始图像中心到旋转中心（新图像的中心）的偏移
    double center_x_orig = original_w / 2.0;
    double center_y_orig = original_h / 2.0;
    double center_x_rotated = rotated_w / 2.0;
    double center_y_rotated = rotated_h / 2.0;

    // 遍历新图像的每个像素
    for (int y_new = 0; y_new < rotated_h; ++y_new) {
        for (int x_new = 0; x_new < rotated_w; ++x_new) {
            // 将新图像坐标转换为相对于其中心的坐标
            double x_centered_new = x_new - center_x_rotated;
            double y_centered_new = y_new - center_y_rotated;

            // 反向旋转，找到它在原始图像中的对应坐标
            // 注意：这里是反向旋转，角度是 -angle_rad
            double x_orig_rotated = x_centered_new * cos_a + y_centered_new * sin_a;
            double y_orig_rotated = -x_centered_new * sin_a + y_centered_new * cos_a;

            // 转换回原始图像的绝对坐标
            int x_orig = static_cast<int>(round(x_orig_rotated + center_x_orig)); // 使用 round 进行更准确的最近邻
            int y_orig = static_cast<int>(round(y_orig_rotated + center_y_orig));

            // 检查原始坐标是否在图像范围内
            if (x_orig >= 0 && x_orig < original_w && y_orig >= 0 && y_orig < original_h) {
                // 复制像素（最近邻插值）
                size_t original_idx = (size_t)(y_orig * original_w + x_orig) * original_d;
                size_t rotated_idx = (size_t)(y_new * rotated_w + x_new) * original_d;
                for (int c = 0; c < original_d; ++c) {
                    rotated_pixels[rotated_idx + c] = original_data[original_idx + c];
                }
            } else {
                // 超出范围的像素已经初始化为透明或背景色
            }
        }
    }
    return rotated_pixels;
    // return std::vector<unsigned char>(original_data);
}

void RotatableCharacter::set_angle(double angle) {
    // 优化：只在角度真正改变时才进行昂贵的图像处理
    if (std::abs(m_rotation_angle - angle) > 0.001) { // 浮点数比较需要容差
        m_rotation_angle = angle;
        update_rotated_image(); // 重新生成旋转图像
        redraw(); // 请求重绘
    }
}

void RotatableCharacter::update_rotated_image() {
    if (m_original_pixels.empty()) return;

    m_current_rotated_image.reset(); // 释放旧的旋转图像

    int rotated_w, rotated_h;
    // 调用我们上面实现的像素旋转函数
    rotated_pixels = rotate_image_pixels(
        m_original_pixels.data(),
        m_original_w, m_original_h, m_original_d,
        m_rotation_angle, rotated_w, rotated_h);

    if (!rotated_pixels.empty()) {
        m_current_rotated_image = std::make_unique<Fl_RGB_Image>(
            rotated_pixels.data(), rotated_w, rotated_h, m_original_d);
    }
}

const int visual_offset = -15;

void RotatableCharacter::draw() {
    if (!m_current_rotated_image) {
		std::cerr << "No image in RotatableCharacter" << std::endl ;
        fl_color(FL_RED);
        fl_rectf(x(), y(), w(), h());
        return;
    }

    // 计算绘制图像的左上角位置，使其在 Fl_Box 中居中
    // 旋转后的图像可能比原始 Fl_Box 大，需要居中或按比例缩放
    int draw_x = x() - m_current_rotated_image->w() / 2;
    int draw_y = y() - m_current_rotated_image->h() / 2 + visual_offset;

    // 直接绘制旋转后的图像
    // std::cerr << "Draw x y : " << draw_x << ' ' << draw_y << std::endl ;
    m_current_rotated_image->draw(draw_x, draw_y);
}

#pragma once

#include <array>
#include <cstdint>
#include <fstream>

namespace mmptf {
    using bbox_t = std::array<float, 6>;

    struct file_header {
        std::uint32_t _start_frame_id;
        std::uint32_t _end_frame_id;
        std::uint64_t _num_trajectories;
        bool _has_colors;
        bool _has_attributes;
        bbox_t _bbox;
    };

    inline file_header read_file_header(std::ifstream& file) {
        file_header ret;
        file.read(&ret, sizeof(file_header));
        return ret;
    }

    inline void write_file_header(std::ofstream& file, file_header const& header) {
        file.write(&header, sizeof(header));
    }
}
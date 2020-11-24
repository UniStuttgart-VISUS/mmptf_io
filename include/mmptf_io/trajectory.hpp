#pragma once

#include <array>
#include <cstdint>
#include <fstream>
#include <vector>
#include <unordered_map>

namespace mmptf {
    using position = std::array<float, 3>;

    using color = std::array<std::uint8_t, 4>;

    using attribute = std::array<float, 4>;

    using id_t = std::uint64_t;

    struct trajectory_header {
        std::uint32_t _start_frame_id;
        std::uint32_t _end_frame_id;
        bool _decycled;
    };

    struct trajectory {
        trajectory_header _header;
        std::vector<position> _positions;
        std::vector<color> _colors;
        std::vector<attribute> _attributes;
    };

    using trajectory_map_t = std::unordered_map<id_t, trajectory>;

    inline std::uint32_t get_num_elements(trajectory_header const& header) {
        return header._end_frame_id - header._start_frame_id;
    }

    inline trajectory_map_t read_trajectories(std::ifstream& file, std::uint64_t num_trajectories, bool has_colors, bool has_attributes) {
        trajectory_map_t ret;
        for (std::uint64_t idx = 0; idx < num_trajectories; ++idx) {
            id_t id = 0;
            trajectory_header header = { 0 };
            file >> id;
            file.read(&header, sizeof(trajectory_header));
            auto const num_elements = get_num_elements(header);

            trajectory traj;
            traj._header = header;
            traj._positions.resize(num_elements);

            file.read(traj._positions.data(), traj._positions.size() * sizeof(decltype(traj._positions)::value_type));

            if (has_colors) {
                traj._colors.resize(num_elements);
                file.read(traj._colors.data(), traj._colors.size() * sizeof(decltype(traj._colors)::value_type));
            }

            if (has_attributes) {
                traj._attributes.resize(num_elements);
                file.read(traj._attributes.data(), traj._attributes.size() * sizeof(decltype(traj._attributes)::value_type));
            }

            ret[id] = traj;
        }
        return ret;
    }

    inline void write_trajectories(std::ofstream& file, trajectory_map_t const& trajectories) {
        for (auto const& traj : trajectories) {
            file.write(&traj.first, sizeof(traj.first));
            auto const& traj_data = traj.second;
            auto const& traj_header = traj.second._header;
            file.write(&traj_header, sizeof(traj_header));
            file.write(traj_data._positions.data(), traj_data._positions.size() * sizeof(decltype(traj_data._positions)::value_type));
            file.write(traj_data._colors.data(), traj_data._colors.size() * sizeof(decltype(traj_data._colors)::value_type));
            file.write(traj_data._attributes.data(), traj_data._attributes.size() * sizeof(decltype(traj_data._attributes)::value_type));
        }
    }
}
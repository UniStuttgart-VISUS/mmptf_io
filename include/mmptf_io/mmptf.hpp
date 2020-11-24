#pragma once

#include <fstream>
#include <string>

#include "file_header.hpp"
#include "trajectory.hpp"

namespace mmptf {

    class immptf {
    public:
        immptf(std::string const& filename) {
            _file.open(filename, std::ios::binary);

            try {
                _file_header = read_file_header(_file);
                _trajectories = read_trajectories(_file, _file_header._num_trajectories, _file_header._has_colors, _file_header._has_attributes);
            } catch (...) {
                _file.close();
                throw;
            }
        }

        ~immptf() {
            if (_file.is_open()) {
                _file.close();
            }
        }

        trajectory get_trajectory(id_t id) const {
            return _trajectories[id];
        }

        trajectory_map_t get_all_trajectories() const {
            return _trajectories;
        }
    private:
        std::ifstream _file;

        file_header _file_header;

        trajectory_map_t _trajectories;
    };

    class ommptf {
    public:
        ommptf(std::string const& filename, file_header const& header, trajectory_map_t const& trajectories) {
            _file.open(filename, std::ios::binary);

            try {
                write_file_header(_file, header);
                write_trajectories(_file, trajectories);
            } catch (...) {
                _file.close();
                throw;
            }
        }

        ~ommptf() {
            if (_file.is_open()) {
                _file.close();
            }
        }
    private:
        std::ofstream _file;
    };

}
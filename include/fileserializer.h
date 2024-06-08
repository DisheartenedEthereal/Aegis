#ifndef FILE_SERIALIZER_H
#define FILE_SERIALIZER_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

// A class that provides static methods for serializing and deserializing any class
template <typename T>
class FileSerializer {
public:
    // Serialize a single object to a file
    static void serialize(const T& obj, const std::string& filename) {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs) {
            throw std::runtime_error("Could not open file for writing");
        }
        obj.serialize(ofs);
    }

    // Deserialize a single object from a file
    static void deserialize(T& obj, const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs) {
            throw std::runtime_error("Could not open file for reading");
        }
        obj.deserialize(ifs);
    }

    // Serialize a vector of objects to a file
    static void serializeVector(const std::vector<T>& vec, const std::string& filename) {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs) {
            throw std::runtime_error("Could not open file for writing");
        }
        size_t size = vec.size();
        ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& obj : vec) {
            obj.serialize(ofs);
        }
    }

    // Deserialize a vector of objects from a file
    static void deserializeVector(std::vector<T>& vec, const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs) {
            throw std::runtime_error("Could not open file for reading");
        }
        size_t size;
        ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
        vec.resize(size);
        for (auto& obj : vec) {
            obj.deserialize(ifs);
        }
    }
};

#endif // FILE_SERIALIZER_H

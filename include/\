#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H
#include <iostream>
#include <fstream>
#include <stdexcept>

class Serializable {
public:
    virtual ~Serializable() = default;

    // Pure virtual methods for serialization and deserialization
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;

    // Method to serialize the object to a file
    void serializeToFile(const std::string& filename) const {
        std::ofstream ofs(filename, std::ios::binary);
        if (!ofs) {
            throw std::runtime_error("Could not open file for writing");
        }
        serialize(ofs);
    }

    // Method to deserialize the object from a file
    void deserializeFromFile(const std::string& filename) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs) {
            throw std::runtime_error("Could not open file for reading");
        }
        deserialize(ifs);
    }
};

#endif // SERIALIZABLE_H

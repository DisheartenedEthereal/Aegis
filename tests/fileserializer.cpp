#include "doctest/doctest.h"
#include "fileserializer.h"
#include "dataframe.h"
#include <fstream>
#include <cstdio>

// Helper function to remove files after tests
void removeFile(const std::string& filename) {
    std::remove(filename.c_str());
}

TEST_CASE("FileSerializer single object serialization and deserialization") {
    const std::string filename = "single_device.dat";

    // Create a network device
    NetworkStructure::NetworkDevice originalDevice("Router A", "192.168.1.1", "Router", true);

    // Serialize the device to a file
    FileSerializer<NetworkStructure::NetworkDevice>::serialize(originalDevice, filename);

    // Deserialize the device from the file
    NetworkStructure::NetworkDevice deserializedDevice;
    FileSerializer<NetworkStructure::NetworkDevice>::deserialize(deserializedDevice, filename);

    // Check that the deserialized device matches the original
    CHECK(deserializedDevice.getDeviceName() == "Router A");
    CHECK(deserializedDevice.getIpAddress() == "192.168.1.1");
    CHECK(deserializedDevice.getDeviceType() == "Router");
    CHECK(deserializedDevice.getIsProtected() == true);

    // Clean up
    removeFile(filename);
}

TEST_CASE("FileSerializer vector serialization and deserialization") {
    const std::string filename = "network_devices.dat";

    // Create some network devices
    NetworkStructure::NetworkDevice device1("Router A", "192.168.1.1", "Router", true);
    NetworkStructure::NetworkDevice device2("Switch B", "192.168.1.2", "Switch", false);
    NetworkStructure::NetworkDevice device3("Firewall C", "192.168.1.3", "Firewall", true);

    std::vector<NetworkStructure::NetworkDevice> originalDevices = { device1, device2, device3 };

    // Serialize the vector of devices to a file
    FileSerializer<NetworkStructure::NetworkDevice>::serializeVector(originalDevices, filename);

    // Deserialize the vector of devices from the file
    std::vector<NetworkStructure::NetworkDevice> deserializedDevices;
    FileSerializer<NetworkStructure::NetworkDevice>::deserializeVector(deserializedDevices, filename);

    // Check that the deserialized vector matches the original
    REQUIRE(deserializedDevices.size() == originalDevices.size());

    for (size_t i = 0; i < originalDevices.size(); ++i) {
        CHECK(deserializedDevices[i].getDeviceName() == originalDevices[i].getDeviceName());
        CHECK(deserializedDevices[i].getIpAddress() == originalDevices[i].getIpAddress());
        CHECK(deserializedDevices[i].getDeviceType() == originalDevices[i].getDeviceType());
        CHECK(deserializedDevices[i].getIsProtected() == originalDevices[i].getIsProtected());
    }

    // Clean up
    removeFile(filename);
}

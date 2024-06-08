#include "serializable.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
class CompanyProfile {
private:
  std::string companyName;
  std::string domain;
  std::string ipAddress;
  double securityRating;
  std::string description;

public:
  // Constructor
  CompanyProfile(const std::string &companyName, const std::string &domain,
                 const std::string &ipAddress, double securityRating,
                 const std::string &description)
      : companyName(companyName), domain(domain), ipAddress(ipAddress),
        securityRating(securityRating), description(description) {}

  // Getter and Setter for companyName
  void setCompanyName(const std::string &companyName) {
    this->companyName = companyName;
  }

  std::string getCompanyName() const { return companyName; }

  // Getter and Setter for domain
  void setDomain(const std::string &domain) { this->domain = domain; }

  std::string getDomain() const { return domain; }

  // Getter and Setter for ipAddress
  void setIpAddress(const std::string &ipAddress) {
    this->ipAddress = ipAddress;
  }

  std::string getIpAddress() const { return ipAddress; }

  // Getter and Setter for securityRating
  void setSecurityRating(double securityRating) {
    this->securityRating = securityRating;
  }

  double getSecurityRating() const { return securityRating; }

  // Getter and Setter for description
  void setDescription(const std::string &description) {
    this->description = description;
  }

  std::string getDescription() const { return description; }

  // Function to print CompanyProfile details
  void printDetails() const {
    std::cout << "Company Profile Details:\n";
    std::cout << "Company Name: " << companyName << "\n";
    std::cout << "Domain: " << domain << "\n";
    std::cout << "IP Address: " << ipAddress << "\n";
    std::cout << "Security Rating: " << securityRating << "\n";
    std::cout << "Description: " << description << "\n";
  }
};

class DataFrame {
private:
  std::vector<CompanyProfile> profiles;

public:
  // Add a new company profile
  void addProfile(const CompanyProfile &profile) {
    profiles.push_back(profile);
  }

  // Get the profile at a specific index
  CompanyProfile getProfile(int index) const {
    if (index >= 0 && index < int(profiles.size())) {
      return profiles[index];
    } else {
      throw std::out_of_range("Index out of range");
    }
  }

  // Print all profiles
  void printAllProfiles() const {
    for (const auto &profile : profiles) {
      profile.printDetails();
      std::cout << "-----------------------------------\n";
    }
  }
};
class NetworkStructure : public Serializable {
public:
  // Nested class representing a network device
  class NetworkDevice : public Serializable {
  private:
    std::string deviceName;
    std::string ipAddress;
    std::string deviceType; // e.g., router, switch, firewall
    bool isProtected; // indicates if the device is protected by a security
                      // measure

  public:
    // Constructor
    //       NetworkDevice(const std::string& deviceName, const std::string&
    //       ipAddress, const std::string& deviceType, bool isProtected)
    //           : deviceName(deviceName), ipAddress(ipAddress),
    //           deviceType(deviceType), isProtected(isProtected) {}
    NetworkDevice(const std::string &deviceName = "",
                  const std::string &ipAddress = "",
                  const std::string &deviceType = "", bool isProtected = false)
        : deviceName(deviceName), ipAddress(ipAddress), deviceType(deviceType),
          isProtected(isProtected) {}

    // Getter methods
    std::string getDeviceName() const { return deviceName; }
    std::string getIpAddress() const { return ipAddress; }
    std::string getDeviceType() const { return deviceType; }
    bool getIsProtected() const { return isProtected; }

    // Setter methods
    void setDeviceName(const std::string &deviceName) {
      this->deviceName = deviceName;
    }
    void setIpAddress(const std::string &ipAddress) {
      this->ipAddress = ipAddress;
    }
    void setDeviceType(const std::string &deviceType) {
      this->deviceType = deviceType;
    }
    void setIsProtected(bool isProtected) { this->isProtected = isProtected; }

    // Method to print device details
    void printDetails() const {
      std::cout << "Device Name: " << deviceName << "\n";
      std::cout << "IP Address: " << ipAddress << "\n";
      std::cout << "Device Type: " << deviceType << "\n";
      std::cout << "Protected: " << (isProtected ? "Yes" : "No") << "\n";
    }
    // Serialization method
    void serialize(std::ostream &os) const override {
      size_t nameLength = deviceName.size();
      size_t ipLength = ipAddress.size();
      size_t typeLength = deviceType.size();

      os.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));
      os.write(deviceName.c_str(), nameLength);
      os.write(reinterpret_cast<const char *>(&ipLength), sizeof(ipLength));
      os.write(ipAddress.c_str(), ipLength);
      os.write(reinterpret_cast<const char *>(&typeLength), sizeof(typeLength));
      os.write(deviceType.c_str(), typeLength);
      os.write(reinterpret_cast<const char *>(&isProtected),
               sizeof(isProtected));
    }

    // Deserialization method
    void deserialize(std::istream &is) override {
      size_t nameLength, ipLength, typeLength;
      is.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
      deviceName.resize(nameLength);
      is.read(&deviceName[0], nameLength);

      is.read(reinterpret_cast<char *>(&ipLength), sizeof(ipLength));
      ipAddress.resize(ipLength);
      is.read(&ipAddress[0], ipLength);

      is.read(reinterpret_cast<char *>(&typeLength), sizeof(typeLength));
      deviceType.resize(typeLength);
      is.read(&deviceType[0], typeLength);

      is.read(reinterpret_cast<char *>(&isProtected), sizeof(isProtected));
    }
  };

private:
  std::vector<NetworkDevice> devices;

public:
  // Method to add a new device to the network
  void addDevice(const NetworkDevice &device) { devices.push_back(device); }

  // Method to get a device by index
  NetworkDevice getDevice(int index) const {
    if (index >= 0 && index < int(devices.size())) {
      return devices[index];
    } else {
      throw std::out_of_range("Index out of range");
    }
  }

  // Method to print all devices in the network
  void printAllDevices() const {
    for (const auto &device : devices) {
      device.printDetails();
      std::cout << "-----------------------------------\n";
    }
  }
  // Serialization method
  void serialize(std::ostream &os) const override {
    size_t size = devices.size();
    os.write(reinterpret_cast<const char *>(&size), sizeof(size));
    for (const auto &device : devices) {
      device.serialize(os);
    }
  }

  // Deserialization method
  void deserialize(std::istream &is) override {
    size_t size;
    is.read(reinterpret_cast<char *>(&size), sizeof(size));
    devices.resize(size);
    for (auto &device : devices) {
      device.deserialize(is);
    }
  }
};

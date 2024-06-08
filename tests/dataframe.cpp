#include "doctest/doctest.h"
#include "dataframe.h"

TEST_CASE("CompanyProfile class tests") {
    CompanyProfile profile("Company A", "companyA.com", "192.168.1.1", 8.5, "Leading provider of cybersecurity solutions.");

    CHECK(profile.getCompanyName() == "Company A");
    CHECK(profile.getDomain() == "companyA.com");
    CHECK(profile.getIpAddress() == "192.168.1.1");
    CHECK(profile.getSecurityRating() == 8.5);
    CHECK(profile.getDescription() == "Leading provider of cybersecurity solutions.");

    profile.setCompanyName("Company B");
    profile.setDomain("companyB.com");
    profile.setIpAddress("192.168.1.2");
    profile.setSecurityRating(9.1);
    profile.setDescription("Innovative tech company focused on cybersecurity.");

    CHECK(profile.getCompanyName() == "Company B");
    CHECK(profile.getDomain() == "companyB.com");
    CHECK(profile.getIpAddress() == "192.168.1.2");
    CHECK(profile.getSecurityRating() == 9.1);
    CHECK(profile.getDescription() == "Innovative tech company focused on cybersecurity.");
}

TEST_CASE("DataFrame class tests") {
    DataFrame df;

    CompanyProfile profile1("Company A", "companyA.com", "192.168.1.1", 8.5, "Leading provider of cybersecurity solutions.");
    CompanyProfile profile2("Company B", "companyB.net", "192.168.1.2", 7.2, "Innovative tech company focused on cybersecurity.");

    df.addProfile(profile1);
    df.addProfile(profile2);

    CHECK(df.getProfile(0).getCompanyName() == "Company A");
    CHECK(df.getProfile(1).getCompanyName() == "Company B");

    CHECK_THROWS_AS(df.getProfile(2), std::out_of_range);
}
TEST_CASE("NetworkDevice class tests") {
    NetworkStructure::NetworkDevice device("Router A", "192.168.1.1", "Router", true);

    CHECK(device.getDeviceName() == "Router A");
    CHECK(device.getIpAddress() == "192.168.1.1");
    CHECK(device.getDeviceType() == "Router");
    CHECK(device.getIsProtected() == true);

    device.setDeviceName("Switch B");
    device.setIpAddress("192.168.1.2");
    device.setDeviceType("Switch");
    device.setIsProtected(false);

    CHECK(device.getDeviceName() == "Switch B");
    CHECK(device.getIpAddress() == "192.168.1.2");
    CHECK(device.getDeviceType() == "Switch");
    CHECK(device.getIsProtected() == false);
}

TEST_CASE("NetworkStructure class tests") {
    NetworkStructure network;

    NetworkStructure::NetworkDevice device1("Router A", "192.168.1.1", "Router", true);
    NetworkStructure::NetworkDevice device2("Switch B", "192.168.1.2", "Switch", false);

    network.addDevice(device1);
    network.addDevice(device2);

    CHECK(network.getDevice(0).getDeviceName() == "Router A");
    CHECK(network.getDevice(0).getIpAddress() == "192.168.1.1");
    CHECK(network.getDevice(0).getDeviceType() == "Router");
    CHECK(network.getDevice(0).getIsProtected() == true);

    CHECK(network.getDevice(1).getDeviceName() == "Switch B");
    CHECK(network.getDevice(1).getIpAddress() == "192.168.1.2");
    CHECK(network.getDevice(1).getDeviceType() == "Switch");
    CHECK(network.getDevice(1).getIsProtected() == false);

    CHECK_THROWS_AS(network.getDevice(2), std::out_of_range);
}

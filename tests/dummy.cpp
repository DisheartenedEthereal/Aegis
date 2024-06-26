#include "doctest/doctest.h"
#include "dataframe.h"
// Tests that don't naturally fit in the headers/.cpp files directly
// can be placed in a tests/*.cpp file. Integration tests are a good example.

// Tests
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

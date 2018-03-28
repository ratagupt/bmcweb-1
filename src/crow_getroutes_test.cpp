#include <crow/app.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace crow;
using namespace std;

TEST(GetRoutes, TestEmptyRoutes) {
  SimpleApp app;
  decltype(app)::server_t server(&app, "127.0.0.1", 45451);

  EXPECT_THAT(app.get_routes(), testing::IsEmpty());
}

// Tests that static urls are correctly passed
TEST(GetRoutes, TestOneRoute) {
  SimpleApp app;
  decltype(app)::server_t server(&app, "127.0.0.1", 45451);
  CROW_ROUTE(app, "/")([]() { return boost::beast::http::status::ok; });

  EXPECT_THAT(app.get_routes(),
              testing::ElementsAre(testing::Pointee(std::string("/"))));
}

// Tests that static urls are correctly passed
TEST(GetRoutes, TestlotsOfRoutes) {
  SimpleApp app;
  decltype(app)::server_t server(&app, "127.0.0.1", 45451);
  CROW_ROUTE(app, "/")([]() { return boost::beast::http::status::ok; });
  CROW_ROUTE(app, "/foo")([]() { return boost::beast::http::status::ok; });
  CROW_ROUTE(app, "/bar")([]() { return boost::beast::http::status::ok; });
  CROW_ROUTE(app, "/baz")([]() { return boost::beast::http::status::ok; });
  CROW_ROUTE(app, "/boo")([]() { return boost::beast::http::status::ok; });
  CROW_ROUTE(app, "/moo")([]() { return boost::beast::http::status::ok; });

  EXPECT_THAT(app.get_routes(), testing::UnorderedElementsAre(
                                    testing::Pointee(std::string("/")),
                                    testing::Pointee(std::string("/foo")),
                                    testing::Pointee(std::string("/bar")),
                                    testing::Pointee(std::string("/baz")),
                                    testing::Pointee(std::string("/boo")),
                                    testing::Pointee(std::string("/moo"))));
}
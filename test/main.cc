#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

#include "http_message.h"
#include "uri.h"

using namespace simple_http_server;

constexpr char EXPECT_TRUE_FAILED_MSG[] = " failed on line ";

inline void ExpectTrue(bool condition, const char* function, int line, int& error_count) {
    if (!condition) {
        error_count++;
        std::cerr << function << EXPECT_TRUE_FAILED_MSG << line << std::endl;
    }
}

int TestUriPathToLowercase() {
    int error_count = 0;
    std::string path = "/SayHello.HTML?name=abc&message=welcome";
    std::string lowercase_path;
    std::transform(path.begin(), path.end(), std::back_inserter(lowercase_path), [](char c) { return std::tolower(c); });

    Uri uri("/SayHello.html?name=abc&message=welcome");
    ExpectTrue(uri.path() == lowercase_path, __FUNCTION__, __LINE__, error_count);
    return error_count;
}

int TestMethodToString() {
    int error_count = 0;
    ExpectTrue(to_string(HttpMethod::GET) == "GET", __FUNCTION__, __LINE__, error_count);
    return error_count;
}

int TestVersionToString() {
    int error_count = 0;
    ExpectTrue(to_string(HttpVersion::HTTP_1_1) == "HTTP/1.1", __FUNCTION__, __LINE__, error_count);
    return error_count;
}

int TestStatusCodeToString() {
    int error_count = 0;
    ExpectTrue(to_string(HttpStatusCode::ImATeapot) == "I'm a Teapot", __FUNCTION__, __LINE__, error_count);
    ExpectTrue(to_string(HttpStatusCode::NoContent).empty(), __FUNCTION__, __LINE__, error_count);
    return error_count;
}

int TestStringToMethod() {
    int error_count = 0;
    ExpectTrue(string_to_method("GET") == HttpMethod::GET, __FUNCTION__, __LINE__, error_count);
    ExpectTrue(string_to_method("post") == HttpMethod::POST, __FUNCTION__, __LINE__, error_count);
    return error_count;
}

int TestStringToVersion() {
    int error_count = 0;
    ExpectTrue(string_to_version("HTTP/1.1") == HttpVersion::HTTP_1_1, __FUNCTION__, __LINE__, error_count);
    return error_count;
}

int TestRequestToString() {
    int error_count = 0;
    HttpRequest request;
    request.SetMethod(HttpMethod::GET);
    request.SetUri(Uri("/"));
    request.SetHeader("Connection", "Keep-Alive");
    request.SetContent("hello, world\n");

    std::ostringstream expected_str;
    expected_str << "GET / HTTP/1.1\r\nConnection: Keep-Alive\r\nContent-Length: 13\r\n\r\nhello, world\n";

    ExpectTrue(to_string(request) == expected_str.str(), __FUNCTION__, __LINE__, error_count);
    return error_count;
}

int TestResponseToString() {
    int error_count = 0;
    HttpResponse response;
    response.SetStatusCode(HttpStatusCode::InternalServerError);

    std::ostringstream expected_str;
    expected_str << "HTTP/1.1 500 Internal Server Error\r\n\r\n";

    ExpectTrue(to_string(response) == expected_str.str(), __FUNCTION__, __LINE__, error_count);
    return error_count;
}

int main() {
    std::cout << "Running tests..." << std::endl;

    int total_errors = 0;
    total_errors += TestUriPathToLowercase();
    total_errors += TestMethodToString();
    total_errors += TestVersionToString();
    total_errors += TestStatusCodeToString();
    total_errors += TestStringToMethod();
    total_errors += TestStringToVersion();
    total_errors += TestRequestToString();
    total_errors += TestResponseToString();

    std::cout << "All tests have finished. There were " << total_errors
              << " errors in total" << std::endl;
    return total_errors;
}

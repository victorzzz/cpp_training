#include <charconv>
#include <exception>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

// Drill rules:
// 1. Implement parse_timeout_ms with std::from_chars and std::optional<int>.
// 2. Implement require_timeout_ms as the throwing wrapper around parse_timeout_ms.
// 3. Accept only full-string decimal integers in the range [0, 60000].
// 4. Before coding, explain time complexity, error strategy, and failure modes.

struct TestResult
{
    std::string name;
    bool passed;
    std::string detail;
};

std::optional<int> parse_timeout_ms(std::string_view text)
{
    (void)text;

    // TODO:
    // - reject empty input
    // - parse with std::from_chars
    // - reject partial parses such as "15ms" or " 15"
    // - reject negative numbers and values > 60000
    // - return std::nullopt on invalid input
    return std::nullopt;
}

int require_timeout_ms(std::string_view text)
{
    (void)text;

    // TODO:
    // - call parse_timeout_ms
    // - return the parsed value on success
    // - otherwise throw std::invalid_argument
    return -1;
}

TestResult expect_optional_value(const std::string &name,
                                 std::optional<int> expected,
                                 std::optional<int> actual)
{
    return {
        name,
        expected == actual,
        "expected=" + (expected ? std::to_string(*expected) : std::string("nullopt")) +
            " actual=" + (actual ? std::to_string(*actual) : std::string("nullopt"))};
}

TestResult expect_throw_invalid_argument(const std::string &name, std::string_view text)
{
    try
    {
        (void)require_timeout_ms(text);
        return {name, false, "expected std::invalid_argument"};
    }
    catch (const std::invalid_argument &)
    {
        return {name, true, "caught std::invalid_argument"};
    }
    catch (const std::exception &ex)
    {
        return {name, false, "caught different exception: " + std::string(ex.what())};
    }
    catch (...)
    {
        return {name, false, "caught non-standard exception"};
    }
}

int main()
{
    std::vector<TestResult> tests;
    tests.push_back(expect_optional_value("optional/zero", 0, parse_timeout_ms("0")));
    tests.push_back(expect_optional_value("optional/normal", 250, parse_timeout_ms("250")));
    tests.push_back(expect_optional_value("optional/max bound", 60000, parse_timeout_ms("60000")));
    tests.push_back(expect_optional_value("optional/empty invalid", std::nullopt, parse_timeout_ms("")));
    tests.push_back(expect_optional_value("optional/suffix invalid", std::nullopt, parse_timeout_ms("15ms")));
    tests.push_back(expect_optional_value("optional/leading space invalid", std::nullopt, parse_timeout_ms(" 15")));
    tests.push_back(expect_optional_value("optional/negative invalid", std::nullopt, parse_timeout_ms("-1")));
    tests.push_back(expect_optional_value("optional/out of range invalid", std::nullopt, parse_timeout_ms("60001")));
    tests.push_back(expect_optional_value("optional/overflow invalid", std::nullopt, parse_timeout_ms("999999999999")));
    tests.push_back(expect_optional_value("throwing/success", 42, require_timeout_ms("42")));
    tests.push_back(expect_throw_invalid_argument("throwing/invalid throws", "abc"));

    int passed = 0;
    for (const auto &test : tests)
    {
        if (test.passed)
        {
            ++passed;
        }

        std::cout << test.name << " | " << test.detail
                  << " => " << (test.passed ? "PASS" : "FAIL") << '\n';
    }

    std::cout << "Passed " << passed << "/" << tests.size() << " tests." << '\n';
    return (passed == static_cast<int>(tests.size())) ? 0 : 1;
}

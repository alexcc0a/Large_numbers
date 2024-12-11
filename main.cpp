#include <iostream>
#include <string>

class big_integer {
private:
    std::string number;
public:
    big_integer(const std::string& num) : number(num) {
        size_t first_non_zero = number.find_first_not_of('0');
        if (first_non_zero != std::string::npos) {
            number = number.substr(first_non_zero);
        } else {
            number = "0";
        }
    }

    big_integer(big_integer&& other) noexcept : number(std::move(other.number)) {
        other.number.clear();
    }

    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            number = std::move(other.number);
            other.number.clear();
        }
        return *this;
    }

    big_integer operator+(const big_integer& other) const {
        std::string result;
        int carry = 0;
        int max_len = std::max(number.size(), other.number.size());

        for (int i = 0; i < max_len || carry != 0; ++i) {
            int digit1 = i < number.size() ? number[number.size() - 1 - i] - '0' : 0;
            int digit2 = i < other.number.size() ? other.number[other.number.size() - 1 - i] - '0' : 0;
            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back('0' + sum % 10);
        }

        std::reverse(result.begin(), result.end());
        return big_integer(result);
    }

    big_integer operator*(int multiplier) const {
        if (multiplier == 0) {
            return big_integer("0");
        }

        std::string result;
        int carry = 0;

        for (int i = number.size() - 1; i >= 0; --i) {
            int digit = number[i] - '0';
            int product = digit * multiplier + carry;
            carry = product / 10;
            result.push_back('0' + product % 10);
        }

        while (carry) {
            result.push_back('0' + carry % 10);
            carry /= 10;
        }

        std::reverse(result.begin(), result.end());
        return big_integer(result);
    }

    friend std::ostream& operator<<(std::ostream& os, const big_integer& obj) {
        os << obj.number;
        return os;
    }
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");

    auto result = number1 + number2;
    std::cout << result << std::endl;

    auto product = number1 * 10;
    std::cout << product << std::endl;

    return 0;
}

#include <string_view>
#include <memory>
#include <cctype>
#include <cassert>

class password_validator
{
public:
    virtual bool validate(std::string_view passowrd) = 0;
    virtual ~password_validator() {}
};

class length_validator final : public password_validator
{
private:
    unsigned int length;

public:
    length_validator(unsigned int min_length) : length(min_length) {}
    virtual bool validate(std::string_view password) override
    {
        return password.length() >= length;
    }
};

class password_validator_decorator : public password_validator
{
private:
    std::unique_ptr<password_validator> inner;

public:
    explicit password_validator_decorator(std::unique_ptr<password_validator> validator) : inner(std::move(validator)) {}

    virtual bool validate(std::string_view password) override
    {
        return inner->validate(password);
    }
};

class digit_password_validator final : public password_validator_decorator
{
public:
    explicit digit_password_validator(std::unique_ptr<password_validator> validator) : password_validator_decorator(std::move(validator)) {}

    virtual bool validate(std::string_view password) override
    {
        if (!password_validator_decorator::validate(password))
        {
            return false;
        }
        return password.find_first_of("0123456789") != std::string::npos;
    }
};

class case_password_validator final : public password_validator_decorator
{
public:
    explicit case_password_validator(std::unique_ptr<password_validator> validator) : password_validator_decorator(std::move(validator)) {}

    virtual bool validate(std::string_view password) override
    {
        if (!password_validator_decorator::validate(password))
        {
            return false;
        }

        bool haslower = false, hasupper = false;

        for (size_t i = 0; i < password.length() && !(hasupper && haslower); i++)
        {
            if (islower(password[i]))
            {
                haslower = true;
            }
            else if (isupper(password[i]))
            {
                hasupper = true;
            }
        }
    }
};

class symbol_password_validator final : public password_validator_decorator
{
public:
    explicit symbol_password_validator(std::unique_ptr<password_validator> validator) : password_validator_decorator(std::move(validator)) {}

    virtual bool validate(std::string_view password) override
    {
        if (!password_validator_decorator::validate(password))
        {
            return false;
        }

        return password.find_first_of("!@#$%^&*(){}[]?<>") != std::string::npos;
    }
};

int main()
{
    auto validator1 = std::make_unique<digit_password_validator>(std::make_unique<length_validator>(8));

    assert(validator1->validate("abc123!@#"));
    assert(!validator1->validate("abcde!@#"));

    auto validator2 = std::make_unique<symbol_password_validator>(std::make_unique<case_password_validator>(std::make_unique<digit_password_validator>(std::make_unique<length_validator>(8))));

    assert(validator2->validate("Abc123!@#"));
    assert(!validator2->validate("Abc1234567"));

    return 0;
}

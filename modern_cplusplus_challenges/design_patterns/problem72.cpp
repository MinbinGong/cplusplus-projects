#include <numeric>

struct discount_type
{
    virtual double discount_percent(double const price, double const quantity) const noexcept = 0;
    virtual ~discount_type() {}
};

struct fixed_discount final : public discount_type
{
    explicit fixed_discount(double const discount) noexcept
        : discount(discount) {}
    virtual double discount_percent(double const, double const) const noexcept
    {
        return discount;
    }

private:
    double discount;
};

struct volume_discount final : public discount_type
{
    explicit volume_discount(double const quantity, double const discount) noexcept
        : discount(discount), min_quantity(quantity) {}

    virtual double discount_percent(double const, double const quantity) const noexcept
    {
        return quantity >= min_quantity ? discount : 0;
    }

private:
    double discount;
    double min_quantity;
};

struct price_discount : public discount_type
{
    explicit price_discount(double const price, double const discount) noexcept
        : discount(discount), min_total_price(price) {}

    virtual double discount_percent(double const price, double const quantity) const noexcept
    {
        return price * quantity >= min_total_price ? discount : 0;
    }

private:
    double discount;
    double min_total_price;
};

struct amount_discount : public discount_type
{
    explicit amount_discount(double const price, double const discount) noexcept
        : discount(discount), min_total_price(price) {}
    virtual double discount_percent(double const price, double const) const noexcept
    {
        return price >= min_total_price ? discount : 0;
    }

private:
    double discount;
    double min_total_price;
};

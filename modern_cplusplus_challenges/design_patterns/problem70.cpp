#include <algorithm>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>

class role {
 public:
  virtual double approval_limit() const noexcept = 0;
  virtual ~role() {}
};

class employee_role : public role {
 public:
  virtual double approval_limit() const noexcept override { return 1000; }
};

class team_manager_role : public role {
 public:
  virtual double approval_limit() const noexcept override { return 10000; }
};

class department_manager_role : public role {
 public:
  virtual double approval_limit() const noexcept override { return 100000; }
};

class president_role : public role {
 public:
  virtual double approval_limit() const noexcept override { return std::numeric_limits<double>::max(); }
};

struct expense {
  double amount;
  std::string description;

  expense(double const amount, std::string_view desc) : amount(amount), description(desc) {}
};

class employee {
 public:
  explicit employee(std::string_view name, std::unique_ptr<role> ownrole) : name(name), own_role(std::move(ownrole)) {}

  void set_direct_manager(std::shared_ptr<employee> manager) { direct_manager = manager; }

  void approve(expense const &e) {
    if (e.amount <= own_role->approval_limit()) {
      std::cout << name << " approved expense '" << e.description << "', cost=" << e.amount << std::endl;
    } else if (direct_manager != nullptr) {
      direct_manager->approve(e);
    }
  }

 private:
  std::string name;
  std::unique_ptr<role> own_role;
  std::shared_ptr<employee> direct_manager;
};

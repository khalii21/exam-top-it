#include <iostream>

struct ITrait
{
  virtual void  operator()(int a) = 0;
  virtual int operator()() = 0;
  virtual ~ITrait() = default;
};

struct Size : ITrait
{
  Size()
  {
    k_ = 0;
  }
  void operator()(int a) override
  {
    k_++;
  }
  int operator()() override
  {
    return k_;
  }
  private:
    int k_;
};

struct SumPositive : ITrait
{
  SumPositive()
 {
    k_ = 0;
  }
  void operator()(int a) override
  {
    if (a > 0)
    {
      k_ += a;
    }
  }
  int operator()() override
  {
    return k_;
  }
  private:
    int k_;
};

struct SumNegative : ITrait
{
  SumNegative()
  {
    k_ = 0;
  }
  void operator()(int a) override
  {
    if (a < 0)
    {
      k_ += a;
    }
  }
  int operator()() override
  {
    return k_;
  }
  private:
    int k_;
};

int main()
{
  int a = 0;
  Size size;
  SumPositive sump;
  SumNegative sumn;
  while (std::cin >> a)
  {
    size(a);
    sump(a);
    sumn(a);
  }
  std::cout << "SIZE = " << size() << "\n";
  std::cout << "SUMP = " << sump() << "\n";
  std::cout << "SUMN = " << sumn() << "\n";
}

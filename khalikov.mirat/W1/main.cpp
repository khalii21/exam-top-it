#include <iostream>

struct ITrait
{
  virtual void  operator()(int a) = 0;
  virtual size_t operator()() = 0;
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
  size_t operator()() override
  {
    return k_;
  }
  private:
    size_t k_;
};

int main()
{
  int a = 0;
  Size size;
  while (std::cin >> a)
  {
    size(a);
  }
  std::cout << "SIZE = " << size() << "\n";
}

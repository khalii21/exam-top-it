#include <iostream>

struct ITrait
{
  virtual void  operator()(int a) = 0;
  virtual size_t operator()() = 0;
  virtual ~ITrait() = default;
};

struct Size : ITrait
{
  private:
    size_t k_;
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
};

int main()
{

}

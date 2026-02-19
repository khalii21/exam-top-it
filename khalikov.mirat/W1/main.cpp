#include <iostream>
#include <cstring>

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
  void operator()(int) override
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

struct Seq
{
  Seq()
  {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 1;
  }

  ~Seq()
  {
    delete[] data_;
  }

  Seq(const Seq & other)
  {
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new int[capacity_];
    for (size_t i = 0; i < size_; i++)
    {
      data_[i] = other.data_[i];
    }
  }

  Seq& operator=(const Seq& other)
  {
    if (this != &other)
    {
      delete[] data_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      data_ = new int[capacity_];
      for (size_t i = 0; i < size_; i++)
      {
        data_[i] = other.data_[i];
      }
    }
    return *this;
  }

  void EnterSeq (int a)
  {
    if (size_ >= capacity_)
    {
      size_t new_capacity = capacity_ * 2;
      Resize(new_capacity);
    }
    data_[size_++] = a;
  }

  private:
    void Resize(size_t newc)
    {
      int * new_data = new int[newc];
      for (size_t i = 0; i < size_; i++)
      {
        new_data[i] = data_[i];
      }
      delete[] data_;
      data_ = new_data;
      capacity_ = newc;
    }
    int * data_;
    size_t size_;
    size_t capacity_;
};

struct Storage
{
  Storage()
  {
    data_ = nullptr;
    size_ = 0;
    capacity_ = 1;
  }

  ~Storage()
  {
    delete[] data_;
  }

  void AddSeq(const Seq& seq)
  {
    if (size_ >= capacity_)
    {
      size_t new_capacity = capacity_ * 2;
      Resize(new_capacity);
    }
    data_[size_++] = seq;
  }

private:
  Seq * data_;
  size_t size_;
  size_t capacity_;
  void Resize(size_t newc)
  {
    Seq * new_data = new Seq[newc];
    for (size_t i = 0; i < size_; i++)
    {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = newc;
  }
};

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    return 4;
  }

  ITrait * traits = nullptr;
  if (std::strcmp(argv[1], "Size") == 0)
  {
    traits = new Size;
  }
  else if (std::strcmp(argv[1], "SumPositive") == 0)
  {
    traits = new SumPositive;
  }
  else if (std::strcmp(argv[1], "SumNegative") == 0)
  {
    traits = new SumNegative;
  }
  else
  {
    std::cout << "<NOT SUPPORT>" << "\n";
    return 5;
  }
  size_t a = 0;
  try
  {
    Storage stge;
    while (std::cin >> a)
    {
      Seq sequence;
      for (size_t i = 0; i < a; i++)
      {
        int val;
        if (!(std::cin >> val))
        {
          return 7;
        }
        sequence.EnterSeq(val);
        (*traits)(val);
      }
      stge.AddSeq(sequence);
    }
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Bad_alloc" << "\n";
    delete traits;
    return 1;
  }
  if ((std::cin.fail()) || (!(std::cin.eof())))
  {
    std::cerr << "Bad input\n";
    delete traits;
    return 2;
  }
  std::cout << (*traits)() << "\n";
  delete traits;
}

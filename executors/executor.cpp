
#include "executor.h"
#include "series.h"
#include <iostream>
#include <thread>

namespace execution{

template<class E, class F>
void execute(E&& e, F&& f)
{
    e.execute(f);
}

} // execution

struct single_thread_executor
{
  template<class F>
  void execute(F&& f) const noexcept 
  {
      std::jthread j((F&&)f);
      j.detach();
  }
};

struct series_printer{
    series_printer(int initial, unsigned int n)
        : _s{initial,n} {}

    void operator()(){
        std::cout << _s() << ","; 
    };

    series _s;
};




int main()
{

//    execution::executor auto foo = [&s](){

    for (unsigned int i = 1; i < 100; ++i) {
            execution::execute(single_thread_executor{}, series_printer{1,i});
    }

    std::cout << '\n';

    return 0;
}


//
//  prorityq.cpp
//  CF.STL_Containers_Priority_queue
//
//  Created by Alan Sampson on 4/17/21.
//
//  MARK: - Reference.
//  @see: https://en.cppreference.com/w/cpp/container/priority_queue
//
#include <iostream>
#include <iomanip>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <compare>
#include <memory>
#include <type_traits>
#include <queue>
#include <array>
#include <map>
#include <vector>
#include <stdexcept>
#include <cassert>
#include <cstddef>

using namespace std::literals::string_literals;
using namespace std::literals::string_view_literals;

//  MARK: - Definitions

//  MARK: - Local Constants.
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  MARK: namespace konst
namespace konst {

auto delimiter(char const dc = '-', size_t sl = 80) -> std::string const {
  auto const dlm = std::string(sl, dc);
  return dlm;
}

static
auto const dlm = delimiter();

static
auto const dot = delimiter('.');

} /* namespace konst */

#if (__cplusplus > 201707L)
#endif  /* (__cplusplus > 201707L) */

//  MARK: - Function Prototype.
auto C_priority_queue(int argc, char const * argv[]) -> decltype(argc);
auto C_priority_queue_deduction_guides(int argc, char const * argv[]) -> decltype(argc);

//  MARK: - Implementation.
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: main()
 */
int main(int argc, const char * argv[]) {
  std::cout << "CF.STL_Containers_Priority_queue\n"sv;
  std::cout << "C++ Version: "s << __cplusplus << std::endl;

  std::cout << '\n' << konst::dlm << std::endl;
  C_priority_queue(argc, argv);
  std::cout << '\n' << konst::dlm << std::endl;
  C_priority_queue_deduction_guides(argc, argv);

  return 0;
}

//  MARK: - C_priority_queue
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  ================================================================================
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: C_priority_queue()
 */
auto C_priority_queue(int argc, char const * argv[]) -> decltype(argc) {
  std::cout << "In "s << __func__ << std::endl;


  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::priority_queue"s << '\n';
  {
    auto print_queue = [](auto pque) { // NB: pass by value so the print uses a copy
      while(!pque.empty()) {
        std::cout << pque.top() << ' ';
        pque.pop();
      }
      std::cout << '\n';
    };

    std::priority_queue<int> q1;

    auto const data = { 1, 8, 5, 6, 3, 4, 0, 9, 7, 2, };

#define FUN_WITH_FOR_EACH_
#if defined(FUN_WITH_FOR_EACH_)
    std::for_each(std::cbegin(data), std::cend(data), [&q1](auto nr) {
      q1.push(nr);
    });
#else
    for (int nr : data) {
      que.push(nr);
    }
#endif  /* defined(FUN_WITH_FOR_EACH_) */

    print_queue(q1);

    std::priority_queue<int, std::vector<int>, std::greater<int>>
      q2(data.begin(), data.end());

    print_queue(q2);

    // Using lambda to compare elements.
    auto cmp = [](int left, int right) {
      return (left ^ 1) < (right ^ 1);
    };
    std::priority_queue<int, std::vector<int>, decltype(cmp)>
      q3(cmp);

#if defined(FUN_WITH_FOR_EACH_)
    std::for_each(std::cbegin(data), std::cend(data), [&q3](auto nr) {
      q3.push(nr);
    });
#else
    for (int nr : data) {
      q3.push(nr);
    }
#endif  /* defined(FUN_WITH_FOR_EACH_) */

    print_queue(q3);

    std::cout << '\n';
  }

  /// Member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::priority_queue - constructor"s << '\n';
  {
    {
      std::priority_queue<int> c1;
      c1.push(5);
      std::cout << c1.size() << '\n';

      std::priority_queue<int> c2(c1);
      std::cout << c2.size() << '\n';

      std::vector<int> vec = { 3, 1, 4, 1, 5, };
      std::priority_queue<int> c3(std::less<int>(), vec);
      std::cout << c3.size() << '\n';
    }

    std::cout << '\n';
  }

  /// Example With Custom Comparator
  {
    using my_pair_t = std::pair<size_t, bool>;

    using my_container_t = std::vector<my_pair_t>;

    auto my_comp = [](my_pair_t const & e1, my_pair_t const & e2) {
      return e1.first > e2.first;
    };

    std::priority_queue<my_pair_t, my_container_t, decltype(my_comp)> queue(my_comp);
    queue.push(std::make_pair(5, true));
    queue.push(std::make_pair(3, false));
    queue.push(std::make_pair(7, true));
    std::cout << std::boolalpha;
    while (!queue.empty()) {
      auto const & my_pr = queue.top();
      std::cout << my_pr.first << ' ' << my_pr.second << '\n';
      queue.pop();
    }
    std::cout << std::noboolalpha;

    std::cout << '\n';
  }

  /// Capasity
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::priority_queue - empty"s << '\n';
  {
    std::priority_queue<int> container;

    std::cout << "Initially, container.empty(): "sv
              << container.empty() << '\n';

    container.push(42);
    std::cout << "After adding elements, container.empty(): "sv
              << container.empty() << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::priority_queue - size"s << '\n';
  {
    std::priority_queue<int> container1;

    std::cout << "Initially, container.size(): "sv
              << container1.size() << '\n';

    for (int i_ = 0; i_ < 7; ++i_) {
      container1.push(i_);
    }

    std::cout << "After adding elements, container.size(): "sv
              << container1.size() << '\n';

    auto v1 = std::vector { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, };
    std::priority_queue container2 { v1.begin(), v1.end() };
    std::cout << "Initially, container.size(): "sv
              << container2.size() << '\n';

    std::cout << '\n';
  }

  /// Modifiers
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::priority_queue - push, emplace, pop"s << '\n';
  {
    std::priority_queue<std::string> container1;
    auto s1 = "zero"s;
    auto s2 = "zorro"s;
    auto s3 = "xyzzy"s;

    container1.push("here"s);
    container1.push("is"s);
    container1.push("the"s);
    container1.push("news"s);
    container1.emplace(std::move(s1));
    container1.emplace(std::move(s3));
    container1.emplace(std::move(s2));

    while (!container1.empty()) {
      auto topper = container1.top();
      container1.pop();
      std::cout << topper << ' ';
    }
    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::priority_queue - swap"s << '\n';
  {
    auto print_queue = [](auto pque) { // NB: pass by value so the print uses a copy
      while(!pque.empty()) {
        std::cout << pque.top() << ' ';
        pque.pop();
      }
      std::cout << '\n';
    };

    auto v1 = std::vector { '4', '3', '2', '1', '0', };
    auto v2 = std::vector {
      '9', '8', '7', '6', '5', '4', '3', '2', '1', '0', 'A', 'B', 'C', 'D', 'E', 'F',
    };
    std::priority_queue container1 { v1.cbegin(), v1.cend() };
    std::priority_queue container2 { v2.cbegin(), v2.cend() };

    print_queue(container1);
    print_queue(container2);

    container1.swap(container2);

    print_queue(container1);
    print_queue(container2);

    std::cout << '\n';
  }

  /// Non-member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::priority_queue - std::swap(std::priority_queue)"s << '\n';
  {
    auto print_queue = [](auto pque) { // NB: pass by value so the print uses a copy
      while(!pque.empty()) {
        std::cout << pque.top() << ' ';
        pque.pop();
      }
      std::cout << '\n';
    };

    std::priority_queue<std::string_view> alice;
    std::priority_queue<std::string_view> bob;

    auto print = [&print_queue](auto const & title, auto const & cont) {
      std::cout << title << " size="sv << cont.size();
      std::cout << " top="sv << cont.top() << ": "sv;

      print_queue(cont);
    };

    auto dat1 = std::vector { "xyzzy"sv };
    auto dat2 = std::vector { "plugh"sv, "plover"sv };
#if defined(FUN_WITH_FOR_EACH_)
    auto fill = [](auto ctnr, auto & que) {
      std::for_each(ctnr.cbegin(), ctnr.cend(), [&que](auto nr) {
        que.push(nr);
      });
      std::cout << que.size() << '\n';
    };

    fill(dat1, alice);
    fill(dat2, bob);
#else
    for (auto ix : dat1) {
      alice.push(ix);
    }
    for (auto ix : dat2) {
      bob.push(ix);
    }
#endif  /* defined(FUN_WITH_FOR_EACH_) */

    // Print state before swap
    print("alice:"sv, alice);
    print("bob  :"sv, bob);

    std::cout << "-- SWAP\n"sv;
    std::swap(alice, bob);

    // Print state after swap
    print("alice:"sv, alice);
    print("bob  :"sv, bob);

    std::cout << '\n';
  }

  std::cout << std::endl; //  make sure cout is flushed.

  return 0;
}

//  MARK: - C_priority_queue_deduction_guides
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  ================================================================================
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: C_priority_queue_deduction_guides()
 */
auto C_priority_queue_deduction_guides(int argc, char const * argv[]) -> decltype(argc) {
  std::cout << "In "s << __func__ << std::endl;

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::priority_queue = deduction guides"s << '\n';
  {
    auto prtq = [](auto pque) {
      while(!pque.empty()) {
        std::cout << pque.top() << ' ';
        pque.pop();
      }
      std::cout << '\n';
    };

    std::vector<int> v1 = { 1, 2, 3, 4, };

    // deduces std::priority_queue<int, std::vector<int>, std::greater<int>>
    std::priority_queue pq1 { std::greater<int> {}, v1 };

    // deduces std::priority_queue<int>
    std::priority_queue pq2 { v1.begin(), v1.end() };

    prtq(pq1);
    std::cout << '\n';

    prtq(pq2);
    std::cout << '\n';

    std::cout << '\n';
  }

  std::cout << std::endl; //  make sure cout is flushed.

  return 0;
}

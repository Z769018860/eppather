
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <type_traits>



#include <cstdint>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

template <class Head, class... Tail>
struct TupleReader {
  static std::tuple<Head, Tail...> read(std::istream& in) {
    Head value;
    in >> value;
    auto head = std::make_tuple(value);
    auto tail = TupleReader<Tail...>::read(in);
    return std::tuple_cat(head, tail);
  }
};

template <class Head>
struct TupleReader<Head> {
  static std::tuple<Head> read(std::istream& in) {
    Head value;
    in >> value;
    return std::make_tuple(value);
  }
};

template <class K, class V>
std::istream& operator >>(std::istream& stream, std::pair<K, V>& pair) {
  return stream >> pair.first >> pair.second;
}

template <class... Ts>
std::istream& operator >>(std::istream& stream, std::tuple<Ts...>& tuple) {
  tuple = TupleReader<Ts...>::read(stream);
  return stream;
}

class InputReader {
 public:
  explicit InputReader(std::istream& stream) : stream(stream) {
    stream.tie(nullptr);
  }

  

  template <class T>
  T next() {
    T value;
    stream >> value;
    return value;
  }

  char next_char() {
    return stream.get();
  }

  int next_int() {
    return next<int>();
  }

  std::int64_t next_long() {
    return next<std::int64_t>();
  }

  float next_float() {
    return next<float>();
  }

  double next_double() {
    return next<double>();
  }

  std::string next_string() {
    return next<std::string>();
  }

  std::string next_line() {
    std::string result;
    std::getline(stream, result);
    return result;
  }

  template <class K, class V>
  std::pair<K, V> next_pair() {
    std::pair<K, V> result;
    stream >> result.first >> result.second;
    return result;
  }

  template <class... Ts>
  std::tuple<Ts...> next_tuple() {
    return TupleReader<Ts...>::read(stream);
  }

  template <class T>
  std::vector<T> next_array(std::size_t size) {
    std::vector<T> result(size);
    for (std::size_t i = 0; i < size; i++) {
      stream >> result[i];
    }
    return result;
  }

  std::vector<int> next_int_array(std::size_t size) {
    return next_array<int>(size);
  }

  std::vector<std::int64_t> next_long_array(std::size_t size) {
    return next_array<std::int64_t>(size);
  }

  std::vector<float> next_float_array(std::size_t size) {
    return next_array<float>(size);
  }

  std::vector<double> next_double_array(std::size_t size) {
    return next_array<double>(size);
  }

  std::vector<char> next_char_array(std::size_t size) {
    std::vector<char> result(size);
    char characters[16];
    for (std::size_t i = 0; i < size; i++) {
      stream >> characters;
      result[i] = characters[0];
    }
    return result;
  }

  template <class Char>
  std::vector<std::basic_string<Char>> next_string_array(std::size_t size) {
    return next_array<std::basic_string<Char>>(size);
  }

  template <class... Ts>
  std::vector<std::tuple<Ts...>> next_tuple_array(std::size_t size) {
    std::vector<std::tuple<Ts...>> result(size);
    for (std::size_t i = 0; i < size; i++) {
      result[i] = TupleReader<Ts...>::read(stream);
    }
    return result;
  }

  template <class T>
  std::vector<std::vector<T>> next_table(std::size_t rows, std::size_t cols) {
    std::vector<std::vector<T>> result(rows, std::vector<T>(cols));
    for (std::size_t i = 0; i < rows; i++) {
      for (std::size_t j = 0; j < cols; j++) {
        stream >> result[i][j];
      }
    }
    return result;
  }

  std::vector<std::vector<int>> next_int_table(
      std::size_t rows, std::size_t cols) {
    return next_table<int>(rows, cols);
  }

  std::vector<std::vector<std::int64_t>> next_long_table(
      std::size_t rows, std::size_t cols) {
    return next_table<std::int64_t>(rows, cols);
  }

  std::vector<std::vector<float>> next_float_table(
      std::size_t rows, std::size_t cols) {
    return next_table<float>(rows, cols);
  }

  std::vector<std::vector<double>> next_double_table(
      std::size_t rows, std::size_t cols) {
    return next_table<double>(rows, cols);
  }

  

  template <class T>
  std::istream& next(T& value) {
    return stream >> value;
  }

  template <class T, class... Args>
  std::istream& next(T& value, Args& ... args) {
    stream >> value;
    return next<Args...>(args...);
  }

  std::istream& next_char(char& value) {
    value = stream.get();
    return stream;
  }

  std::istream& next_int(int& value) {
    return stream >> value;
  }

  std::istream& next_long(std::int64_t& value) {
    return stream >> value;
  }

  std::istream& next_float(float& value) {
    return stream >> value;
  }

  std::istream& next_double(double& value) {
    return stream >> value;
  }

  std::istream& next_string(std::string& value) {
    return stream >> value;
  }

  std::istream& next_line(std::string& value) {
    std::getline(stream, value);
    return stream;
  }

  template <class K, class V>
  std::istream& next_pair(std::pair<K, V>& pair) {
    return stream >> pair.first >> pair.second;
  }

  template <class... Ts>
  std::istream& next_tuple(std::tuple<Ts...>& tuple) {
    tuple = TupleReader<Ts...>::read(stream);
    return stream;
  }

  template <class T>
  std::istream& next_array(std::vector<T>& array) {
    for (std::size_t i = 0; i < array.size(); i++) {
      stream >> array[i];
    }
    return stream;
  }

  std::istream& next_int_array(std::vector<int>& array) {
    return next_array<int>(array);
  }

  std::istream& next_long_array(std::vector<std::int64_t>& array) {
    return next_array<std::int64_t>(array);
  }

  std::istream& next_float_array(std::vector<float>& array) {
    return next_array<float>(array);
  }

  std::istream& next_double_array(std::vector<double>& array) {
    return next_array<double>(array);
  }

  std::istream& next_char_array(std::vector<char>& array) {
    char characters[16];
    for (std::size_t i = 0; i < array.size(); i++) {
      stream >> characters;
      array[i] = characters[0];
    }
    return stream;
  }

  template <class Char>
  std::istream& next_string_array(std::vector<std::basic_string<Char>>& array) {
    return next_array<std::basic_string<Char>>(array);
  }

  template <class... Ts>
  std::istream& next_tuple_array(std::vector<std::tuple<Ts...>>& tuples) {
    for (std::size_t i = 0; i < tuples.size(); i++) {
      tuples[i] = TupleReader<Ts...>::read(stream);
    }
    return stream;
  }

  template <class T>
  std::istream& next_table(std::vector<std::vector<T>>& array) {
    for (std::size_t i = 0; i < array.size(); i++) {
      for (std::size_t j = 0; j < array[i].size(); j++) {
        stream >> array[i][j];
      }
    }
    return stream;
  }

  std::istream& next_int_table(std::vector<std::vector<int>>& array) {
    return next_table<int>(array);
  }

  std::istream& next_long_table(std::vector<std::vector<std::int64_t>>& array) {
    return next_table<std::int64_t>(array);
  }

  std::istream& next_float_table(std::vector<std::vector<float>>& array) {
    return next_table<float>(array);
  }

  std::istream& next_double_table(std::vector<std::vector<double>>& array) {
    return next_table<double>(array);
  }

  

  template <class T>
  friend InputReader& operator >>(InputReader& in, T& value) {
    value = in.next<T>();
    return in;
  }

 private:
  std::istream& stream;
};



#include <cstdarg>
#include <cstdio>
#include <iomanip>

#include <type_traits>





#include <iterator>


template <class T>
struct is_iterator {
  static char test(...);

  template <
      class U,
      class = typename std::iterator_traits<U>::difference_type,
      class = typename std::iterator_traits<U>::pointer,
      class = typename std::iterator_traits<U>::reference,
      class = typename std::iterator_traits<U>::value_type,
      class = typename std::iterator_traits<U>::iterator_category
  >
  static long test(U&&);

  constexpr static bool value = std::is_same<
      decltype(test(std::declval<T>())), long
  >::value;
};


class OutputWriter {
 public:
  explicit OutputWriter(std::ostream& stream) : stream(stream) {
    separator = ' ';
    output_width = -1;
    fill_char = '\0';
  }

  void set_separator(char s) {
    separator = s;
  }

  void set_width(int width, char fill = ' ') {
    output_width = width;
    fill_char = fill;
  }

  void set_precision(int n) {
    stream << std::fixed << std::setprecision(n);
  }

  template <
      class Iterator,
      class = typename std::enable_if<is_iterator<Iterator>::value>::type
  >
  void print(Iterator begin, Iterator end) {
    auto iterator = begin;
    print_single(*iterator++);
    while (iterator != end) {
      print_separator();
      print_single(*iterator++);
    }
  }

  template <
      class Iterator,
      class = typename std::enable_if<is_iterator<Iterator>::value>::type
  >
  void print_line(Iterator begin, Iterator end) {
    print(begin, end);
    stream << '\n';
  }

  template <class T, class... Args>
  void print(const T& first, const Args... args) {
    print_single(first);
    if (sizeof...(args) != 0) {
      print_separator();
      print(args...);
    }
  }

  template <class... Args>
  void print_line(const Args... args) {
    print(args...);
    stream << '\n';
  }

  void print_format(const char* format, ...) {
    static char buffer[4096];
    va_list vars;
    va_start(vars, format);
    vsprintf(buffer, format, vars);
    va_end(vars);
    stream << buffer;
  }

 private:
  std::ostream& stream;
  char separator;
  int output_width;
  char fill_char;

  void print_separator() {
    if (separator != '\0') {
      stream << separator;
    }
  }

  void print() {
  }

  template <class T>
  void print_single(const T& value) {
    if (output_width > 0) {
      stream << std::setw(output_width) << std::setfill(fill_char) << value;
    } else {
      stream << value;
    }
  }

  template <class K, class V>
  void print_single(const std::pair<K, V>& pair) {
    print_single(pair.first);
    print_separator();
    print_single(pair.second);
  }

  template <class T>
  void print_single(const std::vector<T>& array) {
    std::size_t n = array.size();
    for (std::size_t i = 0; i < n; i++) {
      print_single(array[i]);
      if (i + 1 != n) {
        print_separator();
      }
    }
  }
};

template <class T>
OutputWriter& operator <<(OutputWriter& out, const T& value) {
  out.print(value);
  return out;
}




#include <algorithm>
#include <cmath>
#include <functional>
#include <stdexcept>





#include <unordered_map>




#include <cstdlib>

#include <optional>
#include <ostream>





#define MOD7 1000000007
#define MOD9 1000000009
#define MODF 998244353

#define PI std::acos(-1.0)





template <class T>
T gcd(T a, T b) {
  while (b != T()) {
    T temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}

template <class T>
T extended_gcd(T a, T b, T& x, T& y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  T d = extended_gcd(b % a, a, y, x);
  x -= (b / a) * y;
  return d;
}







template <class T, class = std::true_type>
struct IdentityHelper;

template <class T>
struct IdentityHelper<T, typename std::is_arithmetic<T>::type> {
  static T identity() {
    return 1;
  }
};

template <class T>
T identity() {
  return IdentityHelper<T>::identity();
}





#if __cplusplus < 201400
namespace std {

template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;

} 
#endif


template <
    class T, class U = T, class = std::enable_if_t<std::is_integral<U>::value>
>
T power(T base, U n) {
  T result = identity<T>();
  while (n > U()) {
    if (n & 1) {
      result = result * base;
    }
    n >>= 1;
    base = base * base;
  }
  return result;
}

template <
    class T, class U = T,
    class = std::enable_if_t<std::is_integral<T>::value>,
    class = std::enable_if_t<std::is_integral<U>::value>
>
T power(T base, U n, T mod) {
  T result = identity<T>();
  while (n > U()) {
    if (n & 1) {
      result = static_cast<std::int64_t>(result) * base % mod;
    }
    n >>= 1;
    base = static_cast<std::int64_t>(base) * base % mod;
  }
  return result % mod;
}




#include <numeric>



template <class T, class = std::enable_if_t<std::is_integral_v<T>>>
bool is_prime(T value) {
  if (value < 2) { return false; }
  for (T i = 2; static_cast<std::int64_t>(i) * i <= value; i++) {
    if (value % i == 0) { return false; }
  }
  return true;
}

template <class T, class = std::enable_if_t<std::is_integral_v<T>>>
T next_prime(T value) {
  if (value <= 2) { return 2; }
  value += 1 - (value & 1);
  while (!is_prime(value)) { value += 2; }
  return value;
}

template <class ForwardIterator>
void fill_primality(ForwardIterator first, ForwardIterator last) {
  using value_type = typename std::iterator_traits<ForwardIterator>::value_type;
  std::size_t upto = std::distance(first, last);
  std::fill(first, last, value_type(1));
  if (upto > 0) { *first = value_type(0); }
  if (upto > 1) { *(first + 1) = value_type(0); }
  for (std::size_t i = 2; i * i < upto; i++) {
    if (*(first + i) == value_type(1)) {
      for (std::size_t j = i * i; j < upto; j += i) {
        *(first + j) = value_type(0);
      }
    }
  }
}

template <class Container, class Size>
void generate_primes(Container& container, Size upto) {
  using value_type = typename Container::value_type;
  std::vector<int> primality(upto);
  fill_primality(primality.begin(), primality.end());
  for (Size i = 2; i < upto; i++) {
    if (primality[i] != 0) { container.push_back(static_cast<value_type>(i)); }
  }
}

template <class ForwardIterator>
void fill_divisor(ForwardIterator first, ForwardIterator last) {
  using value_type = typename std::iterator_traits<ForwardIterator>::value_type;
  std::size_t upto = std::distance(first, last);
  std::fill(first, last, value_type(0));
  if (upto > 1) { *(first + 1) = 1; }
  for (std::size_t i = 2; i < upto; i++) {
    if (*(first + i) != 0) { continue; }
    *(first + i) = value_type(i);
    for (std::size_t j = i * i; j < upto; j += i) {
      *(first + j) = value_type(i);
    }
  }
}

template <class Container, class T>
void generate_factors(Container& container, T n) {
  using value_type = typename Container::value_type;
  for (T i = 2; static_cast<std::int64_t>(i) * i <= n; i++) {
    if (n % i != 0) { continue; }
    container.push_back(static_cast<value_type>(i));
    while (n % i == 0) { n /= i; }
  }
  if (n > 1) { container.push_back(static_cast<value_type>(n)); }
}


template <class T>
T fermat_inverse(T value, T mod) { return power(value, mod - 2, mod); }

template <class T>
T euclidean_inverse(T value, T mod) {
  T x, y;
  T t = extended_gcd(value, mod, x, y);
  if (t != 1) { return T(-1); }
  return x;
}

template <class T>
T inverse(T value, T mod) {
  if (is_prime(mod)) { return fermat_inverse(value, mod); }
  return euclidean_inverse(value, mod);
}

template <class ForwardIterator, class T>
void fill_inverse(ForwardIterator first, ForwardIterator last, T mod) {
  using value_type = typename std::iterator_traits<ForwardIterator>::value_type;
  std::size_t upto = std::distance(first, last);
  if (upto > 0) { *first = 1; }
  if (upto > 1) { *(first + 1) = 1; }
  for (std::size_t i = 2; i < upto; i++) {
    *(first + i) = (value_type) *(first + mod % i) * (mod - mod / i) % mod;
  }
}




using std::enable_if_t;
using std::is_convertible_v;

template <class T>
class Modulus {
 public:
  using value_type = typename std::decay<decltype(T::value)>::type;
  static_assert(std::is_integral<value_type>::value, "Must be integral");

  constexpr Modulus() : value_(0) {}

  constexpr Modulus(const Modulus& other) : value_(other.value_) {}

  template <class U, class = enable_if_t<is_convertible_v<U, value_type>>>
  constexpr Modulus(const U& other) { value_ = normalize(other); }  

  const value_type& operator ()() const { return value_; }

  template <class U, class = enable_if_t<is_convertible_v<value_type, U>>>
  explicit operator U() const { return static_cast<U>(value_); }

  static constexpr value_type mod() { return T::value; }

  Modulus inverse() const { return Modulus(euclidean_inverse(value_, mod())); }

  std::optional<Modulus> sqrt() const {
    if (value_ < 2) { return *this; }
    if (power(*this, (mod() - 1) >> 1) != 1) { return std::nullopt; }
    Modulus b = 1;
    for (; power(b, (mod() - 1) >> 1) == 1; b += 1) {}
    value_type m = mod() - 1;
    int exponent = 0;
    for (; m % 2 == 0; m >>= 1, exponent++) {}
    Modulus x = power(*this, (m - 1) >> 1);
    Modulus y = *this * x * x;
    Modulus z = power(b, m);
    x *= value_;
    while (y != 1) {
      int new_exponent = 0;
      Modulus t = y;
      while (t != Modulus(1)) {
        ++new_exponent;
        t *= t;
      }
      z = power(z, 1 << (exponent - new_exponent - 1));
      x *= z;
      z *= z;
      y *= z;
      exponent = new_exponent;
    }
    return Modulus(x);
  }

  Modulus& operator =(const Modulus& other) {
    value_ = other.value_;
    return *this;
  }

  Modulus& operator +=(const Modulus& other) {
    value_ += other.value_;
    if (value_ >= mod()) { value_ -= mod(); }
    return *this;
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  Modulus& operator +=(const U& other) { return *this += Modulus(other); }

  Modulus& operator -=(const Modulus& other) {
    value_ -= other.value_;
    if (value_ < 0) { value_ += mod(); }
    return *this;
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  Modulus& operator -=(const U& other) { return *this -= Modulus(other); }

  Modulus& operator ++() { return *this += 1; }

  Modulus operator ++(int) {  
    Modulus result(*this);
    *this += 1;
    return result;
  }

  Modulus& operator --() { return *this -= 1; }

  Modulus operator --(int) {  
    Modulus result(*this);
    *this -= 1;
    return result;
  }

  Modulus operator -() const { return Modulus(-value_); }

  Modulus& operator *=(const Modulus& rhs) {
    value_ = normalize(static_cast<std::int64_t>(value_) * rhs.value_);
    return *this;
  }

  Modulus& operator /=(const Modulus& other) {
    return *this *= other.inverse();
  }

  Modulus operator +(const Modulus& rhs) const { return Modulus(*this) += rhs; }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend Modulus operator +(const Modulus& lhs, const U& rhs) {
    return Modulus(lhs) += Modulus(rhs);
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend Modulus operator +(const U& lhs, const Modulus& rhs) {
    return Modulus(lhs) += Modulus(rhs);
  }

  Modulus operator -(const Modulus& rhs) const { return Modulus(*this) -= rhs; }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend Modulus operator -(const Modulus& lhs, const U& rhs) {
    return Modulus(lhs) -= Modulus(rhs);
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend Modulus operator -(const U& lhs, const Modulus& rhs) {
    return Modulus(lhs) -= Modulus(rhs);
  }

  Modulus operator *(const Modulus& rhs) const { return Modulus(*this) *= rhs; }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend Modulus operator *(const Modulus& lhs, const U& rhs) {
    return Modulus(lhs) *= Modulus(rhs);
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend Modulus operator *(const U& lhs, const Modulus& rhs) {
    return Modulus(lhs) *= Modulus(rhs);
  }

  Modulus operator /(const Modulus& rhs) const { return Modulus(*this) /= rhs; }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend Modulus operator /(const Modulus& lhs, const U& rhs) {
    return Modulus(lhs) /= Modulus(rhs);
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend Modulus operator /(const U& lhs, const Modulus& rhs) {
    return Modulus(lhs) /= Modulus(rhs);
  }

  bool operator ==(const Modulus& rhs) const { return value_ == rhs.value_; }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend bool operator ==(const Modulus& lhs, const U& rhs) {
    return lhs == Modulus(rhs);
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend bool operator ==(const U& lhs, const Modulus& rhs) {
    return Modulus(lhs) == rhs;
  }

  bool operator !=(const Modulus& rhs) const {
    return !(rhs == *this);  
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend bool operator !=(const Modulus& lhs, const U& rhs) {
    return !(lhs == rhs);  
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend bool operator !=(const U& lhs, const Modulus& rhs) {
    return !(lhs == rhs);  
  }

  bool operator <(const Modulus& rhs) const { return value_ < rhs.value_; }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend bool operator <(const Modulus& lhs, const U& rhs) {
    return lhs < Modulus(rhs);
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend bool operator <(const U& lhs, const Modulus& rhs) {
    return Modulus(lhs) < rhs;
  }

  bool operator >(const Modulus& rhs) const { return rhs < *this; }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend bool operator >(const Modulus& lhs, const U& rhs) {
    return Modulus(rhs) < lhs;
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend bool operator >(const U& lhs, const Modulus& rhs) {
    return rhs < Modulus(lhs);
  }

  bool operator <=(const Modulus& rhs) const {
    return !(rhs < *this);  
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend bool operator <=(const Modulus& lhs, const U& rhs) {
    return !(Modulus(rhs) < lhs);  
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend bool operator <=(const U& lhs, const Modulus& rhs) {
    return !(rhs < Modulus(lhs));  
  }

  bool operator >=(const Modulus& rhs) const {
    return !(*this < rhs);  
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend bool operator >=(const Modulus& lhs, const U& rhs) {
    return !(lhs < Modulus(rhs));  
  }

  template <class U, class = enable_if_t<is_convertible_v<U, Modulus>>>
  friend bool operator >=(const U& lhs, const Modulus& rhs) {
    return !(Modulus(lhs) < rhs);  
  }

  friend std::ostream& operator <<(std::ostream& os, const Modulus& number) {
    return os << number.value_;
  }

  friend std::istream& operator >>(std::istream& is, Modulus& number) {
    is >> number.value_;
    number.value_ = normalize(number.value_);
    return is;
  }

 private:
  value_type value_;

  template <class U, class = enable_if_t<is_convertible_v<U, value_type>>>
  constexpr static value_type normalize(const U& x) {
    auto result = static_cast<value_type>(x % mod());
    if (result < 0) { result += mod(); }
    return result;
  }
};

template <class T>
struct IdentityHelper<Modulus<T>> {
  static Modulus<T> identity() {
    return Modulus<T>(1);
  }
};

template <int m>
using ModInt = Modulus<std::integral_constant<int, m>>;

using Mod7 = ModInt<MOD7>;
using Mod9 = ModInt<MOD9>;
using ModF = ModInt<MODF>;

namespace std {  

template <class T>
Modulus<T> abs(const Modulus<T>& value) { return value; }

template <class T>
struct hash<Modulus < T>> {
  size_t operator ()(const Modulus<T>& n) const { return (size_t) n; }
};

} 



template <class T>
typename Modulus<T>::value_type bsgs(
    const Modulus<T>& b, typename Modulus<T>::value_type n) {
  using value_t = typename Modulus<T>::value_type;
  if (n == 1) {
    return 0;
  }
  std::unordered_map<Modulus<T>, value_t> hash;
  auto m = static_cast<value_t>(std::sqrt(Modulus<T>::mod()));
  ModInt<Modulus<T>::mod()> x = 1;
  ModInt<Modulus<T>::mod()> y = 1;
  for (value_t i = 0; i < m; i++, y = y * b) {
    hash[y * n] = i;
  }
  for (value_t i = m; i <= Modulus<T>::mod(); i += m) {
    x = x * y;
    if (hash.find(x) != hash.end()) {
      return i - hash[x];
    }
  }
  return static_cast<value_t>(-1);
}






















template <class T, class = std::enable_if_t<std::is_integral_v<T>>>
bool has_primitive_root(T n) {
  if (n == 2 || n == 4) { return true; }
  if (n % 2 == 0) { n /= 2; }
  if (n % 2 == 0) { return false; }
  std::vector<std::int64_t> primes;
  generate_primes(primes, n);
  for (std::size_t i = 1; primes[i] * primes[i] <= n; i++) {
    if (n % primes[i] == 0) {
      while (n % primes[i] == 0) { n /= primes[i]; }
      return n == 1;
    }
  }
  return true;
}

template <class T, class = std::enable_if_t<std::is_integral_v<T>>>
T smallest_primitive_root(T n, T phi_n) {
  if (n == 2) { return 1; }
  std::vector<int> factors;
  generate_factors(factors, phi_n);
  auto test_root = [&](int g, int mod) -> bool {
    for (int factor : factors) {
      if (power(g, phi_n / factor, mod) == 1) { return false; }
    }
    return true;
  };
  for (T result = 2;; result++) {
    if (gcd(result, n) > 1) { continue; }
    if (test_root(result, n)) { return result; }
  }
}

template <class Container, class T>
void generate_primitive_root(Container& container, T n, T phi_n) {
  using value_type = typename Container::value_type;
  if (!has_primitive_root(n)) { return; }
  T smallest = smallest_primitive_root(n, phi_n);
  container.push_back(static_cast<value_type>(smallest));
  if (phi_n <= 2) { return; }
  container.push_back(static_cast<value_type>(power(smallest, phi_n - 1, n)));
  T m = phi_n / 2;
  for (T i = 2; i <= m; i++) {
    if (gcd(i, phi_n) != 1) { continue; }
    container.push_back(static_cast<value_type>(power(smallest, i, n)));
    container.push_back(static_cast<value_type>(power(smallest, phi_n - i, n)));
  }
  std::sort(container.begin(), container.end());
}


template <class T>
class DiscreteFourierTransform {
 public:
  using value_type = typename T::value_type;

  DiscreteFourierTransform() {
    primitive_root_ = smallest_primitive_root(mod(), mod() - 1);
    gn_.resize(64);
    for (std::size_t i = 0; i < 64; i++) {
      gn_[i] = power(primitive_root_, (mod() - 1) / (1LL << i));
    }
  }

  static constexpr value_type mod() { return T::mod(); }

  T root() const { return primitive_root_; }  

  template <class InputIterator>
  void transform(InputIterator first, InputIterator last, bool invert) const {
    std::size_t length = std::distance(first, last);
    std::size_t half_len = length >> 1;
    for (std::size_t i = 1, j = half_len; i + 1 < length; i++) {
      if (i < j) { std::swap(*(first + i), *(first + j)); }
      std::size_t k = half_len;
      while (j >= k) {
        j -= k;
        k >>= 1;
      }
      j += k;
    }
    for (std::size_t h = 2, id = 1; h <= length; h <<= 1, id++) {
      std::size_t half = h >> 1;
      for (std::size_t j = 0; j < length; j += h) {
        T g = 1;
        for (std::size_t k = j; k < j + half; k++) {
          T u = *(first + k);
          T t = g * *(first + k + half);
          *(first + k) = u + t;
          *(first + k + half) = u - t;
          g = g * gn_[id];
        }
      }
    }
    if (invert) {
      std::reverse(first + 1, last);
      auto inv = static_cast<T>(length).inverse();
      for (; first != last; ++first) { *first = *first * inv; }
    }
  }

 private:
  T primitive_root_;
  std::vector<T> gn_;
};

std::vector<int> multiply(const std::string& a, const std::string& b) {
  std::size_t first_len = a.size();
  std::size_t second_len = b.size();
  std::size_t length = 1;
  while (length < first_len + second_len) { length *= 2; }
  DiscreteFourierTransform<ModF> transformer;
  std::vector<ModF> x1(length, 0);
  std::vector<ModF> x2(length, 0);
  for (std::size_t i = 0; i < first_len; i++) {
    x1[i] = a[first_len - i - 1] - '0';
  }
  for (std::size_t i = 0; i < second_len; i++) {
    x2[i] = b[second_len - i - 1] - '0';
  }
  transformer.transform(x1.begin(), x1.end(), false);
  transformer.transform(x2.begin(), x2.end(), false);
  for (std::size_t i = 0; i < length; i++) { x1[i] = x1[i] * x2[i]; }
  transformer.transform(x1.begin(), x1.end(), true);
  std::vector<int> result;
  int digit = 0;
  for (std::size_t i = 0; i < length; i++, digit /= 10) {
    digit += (int) x1[i];
    result.push_back(digit % 10);
  }
  while (digit != 0) {
    result.push_back(digit % 10);
    digit /= 10;
  }
  while (result[length - 1] == 0 && length > 1) {
    result.pop_back();
    length--;
  }
  std::reverse(result.begin(), result.end());
  return result;
}






template <class T>
constexpr auto has_begin(int) -> decltype(std::begin(std::declval<T>()), true) {
  return true;
}

template <class T>
constexpr bool has_begin(...) {
  return false;
}

template <class T>
using IsContainer = std::integral_constant<bool, has_begin<T>(0)>;



template <class T>
class Polynomial {
 public:
  using container_type = std::vector<T>;
  using value_type = typename container_type::value_type;
  using reference = typename container_type::reference;
  using const_reference = typename container_type::const_reference;
  using size_type = typename container_type::size_type;

  using iterator = typename container_type::iterator;
  using const_iterator = typename container_type::const_iterator;
  using reverse_iterator = typename container_type::reverse_iterator;
  using const_reverse_iterator =
      typename container_type::const_reverse_iterator;

  explicit Polynomial(std::size_t size = 1)
      : coefficients_(size, value_type()) {}

  template <class U>
  Polynomial(std::initializer_list<U> list)
      : coefficients_(list.begin(), list.end()) {}

  template <class InputIterator>
  explicit Polynomial(InputIterator first, InputIterator last)
      : coefficients_(first, last) {}

  iterator begin() { return coefficients_.begin(); }
  const_iterator begin() const { return coefficients_.begin(); }
  iterator end() { return coefficients_.end(); }
  const_iterator end() const { return coefficients_.end(); }
  reverse_iterator rbegin() { return coefficients_.rbegin(); }
  const_reverse_iterator rbegin() const { return coefficients_.rbegin(); }
  reverse_iterator rend() { return coefficients_.rend(); }
  const_reverse_iterator rend() const { return coefficients_.rend(); }
  const_iterator cbegin() const { return begin(); }
  const_iterator cend() const { return end(); }
  const_reverse_iterator crbegin() const { return rbegin(); }
  const_reverse_iterator crend() const { return rend(); }
  reference front() { return coefficients_.front(); }
  const_reference front() const { return coefficients_.front(); }
  reference back() { return coefficients_.back(); }
  const_reference back() const { return coefficients_.back(); }

  size_type size() const { return coefficients_.size(); }

  bool empty() const { return coefficients_.empty(); }

  reference operator [](std::size_t index) { return coefficients_[index]; }

  const_reference operator [](std::size_t index) const {
    return coefficients_[index];
  }

  void pop_back() { coefficients_.pop_back(); }

  void resize(std::size_t n) { coefficients_.resize(n, value_type()); }

  template <class U>
  std::vector<value_type> operator ()(const std::vector<U>& x) const {
    std::vector<Polynomial> tree(x.size() * 4);
    std::function<void(int, int, int)> init_tree =
        [&](int root, int left, int right) {
          if (right <= left) {
            tree[root].resize(2);
            tree[root][0] = value_type::mod() - x[left];
            tree[root][1] = 1;
            return;
          }
          int middle = (left + right) / 2;
          init_tree(root * 2 + 1, left, middle);
          init_tree(root * 2 + 2, middle + 1, right);
          tree[root] = tree[root * 2 + 1] * tree[root * 2 + 2];
        };
    std::vector<value_type> result;
    std::function<void(int, int, int, const Polynomial&)> eval_tree =
        [&](int root, int left, int right, const Polynomial& remainder) {
          if (right - left <= 32) {
            for (int i = left; i <= right; i++) {
              value_type value = remainder[remainder.size() - 1];
              for (int j = remainder.size() - 1; j > 0; j--) {
                value = value * x[i] + remainder[j - 1];
              }
              result.push_back(value);
            }
            return;
          }
          int middle = (left + right) / 2;
          Polynomial l_rem = remainder % tree[root * 2 + 1];
          eval_tree(root * 2 + 1, left, middle, l_rem);
          Polynomial r_rem = remainder % tree[root * 2 + 2];
          eval_tree(root * 2 + 2, middle + 1, right, r_rem);
        };
    init_tree(0, 0, x.size() - 1);
    eval_tree(0, 0, x.size() - 1, *this % tree[0]);
    return result;
  }

  Polynomial reverse() const {
    Polynomial result = *this;
    std::reverse(result.begin(), result.end());
    return result;
  }

  Polynomial operator -() const {
    Polynomial result = *this;
    for (size_type i = 0; i < result.size(); i++) { result[i] = -result[i]; }
    return result;
  }

  Polynomial operator +(const Polynomial& rhs) const {
    Polynomial result(std::max(size(), rhs.size()));
    for (size_type i = 0; i < size(); i++) { result[i] = coefficients_[i]; }
    for (size_type i = 0; i < rhs.size(); i++) {
      result[i] = result[i] + rhs[i];
    }
    return result;
  }

  Polynomial operator -(const Polynomial& rhs) const { return *this + (-rhs); }

  Polynomial operator *(const Polynomial& rhs) const {
    Polynomial result(size() + rhs.size() > 1 ? size() + rhs.size() - 1 : 0);
    if (result.size() <= 32) {
      for (size_type i = 0; i < size(); i++) {
        if (coefficients_[i] == value_type()) { continue; }
        for (size_type j = 0; j < rhs.size(); j++) {
          value_type product = coefficients_[i] * rhs[j];
          result[i + j] = result[i + j] + product;
        }
      }
      return result;
    }
    size_type length = 1;
    while (length < size() + rhs.size()) { length *= 2; }
    std::vector<value_type> x1(length, value_type());
    std::vector<value_type> x2(length, value_type());
    for (size_type i = 0; i < size(); i++) { x1[i] = coefficients_[i]; }
    for (size_type i = 0; i < rhs.size(); i++) { x2[i] = rhs[i]; }
    transformer_.transform(x1.begin(), x1.end(), false);
    transformer_.transform(x2.begin(), x2.end(), false);
    for (size_type i = 0; i < length; i++) { x1[i] = x1[i] * x2[i]; }
    transformer_.transform(x1.begin(), x1.end(), true);
    for (size_type i = 0; i < result.size(); i++) { result[i] = x1[i]; }
    return result;
  }

  Polynomial operator /(const Polynomial& rhs) const {
    Polynomial u = reverse();
    Polynomial v = rhs.reverse();
    std::size_t length = size() > rhs.size() ? size() - rhs.size() + 1 : 1;
    u.resize(length);
    v.resize(length);
    Polynomial result = u * v.inverse();
    result.resize(length);
    return result.reverse();
  }

  Polynomial operator %(const Polynomial& rhs) const {
    Polynomial v = rhs * (*this / rhs);
    Polynomial result = *this;
    std::size_t length = std::max(size(), v.size());
    result.resize(length);
    v.resize(length);
    for (size_type i = 0; i < length; i++) { result[i] = result[i] - v[i]; }
    while (!result.empty() && result.back() == 0) { result.pop_back(); }
    return result;
  }

  Polynomial& operator +=(const Polynomial& rhs) { return *this = *this + rhs; }

  Polynomial& operator -=(const Polynomial& rhs) { return *this = *this - rhs; }

  Polynomial& operator *=(const Polynomial& rhs) { return *this = *this * rhs; }

  Polynomial& operator /=(const Polynomial& rhs) { return *this = *this / rhs; }

  Polynomial& operator %=(const Polynomial& rhs) { return *this = *this % rhs; }

  bool operator ==(const Polynomial& rhs) const {
    return coefficients_ == rhs.coefficients_;
  }

  bool operator !=(const Polynomial& rhs) const {
    return !(rhs == *this);  
  }

  template <class U>
  friend Polynomial operator +(const Polynomial& lhs, const U& rhs) {
    Polynomial result = lhs;
    result[0] = result[0] + rhs;
    return result;
  }

  template <class U>
  friend Polynomial operator +(const U& lhs, const Polynomial& rhs) {
    return rhs + lhs;
  }

  template <class U>
  friend Polynomial operator -(const Polynomial& lhs, const U& rhs) {
    Polynomial result = lhs;
    result[0] = result[0] - rhs;
    return result;
  }

  template <class U>
  friend Polynomial operator -(const U& lhs, const Polynomial& rhs) {
    return -rhs + lhs;
  }

  template <class U>
  friend Polynomial operator *(const Polynomial& lhs, const U& rhs) {
    Polynomial result = lhs;
    for (size_type i = 0; i < result.size(); i++) {
      result[i] = result[i] * rhs;
    }
    return result;
  }

  template <class U>
  friend Polynomial operator *(const U& lhs, const Polynomial& rhs) {
    return rhs * lhs;
  }

  template <class U>
  friend Polynomial operator /(const Polynomial& lhs, const U& rhs) {
    return lhs * value_type(rhs).inverse();
  }

  Polynomial derivate() const {
    Polynomial result(size() - 1);
    for (size_type i = 0; i < result.size(); i++) {
      result[i] = coefficients_[i + 1] * (i + 1);
    }
    return result;
  }

  Polynomial integrate() const {
    Polynomial result(size() + 1);
    for (size_type i = 1; i < result.size(); i++) {
      result[i] = coefficients_[i - 1] * value_type(i).inverse();
    }
    result[0] = value_type();
    return result;
  }

  Polynomial inverse() const {
    std::vector<std::vector<value_type>> f(2, std::vector<value_type>(1, 0));
    f[0][0] = value_type(coefficients_[0]).inverse();
    size_type depth = 1;
    for (size_type len = 1; len < size(); len *= 2, depth++) {
      size_type upto = len * 4;
      std::vector<value_type> temp(upto, 0);
      std::copy_n(coefficients_.begin(), std::min(upto, size()), temp.begin());
      std::fill(temp.begin() + len * 2, temp.end(), 0);
      size_type prev = (depth - 1) & 1u;
      size_type next = depth & 1u;
      f[prev].resize(upto, 0);
      f[next].resize(upto, 0);
      transformer_.transform(f[prev].begin(), f[prev].end(), false);
      transformer_.transform(temp.begin(), temp.end(), false);
      for (size_type i = 0; i < upto; i++) {
        f[next][i] = 2 * f[prev][i] - temp[i] * f[prev][i] * f[prev][i];
      }
      transformer_.transform(f[next].begin(), f[next].end(), true);
      std::fill(f[next].begin() + len * 2, f[next].end(), 0);
    }
    Polynomial result(size());
    std::copy_n(f[(depth - 1) & 1u].begin(), size(), result.begin());
    return result;
  }

  Polynomial log() const {
    if (coefficients_[0] != value_type(1)) {
      throw std::runtime_error("Unsupported operation exception");
    }
    Polynomial result = derivate() * inverse();
    result = result.integrate();
    result.resize(size());
    return result;
  }

  Polynomial exp() const {
    if (coefficients_[0] != value_type(0)) {
      throw std::runtime_error("Unsupported operation exception");
    }
    Polynomial result(2);
    result[0] = 1;
    for (size_type len = 2; len <= size() * 2; len *= 2) {
      Polynomial temp(len);
      std::copy_n(result.begin(), std::min(len, result.size()), temp.begin());
      temp = temp.log();
      temp[0] = coefficients_[0] + 1 - temp[0];
      for (size_type i = 1; i < len; i++) {
        temp[i] = coefficients_[i] - temp[i];
      }
      result = result * temp;
    }
    result.resize(size());
    return result;
  }

  value_type qnrt(value_type c, size_type n) const {
    int p = bsgs(transformer_.root(), (int) c);
    int a, b;
    int m = value_type::mod()- 1;
    int d = extended_gcd(static_cast<int>(n), m, a, b);
    m /= d;
    p /= d;
    int e = static_cast<int>(static_cast<std::int64_t>(p) * a % m + m) % m;
    value_type residual = power(transformer_.root(), e);
    if (n % 2 == 1) { return residual; }
    return std::min(residual, -residual);
  }

  Polynomial nth_root(size_type n) const {
    value_type inv_c = coefficients_[0].inverse();
    Polynomial result(coefficients_.begin(), coefficients_.end());
    result = result * inv_c;
    value_type c = qnrt(coefficients_[0], n);
    n = (int) value_type(n).inverse();
    return result.pow(n) * c;
  }

  Polynomial cbrt() const { return nth_root(3); }

  Polynomial sqrt() const { return nth_root(2); }

  
  template <class U>
  Polynomial pow(const U& k) const {
    return (log() * k).exp();
  }

  Polynomial sin() const {
    static ModF img = power(transformer_.root(), (ModF::mod() - 1) / 4);
    Polynomial result = (*this * img).exp();
    static ModF inv = (img * 2).inverse();
    return (result - result.inverse()) * inv;
  }

  Polynomial cos() const {
    static ModF img = power(transformer_.root(), (ModF::mod() - 1) / 4);
    Polynomial result = (*this * img).exp();
    static ModF inv = ModF(2).inverse();
    return (result + result.inverse()) * inv;
  }

  Polynomial asin() const {
    Polynomial x2 = -(*this * *this);
    x2.resize(size());
    x2[0] = x2[0] + 1;
    static ModF inv = ModF(2).inverse();
    x2 = x2.pow(inv);
    x2.resize(size());
    Polynomial result = derivate() * x2.inverse();
    result.resize(size() - 1);
    return result.integrate();
  }

  Polynomial atan() const {
    Polynomial x2 = *this * *this;
    x2.resize(size());
    x2[0] = x2[0] + 1;
    Polynomial result = derivate() * x2.inverse();
    result.resize(size() - 1);
    return result.integrate();
  }

  friend std::ostream& operator <<(std::ostream& os, const Polynomial& p) {
    if (p.size() == 1) { return os << p[0]; }
    for (std::size_t i = p.size() - 1; static_cast<int>(i) >= 0; i--) {
      if (p[i] == ModF()) { continue; }
      if (p[i] > 0) {
        if (i != p.size() - 1) { os << '+'; }
        if (p[i] > 1 || (p[i] == 1 && i == 0)) { os << p[i]; }
      } else {
        os << '-';
        if (p[i] < -1 || (p[i] == -1 && i == 0)) {
          os << -p[i];
        }
      }
      if (i > 1) { os << "x^" << i; }
      if (i == 1) { os << 'x'; }
    }
    return os;
  }

 private:
  container_type coefficients_;
  DiscreteFourierTransform<T> transformer_;
};

namespace std {  

template <class T>
Polynomial<T> log(const Polynomial<T>& poly) { return poly.log(); }

template <class T>
Polynomial<T> exp(const Polynomial<T>& poly) { return poly.exp(); }

template <class T>
Polynomial<T> sqrt(const Polynomial<T>& poly) { return poly.sqrt(); }

template <class T>
Polynomial<T> sin(const Polynomial<T>& poly) { return poly.sin(); }

template <class T>
Polynomial<T> cos(const Polynomial<T>& poly) { return poly.cos(); }

template <class T>
Polynomial<T> asin(const Polynomial<T>& poly) { return poly.asin(); }

template <class T>
Polynomial<T> atan(const Polynomial<T>& poly) { return poly.atan(); }

} 


class LibreOJ151 {
 public:
  void solve(InputReader& in, OutputWriter& out) {
    int n = in.next_int();
    Polynomial<ModF> a(n + 1);
    for (int i = 0; i < n + 1; i++) {
      a[i] = in.next_int();
    }
    Polynomial<ModF> answer = a.cbrt();
    out.print_line(answer.begin(), answer.end());
  }
};


int main() {
  std::ios::sync_with_stdio(false);
  LibreOJ151 solver;
  InputReader in(std::cin);
  OutputWriter out(std::cout);
  solver.solve(in, out);
  return 0;
}

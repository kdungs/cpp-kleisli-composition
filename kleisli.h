#ifndef KLEISLI_H
#define KLEISLI_H

#include <functional>
#include <experimental/optional>
#include <type_traits>

using std::experimental::optional;

// (>>=) :: m a -> (a -> m b) -> m b
// Bind     M<A>   FN........    M<B>
template <template <typename> class M, typename A, typename FN,
          typename B = typename std::result_of_t<FN(A)>::value_type>
auto Bind(M<A> a, const FN& f) {
  if (!a) {
    return M<B>{};
  }
  return f(*a);
}

// (>=>) :: (a -> m b) -> (b -> m c) -> a -> m c
// Kleisli  FN_LHS....    FN_RHS....    A    M<C>
template <typename FN_LHS, typename FN_RHS>
auto Kleisli(const FN_LHS& fl, const FN_RHS& fr) {
  return [&fl, &fr](const auto& a) { return Bind(fl(a), fr); };
}

#endif  // KLEISLI_H

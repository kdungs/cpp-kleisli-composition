#ifndef KLEISLI_H
#define KLEISLI_H

#include <functional>
#include <type_traits>

#include <experimental/optional>
using std::experimental::optional;

/** Implement monadic bind (>>=) for std::experimental::optional.
 * (>>=) :: m a -> (a -> m b) -> m b
 */
template <typename A, typename FN,
          typename B = typename std::result_of_t<FN(A)>::value_type,
          template <typename> class M = optional>
auto Bind(M<A> a, const FN& f) {
  if (!a) {
    return M<B>{};
  }
  return f(*a);
}

/** Implement Kleisli composition (>=>) independently of the monad in question.
 * (>=>) :: (a -> m b) -> (b -> m c) -> a -> m c
 */
template <typename FN_LHS, typename FN_RHS>
auto Kleisli(const FN_LHS& fl, const FN_RHS& fr) {
  return [&fl, &fr](const auto& a) { return Bind(fl(a), fr); };
}

#endif  // KLEISLI_H

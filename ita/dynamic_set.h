#ifndef _LAWRENCIUM_ITA_DYNAMICSET_H_
#define _LAWRENCIUM_ITA_DYNAMICSET_H_

#include <optional>

template <typename TKey, typename TValue> class DynamicSet {
  virtual std::optional<TValue &> Search(const TKey key) const = 0;

  virtual void Insert(TKey key, TValue &&value) = 0;

  virtual void Delete(TValue *value) = 0;

  virtual TValue &Minimum() const = 0;

  virtual TValue &Maximum() const = 0;

  virtual std::optional<TValue &> Successor(const TKey) const = 0;

  virtual std::optional<TValue &> Predecessor(const TKey) const = 0;
}

#endif
#include <gtest/gtest.h>
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/standard_ops.h"

using namespace tensorflow;

// Checks that tests can be run at all.
TEST(TensorflowPingTest, TensorflowPingTest) {
  Scope root = Scope::NewRootScope().WithDevice("/cpu:0");
  auto a = ops::Placeholder(root, DT_INT32);
  auto c = ops::Add(root, a, {41});
  ClientSession session(root);
}
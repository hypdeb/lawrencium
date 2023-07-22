#include <iostream>
#include "tensorflow/cc/framework/scope.h"
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/standard_ops.h"

using namespace std;
using namespace tensorflow;

int main() {
  Scope root = Scope::NewRootScope();
  auto a = ops::Placeholder(root, DT_INT32);
  auto c = ops::Add(root, a, {41});
  ClientSession session(root);
  std::vector<Tensor> outputs;
  Status s = session.Run({ {a, {1}} }, {c}, &outputs);
  if (!s.ok()) {
    cout << "Failed :(" << "\n";
  } else {
    cout << "Success :)" << "\n";
  }
  
  return 0;
}
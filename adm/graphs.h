#ifndef _LAWRENCIUM_ADM_GRAPHS_H_
#define _LAWRENCIUM_ADM_GRAPHS_H_

namespace adm {
namespace graphs {
constexpr int MAXV = 1000;

struct EdgeNode {
  int y;
  int weight;
  EdgeNode *next;
};

struct graph {
  EdgeNode *edges[MAXV + 1];
  int degree[MAXV + 1];
  int nvertices;
  int nedges;
  bool directed;
};

} // namespace graphs
} // namespace adm

#endif
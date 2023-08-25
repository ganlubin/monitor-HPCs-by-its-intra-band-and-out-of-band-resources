#include <hwloc.h>
#include <stdio.h>

/*

这个示例代码将遍历系统中的每个处理器（PU），并打印出其在拓扑结构中的深度。

*/

void print_cpus(hwloc_topology_t topology, hwloc_obj_t obj, int depth) {
  if (obj->type == HWLOC_OBJ_PU) {
    printf("Processor %u: Depth %d\n", obj->os_index, depth);
  }

  for (unsigned i = 0; i < obj->arity; i++) {
    print_cpus(topology, obj->children[i], depth + 1);
  }
}

int main() {
  hwloc_topology_t topology;

  // 初始化拓扑结构
  hwloc_topology_init(&topology);

  // 构建拓扑结构
  hwloc_topology_load(topology);

  // 获取根节点
  hwloc_obj_t root = hwloc_get_root_obj(topology);

  // 遍历处理器拓扑结构
  print_cpus(topology, root, 0);

  // 释放拓扑结构
  hwloc_topology_destroy(topology);

  return 0;
}
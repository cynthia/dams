/* makestatics.c */
#include "headers.h"

// 統計情報の作成
void make_statics() {
  int i, total;
  for (i = 0; i < STATICS_SIZE; i++) {
    statics[i] = 0;
  }
  damsTryName.MakeStatics();
  total = 0;
  for (i = 0; i < STATICS_SIZE; i++) {
    total += statics[i];
  }
  for (i = 0; i < STATICS_SIZE - 1; i++) {
    fprintf(stderr, "%2d: %d(%f%%)\n", i, statics[i], statics[i] * 100.0 /total );
  }
  i = STATICS_SIZE - 1;
  fprintf(stderr, "%2d+: %d(%f%%)\n\n", i, statics[i], statics[i] * 100.0 / total);

  for (i = 0; i < NODE_STATISTICS_SIZE; i++) {
    node_statistics[i] = 0;
  }
  int count = damsArray.Elements();
  for (i = 0; i < count; i++) {
    dam* d = damsArray.Element(i);
    int n = d->num_children();
    //    fprintf(stderr, "%s has %d children\n", d->_name, n);
    if (n < NODE_STATISTICS_SIZE - 1) {
      node_statistics[n]++;
    } else {
      node_statistics[NODE_STATISTICS_SIZE - 1]++;
    }
  }
  total = 0;
  for (i = 0; i < STATICS_SIZE; i++) {
    total += node_statistics[i];
  }
  for (i = 0; i < NODE_STATISTICS_SIZE - 1; i++) {
    fprintf(stderr, "%2d\t%d\t%f\n", i, node_statistics[i], node_statistics[i] * 100.0 / total);
  }
  i = NODE_STATISTICS_SIZE - 1;
    fprintf(stderr, "%2d+\t%d\t%f\n", i, node_statistics[i], node_statistics[i] * 100.0 / total);  
}

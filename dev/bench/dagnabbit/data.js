window.BENCHMARK_DATA = {
  "lastUpdate": 1643578871062,
  "repoUrl": "https://github.com/derelictcomputer/reciprocal",
  "entries": {
    "dagnabbit Benchmark": [
      {
        "commit": {
          "author": {
            "email": "charlie.huguenard@gmail.com",
            "name": "Charlie Huguenard",
            "username": "charliehuge"
          },
          "committer": {
            "email": "charlie.huguenard@gmail.com",
            "name": "Charlie Huguenard",
            "username": "charliehuge"
          },
          "distinct": true,
          "id": "70ba8de90a1e2bfcf7165eef5b05fee3b4aa976a",
          "message": "add dagnabbit benchmarks to workflow",
          "timestamp": "2022-01-30T13:01:25-05:00",
          "tree_id": "522a6e45aed5dfa726748cf39b67f795b52d813f",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/70ba8de90a1e2bfcf7165eef5b05fee3b4aa976a"
        },
        "date": 1643565745871,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double, 16>",
            "value": 340.9375484150413,
            "unit": "ns/iter",
            "extra": "iterations: 2031910\ncpu: 340.92174358116256 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "charliehuge@users.noreply.github.com",
            "name": "Charlie Huguenard",
            "username": "charliehuge"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "0ce8d571f7aa0dc76359851c2453cbf441311291",
          "message": "Graph add/remove nodes (#20)\n\n* Add graph + addNode\r\n\r\n* capture cb by copy from const ref\r\n\r\n* I am trash man\r\n\r\n* fix SPSCQ reader/writer sig\r\n\r\n* return status\r\n\r\n* make sure condition variable and mutex get initialized before trash thread\r\n\r\n* use a create function and garbage collector to make sure the process thread is not allocating or freeing nodes\r\n\r\n* comments, also return node id on failure\r\n\r\n* add removeNode\r\n\r\n* add multithreaded test for graph add/remove\r\n\r\n* address my review comments\r\n\r\n* test errors for invalid remove\r\n\r\n* use common PassthroughNode\r\n\r\n* * add graph add/remove benchmark\r\n* fix bug exposed by benchmark and write test to catch regressions\r\n\r\n* split assert check so we know what is happening\r\n\r\n* more info for debugging on test runner\r\n\r\n* double garbage collector size to fix test\r\n\r\n* sleep between re-runs to make sure gc has time to run\r\n\r\n* omg print debugging\r\n\r\n* check to see if this is a bug with the gc\r\n\r\n* more print debugging\r\n\r\n* manual dump for test to see if that is why the trash can is full\r\n\r\n* print how many items are left after dumping\r\n\r\n* sleep instead of yield\r\n\r\n* dump every retry in test\r\n\r\n* retry dumping trash until empty\r\n\r\n* busy wait until I come up with a better idea",
          "timestamp": "2022-01-30T16:40:11-05:00",
          "tree_id": "8709fe8c23fcecfce37d0c107cd7a96f0136ae79",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/0ce8d571f7aa0dc76359851c2453cbf441311291"
        },
        "date": 1643578869917,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemoveAll<int32_t, 64>",
            "value": 561499.2294352005,
            "unit": "ns/iter",
            "extra": "iterations: 4267\ncpu: 208651.0663229435 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double, 16>",
            "value": 411.3827237922957,
            "unit": "ns/iter",
            "extra": "iterations: 1742732\ncpu: 402.7968729557957 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}
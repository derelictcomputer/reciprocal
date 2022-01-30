window.BENCHMARK_DATA = {
  "lastUpdate": 1643555347411,
  "repoUrl": "https://github.com/derelictcomputer/reciprocal",
  "entries": {
    "core Benchmark": [
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
          "id": "28f806b986133c8ddefc92afc862a93c4b3ccf62",
          "message": "fix pedantic compile error on Linux",
          "timestamp": "2022-01-30T10:08:00-05:00",
          "tree_id": "11422b5cea24d7554b272277ceed4f387eb907d2",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/28f806b986133c8ddefc92afc862a93c4b3ccf62"
        },
        "date": 1643555345878,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 111835.56145384964,
            "unit": "ns/iter",
            "extra": "iterations: 6273\ncpu: 111796.12625538021 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15507.801427083614,
            "unit": "ns/iter",
            "extra": "iterations: 45127\ncpu: 15503.23088173377 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24702.005502063115,
            "unit": "ns/iter",
            "extra": "iterations: 28353\ncpu: 24698.776143617964 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}
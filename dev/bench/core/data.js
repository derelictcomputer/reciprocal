window.BENCHMARK_DATA = {
  "lastUpdate": 1643563235238,
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
          "id": "991287d36771062e2d8508f1866e5b10021b814a",
          "message": "* add benchmark for node connect/disconnect (#25)\n\n* add node disconnect and test\r\n* pull passthrough node out into templated helper",
          "timestamp": "2022-01-30T12:19:40-05:00",
          "tree_id": "5ee9ffa01997d2f22d4a0a7217cdac8ec4a87943",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/991287d36771062e2d8508f1866e5b10021b814a"
        },
        "date": 1643563234088,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 113427.04386934038,
            "unit": "ns/iter",
            "extra": "iterations: 6337\ncpu: 112940.46078586082 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15484.308470374834,
            "unit": "ns/iter",
            "extra": "iterations: 45181\ncpu: 15482.806932117486 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24609.35851580677,
            "unit": "ns/iter",
            "extra": "iterations: 28406\ncpu: 24609.22692388932 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}
window.BENCHMARK_DATA = {
  "lastUpdate": 1643581327729,
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
      },
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
        "date": 1643565750351,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 128933.70657318151,
            "unit": "ns/iter",
            "extra": "iterations: 5705\ncpu: 128860.61349693254 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 17536.437087373084,
            "unit": "ns/iter",
            "extra": "iterations: 36201\ncpu: 17535.192398000054 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 26710.669479340075,
            "unit": "ns/iter",
            "extra": "iterations: 26428\ncpu: 26708.87316482517 ns\nthreads: 1"
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
        "date": 1643578870345,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 111793.42943133174,
            "unit": "ns/iter",
            "extra": "iterations: 6313\ncpu: 111774.49706953905 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15477.003920265739,
            "unit": "ns/iter",
            "extra": "iterations: 45150\ncpu: 15475.377630121819 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24608.425824175996,
            "unit": "ns/iter",
            "extra": "iterations: 28392\ncpu: 24607.093547478155 ns\nthreads: 1"
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
          "id": "e0049fbaa0702c777eab587c55ab9ba12677c8b5",
          "message": "add benchmark for TrashMan (#26)",
          "timestamp": "2022-01-30T17:17:26-05:00",
          "tree_id": "214057743b13e07464e559202addf9d10b7c97be",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/e0049fbaa0702c777eab587c55ab9ba12677c8b5"
        },
        "date": 1643581101737,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 111774.18299620661,
            "unit": "ns/iter",
            "extra": "iterations: 6328\ncpu: 111732.15865992417 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 16236.146414989134,
            "unit": "ns/iter",
            "extra": "iterations: 43124\ncpu: 16234.795009739357 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24637.092310399126,
            "unit": "ns/iter",
            "extra": "iterations: 28415\ncpu: 24635.618511349636 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 179514.1026597061,
            "unit": "ns/iter",
            "extra": "iterations: 4023\ncpu: 172958.09097688293 ns\nthreads: 1"
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
          "id": "f44d284e2901dcc9d2aa4287bacc445be18b41cf",
          "message": "make InvalidNodeId const. Thanks @thomasjwebb ! (#27)",
          "timestamp": "2022-01-30T17:21:09-05:00",
          "tree_id": "a9accab10a46bcbc7aed29339a8605a977884fcb",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/f44d284e2901dcc9d2aa4287bacc445be18b41cf"
        },
        "date": 1643581326462,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 112453.53442779658,
            "unit": "ns/iter",
            "extra": "iterations: 6274\ncpu: 112434.50749123366 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15653.29308510625,
            "unit": "ns/iter",
            "extra": "iterations: 45120\ncpu: 15650.977393617024 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24601.504586510957,
            "unit": "ns/iter",
            "extra": "iterations: 28453\ncpu: 24599.75749481601 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 174446.6049324173,
            "unit": "ns/iter",
            "extra": "iterations: 4217\ncpu: 167745.34028930514 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}
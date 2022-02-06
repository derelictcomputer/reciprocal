window.BENCHMARK_DATA = {
  "lastUpdate": 1644145492698,
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
          "id": "d953a20289e7315ce8fad0371b42f423432e3ce7",
          "message": "Add badges",
          "timestamp": "2022-01-30T17:32:41-05:00",
          "tree_id": "dbeb4dd9149410d0b8623ff31ba10d1bbe92d799",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/d953a20289e7315ce8fad0371b42f423432e3ce7"
        },
        "date": 1643582020213,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 111972.70796319733,
            "unit": "ns/iter",
            "extra": "iterations: 6304\ncpu: 111830.40926395939 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15670.516823748181,
            "unit": "ns/iter",
            "extra": "iterations: 44669\ncpu: 15669.437417448347 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24665.96654563385,
            "unit": "ns/iter",
            "extra": "iterations: 28367\ncpu: 24664.3529453238 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 175005.76321454195,
            "unit": "ns/iter",
            "extra": "iterations: 4181\ncpu: 168263.6450609903 ns\nthreads: 1"
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
          "id": "f72d63a23818917d6678f87ad92e594a961e7f50",
          "message": "remove debug prints (#28)",
          "timestamp": "2022-01-30T18:12:44-05:00",
          "tree_id": "5d4bc23f8bdb1739c7d6845a91a1d6cc39bd7c20",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/f72d63a23818917d6678f87ad92e594a961e7f50"
        },
        "date": 1643584422469,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 111843.28895849446,
            "unit": "ns/iter",
            "extra": "iterations: 6385\ncpu: 111752.8425998434 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15677.166398749814,
            "unit": "ns/iter",
            "extra": "iterations: 44790\ncpu: 15672.734985487838 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24706.817803190846,
            "unit": "ns/iter",
            "extra": "iterations: 28332\ncpu: 24704.17549061133 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 168152.16696710145,
            "unit": "ns/iter",
            "extra": "iterations: 4438\ncpu: 162022.21721496174 ns\nthreads: 1"
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
          "id": "4d1005289cda1c3e0cc482c91c500bd4f00a4b09",
          "message": "Fresh graph for each iteration. This will make the iteration time longer because it waits for the trash to be emptied (#29)",
          "timestamp": "2022-01-30T18:57:52-05:00",
          "tree_id": "2819ad691b0b292852974feb08309149305b787f",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/4d1005289cda1c3e0cc482c91c500bd4f00a4b09"
        },
        "date": 1643587141016,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 126966.95256388516,
            "unit": "ns/iter",
            "extra": "iterations: 5987\ncpu: 126946.73459161517 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 18343.78235052124,
            "unit": "ns/iter",
            "extra": "iterations: 38902\ncpu: 18342.38342501671 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 27607.189822550878,
            "unit": "ns/iter",
            "extra": "iterations: 25134\ncpu: 27605.832736532186 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 186057.37484617237,
            "unit": "ns/iter",
            "extra": "iterations: 4063\ncpu: 174215.40733448195 ns\nthreads: 1"
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
          "id": "8bf745c0beb32e3419987569dfa02b0fce45b5b7",
          "message": "chron -> cron",
          "timestamp": "2022-02-01T21:49:31-05:00",
          "tree_id": "701b4d22bf569a032839f38aa9274bcf048643b9",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/8bf745c0beb32e3419987569dfa02b0fce45b5b7"
        },
        "date": 1643770236573,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 112175.0874109279,
            "unit": "ns/iter",
            "extra": "iterations: 6315\ncpu: 112137.08630245447 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15585.777875092686,
            "unit": "ns/iter",
            "extra": "iterations: 44529\ncpu: 15563.34523568911 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24658.454244335488,
            "unit": "ns/iter",
            "extra": "iterations: 28379\ncpu: 24657.36283871877 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 170715.70658542388,
            "unit": "ns/iter",
            "extra": "iterations: 4267\ncpu: 164248.86337004913 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "name": "Charlie Huguenard",
            "username": "charliehuge",
            "email": "charlie.huguenard@gmail.com"
          },
          "committer": {
            "name": "Charlie Huguenard",
            "username": "charliehuge",
            "email": "charlie.huguenard@gmail.com"
          },
          "id": "8bf745c0beb32e3419987569dfa02b0fce45b5b7",
          "message": "chron -> cron",
          "timestamp": "2022-02-02T02:49:31Z",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/8bf745c0beb32e3419987569dfa02b0fce45b5b7"
        },
        "date": 1643799892504,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 112024.52478820477,
            "unit": "ns/iter",
            "extra": "iterations: 6374\ncpu: 111998.00753059304 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15645.112633555047,
            "unit": "ns/iter",
            "extra": "iterations: 44738\ncpu: 15644.48120166302 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24662.82673476541,
            "unit": "ns/iter",
            "extra": "iterations: 28390\ncpu: 24661.821063754844 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 165969.89046973776,
            "unit": "ns/iter",
            "extra": "iterations: 4428\ncpu: 159456.36856368568 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "name": "Charlie Huguenard",
            "username": "charliehuge",
            "email": "charlie.huguenard@gmail.com"
          },
          "committer": {
            "name": "Charlie Huguenard",
            "username": "charliehuge",
            "email": "charlie.huguenard@gmail.com"
          },
          "id": "8bf745c0beb32e3419987569dfa02b0fce45b5b7",
          "message": "chron -> cron",
          "timestamp": "2022-02-02T02:49:31Z",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/8bf745c0beb32e3419987569dfa02b0fce45b5b7"
        },
        "date": 1643886303426,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 111889.62608284585,
            "unit": "ns/iter",
            "extra": "iterations: 6349\ncpu: 111648.71633328083 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 16198.335893224601,
            "unit": "ns/iter",
            "extra": "iterations: 43231\ncpu: 16197.945918438158 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24676.66834577961,
            "unit": "ns/iter",
            "extra": "iterations: 28388\ncpu: 24671.449203888966 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 163727.4002686362,
            "unit": "ns/iter",
            "extra": "iterations: 4467\ncpu: 158122.9012760242 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "name": "Charlie Huguenard",
            "username": "charliehuge",
            "email": "charlie.huguenard@gmail.com"
          },
          "committer": {
            "name": "Charlie Huguenard",
            "username": "charliehuge",
            "email": "charlie.huguenard@gmail.com"
          },
          "id": "8bf745c0beb32e3419987569dfa02b0fce45b5b7",
          "message": "chron -> cron",
          "timestamp": "2022-02-02T02:49:31Z",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/8bf745c0beb32e3419987569dfa02b0fce45b5b7"
        },
        "date": 1643972684788,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 111906.04535363097,
            "unit": "ns/iter",
            "extra": "iterations: 6306\ncpu: 111889.08975578814 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 16089.270570929477,
            "unit": "ns/iter",
            "extra": "iterations: 43508\ncpu: 16087.763169991731 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 25600.687138781585,
            "unit": "ns/iter",
            "extra": "iterations: 27338\ncpu: 25600.859609334995 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 157423.4253253915,
            "unit": "ns/iter",
            "extra": "iterations: 4533\ncpu: 147767.39466137212 ns\nthreads: 1"
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
          "id": "d0044f470cc0faeb390a91ad94d9e72a50e9b586",
          "message": "Graph Connect/Disconnect (#31)\n\n* address comment, closes #30\r\n\r\n* add Graph::connectNodes and test\r\n\r\n* add Graph::disconnectNodes and test\r\n\r\n* add benchmark for graph connect/disconnect",
          "timestamp": "2022-02-04T16:36:18-05:00",
          "tree_id": "2649f881334d290a06e5e3beda6b3269d9328796",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/d0044f470cc0faeb390a91ad94d9e72a50e9b586"
        },
        "date": 1644010650432,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 129447.41367365427,
            "unit": "ns/iter",
            "extra": "iterations: 5485\ncpu: 129401.8960802188 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 17691.144748590625,
            "unit": "ns/iter",
            "extra": "iterations: 39199\ncpu: 17688.44868491543 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 28370.004089815055,
            "unit": "ns/iter",
            "extra": "iterations: 24940\ncpu: 28356.066559743394 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 190826.38103943967,
            "unit": "ns/iter",
            "extra": "iterations: 3829\ncpu: 184375.47662575083 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "name": "Charlie Huguenard",
            "username": "charliehuge",
            "email": "charliehuge@users.noreply.github.com"
          },
          "committer": {
            "name": "GitHub",
            "username": "web-flow",
            "email": "noreply@github.com"
          },
          "id": "d0044f470cc0faeb390a91ad94d9e72a50e9b586",
          "message": "Graph Connect/Disconnect (#31)\n\n* address comment, closes #30\r\n\r\n* add Graph::connectNodes and test\r\n\r\n* add Graph::disconnectNodes and test\r\n\r\n* add benchmark for graph connect/disconnect",
          "timestamp": "2022-02-04T21:36:18Z",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/d0044f470cc0faeb390a91ad94d9e72a50e9b586"
        },
        "date": 1644059113797,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 116221.34296849431,
            "unit": "ns/iter",
            "extra": "iterations: 6158\ncpu: 116212.2767132186 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 17862.275725229116,
            "unit": "ns/iter",
            "extra": "iterations: 39815\ncpu: 17861.057390430742 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 26173.83608513294,
            "unit": "ns/iter",
            "extra": "iterations: 25983\ncpu: 26172.562829542407 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 200693.61628797348,
            "unit": "ns/iter",
            "extra": "iterations: 3917\ncpu: 175619.45366351795 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "name": "Charlie Huguenard",
            "username": "charliehuge",
            "email": "charliehuge@users.noreply.github.com"
          },
          "committer": {
            "name": "GitHub",
            "username": "web-flow",
            "email": "noreply@github.com"
          },
          "id": "d0044f470cc0faeb390a91ad94d9e72a50e9b586",
          "message": "Graph Connect/Disconnect (#31)\n\n* address comment, closes #30\r\n\r\n* add Graph::connectNodes and test\r\n\r\n* add Graph::disconnectNodes and test\r\n\r\n* add benchmark for graph connect/disconnect",
          "timestamp": "2022-02-04T21:36:18Z",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/d0044f470cc0faeb390a91ad94d9e72a50e9b586"
        },
        "date": 1644145489838,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 111735.14949590308,
            "unit": "ns/iter",
            "extra": "iterations: 6348\ncpu: 111630.76559546313 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15646.250368847188,
            "unit": "ns/iter",
            "extra": "iterations: 44734\ncpu: 15645.035096347303 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24660.9519044428,
            "unit": "ns/iter",
            "extra": "iterations: 28381\ncpu: 24658.866847538848 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 171929.9495619213,
            "unit": "ns/iter",
            "extra": "iterations: 4223\ncpu: 165050.1539190149 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}
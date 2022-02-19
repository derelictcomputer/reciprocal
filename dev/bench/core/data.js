window.BENCHMARK_DATA = {
  "lastUpdate": 1645306812261,
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
        "date": 1644231897038,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 113444.48304947594,
            "unit": "ns/iter",
            "extra": "iterations: 6165\ncpu: 113354.63098134629 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15653.660417458534,
            "unit": "ns/iter",
            "extra": "iterations: 44699\ncpu: 15652.455312199378 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24768.69056936372,
            "unit": "ns/iter",
            "extra": "iterations: 28365\ncpu: 24622.8591574123 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 178479.87164470565,
            "unit": "ns/iter",
            "extra": "iterations: 4098\ncpu: 170680.28306490975 ns\nthreads: 1"
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
        "date": 1644318304415,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 111543.86047990086,
            "unit": "ns/iter",
            "extra": "iterations: 6293\ncpu: 111540.8866995074 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 16113.794864721589,
            "unit": "ns/iter",
            "extra": "iterations: 43503\ncpu: 16093.848700089651 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 25611.667130053625,
            "unit": "ns/iter",
            "extra": "iterations: 27335\ncpu: 25610.89811596852 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 154400.40281276449,
            "unit": "ns/iter",
            "extra": "iterations: 4764\ncpu: 147671.9983207389 ns\nthreads: 1"
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
        "date": 1644404694561,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 99259.95048393791,
            "unit": "ns/iter",
            "extra": "iterations: 7129\ncpu: 99247.53822415488 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 13834.675031640716,
            "unit": "ns/iter",
            "extra": "iterations: 50568\ncpu: 13833.465828191742 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 21773.870934611263,
            "unit": "ns/iter",
            "extra": "iterations: 32131\ncpu: 21771.127571504156 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 161522.49598572412,
            "unit": "ns/iter",
            "extra": "iterations: 4484\ncpu: 155482.0472792149 ns\nthreads: 1"
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
          "id": "75df708feb48b45f330e70de71a41635a81e7168",
          "message": "Graph process logic (#32)\n\n* Add NodeBase and move connection logic in there\r\n\r\n* spin instead of sleep while waiting for gc thread\r\n\r\n* IPort->PortBase, because it is not an interface\r\n\r\n* just one connect/disconnect in benchmark, the framework handles running it multiple times\r\n\r\n* dump trash before every async call, update tests and benchmarks\r\n\r\n* remove periodic benchmarks\r\n\r\n* PortBase::getConnection()\r\n\r\n* graph sort and process\r\n\r\n* unset topo changed flag so we dont run that every frame",
          "timestamp": "2022-02-09T15:53:45-05:00",
          "tree_id": "8a3c30bfc0c69a8a37d4965cc76bce38db3749a0",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/75df708feb48b45f330e70de71a41635a81e7168"
        },
        "date": 1644440083366,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 112408.24949003966,
            "unit": "ns/iter",
            "extra": "iterations: 6373\ncpu: 112168.17825200062 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15665.433290836627,
            "unit": "ns/iter",
            "extra": "iterations: 44709\ncpu: 15663.099152295963 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24653.614471413308,
            "unit": "ns/iter",
            "extra": "iterations: 28387\ncpu: 24651.93926797477 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 40919.7292032293,
            "unit": "ns/iter",
            "extra": "iterations: 17094\ncpu: 40918.088218088225 ns\nthreads: 1"
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
          "id": "88d58119e906a5c23572cb9a40ce9f73ba483b25",
          "message": "* shared -> static for libs (#34)\n\n* core is header-only, so set it up as an interface library",
          "timestamp": "2022-02-12T10:29:07-05:00",
          "tree_id": "db1417d1fe247e095a4431c30119e40befdfb0da",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/88d58119e906a5c23572cb9a40ce9f73ba483b25"
        },
        "date": 1644679803652,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 112579.72248957318,
            "unit": "ns/iter",
            "extra": "iterations: 6234\ncpu: 112558.50176451716 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 16096.974392011434,
            "unit": "ns/iter",
            "extra": "iterations: 43463\ncpu: 16096.035708533693 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 25613.099048664662,
            "unit": "ns/iter",
            "extra": "iterations: 27330\ncpu: 25611.25869008416 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 32197.611504832512,
            "unit": "ns/iter",
            "extra": "iterations: 21730\ncpu: 32196.971928209852 ns\nthreads: 1"
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
          "id": "79a85a77f3ccb0acf2dc9f0a897e6bbb164fe993",
          "message": "euclidean sequencer (#35)\n\n* add pulse node to drive euclidean sequencer\r\n\r\n* add euclid tests to test runs\r\n\r\n* implement euclid node\r\n\r\n* * move PassthroughNode into core lib, it is useful for non-dev things\r\n* implement main Euclid module/graph\r\n\r\n* wire up params\r\n\r\n* wrap euclid for VST3 (does not quite work yet)\r\n\r\n* got rhythm/params working, still issues when stopping and starting transport\r\n\r\n* start/stop working, still gets out of phase with transport\r\n\r\n* make params a little simpler to work with\r\n\r\n* get/set normalized for params\r\n\r\n* add normalized param interface\r\n\r\n* phase lock pulse, fix some bugs\r\n\r\n* build euclid VST3 on PR review and main merge\r\n\r\n* sample accurate note scheduling",
          "timestamp": "2022-02-14T15:54:15-05:00",
          "tree_id": "45fd70034703b674a3e840b670524c69787874f0",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/79a85a77f3ccb0acf2dc9f0a897e6bbb164fe993"
        },
        "date": 1644872112349,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 112086.6305886103,
            "unit": "ns/iter",
            "extra": "iterations: 6218\ncpu: 112017.41717594082 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 16106.409751944258,
            "unit": "ns/iter",
            "extra": "iterations: 43458\ncpu: 16105.626121772752 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 25616.5391937909,
            "unit": "ns/iter",
            "extra": "iterations: 27313\ncpu: 25616.669717716828 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 32160.164322486162,
            "unit": "ns/iter",
            "extra": "iterations: 21756\ncpu: 32159.468652325802 ns\nthreads: 1"
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
          "id": "9a8926694d3dda37ccbc37208cb1a224e04d790f",
          "message": "Optimize SPSCQ (#40)\n\n* add nextPowerOfTwo helper\r\n\r\n* round capacity to next power of two, ~15% improvement\r\n\r\n* const ref instead of rvalue ref for flexibility, no speed improvement\r\n\r\n* explicit memory ordering\r\n\r\n* concepts for GNU compiler\r\n\r\n* copypaste fix\r\n\r\n* push/pop ref to item instead of std::function\r\n\r\n* fix benchmark name",
          "timestamp": "2022-02-14T18:31:14-05:00",
          "tree_id": "37e3fdb2cd5790a89d655d96db5b4565dc360eb5",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/9a8926694d3dda37ccbc37208cb1a224e04d790f"
        },
        "date": 1644881538295,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 111981.4589587978,
            "unit": "ns/iter",
            "extra": "iterations: 6262\ncpu: 111964.2925582881 ns\nthreads: 1"
          },
          {
            "name": "MathHelpers_NextPowerOfTwo<uint8_t>",
            "value": 73.88746766764592,
            "unit": "ns/iter",
            "extra": "iterations: 9468070\ncpu: 73.8799987748295 ns\nthreads: 1"
          },
          {
            "name": "MathHelpers_NextPowerOfTwo<uint16_t>",
            "value": 248.97507398766572,
            "unit": "ns/iter",
            "extra": "iterations: 2787289\ncpu: 248.9782006817377 ns\nthreads: 1"
          },
          {
            "name": "MathHelpers_NextPowerOfTwo<uint32_t>",
            "value": 106.73350499776511,
            "unit": "ns/iter",
            "extra": "iterations: 6558532\ncpu: 106.73034758388005 ns\nthreads: 1"
          },
          {
            "name": "MathHelpers_NextPowerOfTwo<uint64_t>",
            "value": 124.86280523358114,
            "unit": "ns/iter",
            "extra": "iterations: 5608246\ncpu: 124.86203351279529 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15282.876137083125,
            "unit": "ns/iter",
            "extra": "iterations: 45841\ncpu: 15278.983879060237 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 25612.263356264193,
            "unit": "ns/iter",
            "extra": "iterations: 27328\ncpu: 25611.29244730681 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 32231.299990836702,
            "unit": "ns/iter",
            "extra": "iterations: 21824\ncpu: 32227.611803519074 ns\nthreads: 1"
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
          "id": "e9d6a697cbd572131770f78f72d9d4f9810a84eb",
          "message": "fix issue with wrong size data alloc, detected in other repo",
          "timestamp": "2022-02-15T07:46:26-05:00",
          "tree_id": "164c33586ddacb3f0a41da74e2832ffb5af991bf",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/e9d6a697cbd572131770f78f72d9d4f9810a84eb"
        },
        "date": 1644929255725,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 112022.86422136475,
            "unit": "ns/iter",
            "extra": "iterations: 6216\ncpu: 112006.09716859719 ns\nthreads: 1"
          },
          {
            "name": "MathHelpers_NextPowerOfTwo<uint8_t>",
            "value": 73.88960206964626,
            "unit": "ns/iter",
            "extra": "iterations: 9466355\ncpu: 73.88860865665825 ns\nthreads: 1"
          },
          {
            "name": "MathHelpers_NextPowerOfTwo<uint16_t>",
            "value": 248.0975709444725,
            "unit": "ns/iter",
            "extra": "iterations: 2757368\ncpu: 248.0926738832104 ns\nthreads: 1"
          },
          {
            "name": "MathHelpers_NextPowerOfTwo<uint32_t>",
            "value": 106.7320190506143,
            "unit": "ns/iter",
            "extra": "iterations: 6557899\ncpu: 106.73276608865122 ns\nthreads: 1"
          },
          {
            "name": "MathHelpers_NextPowerOfTwo<uint64_t>",
            "value": 124.83811063150682,
            "unit": "ns/iter",
            "extra": "iterations: 5607842\ncpu: 124.83470468675822 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 15282.410666317248,
            "unit": "ns/iter",
            "extra": "iterations: 45789\ncpu: 15281.890847146697 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 25638.832662617504,
            "unit": "ns/iter",
            "extra": "iterations: 27334\ncpu: 25637.69298309798 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 31913.88111824439,
            "unit": "ns/iter",
            "extra": "iterations: 21963\ncpu: 31908.81937804487 ns\nthreads: 1"
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
          "id": "cac00d6b0584773f4d7e4af85bdcadd79a9083d7",
          "message": "Port UX improvement (#42)\n\n* have NodeBase manage Port lifecycle\r\n\r\n* remove need for storing ports on concrete node classes\r\n\r\n* speed up passthrough chain with num connections check and static_cast instead of dynamic_cast",
          "timestamp": "2022-02-19T16:39:10-05:00",
          "tree_id": "ce68a98e003416a8899f5d4b62ee6842f9cc6f81",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/cac00d6b0584773f4d7e4af85bdcadd79a9083d7"
        },
        "date": 1645306810816,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "LFPool_AcquireReleaseAll",
            "value": 112201.7562094603,
            "unit": "ns/iter",
            "extra": "iterations: 6321\ncpu: 112050.75146337604 ns\nthreads: 1"
          },
          {
            "name": "MathHelpers_NextPowerOfTwo<uint8_t>",
            "value": 63.55537134282003,
            "unit": "ns/iter",
            "extra": "iterations: 11013233\ncpu: 63.54964069133921 ns\nthreads: 1"
          },
          {
            "name": "MathHelpers_NextPowerOfTwo<uint16_t>",
            "value": 207.092153995161,
            "unit": "ns/iter",
            "extra": "iterations: 3308104\ncpu: 207.07048508753047 ns\nthreads: 1"
          },
          {
            "name": "MathHelpers_NextPowerOfTwo<uint32_t>",
            "value": 95.17805014579315,
            "unit": "ns/iter",
            "extra": "iterations: 7351165\ncpu: 95.17611154150394 ns\nthreads: 1"
          },
          {
            "name": "MathHelpers_NextPowerOfTwo<uint64_t>",
            "value": 110.99289980520709,
            "unit": "ns/iter",
            "extra": "iterations: 6308841\ncpu: 110.98678822306663 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 11333.007674870483,
            "unit": "ns/iter",
            "extra": "iterations: 61760\ncpu: 11332.208549222805 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24667.70771502933,
            "unit": "ns/iter",
            "extra": "iterations: 28438\ncpu: 24666.087629228485 ns\nthreads: 1"
          },
          {
            "name": "TrashMan_FillEmpty<int, 512>",
            "value": 40861.612119798076,
            "unit": "ns/iter",
            "extra": "iterations: 17129\ncpu: 40855.75923871794 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}
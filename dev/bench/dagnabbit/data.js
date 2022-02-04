window.BENCHMARK_DATA = {
  "lastUpdate": 1644010641610,
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
        "date": 1643581098803,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemoveAll<int32_t, 64>",
            "value": 188303.74238426573,
            "unit": "ns/iter",
            "extra": "iterations: 4169\ncpu: 134702.08683137444 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double, 16>",
            "value": 348.2738168153936,
            "unit": "ns/iter",
            "extra": "iterations: 1970635\ncpu: 348.25287280495894 ns\nthreads: 1"
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
        "date": 1643581331207,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemoveAll<int32_t, 64>",
            "value": 296820.7451665983,
            "unit": "ns/iter",
            "extra": "iterations: 4862\ncpu: 148708.82352941175 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double, 16>",
            "value": 402.5549161208544,
            "unit": "ns/iter",
            "extra": "iterations: 1732433\ncpu: 402.51698045465537 ns\nthreads: 1"
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
        "date": 1643582021283,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemoveAll<int32_t, 64>",
            "value": 499133.7494617492,
            "unit": "ns/iter",
            "extra": "iterations: 8825\ncpu: 163157.86968838528 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double, 16>",
            "value": 425.44530778768535,
            "unit": "ns/iter",
            "extra": "iterations: 1644640\ncpu: 425.3327779939683 ns\nthreads: 1"
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
        "date": 1643584420713,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemoveAll<int32_t, 64>",
            "value": 234779.52241440176,
            "unit": "ns/iter",
            "extra": "iterations: 8499\ncpu: 133298.10565948937 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double, 16>",
            "value": 359.3102239415113,
            "unit": "ns/iter",
            "extra": "iterations: 1938274\ncpu: 359.27717133903656 ns\nthreads: 1"
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
        "date": 1643587128883,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemoveAll<int32_t, 64>",
            "value": 118549.08518518381,
            "unit": "ns/iter",
            "extra": "iterations: 6750\ncpu: 105233.11111111112 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double, 16>",
            "value": 403.50185371484105,
            "unit": "ns/iter",
            "extra": "iterations: 1746493\ncpu: 400.72241915656116 ns\nthreads: 1"
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
        "date": 1643770232714,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemoveAll<int32_t, 64>",
            "value": 119939.39772727275,
            "unit": "ns/iter",
            "extra": "iterations: 6512\ncpu: 106826.3667076167 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double, 16>",
            "value": 396.8271433730701,
            "unit": "ns/iter",
            "extra": "iterations: 1763797\ncpu: 396.78834922612975 ns\nthreads: 1"
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
        "date": 1643799889904,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemoveAll<int32_t, 64>",
            "value": 118282.57411839826,
            "unit": "ns/iter",
            "extra": "iterations: 6267\ncpu: 105696.90441997768 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double, 16>",
            "value": 350.37231353172166,
            "unit": "ns/iter",
            "extra": "iterations: 1950144\ncpu: 350.29818310852954 ns\nthreads: 1"
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
        "date": 1643886305422,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemoveAll<int32_t, 64>",
            "value": 121763.37130607666,
            "unit": "ns/iter",
            "extra": "iterations: 6531\ncpu: 108577.1857295973 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double, 16>",
            "value": 400.24563038056283,
            "unit": "ns/iter",
            "extra": "iterations: 1757018\ncpu: 400.17393105819076 ns\nthreads: 1"
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
        "date": 1643972687357,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemoveAll<int32_t, 64>",
            "value": 107501.47654454446,
            "unit": "ns/iter",
            "extra": "iterations: 7397\ncpu: 96434.43287819387 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double, 16>",
            "value": 350.609917557328,
            "unit": "ns/iter",
            "extra": "iterations: 1997024\ncpu: 350.588024981172 ns\nthreads: 1"
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
        "date": 1644010640245,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemoveAll<int32_t, 64>",
            "value": 122948.78697293827,
            "unit": "ns/iter",
            "extra": "iterations: 6356\ncpu: 109639.14411579612 ns\nthreads: 1"
          },
          {
            "name": "Graph_ConnectDisconnect<double, double, 16>",
            "value": 55856.22284419635,
            "unit": "ns/iter",
            "extra": "iterations: 15006\ncpu: 46256.137544982004 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double, 16>",
            "value": 404.6109785801283,
            "unit": "ns/iter",
            "extra": "iterations: 1755145\ncpu: 404.5764879824743 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}
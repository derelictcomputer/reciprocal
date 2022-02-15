window.BENCHMARK_DATA = {
  "lastUpdate": 1644929259116,
  "repoUrl": "https://github.com/derelictcomputer/reciprocal",
  "entries": {
    "dagnabbit Benchmark": [
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
        "date": 1644440083608,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemove<double>",
            "value": 355.2032423462007,
            "unit": "ns/iter",
            "extra": "iterations: 1963208\ncpu: 355.20535776137825 ns\nthreads: 1"
          },
          {
            "name": "Graph_ConnectDisconnect<double, double>",
            "value": 116.54561774876046,
            "unit": "ns/iter",
            "extra": "iterations: 6241518\ncpu: 116.54597487342022 ns\nthreads: 1"
          },
          {
            "name": "Graph_Process_PassthroughChain<double, double, 64>",
            "value": 2393.940611050363,
            "unit": "ns/iter",
            "extra": "iterations: 287865\ncpu: 2393.941951956647 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double>",
            "value": 18.843697849979645,
            "unit": "ns/iter",
            "extra": "iterations: 37197972\ncpu: 18.843798796342988 ns\nthreads: 1"
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
        "date": 1644440083608,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemove<double>",
            "value": 355.2032423462007,
            "unit": "ns/iter",
            "extra": "iterations: 1963208\ncpu: 355.20535776137825 ns\nthreads: 1"
          },
          {
            "name": "Graph_ConnectDisconnect<double, double>",
            "value": 116.54561774876046,
            "unit": "ns/iter",
            "extra": "iterations: 6241518\ncpu: 116.54597487342022 ns\nthreads: 1"
          },
          {
            "name": "Graph_Process_PassthroughChain<double, double, 64>",
            "value": 2393.940611050363,
            "unit": "ns/iter",
            "extra": "iterations: 287865\ncpu: 2393.941951956647 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double>",
            "value": 18.843697849979645,
            "unit": "ns/iter",
            "extra": "iterations: 37197972\ncpu: 18.843798796342988 ns\nthreads: 1"
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
        "date": 1644679805915,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemove<double>",
            "value": 351.3003993057846,
            "unit": "ns/iter",
            "extra": "iterations: 1992458\ncpu: 351.29232335135805 ns\nthreads: 1"
          },
          {
            "name": "Graph_ConnectDisconnect<double, double>",
            "value": 114.67371851127605,
            "unit": "ns/iter",
            "extra": "iterations: 6612407\ncpu: 114.67261467722722 ns\nthreads: 1"
          },
          {
            "name": "Graph_Process_PassthroughChain<double, double, 64>",
            "value": 2414.088776671478,
            "unit": "ns/iter",
            "extra": "iterations: 293478\ncpu: 2413.3328562958723 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double>",
            "value": 10.955166419586211,
            "unit": "ns/iter",
            "extra": "iterations: 64134338\ncpu: 10.955270170559805 ns\nthreads: 1"
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
        "date": 1644872114456,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemove<double>",
            "value": 353.92488271938777,
            "unit": "ns/iter",
            "extra": "iterations: 1976030\ncpu: 353.8998395773344 ns\nthreads: 1"
          },
          {
            "name": "Graph_ConnectDisconnect<double, double>",
            "value": 106.8536854311836,
            "unit": "ns/iter",
            "extra": "iterations: 6479676\ncpu: 106.84293473932958 ns\nthreads: 1"
          },
          {
            "name": "Graph_Process_PassthroughChain<double, double, 64>",
            "value": 2444.2106498403223,
            "unit": "ns/iter",
            "extra": "iterations: 285901\ncpu: 2444.0442670714697 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double>",
            "value": 10.762432345125971,
            "unit": "ns/iter",
            "extra": "iterations: 64652585\ncpu: 10.761527941999539 ns\nthreads: 1"
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
        "date": 1644881533983,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemove<double>",
            "value": 345.3371771825985,
            "unit": "ns/iter",
            "extra": "iterations: 2039969\ncpu: 345.2940706451912 ns\nthreads: 1"
          },
          {
            "name": "Graph_ConnectDisconnect<double, double>",
            "value": 105.56903064337985,
            "unit": "ns/iter",
            "extra": "iterations: 6647048\ncpu: 105.55765506733215 ns\nthreads: 1"
          },
          {
            "name": "Graph_Process_PassthroughChain<double, double, 64>",
            "value": 1986.712678178756,
            "unit": "ns/iter",
            "extra": "iterations: 327831\ncpu: 1986.5357455518235 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double>",
            "value": 11.259991389788533,
            "unit": "ns/iter",
            "extra": "iterations: 62620993\ncpu: 11.25922420297615 ns\nthreads: 1"
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
        "date": 1644929256490,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "Graph_AddRemove<double>",
            "value": 387.51433531436055,
            "unit": "ns/iter",
            "extra": "iterations: 1805297\ncpu: 387.469097882509 ns\nthreads: 1"
          },
          {
            "name": "Graph_ConnectDisconnect<double, double>",
            "value": 158.73022418862098,
            "unit": "ns/iter",
            "extra": "iterations: 4405799\ncpu: 158.71293719935935 ns\nthreads: 1"
          },
          {
            "name": "Graph_Process_PassthroughChain<double, double, 64>",
            "value": 2158.210191082807,
            "unit": "ns/iter",
            "extra": "iterations: 325304\ncpu: 2158.064456631336 ns\nthreads: 1"
          },
          {
            "name": "Node_Passthrough_ConnectDisconnect<double, double>",
            "value": 13.161195514366728,
            "unit": "ns/iter",
            "extra": "iterations: 53209967\ncpu: 13.159572153089291 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}
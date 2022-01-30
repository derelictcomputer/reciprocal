window.BENCHMARK_DATA = {
  "lastUpdate": 1643552548670,
  "repoUrl": "https://github.com/derelictcomputer/reciprocal",
  "entries": {
    "core Benchmark": [
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
          "id": "6133983e6b1d29bd8527211d006b49eea8ef81b8",
          "message": "Benchmarks (#23)\n\n* add google benchmark\r\n\r\n* compare SPSCQ and MPMCQ for fun\r\n\r\n* do not build/test google benchmark, they did that already\r\n\r\n* add benchmark workflow\r\n\r\n* explicitly build test targets to keep build times down\r\n\r\n* store benchmark result and alert on regression\r\n\r\n* fix typo\r\n\r\n* fix typo\r\n\r\n* maybe fix writing json\r\n\r\n* fix paths\r\n\r\n* benchmark_out\r\n\r\n* publish to gh pages\r\n\r\n* no deploy permission",
          "timestamp": "2022-01-30T09:13:25-05:00",
          "tree_id": "82fa6cf5e3c02a0b105d67171db7366befe765d9",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/6133983e6b1d29bd8527211d006b49eea8ef81b8"
        },
        "date": 1643552072519,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "SPSCQ_PushPop<int, 64>",
            "value": 31.358221449894128,
            "unit": "ns/iter",
            "extra": "iterations: 22315188\ncpu: 31.356818504060996 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_PushPop<double, 512>",
            "value": 31.346069957905407,
            "unit": "ns/iter",
            "extra": "iterations: 22322738\ncpu: 31.344680925789643 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_PushPop<float, 128>",
            "value": 31.348274578563046,
            "unit": "ns/iter",
            "extra": "iterations: 22328371\ncpu: 31.34740102625489 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<int, 64>",
            "value": 2052.3680007039347,
            "unit": "ns/iter",
            "extra": "iterations: 340945\ncpu: 2052.2242590447145 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 16093.6557132015,
            "unit": "ns/iter",
            "extra": "iterations: 43487\ncpu: 16092.413824821228 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<float, 128>",
            "value": 4080.736610822669,
            "unit": "ns/iter",
            "extra": "iterations: 172266\ncpu: 4080.515597970582 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<int, 64>",
            "value": 3224.327010702549,
            "unit": "ns/iter",
            "extra": "iterations: 217051\ncpu: 3224.248218160708 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 25613.39179937763,
            "unit": "ns/iter",
            "extra": "iterations: 27315\ncpu: 25611.367380560125 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<float, 128>",
            "value": 6387.652435627076,
            "unit": "ns/iter",
            "extra": "iterations: 109479\ncpu: 6387.437773454281 ns\nthreads: 1"
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
          "id": "dede05beb044912001411132c1f895cebc9e3af4",
          "message": "intentionally make a benchmark slower",
          "timestamp": "2022-01-30T09:21:21-05:00",
          "tree_id": "48440c39a637799dc656a23338ee3388522e48c5",
          "url": "https://github.com/derelictcomputer/reciprocal/commit/dede05beb044912001411132c1f895cebc9e3af4"
        },
        "date": 1643552547493,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "SPSCQ_PushPop<int, 64>",
            "value": 30.14269705520518,
            "unit": "ns/iter",
            "extra": "iterations: 23237270\ncpu: 30.13586793973646 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_PushPop<double, 512>",
            "value": 30.127576088354765,
            "unit": "ns/iter",
            "extra": "iterations: 23241730\ncpu: 30.126277174719792 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_PushPop<float, 128>",
            "value": 30.120583965741925,
            "unit": "ns/iter",
            "extra": "iterations: 23237733\ncpu: 30.11916007469402 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<int, 64>",
            "value": 4122.222791052629,
            "unit": "ns/iter",
            "extra": "iterations: 175604\ncpu: 3988.980319354913 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<double, 512>",
            "value": 31087.516636311157,
            "unit": "ns/iter",
            "extra": "iterations: 22511\ncpu: 31079.32122073654 ns\nthreads: 1"
          },
          {
            "name": "SPSCQ_FillDrain<float, 128>",
            "value": 7840.418915589782,
            "unit": "ns/iter",
            "extra": "iterations: 89302\ncpu: 7839.847931737255 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<int, 64>",
            "value": 3064.09511115777,
            "unit": "ns/iter",
            "extra": "iterations: 228459\ncpu: 3063.582962369617 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<double, 512>",
            "value": 24609.37579998603,
            "unit": "ns/iter",
            "extra": "iterations: 28438\ncpu: 24603.896195231715 ns\nthreads: 1"
          },
          {
            "name": "MPMCQ_FillDrain<float, 128>",
            "value": 6153.321596987636,
            "unit": "ns/iter",
            "extra": "iterations: 113664\ncpu: 6152.323514921161 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}
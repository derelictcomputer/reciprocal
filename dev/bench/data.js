window.BENCHMARK_DATA = {
  "lastUpdate": 1643552073973,
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
      }
    ]
  }
}
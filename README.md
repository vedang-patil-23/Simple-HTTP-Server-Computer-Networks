Got it! Here’s an updated setup and performance section adapted for Windows.

---

# Simple HTTP Server - Networking Project

This project demonstrates a basic HTTP server built in C++ as part of my Computer Networks course.
### Project Objective Specified: 
Create a simple HTTP web server.
### Description Specified: 
Develop a basic web server capable of serving static web pages. The server should handle HTTP GET and POST requests. You can extend the project by 
adding functionalities like multi-threading to handle multiple client requests simultaneously.

## Key Features

- Manages multiple simultaneous connections, successfully tested with up to 10,000.
- Supports essential HTTP requests and responses, with a framework that's easy to extend for additional HTTP functionality.
- HTTP/1.1 compliant with persistent connections enabled by default.

## Quick Setup

```bash
mkdir build && cd build
cmake ..
make
.\test_SimpleHttpServer.exe     # Run unit tests (on Windows)
.\SimpleHttpServer.exe          # Start the HTTP server on port 8080
```

- Two demo endpoints are available at `/` and `/hello.html`.
- To support many concurrent clients, it’s recommended to increase the file descriptor limit on Windows by setting the appropriate `ulimit` equivalent in Windows PowerShell or Command Prompt.

## Architecture Overview

The server program uses:

- A primary thread for user interactions.
- A listener thread dedicated to accepting incoming client connections.
- Five worker threads for processing HTTP requests and sending responses.
- Utility functions to easily parse and manage HTTP requests and responses.

## Performance Testing

To evaluate server performance, I used [wrk](https://github.com/wg/wrk) (note: **wrk** needs to be installed through Windows Subsystem for Linux (WSL) or a similar tool as it is natively Unix-based). Testing was conducted on the following Windows laptop setup:

```bash
Model: Thinkpad T480
OS: Windows 10
Processor: Intel i7-8550 (8) @ 4.000 GHz
GPU: Intel UHD Graphics 620
Memory: 16GB RAM
```

Below are the results from two benchmark tests, each running for 1 minute with 10 client threads. The first test had 500 concurrent connections, and the second test was conducted with 10,000.

```bash
$ ./wrk -t10 -c500 -d60s http://localhost:8080/
Running 1m test @ http://localhost:8080/
  10 threads and 500 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency     5.01ms    1.31ms  57.86ms   86.35%
    Req/Sec     9.94k     0.99k   36.28k    76.69%
  5933266 requests in 1.00m, 441.36MB read
Requests/sec:  98760.82
Transfer/sec:      7.35MB
```

```bash
$ ./wrk -t10 -c10000 -d60s http://localhost:8080/
Running 1m test @ http://localhost:8080/
  10 threads and 10000 connections
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency   111.78ms   21.38ms 403.80ms   76.79%
    Req/Sec     8.73k     1.42k   18.77k    75.62%
  5174508 requests in 1.00m, 384.91MB read
Requests/sec:  86123.84
Transfer/sec:      6.41MB
```

These results show the server’s capacity to handle a high volume of requests efficiently, even under heavy load.

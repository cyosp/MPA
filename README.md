# MPA
My Personal Accounts (MPA) is a Web Application to manage personal accounts in a centralized way

**/!\ WARNING /!\**
**This project is Work In Progress (WIP) and is not stable for a production use.**

## Server side

Server building environnement is:
 * Eclipse IDE with CDT
 * Debian GNU Linux Stretch x86_64

## TESTS

When MPA binary is built it can be tested to check all is ok.

Tests are driven using [node.js](https://nodejs.org).

### Prerequisites

In order to have a test environment ready to use you must:

 1. Install [node.js](https://nodejs.org) or use `sudo apt-get install npm nodejs-legacy`
 2. Move into MPA GitHub directory
 3. Run: `npm install --save` to install locally dependencies

### Check MPA server

Before to launch tests you must check MPA:

* Is running on the test machine
* Can be reached using: *http://localhost:8080*
* Login: *cyosp* with password *CYOSP1* is defined

If all is OK, you can execute `npm test` to run MPA server test suite

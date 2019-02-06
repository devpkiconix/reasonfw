App development framework
=======
This is TeamIconix Application framework for developing end-to-end applications
based on ReasonML eco sytem.  This is work in progress and currently alpha quality.

# Main Layers

The functionality and code is organized into the following layers:

     -----------------
     |    App/UI     |
     -----------------
     |   Service     |
     -----------------
     |   Process     |
     -----------------
     |     DB        |
     -----------------

## DB Layer

This layer defines DB-specific operations such as CRUD
operations. This is the only layer that understands the schemas and
the structure of the DB. The layers above simply use this layer's API
to persist and retrieve data.

## Process Layer

The process layer is responsible for implementing "business logic" for
requests from various external entities. This layer usually splits up
its processing into logical steps in the process. Each step in the
process typically executes upto one async operation, and returns a
future value to encapsulate the asynchronous nature of the operation.

The data type for all the steps in a process is defined using a
"Variant" type.  For example, in the following process:

    let preRegister = (data) =>
      data |> loadDeviceFromDb >>= otpValidator >>= uidChecker >>=
              stateValidator >>= userIdValidator >>= dbUpdater;

(Note: the ">>=" operator represents chain method on the future).

Each of the steps (loadDeviceFromDb, otpValidator, uidChecker etc)
returns the same ReasonML data type,but with a variant, for example:

    type preRegisterFloData =
      | Start(uid_t, userId_t, otp_t)
      | DbLoaded(regStatus, uid_t, userId_t, otp_t, dbInfo_t)
      | OtpFormatOk(regStatus, uid_t, userId_t, otp_t, dbInfo_t)
      | DbStateOk(regStatus, uid_t, userId_t, otp_t, dbInfo_t)
      | DbUpdated(regStatus, uid_t, userId_t, otp_t, dbInfo_t)

So each step takes the same data type as input and returns the same
(future) data type as output.

#### Workers and Transaction FSM

Each process is executed (typically) by a finite state machine called
a Transaction FSM. This state machine executes the following steps:

  - Open DB connection
  - Start transaction
  - Delegates the real process work to a "worker". Passes the
    transaction and DB info to the worker.
  - Commit/rollback the transaction when the async worker completes/fails


## Service Layer

The service layer is responsible for receiving networks over the
network (i.e. from clients, over HTTP for example), process and return
results.  This layer is responsible for the following:

  - Unmarshal request
  - Verify user authenticity & authorization
  - Build a request object for the corresponding process
  - Kick off the process
  - Extract results
  - Marshal results back to client

## App/UI Layer

This layer is responsible for interacting with the user, passing
user's requests to the the service layer, and presenting the results
to the user.

This layer is also responsible for configuring the service layer and
injecting the dependencies. For example, turning logging/debugging
on/off, DB connection pools etc.  This configurability allows us to
mock certain aspects and simplifies the testing process.  Some of the
dependencies are passed all the way to the process layer, allowing us
to share core behavior between testing and production and improving
testability.

# Framework

The TeamIconix framework provides the following features:

  - A general purpose Finite state machine based on Futures. (see
    https://www.npmjs.com/package/fluture and
https://www.npmjs.com/package/bs-fluture)

  - Injection of external configuration & dependencies such as DB
    connection, log configuration etc at App layer

  - A CLI to help test all services. This is intended to provide a
    command line prototype at the beginning of the project. Plus it
    provides comprehensive list of all the UI interaction points and
    code examples for teh UI developers.

# Pure vs Impure Code

Pure functions strictly depend on their inputs to compute their
outputs. Impure functions may depend on other things such as global
variables, external services such as DB etc.

Pure functions make it easy to develop, test and maintain code, and we
should try to maximize the pure code in our projects.

However, impure code allows us to interact with world and provide
useful functionality. We attempt to restrict impure code to the
following:

  - External service interaction such as databases, caches,
    authentication services etc.

There should be no global variables in the application, with one
exception: Non-production code used for mocking some behaviors for
testability.

# Types

Types provide a safety net and help us write correct code. The
compiler, even if annoying sometimes, is our friend, parent and a
teacher. ReasonML makes it difficult to cheat (vs. Typescript for
example). Spend as much time as possible early on, in defining types
and the project is likely to go smooth, and would make it easy to spot
errors and simplify refactoring process.

# Directory structure

    src/
     cli/ - CLI code for demonstrating the functionality
     dblayer - DB related code
     framework - Framework code for FSM, flow engine etc
     processlayer - Process layer modules
     svclayer - Service layer modules
     types/ - type definitions shared across different modules

# High-level Development Approach

  1. Identify all services
  2. Implement dummy functions for all services
  3. Implement Mock functionality with no external services (including
     DB, authentication svc etc)
  4. Define CLI commands for each service entry point
  5. Share prototype with customer and get feedback on the core
     process behavior
  6. Build server with real external dependencies (including DB)
  7. In parallel to the server, design and build UI
  8. Split the server into deployable microservices
  9. Develop orchestration such as Kubernetes

# Build
```
npm run build
```

# Build + Watch

```
npm run start
```

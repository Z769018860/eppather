# Source-grounded function summary prompt

Input: the exact original function body, all called-function signatures and bodies that can affect memory, a bounded input contract, and the MEMS access-count rules.

Produce a C projection accepted by Eppather. In the output, supply:

1. The exact input domain and which branches/callees are excluded. When a callee is unavailable, declare it unresolved; never replace it with an unconstrained success Boolean and claim source equivalence.
2. A state map from each source field/pointer to one unique projection location; preserve alias relationships, nested member reads, array indices, and short-circuit order.
3. A call model for memcpy/memmove/strlen/allocation and reader callbacks. Separate accesses visible directly in the source from accesses attributed to library internals.
4. A trace correspondence for each feasible path in the bounded domain: branch decisions, source read/write sites, projection read/write sites, return value, and final observable state.
5. A runnable original-source instrumentation harness that checks at least zero/one/multiple iterations and failure/early-return paths against the projection.

Do not initialize synthetic arrays inside the summarized function solely to create memory accesses; inputs and caller-owned state must enter through parameters. Do not replace a real loop by a fixed scan or cap its transfer count without stating a bound on valid inputs. Do not use DFS2/DP agreement as a substitute for original-source access validation.

Accept the projection as source calibrated only after compiling both versions, verifying output and state, and observing equal access counts on every tested input. Report the tested domain and unsupported paths beside any Eppather result. A maximum over unconstrained parameters is only a model result unless the same input domain is encoded in the analyzer.

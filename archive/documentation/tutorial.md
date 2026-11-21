# Tutorial Template

Use this template when writing a step-by-step guide for a feature, class, or
hardware experiment in this repository. Replace the bracketed prompts, remove
sections that do not apply, and verify each instruction against the current
source and hardware. This file is a reusable template, not a claim that every
project feature is complete.

---

# [Tutorial title: action + outcome]

In this tutorial, you will [specific outcome]. You will use [feature/module]
with [board or environment]. At the end, you should be able to [observable
result].

## Audience and prerequisites

- **Experience assumed:** [for example, basic C++ and PlatformIO]
- **Hardware:** [board, components, wiring, and any required driver circuit]
- **Software:** [tool names and versions, if version-sensitive]
- **Starting point:** [branch, file, or earlier tutorial]

## Safety and scope

Describe relevant electrical and operational safety constraints. State what
this tutorial does **not** make safe, certified, or production-ready.

## What you will build

Briefly describe the result and how the main pieces fit together:

1. [First action/component]
2. [Second action/component]
3. [Expected behavior]

## Before you begin

1. [Install or open required tool.]
2. [Clone/open the repository or create the project.]
3. [Check board selection, wiring, and configuration.]

## Step 1: [First concrete task]

Explain what to do and why. Include the relevant file path and exact setting or
identifier.

```cpp
// Add a small, verified example here.
```

**Expected result:** [What the reader should see or measure.]

## Step 2: [Next task]

Give numbered, reproducible instructions. Include complete commands where
useful and name the directory from which to run them.

```sh
# Replace with a verified command.
```

**Expected result:** [Build output, serial output, LED state, or other check.]

## Verify the result

- [ ] [Build or static check passes.]
- [ ] [Hardware/output behaves as described.]
- [ ] [Important edge case is checked.]

If a result differs, see [Troubleshooting](#troubleshooting).

## How it works

Explain the relevant control flow or state transitions. Define acronyms, units,
and non-obvious design choices. Link to the reference page for the module.

## Troubleshooting

| Symptom | Likely cause | What to check |
|---|---|---|
| [Observed problem] | [Possible cause] | [Concrete diagnostic action] |
| [Observed problem] | [Possible cause] | [Concrete diagnostic action] |

## Limitations and next steps

List current limitations honestly. Separate behavior implemented in the code
from possible future improvements.

## References

- [Relevant module reference](./trafficsignal.md)
- [Source file](../../src/main.cpp)
- Relevant official hardware/tool documentation: [insert a verified URL].

---

## Example topic for this repository

A tutorial based on the current application could show how to configure one
`TrafficSignal`, call `Initialize()` in `setup()`, and call `Update()` in
`loop()`. Be explicit that the current two signals are independent, the
pedestrian button is not integrated, and the project is not suitable for
controlling real traffic.
# Writing and Maintaining Project Documentation

Good documentation helps a reader answer three questions: what is this project
for, how do I use it, and where should I look when something goes wrong? Keep
these pages focused on the code and hardware that actually exist. The reusable
lesson structure is in [tutorial.md](./tutorial.md).

## A practical workflow

1. **Identify the reader and goal.** Decide whether the page is for someone
   installing the project, using a class, troubleshooting hardware, or
   contributing code.
2. **Inspect the current source.** Verify names, defaults, pins, timing,
   commands, and limitations against the implementation before writing.
3. **Give the answer early.** Start with a short purpose statement, then provide
   prerequisites and actionable steps.
4. **Use a small, complete example.** Show enough surrounding context that a
   reader can tell where the code belongs and how to build or test it.
5. **Verify every claim.** Follow the instructions from a clean checkout when
   practical. Do not describe planned behavior as an implemented feature.
6. **Review links and dates.** Check relative paths and update docs when a
   related API, configuration, or behavior changes.

## Do

- Use descriptive headings and a predictable order: purpose, requirements,
  usage, behavior, limitations, and troubleshooting.
- Prefer short sentences, active voice, and direct instructions.
- Use exact identifiers from the code, including capitalization, such as
  `SetCurrentPhase()` and `Update()`.
- State units and defaults explicitly. For this project, timing values are in
  milliseconds unless stated otherwise.
- Label assumptions and unfinished work. Distinguish **implemented**,
  **partially implemented**, and **planned** behavior.
- Document important safety constraints and hardware requirements near the
  instructions they affect.
- Use fenced code blocks with a language tag, such as `cpp`, `ini`, or `sh`.
- Use tables for compact reference data, but explain non-obvious behavior in
  prose.
- Prefer relative links within the repository so the documentation works after
  cloning or moving the project.
- Keep examples consistent with the current source and build configuration.

## Don't

- Don't claim a prototype is production-ready, safety-certified, or suitable
  for real traffic control without the required engineering and validation.
- Don't invent API behavior, pin assignments, test results, compatibility, or
  hardware requirements.
- Don't present commented-out code, empty stubs, or TODOs as working features.
- Don't leave commands or examples ambiguous about the working directory,
  board, wiring, units, or expected result.
- Don't duplicate long explanations across pages. Link to the page that owns
  the detail and keep summaries brief.
- Don't use unexplained abbreviations, unexplained acronyms, or large blocks of
  unannotated code.
- Don't silently omit known limitations just because they make a feature look
  incomplete.

## Useful structure for a reference page

For a class or module page, consider including:

1. Purpose and source/header links.
2. Implemented behavior and state flow.
3. Public API, arguments, defaults, and units.
4. A minimal usage example.
5. Hardware assumptions and wiring notes.
6. Known limitations and troubleshooting.

Not every page needs every section. Remove sections that do not apply rather
than filling them with generic text.

## Project-specific accuracy and safety notes

- This repository targets an ESP32 Dev Module using the Arduino framework in
  PlatformIO. See [`platformio.ini`](../../platformio.ini).
- The current entry point constructs two independent `TrafficSignal` objects;
  it does not coordinate them as a safe intersection controller.
- The pedestrian button is not connected to the traffic-signal logic, the
  buzzer is not initialized or updated by the entry point, and the
  `Intersection` class has no implemented control logic.
- Do not use this prototype to control real roads, vehicles, or public
  infrastructure. It is not a certified or fail-safe traffic-control system.
- When changing pins or timing, update the source and the corresponding
  documentation together, and verify the hardware setup before powering it.